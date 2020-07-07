#pragma once
#define CHARBUFF 124
#define BUFFSIZE 1024
#define FIRSTCLASS 1.0
#define SECONDCLASS 2.0

struct learnModel {
	int learnNum;
	int featureNum;
	int teacherNum;
	double coefficient;
	float *params;
};

#include "inputOutput.h"
#include "machineLearning.h"