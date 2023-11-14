#include "DataFuncs.h"

using namespace std; 
int main()
{
	ifstream infile;
	infile.open("csvText.txt");
	vector<vector<string>>generalData;
	
	parseCSVData(infile, generalData);

	cout << "[";
	for (const auto& row : generalData) {
		cout << "[";
		for (const auto& value : row) {
			cout << value <<", ";
		}

		cout <<"]" << endl;
	}
	cout << "]";
	
}