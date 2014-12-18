/*Samuel Baker dragonmost@live.ca
Derniere modification: 5 novembre 2014
Jeux Snake*/

#define LABYRINTHE tabchrNiveau1	// Plan du labyrinthe sous forme de tableau, à deux dimenssions, de caractères. ('X' = Mur, ' ' = Passage, 'E' = Entrée, 'S' = Sortie)

char chrDirection;
const int SIZE_X = 52;	//largeur du level
const int SIZE_Y = 52;	//hauteur du level


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

#include "CTP2.h"	// Inclusion nécessaire au TP1.
#include "Snake.h"
#include "Food.h"
#include "CelluleFile.h"
#include "CelluleListe.h"
#include "FileCirc.h"
#include "ListeSC.h"


/*
 * Programme permettant de jouer une partie de serpentin.
 *     argc : Nombre de paramètres passés au programme.
 *     argv : Pointeur vers un tableau de pointeurs de tableau de caractères représentant les paramètres.
 *   return : Code de fin du programme.
 */
int main(int argc, char** argv)
{
	int iPosX;						//position du snake en X
	int iPosY;						//position du snake en Y
	int iSizeSnake = 4;				//grandeur du snake												
	int iSleepTime = 60;			//temps de pause entre chaque mouvement
	int iFoodTimer = 0;				//Intervale entre chaque apparition de consommation
	int iDisband = 0;				//nombre de case restante a retirer du Snake
	int iScore = 0;					//Score de la game
	char chrCurrentDir;				//la direction de deplacement courante
	bool boStart = true;			//verification du depart d'une partie
	bool boGameOver = false;		//verification si la partie est terminer ou pas
	bool boSpawn = false;			//verifie si la consommation peux apparaitre
	bool boInvert = false;			//verifie dans quel sens on ce deplace
	bool boSingleInvert = false;	//verifie si l'inversement simple a été effectuer
	CSnake* arrPortal[10];			//tableau des position des portail
	int iPortalPos;					//sert a stocker la position du portail dans le tableau
	int iPortalNb;					//sert a savoir le numero du portail


	srand(time(NULL));

	CTP2* TP2 = new CTP2();			// Pointeur vers un nouvel objet de type CTP1.
	CFileCirc<CSnake*>* pFile = new CFileCirc<CSnake*>();	//pointeur vers une file circulaire
	CListSC<CFood*>* pList = new CListSC<CFood*>();			//pointeur vers une file simplement chaine
	CSnake* pSnake = nullptr;								//pointeur vers un element contenu dans la file circulaire
	CFood* pFood = nullptr;									//pointeur vers un element contenu dans la liste
	while (TP2->EnExecution() && !boGameOver)		// Tant que le TP1 s'exécute.
	{
		for (int ii = 0; ii <= SIZE_X; ii++)		//double boucle pour parcourir et afficher le labyrinthe
			for (int ij = 0; ij <= SIZE_Y; ij++)
			{
			TP2->DessinerCarre(ii, ij, tabchrNiveau1[ii][ij]);
			if (tabchrNiveau1[ii][ij] == 'V' && boStart){ iPosX = ii; iPosY = ij; }
			if (boStart && (tabchrNiveau1[ii][ij]) >= 48 && tabchrNiveau1[ii][ij] <= 58)
			{
				iPortalPos = tabchrNiveau1[ii][ij];
				arrPortal[iPortalPos - 48] = new CSnake(ii, ij);
			}

			}

		//boucle pour initialiser et empile le Snake a son start point
		if (boStart)
		{
			for (int ii = 1; ii <= iSizeSnake; ii++)
			{
				pSnake = new CSnake(iPosX, iPosY);
				pFile->Enfiler(pSnake);
			}
			boStart = false;
		}
		else
		{

			if (chrDirection == 'N' && chrCurrentDir == 'S')
				chrDirection = 'S';
			if (chrDirection == 'S' && chrCurrentDir == 'N')
				chrDirection = 'N';
			if (chrDirection == 'O' && chrCurrentDir == 'E')
				chrDirection = 'E';
			if (chrDirection == 'E' && chrCurrentDir == 'O')
				chrDirection = 'O';

			if (chrDirection == 'N')
				iPosY--;
			if (chrDirection == 'S')
				iPosY++;
			if (chrDirection == 'E')
				iPosX++;
			if (chrDirection == 'O')
				iPosX--;

			//verifier si collision avec le MUR
			if ((iPosX == 0 || iPosY == 0 || iPosX == 52 || iPosY == 52) && tabchrNiveau1[iPosX][iPosY] == MUR)
				boGameOver = true;

			//verifie si collision avec portail
			if ((iPosX == 0 || iPosX == 52 || iPosY == 0 || iPosY == 52) &&
				(tabchrNiveau1[iPosX][iPosY] != MUR))
			{
				iPortalNb = tabchrNiveau1[iPosX][iPosY] - 48;

				if (iPortalNb % 2 == 0){
					iPosX = arrPortal[iPortalNb + 1]->ObtenirX();
					iPosY = arrPortal[iPortalNb + 1]->ObtenirY();
				}
				else{
					iPosX = arrPortal[iPortalNb - 1]->ObtenirX();
					iPosY = arrPortal[iPortalNb - 1]->ObtenirY();
				}
				if (iPosX == 0)
					chrDirection = 'E';
				if (iPosX == 52)
					chrDirection = 'O';
				if (iPosY == 52)
					chrDirection = 'N';
				if (iPosY == 0)
					chrDirection = 'S';
			}

			//verifie si collision avec une consommation
			for (int ii = 1; ii <= pList->ObtenirCompte(); ii++)
			{
				pFood = pList->Obtenir(ii);
				if (iPosX == pFood->ObtenirX() && iPosY == pFood->ObtenirY())
				{
					int iLenght = rand() % 5 + 1;//random pour ajouter ou retirer des bouts de Snake
					switch (pFood->ObtenirType())
					{
						//Ajouter
					case 'A':	//Mauve
					{
						pSnake = pFile->DefilerQueue();
						int iQueueX = pSnake->ObtenirX();
						int iQueueY = pSnake->ObtenirY();
						pFile->Enfiler(pSnake);
						for (int ii = 1; ii <= iLenght; ii++)
						{
							pSnake = new CSnake(iQueueX, iQueueY);
							pFile->Enfiler(pSnake);
							iSizeSnake++;
						}
						iScore = iScore - (1000 * iLenght);
						break;
					}
						//Retirer
					case 'B':	//Bleu Pale
					{
						iScore = iScore + (1000 * iLenght);
						iDisband = iDisband + iLenght;
						break;
					}
						//Inverser
					case 'C':	//Beige	
					{
						boInvert = !boInvert;
						if (chrDirection == 'N')
							iPosY++;
						if (chrDirection == 'S')
							iPosY--;
						if (chrDirection == 'E')
							iPosX--;
						if (chrDirection == 'O')
							iPosX++;

						if (iSizeSnake >= 2)
						{
							if (boInvert)
							{
								pSnake = pFile->DefilerQueue();
								int iQueueX = pSnake->ObtenirX();
								int iQueueY = pSnake->ObtenirY();
								pSnake = pFile->DefilerQueue();
								if (iQueueX - pSnake->ObtenirX() == 1)
								{
									chrDirection = 'E';
									iPosX = iQueueX + 1;
									iPosY = iQueueY;
								}
								if (iQueueX - pSnake->ObtenirX() == -1)
								{
									chrDirection = 'O';
									iPosX = iQueueX - 1;
									iPosY = iQueueY;
								}
								if (iQueueY - pSnake->ObtenirY() == 1)
								{
									chrDirection = 'S';
									iPosX = iQueueX;
									iPosY = iQueueY + 1;
								}
								if (iQueueY - pSnake->ObtenirY() == -1)
								{
									chrDirection = 'N';
									iPosX = iQueueX;
									iPosY = iQueueY - 1;
								}
								pFile->Enfiler(pSnake);
								pSnake = new CSnake(iQueueX, iQueueY);
								pFile->Enfiler(pSnake);
							}
							else
							{
								pSnake = pFile->Defiler();
								int iInvQueueX = pSnake->ObtenirX();
								int iInvQueueY = pSnake->ObtenirY();
								pSnake = pFile->Defiler();
								if (iInvQueueX - pSnake->ObtenirX() == 1)
								{
									chrDirection = 'E';
									iPosX = iInvQueueX + 1;
									iPosY = iInvQueueY;
								}
								if (iInvQueueX - pSnake->ObtenirX() == -1)
								{
									chrDirection = 'O';
									iPosX = iInvQueueX - 1;
									iPosY = iInvQueueY;
								}
								if (iInvQueueY - pSnake->ObtenirY() == 1)
								{
									chrDirection = 'S';
									iPosX = iInvQueueX;
									iPosY = iInvQueueY + 1;
								}
								if (iInvQueueY - pSnake->ObtenirY() == -1)
								{
									chrDirection = 'N';
									iPosX = iInvQueueX;
									iPosY = iInvQueueY - 1;
								}
								pFile->EnfilerTete(pSnake);
								pSnake = new CSnake(iInvQueueX, iInvQueueY);
								pFile->EnfilerTete(pSnake);
							}
						}
						else
						{
							if (boInvert)
							{

								if (chrDirection == 'N' && !boSingleInvert)
								{
									chrDirection = 'S';
									iPosY--;
									boSingleInvert = true;
								}
								if (chrDirection == 'S' && !boSingleInvert)
								{
									chrDirection = 'N';
									iPosY++;
									boSingleInvert = true;
								}
								if (chrDirection == 'E' && !boSingleInvert)
								{
									chrDirection = 'O';
									iPosX--;
									boSingleInvert = true;
								}
								if (chrDirection == 'O' && !boSingleInvert)
								{
									chrDirection = 'E';
									iPosX--;
									boSingleInvert = true;
								}
							}
							else
							{
								if (chrDirection == 'N' && !boSingleInvert)
								{
									chrDirection = 'S';
									iPosY++;
									boSingleInvert = true;
								}
								if (chrDirection == 'S' && !boSingleInvert)
								{
									chrDirection = 'N';
									iPosY--;
									boSingleInvert = true;
								}
								if (chrDirection == 'E' && !boSingleInvert)
								{
									chrDirection = 'O';
									iPosX++;
									boSingleInvert = true;
								}
								if (chrDirection == 'O' && !boSingleInvert)
								{
									chrDirection = 'E';
									iPosX--;
									boSingleInvert = true;
								}
							}
							boSingleInvert = false;
						}
						break;
					}
						//Ralentir
					case 'D':	//Cyan
						iScore = iScore + 1000;
						if (iSleepTime > 10)
							iSleepTime = iSleepTime + 10;
						break;
						//Accelerer
					case 'E':	//Bleu
						iScore = iScore + 1000;
						//if (iSleepTime < 100)
						iSleepTime = iSleepTime - 10;
						break;
					}
					pList->retirer(ii);
				}
			}

			//detection de collision avec lui meme
			if (chrDirection != NULL)
				for (int ii = 0; ii <= iSizeSnake - 1; ii++)
				{
				pSnake = pFile->DefilerQueue();
				if (iPosX == pSnake->ObtenirX() && iPosY == pSnake->ObtenirY())
					boGameOver = true;
				pFile->EnfilerTete(pSnake);
				}
			//enlever les parties de trop a chaque tour
			if (iSizeSnake > 1 && iDisband >= 1)
			{
				iSizeSnake--;
				iDisband--;
				if (boInvert)
					delete	pFile->Defiler();
				else
					delete pFile->DefilerQueue();
			}
			else
				iDisband = 0;

			//enfiler du bon coter celui l'etat de l'inversement(consommation beige)
			if (!boInvert)
			{
				delete pFile->DefilerQueue();
				pSnake = new CSnake(iPosX, iPosY);
				pFile->EnfilerTete(pSnake);
			}
			else
			{
				delete pFile->Defiler();
				pSnake = new CSnake(iPosX, iPosY);
				pFile->Enfiler(pSnake);
			}
		}

		//Dessiner le Snake
		for (int ii = 1; ii <= iSizeSnake; ii++)
		{
			pSnake = pFile->DefilerQueue();
			TP2->DessinerCarre(pSnake->ObtenirX(), pSnake->ObtenirY(), SERPENTIN);
			pFile->EnfilerTete(pSnake);
		}

		//creation des consommations
		boSpawn = false;
		while (chrDirection != NULL && boSpawn == false)
		{
			boSpawn = true;
			if (iFoodTimer == 4)
			{
				iFoodTimer = 0;
				int iFoodX = rand() % 50 + 1;
				int iFoodY = rand() % 50 + 1;
				char iFoodT = rand() % 5 + 65;	//+65 ASCII

				for (int ii = 1; ii <= pList->ObtenirCompte(); ii++)
				{
					pFood = pList->Obtenir(ii);
					if (iFoodX == pFood->ObtenirX() && iFoodY == pFood->ObtenirY())
						boSpawn = false;
				}
				for (int ii = 0; ii <= iSizeSnake - 1; ii++)
				{
					pSnake = pFile->DefilerQueue();
					if (iFoodX == pSnake->ObtenirX() && iFoodY == pSnake->ObtenirY())
						boSpawn = false;
					pFile->EnfilerTete(pSnake);
				}
				if (boSpawn)
				{
					pFood = new CFood(iFoodX, iFoodY, iFoodT);
					pList->Ajouter(pFood);
				}
			}
			else
				iFoodTimer++;
			boSpawn = true;
		}

		//affichage des consommations
		for (int ii = 1; ii <= pList->ObtenirCompte(); ii++)
		{
			pFood = pList->Obtenir(ii);
			TP2->DessinerCarre(pFood->ObtenirX(), pFood->ObtenirY(), pFood->ObtenirType());
		}

		chrCurrentDir = chrDirection;

		TP2->Pause(iSleepTime);

		if (chrDirection != NULL)
		{
			iScore += 10;
			if (iScore < 0)
				iScore = 0;

			system("cls");
			cout << "Score: " << iScore << endl;
			cout << "Size: " << iSizeSnake << endl;
			cout << endl << "Coordonner: (" << iPosX << ", " << iPosY << ")" << endl;
		}
	}

	delete TP2;						// Destruction de l'objet pointé par TP1.
	delete pFood;					//destruction de l'objet pointé par pFood
	delete pFile;					//destruction de l'objet pointé par pFile
	delete pList;					//destruction de l'objet pointé par pList
	for (int ii = 0; ii < 10; ii++)	//destruction des objet dans le tableau de portail
		delete arrPortal[ii];


	system("pause");

	return 0;						// Fin normal du programme.
}



/*	note:
if (chrDirection == 'S')
portal impaire -1 / paire +1
allonger graduellement (tout enfiller au mm coordonnées)
retrecir graduellement (defiler 2x)
retrecir minimum 1
inverse (regarde quel sens avec les 2 dernier points)
changer la valeur du sleep
CListeSC* pConsommation
CConsommation


*/