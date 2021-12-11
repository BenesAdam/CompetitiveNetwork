#include "TrainingSet.hpp"
#include <bitset>

cGeneratorBinaryTrainingSet::cGeneratorBinaryTrainingSet(unsigned int nInputs, unsigned int nOutputs, BinaryTrainingSetFunction fFunction)
	: nInputs(nInputs), nOutputs(nOutputs), fFunction(fFunction)
{
	GenerateInputs();
	GenerateOutputs();
}

vector<vector<float>> cGeneratorBinaryTrainingSet::GetInputs()
{
	return vInputs;
}

unsigned int cGeneratorBinaryTrainingSet::GetInputsSize()
{
	return vInputs.size();
}

void cGeneratorBinaryTrainingSet::PrintInputs()
{
	cout << setprecision(0);
	cout << fixed;
	for (vector<float> vInput : vInputs)
	{
		for (float fValue : vInput)
			cout << fValue << " ";
		cout << endl;
	}
}

vector<vector<float>> cGeneratorBinaryTrainingSet::GetOutputs()
{
	return vOutputs;
}

unsigned int cGeneratorBinaryTrainingSet::GetOutputsSize()
{
	return vOutputs.size();
}

void cGeneratorBinaryTrainingSet::PrintOutputs()
{
	cout << setprecision(0);
	cout << fixed;
	for (vector<float> vOutput : vOutputs)
	{
		for (float fValue : vOutput)
			cout << fValue << " ";
		cout << "(" << OutputMapping(vOutput) << ")" << endl;
	}
}

void cGeneratorBinaryTrainingSet::PrintInputsAndOutputs()
{
	cout << setprecision(0);
	cout << fixed;
	
	if (GetInputsSize() != GetOutputsSize())
		cout << "Input size and output size are diferent." << endl;

	for (unsigned int nIndex = 0; nIndex < GetInputsSize(); nIndex++)
	{
		vector<float> vInput = vInputs[nIndex];
		vector<float> vOutput = vOutputs[nIndex];

		for (unsigned int i = 0; i < vInput.size(); i++)
			cout << vInput[i] << " ";
		cout << "-> ";
		for (unsigned int i = 0; i < vOutput.size(); i++)
			cout << vOutput[i] << " ";
		cout << "(" << OutputMapping(vOutput) << ")" << endl;
	}
}

cGeneratorBinaryTrainingSet cGeneratorBinaryTrainingSet::GenerateAND()
{
	cGeneratorBinaryTrainingSet result = cGeneratorBinaryTrainingSet(2, 1, [](vector<float> vInput)
		{
			vector<float> vOutput = vector<float>();
			vOutput.push_back((int)vInput[0] && (int)vInput[1]);
			return vOutput;
		});
	return result;
}

cGeneratorBinaryTrainingSet cGeneratorBinaryTrainingSet::GenerateOR()
{
	cGeneratorBinaryTrainingSet result = cGeneratorBinaryTrainingSet(2, 1, [](vector<float> vInput)
		{
			vector<float> vOutput = vector<float>();
			vOutput.push_back((int)vInput[0] || (int)vInput[1]);
			return vOutput;
		});
	return result;
}

void cGeneratorBinaryTrainingSet::GenerateInputs(unsigned int nInputIndex, vector<float>& vGeneratedInput)
{
	if (nInputIndex >= nInputs)
	{
		vector<float> vNewInputVector = vector<float>(vGeneratedInput);
		vInputs.push_back(vNewInputVector);
	}
	else
	{
		nInputIndex++;
		vGeneratedInput.push_back(0);
		GenerateInputs(nInputIndex, vGeneratedInput);
		vGeneratedInput.pop_back();
		vGeneratedInput.push_back(1);
		GenerateInputs(nInputIndex, vGeneratedInput);
		vGeneratedInput.pop_back();
	}
}

void cGeneratorBinaryTrainingSet::GenerateInputs()
{
	vector<float> vGeneratedInput = vector<float>();
	GenerateInputs(0, vGeneratedInput);
}

void cGeneratorBinaryTrainingSet::GenerateOutputs()
{
	for (vector<float> vInput : vInputs)
	{
		vector<float> vOutput = fFunction(vInput);
		vOutputs.push_back(vOutput);
	}
}

unsigned int cGeneratorBinaryTrainingSet::OutputMapping(vector<float> vOutput)
{
	unsigned int result = 0;
	for (float fValue : vOutput)
	{
		result <<= 1;
		unsigned int nValue = (unsigned int)roundf(fValue);
		if (nValue == 1)
			result |= 1;
	}
	return result;
}
