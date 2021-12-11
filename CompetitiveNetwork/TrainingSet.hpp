#pragma once
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

typedef vector<float>(*BinaryTrainingSetFunction)(vector<float>);

class cGeneratorBinaryTrainingSet
{
	BinaryTrainingSetFunction fFunction;
	unsigned int nInputs, nOutputs;
	vector<vector<float>> vInputs;
	vector<vector<float>> vOutputs;

	void GenerateInputs(unsigned int nInputIndex, vector<float>& vGeneratedInput);
	void GenerateInputs();
	void GenerateOutputs();
public:
	cGeneratorBinaryTrainingSet(unsigned int nInputs, unsigned int nOutputs, BinaryTrainingSetFunction fFunction);

	vector<vector<float>> GetInputs();
	unsigned int GetInputsSize();
	void PrintInputs();

	vector<vector<float>> GetOutputs();
	unsigned int GetOutputsSize();
	void PrintOutputs();

	void PrintInputsAndOutputs();

	static unsigned int OutputMapping(vector<float> vOutput);
	static cGeneratorBinaryTrainingSet GenerateAND();
	static cGeneratorBinaryTrainingSet GenerateOR();

};

