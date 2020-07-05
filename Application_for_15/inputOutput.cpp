#include "stdafx.h"
#include "setting.h"
#include <Windows.h>
#include <stdio.h>
#include <string>


int readInt(const char *section, const char *keyword, int defaultValue, const char *filePath) {
	return GetPrivateProfileInt(section, keyword, defaultValue, filePath);
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
		fprintf(stderr, "failed to write [$s] %s to %s \n", section, keyword, filePath);
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
		fprintf(stderr, "failed to write [$s] %s to %s \n", section, keyword, filePath);
		return false;
	}
};

void getVectors(double* se_vectors[], double* ve_vectors[], double* vi_vectors[]) {
	//TODO
};