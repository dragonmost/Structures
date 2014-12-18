#include "MSFV.h"
#include "CelluleListe.h"
#include "ListDCwCur.h"
#include "Fichier.h"
#include "Dossier.h"
#include "CelluleFile.h"
#include "FileCirc.h"
#include "NoeudArbreBinaire.h"
#include "ArbreAVL.h"
#include "Procedure_Baker.h"

/* --------------------------------------------------------------------------------------
 *   Variables globales
 * ----------------------------------------------------------------------------------- */

CMSFVTextBox* dlgNom;	// Boîte de dialogue pour la saisie de nom.
CMSFVMemo* dlgTexte;	// Boîte de dialogue pour la saisie de contenu de fichier texte.
CMenu* mnuContextuel;	// Menu contextuel.
CDossier* pRacine = new CDossier(nullptr, new CListDCwCur<CDossier*>(), new CListDCwCur<CFichier*>(), "Racine");	//pointeur vers le dossier racine
CDossier* pCurrent = pRacine; //pointeur du dossier courant
CArbreAVL<int>* pArbreIndSelect = new CArbreAVL<int>();	//pointeur vers un arbre d'indice de documents selectionner
/* --------------------------------------------------------------------------------------
 *   Événement exécuté au démarrage du programme.
 * ----------------------------------------------------------------------------------- */

void OnShow(void) {


}

/* --------------------------------------------------------------------------------------
 *   Événement exécuté lors d'un click avec la souris souris.
 * --------------------------------------------------------------------------------------
 *         _iX : Position du click sur l'axe des X.
 *         _iY : Position du click sur l'axe des Y.
 *   _ucBouton : Bouton utilisé pour clicker (BOUTON_GAUCHE, BOUTON_DROITE).
 *     _boCTRL : Si la touche Ctrl du clavier est enfoncée.
 * ----------------------------------------------------------------------------------- */

