// Application_for_15.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "setting.h"
#include <stdlib.h>

int main()
{
	//TODO
	/*
	�����̗���Ƃ��āA
	1: �f�[�^��ǂݍ���(setting.ini��iris.txt����)
	2: �w�K(�p�[�Z�v�g������)����
	3: �w�K���Đ��܂ꂽ���f����p���āA���ʂ��o�͂���
	4: ���ʂ�result.txt�ɏ�������(�w�K���f���A���ތ���)
	*/

	/****1:�f�[�^��ǂݍ���****/
	learnModel model;
	/*�p�X�̎擾*///���s����Ƃ��́Aconst���ۂ���c��
	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);
	/*�Z�N�V�����ƃL�[�̐ݒ�*/
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
	/*�ǂݍ���*/
	char firstFile[CHARBUFF];
	char secondFile[CHARBUFF];
	readChar(section1, key0, "none", firstFile, settingFile);
	readChar(section1, key1, "none", secondFile, settingFile);
	model.learnNum = readInt(section1, key4, 30, settingFile);
	model.featureNum = readInt(section1, key5, 5, settingFile);
	model.teacherNum = readInt(section1, key6, 50, settingFile);
	model.coefficient = (float)readDouble(section1, key7, 0.1, settingFile);
	model.params = (float*)malloc(sizeof(float *)*(model.featureNum+1));

	int i, j;
	float **firstVectors, *firstVector;
	float **secondVectors, *secondVector;
	firstVectors = (float**)malloc(sizeof(float *)*model.teacherNum);
	secondVectors = (float**)malloc(sizeof(float *)*model.teacherNum);
	firstVector = (float*)malloc(sizeof(float *)*model.teacherNum*model.featureNum);
	secondVector = (float*)malloc(sizeof(float *)*model.teacherNum*model.featureNum);
	for (i = 0; i<model.teacherNum; i++) {
		firstVectors[i] = firstVector + i * model.featureNum;
		secondVectors[i] = secondVector + i * model.featureNum;
	}
	getClassDatas(firstFile, secondFile, firstVectors, secondVectors, model);
	fprintf_s(stdout, "*****************firstVectors***********************\n");
	for (i = 0; i<model.teacherNum; i++) {
		for (j = 0; j<model.featureNum; j++) {
			fprintf_s(stdout,"%f\t", firstVectors[i][j]);
		}
		fprintf_s(stdout, "\n");
	}
	
	fprintf_s(stdout, "*****************secondVectors***********************\n");
	for (i = 0; i<model.teacherNum; i++) {
		for (j = 0; j<model.featureNum; j++) {
			fprintf_s(stdout, "%f\t", secondVectors[i][j]);
		}
		fprintf_s(stdout, "\n");
	}


	/****2: �w�K����****/
	fprintf_s(stdout, "\n�p�����[�^_�v�Z�O");
	for (i = 0; i < model.featureNum+1; i++) {
		model.params[i] = ((float)rand() / RAND_MAX) - (float)0.5;
		fprintf_s(stdout, "%f\t", model.params[i]);
	}

	learnPerceptron(firstVectors, secondVectors, model);
	fprintf_s(stdout, "\n�p�����[�^_�v�Z��:");
	for (i = 0; i < model.featureNum+1; i++) fprintf_s(stdout, "%f\t", model.params[i]);
	

	/***3: �w�K���Đ��܂ꂽ���f����p���āA���ʂ��o�͂���***/
	/*���f���̕]��*/
	float correctRate;
	correctRate = evaluateModel(firstVectors, secondVectors, model);
	fprintf_s(stdout, "\n����: %f", correctRate);
	/*���ނ������f�[�^�𕪗ނ�������*/
	float *test_vector;
	char result[CHARBUFF];
	test_vector = (float*)malloc(sizeof(float *)*model.featureNum);
	getTestData(test_vector, model);
	if(calculation(test_vector, model) >= 0.0) readChar(section1, key2, "none", result, settingFile);
	else readChar(section1, key3, "none", result, settingFile);
	fprintf_s(stdout, "\n�N���X���ނ̌���: %s", result);

	/***4: ���ʂ�result.txt�ɏ�������(�w�K���f���A���ތ���)***/
	writeResult(correctRate,test_vector,result, model);


	free(firstVector);
	free(firstVectors);
	free(secondVector);
	free(secondVectors);
	
	return 0;
}

