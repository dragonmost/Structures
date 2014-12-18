#include "Personne.h"
#include "CelluleListe.h"
#include "ListeSC.h"
#include <iostream>

using namespace std;

void main()
{
	CListSC<CPersonne*>* pList = new CListSC<CPersonne*>();
	CPersonne* pPersonne = new CPersonne("Sam", "Baker", 19);
	pList->Ajouter(pPersonne);
	pPersonne = new CPersonne("Sam", "Nadeau", 20);
	pList->Inserer(pPersonne, 3);
	pList->Inserer(pPersonne, 2);
	pPersonne = new CPersonne("Sam", "Dery", 17);
	pList->Inserer(pPersonne, 1);

	
	
	cout << pList->Obtenir(1)->ObtenirPrenom() << endl;
	cout << pList->Obtenir(2)->ObtenirPrenom() << endl;
	cout << pList->Obtenir(3)->ObtenirPrenom() << endl;
	if (pList->Obtenir(4)!= nullptr)
	cout << pList->Obtenir(4)->ObtenirPrenom() << endl;
	system("Pause");

}