void OnMouseClick(int _iX, int _iY, unsigned char _ucBouton, bool _boCTRL) {
	int iMenuVal = MENU_AUCUN;
	string strNom;		//contient le nom a mettre dans le dossier/fichier
	string strContent;	//contient le contenu du showDialog pour les mettre dans le dossier/fichier
	bool boSameName = false; //verifie si le nouveau fichier ou dossier a le meme nom qu'un autre dans le meme dossier
	int iIndX, iIndY, iIndSelect;	//sert a calculer l'indice du dossier/fichier qui a ete clicker

	iIndX = ((_iX * (FENETRE_LARGEUR / ICONE_LARGEUR)) / (FENETRE_LARGEUR)+1);
	iIndY = ((_iY * (FENETRE_HAUTEUR / ICONE_HAUTEUR)) / (FENETRE_HAUTEUR));
	iIndSelect = iIndX + (iIndY * (FENETRE_LARGEUR / ICONE_LARGEUR));

	//click gauche
	if (_ucBouton == BOUTON_GAUCHE && (!boCTRL))
	{
		//verifie si le click n'est pas dans le vide
		if (iIndSelect <= (pCurrent->ObtenirListeDossier()->ObtenirCompte() + pCurrent->ObtenirListeFichier()->ObtenirCompte()) + 1)
		{
			//si dans la racine
			if ((pCurrent == pRacine))
			{
				//si c'est un dossier
				if (iIndSelect <= pCurrent->ObtenirListeDossier()->ObtenirCompte())
				{
					pCurrent->ObtenirListeFichier()->AllerA(iIndSelect);
					pCurrent = pCurrent->ObtenirListeDossier()->Obtenir();
				}
				//si c'est un Fichier
				else if (iIndSelect > pCurrent->ObtenirListeDossier()->ObtenirCompte())
				{
					pCurrent->ObtenirListeFichier()->AllerA(iIndSelect - pCurrent->ObtenirListeDossier()->ObtenirCompte());
					CFichier* pfichier = pCurrent->ObtenirListeFichier()->Obtenir();	//point vers le meme fichier sans avoir a reecrir tout la ligne
					dlgTexte->SetTitle(pfichier->ObtenirNom());
					dlgTexte->SetText(pfichier->ObtenirContent());
					strContent = dlgTexte->ShowDialog();
					pfichier->DefinirContent(strContent);
				}
			}
			//si dans un fichier enfant (pas la racine)
			else
			{
				//click sur le fichier parent
				if (iIndSelect == 1)
					pCurrent = pCurrent->ObtenirParent();
				//click sur un dossier enfant
				if ((iIndSelect > 1) && (iIndSelect <= pCurrent->ObtenirListeDossier()->ObtenirCompte() + 1))
				{
					pCurrent->ObtenirListeDossier()->AllerA(iIndSelect - 1);
					pCurrent = pCurrent->ObtenirListeDossier()->Obtenir();
				}
				//si c'est un Fichier
				else if (iIndSelect > pCurrent->ObtenirListeDossier()->ObtenirCompte() + 1)
				{
					pCurrent->ObtenirListeFichier()->AllerA(iIndSelect - pCurrent->ObtenirListeDossier()->ObtenirCompte());
					CFichier* pfichier = pCurrent->ObtenirListeFichier()->Obtenir();	//point vers le meme fichier sans avoir a reecrir tout la ligne
					dlgTexte->SetTitle(pfichier->ObtenirNom());
					dlgTexte->SetText(pfichier->ObtenirContent());
					strContent = dlgTexte->ShowDialog();
					pfichier->DefinirContent(strContent);
				}
			}
		}
		//deselectionner
		delete pArbreIndSelect;
		pArbreIndSelect = new CArbreAVL<int>();
	}
	//click gauche avec CTRL
	if ((_ucBouton == BOUTON_GAUCHE) && (_boCTRL))
	{
		//si deja selectionner il deselectionne
		if (pArbreIndSelect->Rechercher(iIndSelect))
			pArbreIndSelect->Retirer(iIndSelect);
		//verifie si le click n'est pas dans le vide
		else if (iIndSelect <= (pCurrent->ObtenirListeDossier()->ObtenirCompte() + pCurrent->ObtenirListeFichier()->ObtenirCompte() + 1))
		{
			//si on n'est pas a la racine l'indice 1 est selui du dossier parent
			if ((pCurrent != pRacine) && (iIndSelect != 1))
				pArbreIndSelect->Ajouter(iIndSelect - 1);
			//ajout d'indice dans le dossier racine
			else
				pArbreIndSelect->Ajouter(iIndSelect);
		}
	}
	//click droit
	else if (_ucBouton == BOUTON_DROITE)
	{
		if (((pCurrent == pRacine) && iIndSelect <=
			(pCurrent->ObtenirListeDossier()->ObtenirCompte() + pCurrent->ObtenirListeFichier()->ObtenirCompte())) ||
			((pCurrent != pRacine) && iIndSelect <=
			(pCurrent->ObtenirListeDossier()->ObtenirCompte() + pCurrent->ObtenirListeFichier()->ObtenirCompte()) + 1))
		{
			iMenuVal = mnuContextuel->ShowDialog(_iX, _iY, MENU_RENOMMER | MENU_SUPPRIMER);//valeur du menu(click droit) selectionner	
		}
		else if (pCurrent != pRacine && iIndSelect == 1)
		{
			iMenuVal = mnuContextuel->ShowDialog(_iX, _iY, MENU_AUCUN);
		}
		else
		{
			iMenuVal = mnuContextuel->ShowDialog(_iX, _iY, MENU_NOUVEAU_DOSSIER | MENU_NOUVEAU_FICHIER | MENU_SELECTIONNER_TOUT);
		}

		switch (iMenuVal)
		{
		case MENU_NOUVEAU_DOSSIER:
		{
			dlgNom->SetTitle("Nouveau Dossier");
			dlgNom->SetText("Nouveau Dossier");
			strNom = dlgNom->ShowDialog();

			int ii = 0;
			int iNbDossier = pCurrent->ObtenirListeDossier()->ObtenirCompte();
			//boucle pour verifier si un autre dossier a le meme nom dans le dossier

			pCurrent->ObtenirListeDossier()->AllerPremier();
			while ((ii < iNbDossier) && (!boSameName))
			{
				boSameName = pCurrent->ObtenirListeDossier()->Obtenir()->ObtenirNom() == strNom;
				pCurrent->ObtenirListeDossier()->AllerSuivant();
				ii++;
			}

			if ((strNom != "") && (!boSameName))
				pCurrent->ObtenirListeDossier()->Ajouter(new CDossier(pCurrent, new CListDCwCur<CDossier*>(), new CListDCwCur<CFichier*>(), strNom));

			QuickSortDossier(1, pCurrent->ObtenirListeDossier()->ObtenirCompte(), pCurrent->ObtenirListeDossier());
			break;
		}
		case MENU_NOUVEAU_FICHIER:
		{
			dlgNom->SetText("Nouveau Fichier");
			dlgNom->SetTitle("Nouveau Fichier");
			strNom = dlgNom->ShowDialog();

			int ii = 0;
			int iNbFichier = pCurrent->ObtenirListeFichier()->ObtenirCompte();
			//boucle pour verifier si un autre fichier a le meme nom dans le dossier

			pCurrent->ObtenirListeFichier()->AllerPremier();
			while ((ii < iNbFichier) && (!boSameName))
			{
				boSameName = pCurrent->ObtenirListeFichier()->Obtenir()->ObtenirNom() == strNom;
				pCurrent->ObtenirListeFichier()->AllerSuivant();
				ii++;
			}
			if ((strNom != "") && (!boSameName))
				pCurrent->ObtenirListeFichier()->Ajouter(new CFichier(strNom, string()));
			
			QuickSortFichier(1, pCurrent->ObtenirListeFichier()->ObtenirCompte(), pCurrent->ObtenirListeFichier());
			break;
		}
		case MENU_RENOMMER:
		{
			//si dossier
			if (iIndSelect <= pCurrent->ObtenirListeDossier()->ObtenirCompte())
			{
				pCurrent->ObtenirListeDossier()->AllerA(iIndSelect);
				dlgNom->SetTitle("Renommer");
				dlgNom->SetText(pCurrent->ObtenirListeDossier()->Obtenir()->ObtenirNom());
				CDossier* pDossier = pCurrent->ObtenirListeDossier()->Obtenir();
				string strNewName = dlgNom->ShowDialog();

				//boucle pour verifier si un autre fichier a le meme nom dans le dossier
				int ii = 0;
				int iNbFichier = pCurrent->ObtenirListeDossier()->ObtenirCompte();
				pCurrent->ObtenirListeDossier()->AllerPremier();
				while ((ii < iNbFichier) && (!boSameName))
				{
					boSameName = pDossier->ObtenirNom() == strNewName;
					pCurrent->ObtenirListeDossier()->AllerSuivant();
					ii++;
				}
				if ((strNewName != "") && (!boSameName))
					pDossier->DefinirNom(strNewName);

			}
			//si c'est un Fichier
			else if (iIndSelect > pCurrent->ObtenirListeFichier()->ObtenirCompte())
			{
				pCurrent->ObtenirListeFichier()->AllerA(iIndSelect - pCurrent->ObtenirListeDossier()->ObtenirCompte());
				dlgNom->SetTitle("Renommer");
				dlgNom->SetText(pCurrent->ObtenirListeFichier()->Obtenir()->ObtenirNom());
				CFichier* pFichier = pCurrent->ObtenirListeFichier()->Obtenir();
				string strNewName = dlgNom->ShowDialog();

				//boucle pour verifier si un autre fichier a le meme nom dans le dossier
				int ii = 0;
				int iNbFichier = pCurrent->ObtenirListeFichier()->ObtenirCompte();
				pCurrent->ObtenirListeFichier()->AllerPremier();
				while ((ii < iNbFichier) && (!boSameName))
				{
					boSameName = pCurrent->ObtenirListeFichier()->Obtenir()->ObtenirNom() == strNewName;
					pCurrent->ObtenirListeFichier()->AllerSuivant();
					ii++;
				}
				if ((strNewName != "") && (!boSameName))
					pCurrent->ObtenirListeFichier()->Obtenir()->DefinirNom(strNewName);

			}
			break;
		}
		case MENU_SUPPRIMER:
		{
			CFileCirc<int>* pFileSelect = new CFileCirc<int>();		//file des indice selectionner
			
			pFileSelect = pArbreIndSelect->RunInfix();
			
			int iIndASup = pFileSelect->DefilerQueue();
			//si il y a des element de selectionner
			if (iIndASup != -1)
				while (iIndASup != -1)
				{
					if (iIndASup <= pCurrent->ObtenirListeDossier()->ObtenirCompte())
					{
						pCurrent->ObtenirListeDossier()->AllerA(iIndASup);
						pCurrent->ObtenirListeDossier()->Retirer();
					}
					else
					{
						pCurrent->ObtenirListeFichier()->AllerA(iIndASup - pCurrent->ObtenirListeDossier()->ObtenirCompte());
						pCurrent->ObtenirListeFichier()->Retirer();
					}
					iIndASup = pFileSelect->DefilerQueue();

					delete pArbreIndSelect;
					pArbreIndSelect = new CArbreAVL<int>();
				}
			else
			{
				pCurrent->ObtenirListeDossier()->AllerA(iIndSelect);
				pCurrent->ObtenirListeDossier()->Retirer();
			}
			break;
		}
			//			case MENU_COMPRESSER:
			//			{
			//			
			//				break;
			//			}
			//			case MENU_DECOMPRESSER:
			//			{
			//			
			//				break;
			//			}
		case MENU_SELECTIONNER_TOUT:
		{
			for (int ii = 1; ii <= pCurrent->ObtenirListeDossier()->ObtenirCompte(); ii++)
				pArbreIndSelect->Ajouter(ii);
			for (int ii = 1; ii <= pCurrent->ObtenirListeFichier()->ObtenirCompte(); ii++)
				pArbreIndSelect->Ajouter(ii + pCurrent->ObtenirListeDossier()->ObtenirCompte());
			break;
		}
		}
	}
}

