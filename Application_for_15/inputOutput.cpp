#include "stdafx.h"
#include "setting.h"
#include <Windows.h>
#include <stdio.h>
#include <string>


int readInt(const char *section, const char *keyword, int defaultValue, const char *filePath) {
	return GetPrivateProfileInt(section, keyword, defaultValue, filePath);
}

bool readChar(const char *section, const char *keyword, const char *defaultValue, char *returnValue, const char *filePath) {
	if (GetPrivateProfileString(section, keyword, defaultValue, returnValue, CHARBUFF, filePath) != 0) {
		return true;
	}
	else {
		fprintf(stdout, "%s doesn't contain [%s] %s\n", filePath, section, keyword);
		return false;
	}
}

double readDouble(const char *section, const char *keyword, double defaultValue, const char *filePath) {
	char buf[CHARBUFF];
	GetPrivateProfileString(section, keyword, "none", buf, CHARBUFF, filePath);
	defaultValue = strtod(buf, NULL);
	return defaultValue;
}

void getCurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

/*�t�@�C������f�[�^���擾*/
void fetchFile(char importFile[CHARBUFF], float** vectors, learnModel model) {
	char lineData[BUFFSIZE];
	int index = 0;
	FILE *fp;
	errno_t error;
	error = fopen_s(&fp, importFile, "r");
	if (error != 0) {
		fprintf_s(stderr, "failed to open for %s in importFile", importFile);
	} else {
		while (fgets(lineData, BUFFSIZE, fp) != NULL) {
			strPicker(lineData, vectors[index]);
			index++;
		}
		fclose(fp);
	}
}

/*2�N���X���̃f�[�^��2�����z��Ɋi�[*/
void getClassDatas(char firstFile[CHARBUFF], char secondFile[CHARBUFF], float** firstVectors, float** secondVectors, learnModel model) {
	fetchFile(firstFile, firstVectors, model);
	fetchFile(secondFile, secondVectors, model);
}

/*���ނ������e�X�g�f�[�^��z��Ɋi�[*/
void getTestData(float* vector, learnModel model) {
	char lineData[BUFFSIZE];
	int j = 0;
	FILE *fp;
	errno_t error;
	error = fopen_s(&fp, "test.txt", "r");
	if (error != 0) {
		fprintf_s(stderr, "failed to open for txt in test.txt");
	}
	else {
		while (fgets(lineData, BUFFSIZE, fp) != NULL) {
			strPicker(lineData, vector);
		}
		fclose(fp);
	}
}

/*�t�@�C���Ƀf�[�^����������*/
void writeResult(float correctRate, float *test_vector, char *result, learnModel model) {
	FILE *fp;
	errno_t error;
	int i;

	error = fopen_s(&fp, "result.txt", "w");
	if (error == 0)
	{
		fprintf_s(fp, "�w�K�W��: %f\n", model.coefficient);
		fprintf_s(fp, "�w�K��: %d\n", model.learnNum);
		fprintf_s(fp, "�d�ݕt���ϐ�:\n");
		for (i = 0; i < model.featureNum+1; i++) {
			fprintf_s(fp, "\tw%d = %f\n", i, model.bias[i]);
		}
		fprintf_s(fp, "����: %f\n", correctRate);
		fprintf_s(fp, "****���ތ���*****\n���͂��ꂽtest�f�[�^�́A %s�Ɣ��f����܂���!!!", result);
		fclose(fp);
	}
}

/*�s�̃e�L�X�g�f�[�^���A������ɕ������A
float�^�ɕϊ����Ĕz��Ɋi�[����B
*/
void strPicker(char *lineData, float *vector) {
	char *character_line;
	char delim[] = " ";
	char *ctx;
	int i;
	i = 0;

	character_line = strtok_s(lineData, delim, &ctx);
	while (character_line != NULL) {
		try {
			*(vector + i) = strtof(character_line, NULL);
			character_line = strtok_s(NULL, delim, &ctx);
			i++;
		}
		catch (...) {//��O�擾�ł��Ă��Ȃ�
			fprintf_s(stdout, "�q�[�v�̈悪���܂����B�w�K���鋳�t�f�[�^�̐������炵�Ă��������B\n");
			fprintf_s(stdout, "�A�v�����I������ɂ́A��������̃L�[����͂��Ă��������B\n");
			char input[CHARBUFF];
			scanf_s("%s", &input);
			exit(0);
		}
	}
}