#pragma once
int readInt(const char *section, const char *keyword, int defaultValue, const char *filePath);
bool readChar(const char *section, const char *keyword, const char *defaultValue, char *returnValue, const char *filePath);
double readDouble(const char *section, const char *keyword, double defaultValue, const char *filePath);
void getCurrentDirectory(char *currentDirectory);
bool writeInt(const char *section, const char *keyword, int returnValue, const char *filePath);
bool writeChar(const char *section, const char *keyword, const char *returnValue, const char *filePath);
bool writeDouble(const char *section, const char *keyword, double returnValue, const char *filePath);
void getVectors(char importFile[BUFFSIZE], float** first_vectors, float** second_vectors, learnModel model);
void strPicker(char *lineData, float *temp);