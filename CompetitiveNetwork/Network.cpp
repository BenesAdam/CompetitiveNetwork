#include "Network.hpp"
cNetwork::cNetwork(unsigned int nInputs, unsigned int nCompetitors)
	: nN(nInputs), nM(nCompetitors)
{
	W = vector<vector<float>>(nN);
	for (unsigned int i = 0; i < nN; i++)
	{
		vector<float> Wi = vector<float>(nM);
		for (unsigned int j = 0; j < nM; j++)
		{
			Wi[j] = j;
		}
		W[i] = Wi;
	}
}

void cNetwork::RandomWeights()
{
	for (unsigned int i = 0; i < nN; i++)
	{
		for (unsigned int j = 0; j < nM; j++)
		{
			double dRandomVal = (double)rand() / RAND_MAX;
			W[i][j] = dRandomVal;
		}
	}
}

void cNetwork::Print()
{
	cout << setprecision(printPrecision);
	cout << fixed;
	cout << "     (yi)" << endl;
	for (unsigned int i = 0; i < nN; i++)
	{
		cout << "x" << i << "|";
		for (unsigned int j = 0; j < nM; j++)
		{
			cout << W[i][j] << " ";
		}
		cout << endl;
	}
}

unsigned int cNetwork::GetBestCompetitor(vector<float> vInput)
{
	float fBestScore = 0;
	unsigned int nBestCompetitor = 0;
	AssignBestCompetitorAndScore(vInput, nBestCompetitor, fBestScore);
	return nBestCompetitor;
}

void cNetwork::AssignBestCompetitorAndScore(vector<float> vInput, unsigned int& nWinner, float& fScore)
{
	float fBestScore = FLT_MAX;
	unsigned int nBestCompetitor = 0;
	for (unsigned int nCompetitor = 0; nCompetitor < nM; nCompetitor++)
	{
		float fActualScore = CompetitorScore(nCompetitor, vInput);
		if (fActualScore < fBestScore)
		{
			nBestCompetitor = nCompetitor;
			fBestScore = fActualScore;
		}
	}
	nWinner = nBestCompetitor;
	fScore = fBestScore;
}

float cNetwork::CompetitorScore(unsigned int nCompetitor, vector<float> vInput)
{
	float result = 0;
	for (unsigned int i = 0; i < nN; i++)
	{
		float fTemp = vInput[i] - W[i][nCompetitor];
		result += fTemp * fTemp;
	}
	return sqrtf(result);
}

float cNetwork::GetError(vector<vector<float>> vInputs)
{
	float fSum = 0;
	for (vector<float> vInput : vInputs)
	{
		unsigned int nBestCompetitor = 0;
		float fCompetitorScore = 0;
		AssignBestCompetitorAndScore(vInput, nBestCompetitor, fCompetitorScore);
		fSum += fCompetitorScore * fCompetitorScore;
	}
	return (1.0 / vInputs.size()) * fSum;
}

// 0 <= fTheta <= 1
float cNetwork::TrainingKohonen(vector<vector<float>> vInputs, float fTheta)
{
	for (vector<float> vInput : vInputs)
	{
		unsigned int nWinner = 0;
		float fScore = 0;
		AssignBestCompetitorAndScore(vInput, nWinner, fScore);

		for (unsigned int i = 0; i < nM; i++)
		{
			W[i][nWinner] += fTheta * (vInput[i] - W[i][nWinner]);
		}
	}
	return GetError(vInputs);
}