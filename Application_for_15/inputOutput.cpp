#include "stdafx.h"
#include "setting.h"
#include <Windows.h>
#include <stdio.h>
#include <string>


int readInt(const char *section, const char *keyword, int defaultValue, const char *filePath) {
	return GetPrivateProfileInt(section, keyword, defaultValue, filePath);
};

bool readChar(const char *section, const char *keyword, const char *defaultValue, char *returnValue, const char *filePath) {
	if (GetPrivateProfileString(section, keyword, defaultValue, returnValue, CHARBUFF, filePath) != 0) {
		return true;
	}
	else {
		fprintf(stdout, "%s doesn't contain [%s] %s\n", filePath, section, keyword);
		return false;
	}
};

double readDouble(const char *section, const char *keyword, double defaultValue, const char *filePath) {
	char buf[CHARBUFF];
	GetPrivateProfileString(section, keyword, "none", buf, CHARBUFF, filePath);
	defaultValue = strtod(buf, NULL);
	return defaultValue;
};

void getCurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
};

bool writeChar(const char *section, const char *keyword, const char *returnValue, const char *filePath) {
	return WritePrivateProfileString(section, keyword, returnValue, filePath);
};

bool writeInt(const char *section, const char *keyword, int returnValue, const char *filePath) {
	char buf[CHARBUFF];
	sprintf_s(buf, "%d", returnValue);
	if (WritePrivateProfileString(section, keyword, buf, filePath)) {
		return true;
	}
	else {
		//fprintf(stderr, "failed to write [$s] %s to %s \n", section, keyword, filePath);
		return false;
	}
};

bool writeDouble(const char *section, const char *keyword, double returnValue, const char *filePath) {
	char buf[CHARBUFF];
	sprintf_s(buf, "%f", returnValue);
	if (WritePrivateProfileString(section, keyword, buf, filePath)) {
		return true;
	}
	else {
		//fprintf(stderr, "failed to write [$s] %s to %s \n", section, keyword, filePath);
		return false;
	}
};

void getVectors(char importFile[BUFFSIZE], float** first_vectors, float** second_vectors, learnModel model) {
	char lineData[BUFFSIZE];
	int index_1 = 0, index_2 = 0, j = 0;
	FILE *fp;
	errno_t error;
	error = fopen_s(&fp, importFile, "r");
	if (error != 0)
		fprintf_s(stderr, "failed to open for txt in importFile_%s", importFile);
	else {
		while (fgets(lineData, BUFFSIZE, fp) != NULL) {
			fprintf_s(stdout, "++++++++++++++テキスト: %s++++++++++++++++++\n", lineData);
			j = 0;
			if (index_1 < model.teacherNum) {
				fprintf_s(stdout, "**************%d行目のデータ***************\n", index_1);
				strPicker(lineData, first_vectors[index_1]);
				for (j = 0; j < 5; j++) {
					fprintf_s(stdout, "%f\t", first_vectors[index_1][j]);
				}
				fprintf_s(stdout, "\n");
				index_1++;
			}
			else if (index_2 < model.teacherNum) {
				fprintf_s(stdout, "**************%d行目のデータ***************\n", index_2);
				strPicker(lineData, second_vectors[index_2]);
				for (j = 0; j < 5; j++) {
					fprintf_s(stdout, "%f\t", second_vectors[index_2][j]);
					fprintf_s(stdout, "\n");
				}
				index_2++;
			}
		}
		fclose(fp);
	}
}

void strPicker(char *lineData, float *temp) {
	char *character_line;
	char delim[] = " ";
	char *ctx;
	int count, i;
	count = 0; i = 0;

	character_line = strtok_s(lineData, delim, &ctx);
	while (character_line != NULL) {
		fprintf_s(stdout, "＊＊＊＊＊取得データ%d番＊＊＊＊＊\n", count);
		fprintf_s(stdout, "%s\n", character_line);
		*(temp + i) = strtof(character_line,NULL);
		fprintf_s(stdout, "数字:%lf\n", *(temp + i));
		character_line = strtok_s(NULL, delim, &ctx);
		i++;
		count++;
	}
}