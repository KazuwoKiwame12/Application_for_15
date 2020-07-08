// Application_for_15.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "setting.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void heapCheckOne(float *data, char *str);
void heapCheckDouble(float **data, char *str);
void explain();
void startSentence(char *str);
void endSentence();
void finish();


int main()
{
	/*
	処理の流れとして、
	0: アプリの説明
	1: データを読み込む(setting.iniとiris.txtから)
	2: 学習する
	3: 学習してできた分類モデルを用いて、評価結果と分類結果を出力する
	4: 結果をresult.txtに書き込む(学習モデル、分類結果)
	*/
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~0: アプリの説明 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	explain();


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~1:データを読み込む ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*構造体の宣言*/
	learnModel model;
	/*パスの取得*/
	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);
	/*セクションとキーの設定*/
	char section1[CHARBUFF];
	sprintf_s(section1, "Learning");
	char key0[CHARBUFF];
	sprintf_s(key0, "file1s");
	char key1[CHARBUFF];
	sprintf_s(key1, "file2nd");
	char key2[CHARBUFF];
	sprintf_s(key2, "firstClass");
	char key3[CHARBUFF];
	sprintf_s(key3, "secondClass");
	char key4[CHARBUFF];
	sprintf_s(key4, "num");
	char key5[CHARBUFF];
	sprintf_s(key5, "featureNum");
	char key6[CHARBUFF];
	sprintf_s(key6, "teacherNum");
	char key7[CHARBUFF];
	sprintf_s(key7, "coefficient");
	/*iniファイルからの読み込みと代入*/
	char firstFile[CHARBUFF];
	char secondFile[CHARBUFF];
	readChar(section1, key0, "firstClass.txt", firstFile, settingFile);
	readChar(section1, key1, "secondClass.txt", secondFile, settingFile);
	model.learnNum = readInt(section1, key4, 30, settingFile);
	model.featureNum = readInt(section1, key5, 5, settingFile);
	model.teacherNum = readInt(section1, key6, 50, settingFile);
	model.coefficient = (float)readDouble(section1, key7, 0.1, settingFile);	
	model.bias = (float*)malloc(sizeof(float *)*(model.featureNum + 1));
	heapCheckOne(model.bias, "setting.iniのfeatureNumの値を小さくしてください。");
	/*setting.iniに記載された要素数と教師数分の
	配列を動的に取得する*/
	float **firstVectors, *firstVector;
	float **secondVectors, *secondVector;
	firstVectors = (float**)malloc(sizeof(float *)*model.teacherNum);
	secondVectors = (float**)malloc(sizeof(float *)*model.teacherNum);
	firstVector = (float*)malloc(sizeof(float *)*model.teacherNum*model.featureNum);
	secondVector = (float*)malloc(sizeof(float *)*model.teacherNum*model.featureNum);
	heapCheckOne(firstVector, "setting.iniのfeatureNumの値を小さくしてください。");
	heapCheckOne(secondVector, "setting.iniのfeatureNumの値を小さくしてください。");
	heapCheckDouble(firstVectors, "setting.iniのteacherNumの値を小さくしてください。");
	heapCheckDouble(secondVectors, "setting.iniのteacherNumの値を小さくしてください。");
	
	int i;
	for (i = 0; i<model.teacherNum; i++) {
		firstVectors[i] = firstVector + i * model.featureNum;
		secondVectors[i] = secondVector + i * model.featureNum;
	}
	/*firstClass, secondClassからのデータ読み込み*/
	getClassDatas(firstFile, secondFile, firstVectors, secondVectors, model);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~2: 学習する ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*初期重み変数決定*/
	startSentence("学習する_パーセプトロン則");
	for (i = 0; i < model.featureNum + 1; i++) model.bias[i] = ((float)rand() / RAND_MAX) - (float)0.5;
	/*最適な重み変数を学習*/
	updateBias(firstVectors, secondVectors, model);
	startSentence("学習完了");
	fprintf_s(stdout, "\n学習終了後の重み変数:");
	for (i = 0; i < model.featureNum + 1; i++) fprintf_s(stdout, "w%d: %f\t", i, model.bias[i]);
	fprintf_s(stdout, "\n");
	endSentence();


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~3:学習してできた分類モデルを用いて、評価結果と分類結果を出力する ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*モデルの評価*/
	startSentence("分類モデルの評価");
	float correctRate;
	correctRate = evaluateModel(firstVectors, secondVectors, model);
	endSentence();
	/*分類したいデータを分類した結果*/
	startSentence("分類結果");
	float *test_vector;
	char result[CHARBUFF];
	test_vector = (float*)malloc(sizeof(float *)*model.featureNum);
	getTestData(test_vector, model);
	if (calculation(test_vector, model) >= 0.0) readChar(section1, key2, "none", result, settingFile);
	else readChar(section1, key3, "none", result, settingFile);
	fprintf_s(stdout, "\nクラス分類の結果: %s\n", result);
	endSentence();


	/***4: 結果をresult.txtに書き込む(学習モデル、分類結果)***/
	/*アプリの終了*/
	finish();
	/*ファイルに結果の記入*/
	writeResult(correctRate, test_vector, result, model);
	/*ヒープ領域のメモリの開放*/
	free(firstVector);
	free(firstVectors);
	free(secondVector);
	free(secondVectors);

	return 0;
}




