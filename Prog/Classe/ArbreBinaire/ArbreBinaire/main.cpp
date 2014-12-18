#include "CelluleFile.h"
#include "FileCirc.h"
#include "CNombre.h"
#include "CelluleListe.h"
#include "ListeSC.h"
#include "NoeudArbreBinaire.h"
#include "ArbreBinaire.h"
#include <iostream>

using namespace std;

void main()
{
	CArbreBinaire<int>* pArbre = new CArbreBinaire<int>();
	CListSC* pList = new CListSC();

	pArbre->Ajouter(50);
	pArbre->Ajouter(25);
	pArbre->Ajouter(30);
	pArbre->Ajouter(15);
	pArbre->Ajouter(60);
	pArbre->Ajouter(55);
	pArbre->Ajouter(75);
	pArbre->Ajouter(70);
	pArbre->Ajouter(50);

	int k = 30;

	/*cout << pArbre->Rechercher(k) << endl;
	pArbre->Retirer(25);
	cout << pArbre->Rechercher(k) << endl;
	cout << pArbre->Rechercher(25) << endl;*/

	pList = pArbre->RunPrefix();

	for (int ii = 1; ii < pList->ObtenirCompte()+1; ii++)
		cout << pList->Obtenir(ii) << endl;
	delete pList;
	
	cout << endl;
	pList = pArbre->RunInfix();
	
	for (int ii = 1; ii < pList->ObtenirCompte() + 1; ii++)
		cout << pList->Obtenir(ii) << endl;
	delete pList;
	
	cout << endl;
	pList = pArbre->RunPostfix();
	
	for (int ii = 1; ii < pList->ObtenirCompte() + 1; ii++)
		cout << pList->Obtenir(ii) << endl;
	delete pList;

	cout << endl;
	pList = pArbre->RunLargeur();

	for (int ii = 1; ii < pList->ObtenirCompte() + 1; ii++)
		cout << pList->Obtenir(ii) << endl;
	delete pList;
	
	pArbre->Retirer(50);

	cout << endl;
	pList = pArbre->RunLargeur();

	for (int ii = 1; ii < pList->ObtenirCompte() + 1; ii++)
		cout << pList->Obtenir(ii) << endl;
	delete pList;

	system("Pause");
}