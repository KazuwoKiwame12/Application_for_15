#pragma once
void updateBias(float** firstVectors, float** secondVectors, learnModel model);
float calculation(float* vectors, learnModel model);
float evaluateModel(float** firstVectors, float** secondVectors, learnModel model);