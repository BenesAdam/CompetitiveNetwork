#include <iostream>
#include "Network.hpp"

using namespace std;

int main()
{
	// link: https://drive.google.com/open?id=1JEM_gcdX95I2N-95Hoxea2qWArsvjMz7&authuser=adam.beny.benes%40gmail.com&usp=drive_fs
	NETWORK_INITIALIZE_RANDOMIZER
	cNetwork network = cNetwork(2, 5);

	network.Print();

	//network.RandomWeights();
	//cout << endl << endl;
	//network.Print();

	vector<float> vInput1 = { 1,2 };
	vector<float> vInput2 = { 3,4 };
	vector<vector<float>> vInputs = { vInput1, vInput2 };
	

	for (int i = 0; i < 10; i++)
	{
		network.RandomWeights();
		cout << "Won: " << network.GetBestCompetitor(vInput1) << endl;
		cout << "Won: " << network.GetBestCompetitor(vInput2) << endl;
		cout << "Network error: " << network.GetError(vInputs);
		cout << endl;
	}

}