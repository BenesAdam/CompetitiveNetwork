#include "Network.hpp"
cNetwork::cNetwork(unsigned int nInputs, unsigned int nCompetitors)
{
	nN = nInputs;
	nM = nCompetitors;

	W = vector<vector<float>>(nN);
	for (int i = 0; i < nN; i++)
	{
		vector<float> Wi = vector<float>(nM);
		for (int j = 0; j < nM; j++)
		{
			Wi[j] = j;
		}
		W[i] = Wi;
	}
}

void cNetwork::RandomWeights()
{
	for (int i = 0; i < nN; i++)
	{
		for (int j = 0; j < nM; j++)
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
	for (int i = 0; i < nN; i++)
	{
		cout << "x" << i << "|";
		for (int j = 0; j < nM; j++)
		{
			cout << W[i][j] << " ";
		}
		cout << endl;
	}
}

unsigned int cNetwork::GetBestCompetitor(vector<float> vInput)
{
	float fBestScore = FLT_MAX;
	int nBestCompetitor = 0;
	for (int nCompetitor = 0; nCompetitor < nM; nCompetitor++)
	{
		float fActualScore = CompetitorScore(nCompetitor, vInput);
		if (fActualScore < fBestScore)
		{
			nBestCompetitor = nCompetitor;
		}
	}
	return nBestCompetitor;
}

float cNetwork::CompetitorScore(unsigned int nCompetitor, vector<float> vInput)
{
	float result = 0;
	for (int i = 0; i < nN; i++)
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
		unsigned int nBestCompetitor = GetBestCompetitor(vInput);
		float fCompetitorScore = CompetitorScore(nBestCompetitor, vInput);
		fSum += fCompetitorScore * fCompetitorScore;
	}
	return (1.0 / vInputs.size()) * fSum;
}