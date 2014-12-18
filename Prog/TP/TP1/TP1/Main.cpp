/*Samuel Baker dragonmost@live.ca
24 septembre 2014 
resolution de labyrinthe*/

#define LABYRINTHE tabchrLabyrinthe3	// Plan du labyrinthe sous forme de tableau, à deux dimenssions, de caractères. ('X' = Mur, ' ' = Passage, 'E' = Entrée, 'S' = Sortie)

#include "CTP1.h"	// Inclusion nécessaire au TP1.
#include "CPosition.h"
#include "CCellulePile.h"
#include "CPile.h"
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

/*
 * Programme permettant de résoudre des plans de labyrinthe à 2 dimenssions.
 *     argc : Nombre de paramètres passés au programme.
 *     argv : Pointeur vers un tableau de pointeurs de tableau de caractères représentant les paramètres.
 *   return : Code de fin du programme.
 */
int main(int argc, char** argv) {
	
	int iRandom;	//generation de nombre aleatoire
	int iSize_x = 52;	//indice de la largeur du labyrinthe pour parcourir le tableau LABYRINTHE
	int iSize_y = 52;	//indice de la hauteur du labyrinthe pour parcourir le tableau LABYRINTHE
	int iPos_x = 0;		//indice de la position en X du curseur
	int iPos_y = 0;		//indice de la position en Y du curseur
	int iNbCas = 0;		//indice du nombre de cas de deplacement possible
	bool arrboDirection[4];		//tableau des directions disposible
	char chrDernDirection = 'X';	//indique la direction du dernier mouvement
	bool boCheck = true; //regarde si on doit verifier les direction disponible
	bool boFini = false;	//boolean pour verifier si la sortie a ete trouve
	bool boDepile = false;	//verifie si jai depile durant la derniere action

	CTP1* TP1 = new CTP1();				// Pointeur vers un nouvel objet de type CTP1.
	CPile* pPile = new CPile();			//pointeur vers une nouvelle pile
	CPosition* pPosition = nullptr;		//pointeur vers un CPosition
	while ((TP1->EnExecution()) && (!boFini)) {		// Tant que le TP1 s'exécute.
		if (iPos_x == 0 && iPos_y ==0){
			for (int ii = 0; ii <= iSize_x; ii++){		//double boucle pour parcourir et afficher le labyrinthe
				for (int ij = 0; ij <= iSize_y; ij++){
					pPosition = new CPosition(iPos_x, iPos_y, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					TP1->DessinerCarre(ii, ij, LABYRINTHE[ii][ij]);
					if (LABYRINTHE[ii][ij] == ENTREE){
						iPos_x = ii;
						iPos_y = ij;
					}
				}
			}
		}
		iNbCas = 0;
		if (boCheck){
			//serie de condition pour verifier les disponibilite de mouvement
			if (LABYRINTHE[iPos_x][iPos_y - 1] == PASSAGE && chrDernDirection != 'N'){
				arrboDirection[0] = true;
				iNbCas++;
			}
			else
				arrboDirection[0] = false;
			if (LABYRINTHE[iPos_x][iPos_y + 1] == PASSAGE && chrDernDirection != 'S'){
				arrboDirection[1] = true;
				iNbCas++;
			}
			else
				arrboDirection[1] = false;
			if (LABYRINTHE[iPos_x + 1][iPos_y] == PASSAGE && chrDernDirection != 'E'){
				arrboDirection[2] = true;
				iNbCas++;
			}
			else
				arrboDirection[2] = false;
			if (LABYRINTHE[iPos_x - 1][iPos_y] == PASSAGE && chrDernDirection != 'W'){
				arrboDirection[3] = true;
				iNbCas++;
			}
			else
				arrboDirection[3] = false;
		}
		else{
			for (int ii = 0; ii <= 3; ii++)
				if (arrboDirection[ii])
					iNbCas++;
		}

		//switch qui effectu une operation differente selon le nombre de mouvement disponible
		switch (iNbCas){
		case 1:
			if (arrboDirection[0]){
				TP1->DessinerCarre(iPos_x, --iPos_y, CHEMIN);
				chrDernDirection = 'S';
				arrboDirection[0] = false;
			}
			if (arrboDirection[1]){
				TP1->DessinerCarre(iPos_x, ++iPos_y, CHEMIN);
				chrDernDirection = 'N';
				arrboDirection[1] = false;
			}
			if (arrboDirection[2]){
				TP1->DessinerCarre(++iPos_x, iPos_y, CHEMIN);
				chrDernDirection = 'W';
				arrboDirection[2] = false;
			}
			if (arrboDirection[3]){
				TP1->DessinerCarre(--iPos_x, iPos_y, CHEMIN);
				chrDernDirection = 'E';
				arrboDirection[3] = false;
			}
			boCheck = true;
			if (boDepile){
				
				switch (chrDernDirection){
				case'S':
					pPosition = new CPosition(iPos_x, iPos_y + 1, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					break;
				case'N':
					pPosition = new CPosition(iPos_x, iPos_y - 1, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					break;
				case'W':
					pPosition = new CPosition(iPos_x + 1, iPos_y, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					break;
				case'E':
					pPosition = new CPosition(iPos_x - 1, iPos_y, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					break;
				}
				//pPosition = new CPosition(iPos_x, iPos_y, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
				//pPile->Empiler(pPosition);
				//pPosition = new CPosition(iPos_x, iPos_y, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
				switch (chrDernDirection){
				case'S':
					pPosition = new CPosition(iPos_x, iPos_y + 1, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					break;
				case'N':
					pPosition = new CPosition(iPos_x, iPos_y - 1, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					break;
				case'W':
					pPosition = new CPosition(iPos_x + 1, iPos_y, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					break;
				case'E':
					pPosition = new CPosition(iPos_x - 1, iPos_y, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					break;
				}
				

				boDepile = false;
			}
			break;


		case 0:
			iPos_x = pPosition->ObtenirPosX();
			iPos_y = pPosition->ObtenirPosY();
			for (int ii = 0; ii <= 3; ii++)
				arrboDirection[ii] = pPosition->ObtenirDirection(ii);
			if (pPile != nullptr)
				pPosition = pPile->Depiler();

			boDepile = true;
			boCheck = false;
			TP1->DessinerCarre(--iPos_x, iPos_y, SORTIE);
			TP1->DessinerCarre(--iPos_x+1, iPos_y+1, CHEMIN);
		break;

		case 2: 
		case 3:
			//pPosition = new CPosition(iPos_x, iPos_y, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
			//pPile->Empiler(pPosition);
			//choisir un chiffre random et effectuer les mouvement selon le resulat
			srand(time(NULL));	//generation de nombre aleatoire
			iRandom = rand() % iNbCas + 1;	
			int iindex = 0; //index pour parcourir le tableau de boolean (direction)
			if (iRandom == 1){
				while (!arrboDirection[iindex]){
					iindex++;
				}
				if (iindex == 0){
					arrboDirection[0] = false;
					TP1->DessinerCarre(iPos_x, --iPos_y, CHEMIN);
					chrDernDirection = 'S';
				}
				if (iindex == 1){
					arrboDirection[1] = false;
					TP1->DessinerCarre(iPos_x, ++iPos_y, CHEMIN);
					chrDernDirection = 'N';
				}
				if (iindex == 2){
					arrboDirection[2] = false;
					TP1->DessinerCarre(++iPos_x, iPos_y, CHEMIN);
					chrDernDirection = 'W';
				}
				if (iindex == 3){
					arrboDirection[3] = false;
					TP1->DessinerCarre(--iPos_x, iPos_y, CHEMIN);
					chrDernDirection = 'E';
				}
			}
			if (iRandom == 2){
				int iNbTrouve = 0; //le nombre de true trouver afin d'arreter au 2ieme true
				while (iNbTrouve <= 1){
					if (arrboDirection[iindex])
					iNbTrouve++;
					iindex++;
				}
				if (iindex == 0){
					arrboDirection[0] = false;
					TP1->DessinerCarre(iPos_x, --iPos_y, CHEMIN);
					chrDernDirection = 'S';
				}
				if (iindex == 1){
					arrboDirection[1] = false;
					TP1->DessinerCarre(iPos_x, ++iPos_y, CHEMIN);
					chrDernDirection = 'N';
				}
				if (iindex == 2){
					arrboDirection[2] = false;
					TP1->DessinerCarre(++iPos_x, iPos_y, CHEMIN);
					chrDernDirection = 'W';
				}
				if (iindex == 3){
					arrboDirection[3] = false;
					TP1->DessinerCarre(--iPos_x, iPos_y, CHEMIN);
					chrDernDirection = 'E';
				}
			}

			if (iRandom == 3){
				iindex = 3;
				while (!arrboDirection[iindex]){
					iindex--;
				}
				if (iindex == 0){
					arrboDirection[0] = false;
					TP1->DessinerCarre(iPos_x, --iPos_y, CHEMIN);
					chrDernDirection = 'S';
				}
				if (iindex == 1){
					arrboDirection[1] = false;
					TP1->DessinerCarre(iPos_x, ++iPos_y, CHEMIN);
					chrDernDirection = 'N';
				}
				if (iindex == 2){
					arrboDirection[2] = false;
					TP1->DessinerCarre(++iPos_x, iPos_y, CHEMIN);
					chrDernDirection = 'W';
				}
				if (iindex == 3){
					arrboDirection[3] = false;
					TP1->DessinerCarre(--iPos_x, iPos_y, CHEMIN);
					chrDernDirection = 'E';
				}
			}
				switch (chrDernDirection){
				case'S':
					pPosition = new CPosition(iPos_x, iPos_y + 1, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					break;
				case'N':
					pPosition = new CPosition(iPos_x, iPos_y - 1, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					break;
				case'W':
					pPosition = new CPosition(iPos_x + 1, iPos_y, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					break;
				case'E':
					pPosition = new CPosition(iPos_x - 1, iPos_y, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					break;
				}
				//pPosition = new CPosition(iPos_x, iPos_y, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
				pPile->Empiler(pPosition);
				//pPosition = new CPosition(iPos_x, iPos_y, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
				switch (chrDernDirection){
				case'S':
					pPosition = new CPosition(iPos_x, iPos_y + 1, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					break;
				case'N':
					pPosition = new CPosition(iPos_x, iPos_y - 1, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					break;
				case'W':
					pPosition = new CPosition(iPos_x + 1, iPos_y, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					break;
				case'E':
					pPosition = new CPosition(iPos_x - 1, iPos_y, arrboDirection[0], arrboDirection[1], arrboDirection[2], arrboDirection[3]);
					break;
				}
			boCheck = true;
		break;
		}
		Sleep(10);
		//TP1->DessinerCarre(iPos_x, iPos_y, CHEMIN);
		if (LABYRINTHE[iPos_x - 1][iPos_y] == SORTIE || LABYRINTHE[iPos_x][iPos_y - 1] == SORTIE || LABYRINTHE[iPos_x + 1][iPos_y] == SORTIE || LABYRINTHE[iPos_x][iPos_y + 1] == SORTIE)
			boFini = true;
	}
	delete pPosition;											//destruction de l'objet pointé par pPosition
	delete pPile;												//Destruction de l'objet pointé par pPile
	delete TP1;													// Destruction de l'objet pointé par TP1.
	return 0;														// Fin normal du programme.
}



