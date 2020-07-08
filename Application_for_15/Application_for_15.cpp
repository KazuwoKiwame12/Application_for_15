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
	�����̗���Ƃ��āA
	0: �A�v���̐���
	1: �f�[�^��ǂݍ���(setting.ini��iris.txt����)
	2: �w�K����
	3: �w�K���Ăł������ރ��f����p���āA�]�����ʂƕ��ތ��ʂ��o�͂���
	4: ���ʂ�result.txt�ɏ�������(�w�K���f���A���ތ���)
	*/
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~0: �A�v���̐��� ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	explain();


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~1:�f�[�^��ǂݍ��� ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*�\���̂̐錾*/
	learnModel model;
	/*�p�X�̎擾*/
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
	/*ini�t�@�C������̓ǂݍ��݂Ƒ��*/
	char firstFile[CHARBUFF];
	char secondFile[CHARBUFF];
	readChar(section1, key0, "firstClass.txt", firstFile, settingFile);
	readChar(section1, key1, "secondClass.txt", secondFile, settingFile);
	model.learnNum = readInt(section1, key4, 30, settingFile);
	model.featureNum = readInt(section1, key5, 5, settingFile);
	model.teacherNum = readInt(section1, key6, 50, settingFile);
	model.coefficient = (float)readDouble(section1, key7, 0.1, settingFile);	
	model.bias = (float*)malloc(sizeof(float *)*(model.featureNum + 1));
	heapCheckOne(model.bias, "setting.ini��featureNum�̒l�����������Ă��������B");
	/*setting.ini�ɋL�ڂ��ꂽ�v�f���Ƌ��t������
	�z��𓮓I�Ɏ擾����*/
	float **firstVectors, *firstVector;
	float **secondVectors, *secondVector;
	firstVectors = (float**)malloc(sizeof(float *)*model.teacherNum);
	secondVectors = (float**)malloc(sizeof(float *)*model.teacherNum);
	firstVector = (float*)malloc(sizeof(float *)*model.teacherNum*model.featureNum);
	secondVector = (float*)malloc(sizeof(float *)*model.teacherNum*model.featureNum);
	heapCheckOne(firstVector, "setting.ini��featureNum�̒l�����������Ă��������B");
	heapCheckOne(secondVector, "setting.ini��featureNum�̒l�����������Ă��������B");
	heapCheckDouble(firstVectors, "setting.ini��teacherNum�̒l�����������Ă��������B");
	heapCheckDouble(secondVectors, "setting.ini��teacherNum�̒l�����������Ă��������B");
	
	int i;
	for (i = 0; i<model.teacherNum; i++) {
		firstVectors[i] = firstVector + i * model.featureNum;
		secondVectors[i] = secondVector + i * model.featureNum;
	}
	/*firstClass, secondClass����̃f�[�^�ǂݍ���*/
	getClassDatas(firstFile, secondFile, firstVectors, secondVectors, model);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~2: �w�K���� ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*�����d�ݕϐ�����*/
	startSentence("�w�K����_�p�[�Z�v�g������");
	for (i = 0; i < model.featureNum + 1; i++) model.bias[i] = ((float)rand() / RAND_MAX) - (float)0.5;
	/*�œK�ȏd�ݕϐ����w�K*/
	updateBias(firstVectors, secondVectors, model);
	startSentence("�w�K����");
	fprintf_s(stdout, "\n�w�K�I����̏d�ݕϐ�:");
	for (i = 0; i < model.featureNum + 1; i++) fprintf_s(stdout, "w%d: %f\t", i, model.bias[i]);
	fprintf_s(stdout, "\n");
	endSentence();


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~3:�w�K���Ăł������ރ��f����p���āA�]�����ʂƕ��ތ��ʂ��o�͂��� ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*���f���̕]��*/
	startSentence("���ރ��f���̕]��");
	float correctRate;
	correctRate = evaluateModel(firstVectors, secondVectors, model);
	endSentence();
	/*���ނ������f�[�^�𕪗ނ�������*/
	startSentence("���ތ���");
	float *test_vector;
	char result[CHARBUFF];
	test_vector = (float*)malloc(sizeof(float *)*model.featureNum);
	getTestData(test_vector, model);
	if (calculation(test_vector, model) >= 0.0) readChar(section1, key2, "none", result, settingFile);
	else readChar(section1, key3, "none", result, settingFile);
	fprintf_s(stdout, "\n�N���X���ނ̌���: %s\n", result);
	endSentence();


	/***4: ���ʂ�result.txt�ɏ�������(�w�K���f���A���ތ���)***/
	/*�A�v���̏I��*/
	finish();
	/*�t�@�C���Ɍ��ʂ̋L��*/
	writeResult(correctRate, test_vector, result, model);
	/*�q�[�v�̈�̃������̊J��*/
	free(firstVector);
	free(firstVectors);
	free(secondVector);
	free(secondVectors);

	return 0;
}




