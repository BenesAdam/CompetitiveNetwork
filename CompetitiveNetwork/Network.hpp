#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <limits>

using namespace std;

#define NETWORK_INITIALIZE_RANDOMIZER srand((unsigned)time(0));

class cNetwork
{
	const unsigned int printPrecision = 5;
	unsigned int nN;
	unsigned int nM;
	vector<vector<float>> W;

	float CompetitorScore(unsigned int competitor, vector<float> inputs);
public: 
	cNetwork(unsigned int nInputs, unsigned int nCompetitors);
	void RandomWeights();
	void Print();
	unsigned int GetBestCompetitor(vector<float> inputs);
	float GetError(vector<vector<float>> vInputs);
};

