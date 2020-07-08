#include "stdafx.h"
#include "setting.h"

/*�w�肳�ꂽ�w�K�񐔕��A�w�K���s���d�ݕt���ϐ����X�V����*/
void updateBias(float** firstVectors, float** secondVectors, learnModel model) {
	int i, j, k, l;
	float correctRate;
	for (i = 0; i < model.learnNum; i++) {
		/*��ʏo��*/
		fprintf_s(stdout, "�w�K��: %d���\n�d�ݕt���ϐ�:", i);
		for (l = 0; l < model.featureNum + 1; l++) fprintf_s(stdout, "w%d: %f\t", l, model.bias[l]);
		evaluateModel(firstVectors, secondVectors, model);

		/*first_vecotrs�ɂ��p�����[�^����*/
		for (j = 0; j < model.teacherNum; j++) {
			if (!(calculation(firstVectors[j], model) >= 0.0)) {
				for (k = 0; k < model.featureNum; k++) {
					if (k == 0) model.bias[k] += model.coefficient*1.0;
					else model.bias[k] += model.coefficient*firstVectors[j][k-1];
				}
			}
		}
		/*second_vecotrs�ɂ��p�����[�^����*/
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

/*�d�ݕt���ϐ��ƁA�Ή�����N���X�̓����ʂ̌v�Z*/
float calculation(float* vectors, learnModel model) {
	int i;
	float result = 0.0;
	for (i = 0; i < model.featureNum; i++) {
		if(i == 0) result += model.bias[i] * 1.0;
		else result += model.bias[i] * vectors[i-1];
	}
	return result;
}

/*���ރ��f���𗘗p�����A���ސ��x��Ԃ�*/
float evaluateModel(float** firstVectors, float** secondVectors, learnModel model) {
	int i, correctNum;
	float result, correctRate;
	correctNum = 0;
	/*first_vecotrs�ɂ����鐳��*/
	for (i = 0; i < model.teacherNum; i++) {
		result = calculation(firstVectors[i], model);
		if(result>= 0.0) correctNum++;
	}
	/*second_vecotrs�ɂ����鐳��*/
	for (i = 0; i < model.teacherNum; i++) {
		result = calculation(secondVectors[i], model);
		if (result < 0.0) correctNum++;
	}

	correctRate = (float)((float)correctNum / (float)(2 * model.teacherNum));
	fprintf_s(stdout, "\n����: %f\n\n", correctRate);
	return correctRate;
}