/* --------------------------------------------------------------------------------------
 *   Événement exécuté lors de l'affichage.
 * ----------------------------------------------------------------------------------- */

void OnRefresh(void){
	//DessinerBarreEtat(1, 0);
	int iNbIconRow = (iLargeurFenetre - ICONE_LARGEUR) / ICONE_LARGEUR;	//calcule le nombre d'icon qui entre par ligne
	int iHauteur = 0;	//sert a calculer la hauteur afin de mettre les icons dans la bonne ranger
	int iRow = 0;	//sert a calculer le nombre de pixel en X et aligner les icon dans la meme ranger

	//dessiner le dossier parent
	if (pCurrent != pRacine)
	{
		DessinerIcone(iRow, iHauteur, ICONE_DOSSIER, 0);
		DessinerChaine("..", iRow + (ICONE_LARGEUR / 2) - (LargeurChaine("..") / 2), iHauteur + ICONE_HAUTEUR);
		iRow = 1;
	}

	pCurrent->ObtenirListeDossier()->AllerPremier();
	pCurrent->ObtenirListeFichier()->AllerPremier();

	//afficher les dossier
	for (int ii = 1; ii <= pCurrent->ObtenirListeDossier()->ObtenirCompte(); ii++)
	{
		DessinerIcone(iRow * ICONE_LARGEUR, iHauteur, ICONE_DOSSIER, pArbreIndSelect->Rechercher(ii));

		int iXNomCentrer = iRow * ICONE_LARGEUR + ((ICONE_LARGEUR / 2) - (LargeurChaine(pCurrent->ObtenirListeDossier()->Obtenir()->ObtenirNom().c_str()) / 2));	//la coordonne en X du nom pour qu'il soit centrer
		if (LargeurChaine(pCurrent->ObtenirListeDossier()->Obtenir()->ObtenirNom().c_str()) <= ICONE_LARGEUR)
			DessinerChaine(pCurrent->ObtenirListeDossier()->Obtenir()->ObtenirNom().c_str(), iXNomCentrer, iHauteur + ICONE_HAUTEUR);
		else
		{
			string strShortName = pCurrent->ObtenirListeDossier()->Obtenir()->ObtenirNom().substr(0, 7) + "...";
			iXNomCentrer = iRow * ICONE_LARGEUR + ((ICONE_LARGEUR / 2) - (LargeurChaine(strShortName.c_str()) / 2));	//la coordonne en X du nom pour qu'il soit centrer
			DessinerChaine(strShortName.c_str(), iXNomCentrer, iHauteur + ICONE_HAUTEUR);
		}

		if (iRow < iNbIconRow)
			iRow++;
		else
		{
			iRow = 0;
			iHauteur += ICONE_HAUTEUR + 15;
		}

		pCurrent->ObtenirListeDossier()->AllerSuivant();
	}
	//afficher les fichier
	for (int ii = 1; ii <= pCurrent->ObtenirListeFichier()->ObtenirCompte(); ii++)
	{
		DessinerIcone(iRow * ICONE_LARGEUR, iHauteur, ICONE_FICHIER, pArbreIndSelect->Rechercher(ii + pCurrent->ObtenirListeDossier()->ObtenirCompte()));

		int iXNomCentrer = iRow * ICONE_LARGEUR + ((ICONE_LARGEUR / 2) - (LargeurChaine(pCurrent->ObtenirListeFichier()->Obtenir()->ObtenirNom().c_str()) / 2));	//la coordonne en X du nom pour qu'il soit centrer
		if (LargeurChaine(pCurrent->ObtenirListeFichier()->Obtenir()->ObtenirNom().c_str()) <= ICONE_LARGEUR)
			DessinerChaine(pCurrent->ObtenirListeFichier()->Obtenir()->ObtenirNom().c_str(), iXNomCentrer, iHauteur + ICONE_HAUTEUR);
		else
		{
			string strShortName = pCurrent->ObtenirListeFichier()->Obtenir()->ObtenirNom().substr(0, 7) + "...";
			iXNomCentrer = iRow * ICONE_LARGEUR + ((ICONE_LARGEUR / 2) - (LargeurChaine(strShortName.c_str()) / 2));
			DessinerChaine(strShortName.c_str(), iXNomCentrer, iHauteur + ICONE_HAUTEUR);
		}

		if (iRow < iNbIconRow)
			iRow++;
		else
		{
			iRow = 0;
			iHauteur += ICONE_HAUTEUR + 15;
		}

		pCurrent->ObtenirListeFichier()->AllerSuivant();
	}
}

