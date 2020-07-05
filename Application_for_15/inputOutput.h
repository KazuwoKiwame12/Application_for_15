#pragma once
int readInt(const char *section, const char *keyword, int defaultValue, const char *filePath);
double readDouble(const char *section, const char *keyword, double defaultValue, const char *filePath);
void getCurrentDirectory(char *currentDirectory);
bool writeInt(const char *section, const char *keyword, int returnValue, const char *filePath);
bool writeChar(const char *section, const char *keyword, const char *returnValue, const char *filePath);
bool writeDouble(const char *section, const char *keyword, double returnValue, const char *filePath);
void getVectors(double* se_vectors[], double* ve_vectors[], double* vi_vectors[]);