/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~関数群 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void heapCheckOne(float *data, char *str) {
	if (data == NULL) {
		fprintf_s(stdout, "重み付け変数のメモリ確保に失敗しました。%s。\n", str);
		finish();
		exit(0);
	}
}

void heapCheckDouble(float **data, char *str) {
	if (data == NULL) {
		fprintf_s(stdout, "重み付け変数のメモリ確保に失敗しました。%s\n", str);
		finish();
		exit(0);
	}
}

void startSentence(char *str) {
	fprintf_s(stdout, "****************************%s***********************************\n", str);
}

void endSentence() {
	fprintf_s(stdout, "***************************************************************\n↓\n↓\n");
}

void explain() {
	fprintf_s(stdout, "********2クラス分類を行う分析ツールアプリ********\n");
	fprintf_s(stdout, "このアプリでは、以下のことを行う\n");
	fprintf_s(stdout, "2つのクラスの教師データから最適な分類モデルを作成する\n");
	fprintf_s(stdout, "そして、その分類モデルを用いて、ユーザが設定した入力データを分類する。\n");
	fprintf_s(stdout, "'A'を入力: 更なる説明, 'Bを入力: 説明をスキップして分類実行'\n");
	char input[CHARBUFF];
	bool moreExplain = true;
	while (1) {
		scanf_s("%s", &input);
		if (strcmp(input, "A") == 0) {
			moreExplain = true;
			break;
		}
		else if (strcmp(input, "B") == 0) {
			moreExplain = false;
			break;
		}
		else {
			fprintf_s(stdout, "'A'もしくは, 'B'を入力してください\n");
		}
	}
	/*詳細説明*/
	fprintf_s(stdout, "↓\n↓\n");
	if (moreExplain) {
		fprintf_s(stdout, "アプリの詳細説明\n");
		fprintf_s(stdout, "アプリの仕様は、以下の通りである。\n");
		fprintf_s(stdout, "\t2つのクラスの教師データから最適な分類モデルを作成する。\n");
		fprintf_s(stdout, "\tそして、その分類モデルを用いて、ユーザが設定した入力データを分類する。\n");
		startSentence("ファイルについて");
		fprintf_s(stdout, "利用するファイル: setting.ini, firstClass.txt, secondClass.txt, test.txt\n");
		fprintf_s(stdout, "各ファイルの中身を変更しても問題なし。しかし、setting.iniのセクションとキーは変更不可\n");
		fprintf_s(stdout, "setting.iniの役割: 学習に必要な設定を定義する\n");
		fprintf_s(stdout, "\t各クラスの名前, 学習回数, 特徴量, \n");
		fprintf_s(stdout, "\t1クラスの教師量, 学習係数などの値を記入する。\n");
		fprintf_s(stdout, "各クラス.txtの役割: 学習データを設定する\n");
		fprintf_s(stdout, "\t各クラスの特徴量を、スペースを空けて記入する。\n");
		fprintf_s(stdout, "test.txtの役割: 分類したいデータを設定する\n");
		fprintf_s(stdout, "\t分類したいデータの特徴量を記入する。(一つだけ)\n");
		startSentence("分類実行");
		fprintf_s(stdout, "'A'を入力: 分類実行\n");
		while (1) {
			scanf_s("%s", &input);
			if (strcmp(input, "A") == 0) break;
			else fprintf_s(stdout, "'A'を入力してください\n");
		}
	}
	fprintf_s(stdout, "↓\n↓\n↓\n");
}

void finish() {
	startSentence("アプリ終了");
	fprintf_s(stdout, "アプリを終了するには、何かしらのキーを入力してください。\n");
	char input[CHARBUFF];
	scanf_s("%s", &input);
}