/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~�֐��Q ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void heapCheckOne(float *data, char *str) {
	if (data == NULL) {
		fprintf_s(stdout, "�d�ݕt���ϐ��̃������m�ۂɎ��s���܂����B%s�B\n", str);
		finish();
		exit(0);
	}
}

void heapCheckDouble(float **data, char *str) {
	if (data == NULL) {
		fprintf_s(stdout, "�d�ݕt���ϐ��̃������m�ۂɎ��s���܂����B%s\n", str);
		finish();
		exit(0);
	}
}

void startSentence(char *str) {
	fprintf_s(stdout, "****************************%s***********************************\n", str);
}

void endSentence() {
	fprintf_s(stdout, "***************************************************************\n��\n��\n");
}

void explain() {
	fprintf_s(stdout, "********2�N���X���ނ��s�����̓c�[���A�v��********\n");
	fprintf_s(stdout, "���̃A�v���ł́A�ȉ��̂��Ƃ��s��\n");
	fprintf_s(stdout, "2�̃N���X�̋��t�f�[�^����œK�ȕ��ރ��f�����쐬����\n");
	fprintf_s(stdout, "�����āA���̕��ރ��f����p���āA���[�U���ݒ肵�����̓f�[�^�𕪗ނ���B\n");
	fprintf_s(stdout, "'A'�����: �X�Ȃ����, 'B�����: �������X�L�b�v���ĕ��ގ��s'\n");
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
			fprintf_s(stdout, "'A'��������, 'B'����͂��Ă�������\n");
		}
	}
	/*�ڍא���*/
	fprintf_s(stdout, "��\n��\n");
	if (moreExplain) {
		fprintf_s(stdout, "�A�v���̏ڍא���\n");
		fprintf_s(stdout, "�A�v���̎d�l�́A�ȉ��̒ʂ�ł���B\n");
		fprintf_s(stdout, "\t2�̃N���X�̋��t�f�[�^����œK�ȕ��ރ��f�����쐬����B\n");
		fprintf_s(stdout, "\t�����āA���̕��ރ��f����p���āA���[�U���ݒ肵�����̓f�[�^�𕪗ނ���B\n");
		startSentence("�t�@�C���ɂ���");
		fprintf_s(stdout, "���p����t�@�C��: setting.ini, firstClass.txt, secondClass.txt, test.txt\n");
		fprintf_s(stdout, "�e�t�@�C���̒��g��ύX���Ă����Ȃ��B�������Asetting.ini�̃Z�N�V�����ƃL�[�͕ύX�s��\n");
		fprintf_s(stdout, "setting.ini�̖���: �w�K�ɕK�v�Ȑݒ���`����\n");
		fprintf_s(stdout, "\t�e�N���X�̖��O, �w�K��(�ő�100��), ������, \n");
		fprintf_s(stdout, "\t1�N���X�̋��t��, �w�K�W���Ȃǂ̒l���L������B\n");
		fprintf_s(stdout, "�e�N���X.txt�̖���: �w�K�f�[�^��ݒ肷��\n");
		fprintf_s(stdout, "\t�e�N���X�̓����ʂ��A�X�y�[�X���󂯂ċL������B\n");
		fprintf_s(stdout, "test.txt�̖���: ���ނ������f�[�^��ݒ肷��\n");
		fprintf_s(stdout, "\t���ނ������f�[�^�̓����ʂ��L������B(�����)\n");
		startSentence("���ގ��s");
		fprintf_s(stdout, "'A'�����: ���ގ��s\n");
		while (1) {
			scanf_s("%s", &input);
			if (strcmp(input, "A") == 0) break;
			else fprintf_s(stdout, "'A'����͂��Ă�������\n");
		}
	}
	fprintf_s(stdout, "��\n��\n��\n");
}

void finish() {
	startSentence("�A�v���I��");
	fprintf_s(stdout, "�A�v�����I������ɂ́A��������̃L�[����͂��Ă��������B\n");
	char input[CHARBUFF];
	scanf_s("%s", &input);
}