#pragma once
void learnPerceptron(float** first_vectors, float** second_vectors, learnModel model);
float calculation(float* params, float* vectors, int featureNum);
float evaluateModel(float*params, float** first_vectors, float** second_vectors, learnModel model);
float classification(float* params, float* testData);