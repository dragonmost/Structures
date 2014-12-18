#include "CelluleFile.h"
#include "FileCirc.h"
#include "CNombre.h"
#include "CelluleListe.h"
#include "ListeSC.h"
#include "NoeudArbreBinaire.h"
#include "ArbreAVL.h"
#include <iostream>

using namespace std;

void main()
{
	CArbreAVL<int>* pArbre = new CArbreAVL<int>();
	CListSC* pList = new CListSC();
	int i = 1;
	//pArbre->Ajouter(50);
	//pArbre->Ajouter(25);
	//pArbre->Ajouter(30);
	//pArbre->Ajouter(15);
	//pArbre->Ajouter(60);
	//pArbre->Ajouter(55);
	//pArbre->Ajouter(75);
	//pArbre->Ajouter(70);
	//pArbre->Ajouter(50);
	pArbre->Ajouter(1);
	pArbre->Ajouter(2);
	pArbre->Ajouter(3);
	//pArbre->Ajouter(4);
	//pArbre->Ajouter(5);
	//pArbre->Ajouter(6);
	//pArbre->Ajouter(7);
	//pArbre->Ajouter(8);
	//pArbre->Ajouter(9);
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