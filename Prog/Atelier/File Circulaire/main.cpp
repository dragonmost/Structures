/*Samuel Baker dragonmost@live.ca
8 octobre 2014
Tester la File Oriente Objet*/

#include <iostream>
#include "Personne.h"
#include "CelluleFile.h"
#include "FileCirc.h"

using namespace std;

void main(){
	CFileCirc<CPersonne*>* pFile = new CFileCirc<CPersonne*>();			//pointeur vers un objet file
	CPersonne* pPersonne = new CPersonne("Baker", "Sam", 19);	//pointeur vers un objet personne
	pFile->EnfilerTete(pPersonne);
	pPersonne = new CPersonne("Nadeau", "Sam", 20);
	pFile->EnfilerTete(pPersonne);
	pPersonne = new CPersonne("Miron", "Simon", 21);
	pFile->EnfilerTete(pPersonne);
	pPersonne = new CPersonne("Charpentier", "Jeremie", 32);
	pFile->EnfilerTete(pPersonne);

	
	pPersonne = pFile->DefilerQueue();
	cout << pPersonne->ObtenirNom() << endl;
	pPersonne = pFile->DefilerQueue();
	cout << pPersonne->ObtenirNom() << endl;
	pPersonne = pFile->DefilerQueue();
	cout << pPersonne->ObtenirNom() << endl;
	pPersonne = pFile->DefilerQueue();
	cout << pPersonne->ObtenirNom() << endl;
	system("pause");

	delete pFile;
}