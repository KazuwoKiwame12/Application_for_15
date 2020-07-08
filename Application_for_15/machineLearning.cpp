#include "stdafx.h"
#include "setting.h"

/*指定された学習回数分、学習を行い重み付け変数を更新する*/
void updateBias(float** firstVectors, float** secondVectors, learnModel model) {
	int i, j, k, l;
	float correctRate;
	for (i = 0; i < model.learnNum; i++) {
		/*画面出力*/
		fprintf_s(stdout, "学習回数: %d回目\n重み付け変数:", i);
		for (l = 0; l < model.featureNum + 1; l++) fprintf_s(stdout, "w%d: %f\t", l, model.bias[l]);
		evaluateModel(firstVectors, secondVectors, model);

		/*first_vecotrsによるパラメータ調整*/
		for (j = 0; j < model.teacherNum; j++) {
			if (!(calculation(firstVectors[j], model) >= 0.0)) {
				for (k = 0; k < model.featureNum; k++) {
					if (k == 0) model.bias[k] += model.coefficient*1.0;
					else model.bias[k] += model.coefficient*firstVectors[j][k-1];
				}
			}
		}
		/*second_vecotrsによるパラメータ調整*/
		for (j = 0; j < model.teacherNum; j++) {
			if (!(calculation(secondVectors[j], model) < 0.0)) {
				for (k = 0; k < model.featureNum; k++) {
					if (k == 0) model.bias[k] -= model.coefficient*1.0;
					else model.bias[k] -= model.coefficient*secondVectors[j][k-1];
				}
			}
		}
	}
}

/*重み付け変数と、対応するクラスの特徴量の計算*/
float calculation(float* vectors, learnModel model) {
	int i;
	float result = 0.0;
	for (i = 0; i < model.featureNum; i++) {
		if(i == 0) result += model.bias[i] * 1.0;
		else result += model.bias[i] * vectors[i-1];
	}
	return result;
}

/*分類モデルを利用した、分類精度を返す*/
float evaluateModel(float** firstVectors, float** secondVectors, learnModel model) {
	int i, correctNum;
	float result, correctRate;
	correctNum = 0;
	/*first_vecotrsにおける正解数*/
	for (i = 0; i < model.teacherNum; i++) {
		result = calculation(firstVectors[i], model);
		if(result>= 0.0) correctNum++;
	}
	/*second_vecotrsにおける正解数*/
	for (i = 0; i < model.teacherNum; i++) {
		result = calculation(secondVectors[i], model);
		if (result < 0.0) correctNum++;
	}

	correctRate = (float)((float)correctNum / (float)(2 * model.teacherNum));
	fprintf_s(stdout, "\n正解率: %f\n\n", correctRate);
	return correctRate;
}