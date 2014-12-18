#include <iostream>
#include "ArbreLineaire.h"

using namespace std;

void main(){
	CArbreLineaire<int>* arb = new CArbreLineaire<int>(20);

	arb->Ajouter(10);
	arb->Ajouter(12);

	cout << arb->Rechercher(10) << endl;
	cout << arb->Rechercher(9) << endl;
	cout << arb->Rechercher(12) << endl;

	system("pause");

	delete arb;
}