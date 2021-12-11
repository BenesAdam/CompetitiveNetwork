#include <iostream>
#include <bitset>
#include "Network.hpp"
#include "TrainingSet.hpp"

using namespace std;

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

	const unsigned int oneFourth = (int)(trainingSet.GetInputsSize() / 4.0);
	vector<vector<float>> vInputs = trainingSet.GetInputs();
	auto input_test_first  = vInputs.begin();
	auto input_test_last   = vInputs.begin() + oneFourth;
	auto input_train_first = vInputs.begin() + oneFourth + 1;
	auto input_train_last  = vInputs.end();
	auto vInputsTest = vector<vector<float>>(input_test_first, input_test_last);
	auto vInputsTrain = vector<vector<float>>(input_train_first, input_train_last);

	vector<vector<float>> vOutput = trainingSet.GetOutputs();
	auto output_test_first = vOutput.begin();
	auto output_test_last = vOutput.begin() + oneFourth;
	auto output_train_first = vOutput.begin() + oneFourth + 1;
	auto output_train_last = vOutput.end();
	auto vOutputTest = vector<vector<float>>(output_test_first, output_test_last);
	auto vOutputTrain = vector<vector<float>>(output_train_first, output_train_last);

	unsigned int nIterations = 0;
	cout << "Error on start: " << network.GetError(vInputsTrain) << endl;
	float fTheta = 0.9;
	while (network.GetError(vInputsTrain) > 0.1)
	{
		network.TrainingKohonen(vInputsTrain, fTheta);
		if(nIterations % 100 == 0)
			fTheta *= 0.99;

		cout << fTheta << " " << network.GetError(vInputs) << endl;
		nIterations++;
	}

	cout << "Trained." << endl;
	cout << "Error on end: " << network.GetError(vInputsTrain) << endl;



}