/* --------------------------------------------------------------------------------------
 *   Événement exécuté à la fermeture du programme.
 * ----------------------------------------------------------------------------------- */

void OnClose(void) {
	ofstream File;
	File.open("Micro.sam");
	File << pCurrent;
	File.close();

}

/* --------------------------------------------------------------------------------------
 *   Fonction principale du programme.
 * --------------------------------------------------------------------------------------
 *      _NbrParams : Nombre de paramètres passés au programme.
 *   _tabstrParams : Tableau de chaîne de caractères des paramètres passés au programme.
 *          return : Code de fin du programme.
 * ----------------------------------------------------------------------------------- */


int main(int _NbrParams, char* _tabstrParams[]) {
	// Initialisation...
	Init(1024, 768);
	dlgNom = new CMSFVTextBox(pSDLRenderer);
	dlgTexte = new CMSFVMemo(pSDLRenderer);
	mnuContextuel = new CMenu();

	// Exécution...
	OnShow();
	while (Execution());
	OnClose();

	// Conclusion...
	delete mnuContextuel;
	delete dlgTexte;
	delete dlgNom;

	delete pArbreIndSelect;
	//	delete pRacine;
	//	delete pCurrent;

	return 0;
}


/* ------------------------------------ NOTE -------------------------------------
 *	DOSSIER: debut du contenu dossier
 *	REISSOD: fin du contenu dossier
 *	FICHIER: debut du contenu du fichier
 *	REIHCIF: fin du contenu du fichier
 *	HUFFMAN: compression
 *	NAMFFUH: decompression
 * -----------------------------------------------------------------------------*/