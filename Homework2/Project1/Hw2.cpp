#include <iostream>
#include "questions.h"


using namespace std;

int main()
{
	int question;
	cout << "type question number" << endl;
	cin >> question;
	switch (question)
	{
	case 1:
		question1();
		break;
/*	case 2:
		question2();
		break;
	case 3:
		question3();
		break;
	case 4:
		question4();
		break;
	case 5:
		question5();
		break;
	case 6:
		question6();
		break;
	case 7:
		question7();
		break;
	case 8:
		question8();
		break;*/
	}
}