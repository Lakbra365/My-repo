#include "DataFuncs.h"
#include <iostream>

using namespace std; 
int main()
{
	DataManager test;
	regex pattern("G$");
	vector<int> specificData;
	test.parseSpecificData(pattern, specificData);

	cout << "[";
	for (const auto& row : specificData) 
	{
		cout << row <<", ";
	}
	cout << "]";
	
}