#include <iostream>
#include <bitset>
#include "Network.hpp"
#include "TrainingSet.hpp"

using namespace std;

void SplitVector(float factor, vector<vector<float>> vIn, vector<vector<float>>& vOut1, vector<vector<float>>& vOut2)
{
	unsigned int nPivot = (unsigned int)(factor * vIn.size());
	auto itOut1_first	= vIn.begin();
	auto itOut1_last	= vIn.begin() + nPivot;
	auto itOut2_first	= vIn.begin() + nPivot;
	auto itOut2_last	= vIn.end();
	vOut1 = vector<vector<float>>(itOut1_first, itOut1_last);
	vOut2 = vector<vector<float>>(itOut2_first, itOut2_last);
}

void PrintVector(vector<float> vInput)
{
	for (float fValue : vInput)
	{
		cout << fValue << " ";
	}
}

int main()
{
	// link: https://drive.google.com/open?id=1JEM_gcdX95I2N-95Hoxea2qWArsvjMz7&authuser=adam.beny.benes%40gmail.com&usp=drive_fs
	
	const unsigned int nInputs = 2;
	const unsigned int nOutputs = 1;
	cGeneratorBinaryTrainingSet trainingSet = cGeneratorBinaryTrainingSet::GenerateOR();

	//// AND and OR
	//const unsigned int nInputs = 4;
	//const unsigned int nOutputs = 2;
	//cGeneratorBinaryTrainingSet trainingSet = cGeneratorBinaryTrainingSet(nInputs, nOutputs, [](vector<float> vInput)
	//	{
	//		vector<float> vOutput = vector<float>();
	//		float fAND = (int)vInput[0] && (int)vInput[1];
	//		float fOR = (int)vInput[2] || (int)vInput[3];
	//		vOutput.push_back(fAND);
	//		vOutput.push_back(fOR);
	//		return vOutput;
	//	});

	cout << "Inputs and outputs(" << trainingSet.GetInputsSize() <<"): " << endl;
	trainingSet.PrintInputsAndOutputs();
	cout << endl;

	NETWORK_INITIALIZE_RANDOMIZER
	cNetwork network = cNetwork(nInputs, nOutputs);
	network.RandomWeights();

	network.Print();
	cout << endl;

	vector<vector<float>> vInputsTrain;
	vector<vector<float>> vInputsTest;
	SplitVector(0.8, trainingSet.GetInputs(), vInputsTrain, vInputsTest);



	float fError = network.GetError(vInputsTrain);
	cout << "Error start: " << fError << endl;
	float fErrorPrev;
	unsigned int nSameErrorTimes = 0;
	unsigned int nIterations = 0;
	float fTheta = 0.9;
	while(true)
	{
		fErrorPrev = fError;
		network.TrainingKohonen(vInputsTrain, fTheta);
		fError = network.GetError(vInputsTrain);
		if (nIterations % 50 == 0)
			fTheta *= 0.95;
		nIterations++;

		if (fErrorPrev == fError)
		{
			nSameErrorTimes++;
			if (nSameErrorTimes >= 300)
				break;
		}
		else
		{
			nSameErrorTimes = 0;
		}
	}

	cout << "Trained. Iterations: " << nIterations << endl;
	cout << "Error end: " << network.GetError(vInputsTrain) << endl;

	for (unsigned int nIndex = 0; nIndex < trainingSet.GetInputsSize(); nIndex++)
	{
		vector<float> vInput  = trainingSet.GetInputs()[nIndex];
		vector<float> vOutput = trainingSet.GetOutputs()[nIndex];
		unsigned int nWinner = network.GetBestCompetitor(vInput);
		PrintVector(vOutput);
		cout << "-> " << nWinner << endl;
	}

}