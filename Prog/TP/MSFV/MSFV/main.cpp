#include "MSFV.h"

/* --------------------------------------------------------------------------------------
 *   Variables globales
 * ----------------------------------------------------------------------------------- */

CMSFVTextBox* dlgNom;	// Bo�te de dialogue pour la saisie de nom.
CMSFVMemo* dlgTexte;	// Bo�te de dialogue pour la saisie de contenu de fichier texte.
CMenu* mnuContextuel;	// Menu contextuel.

/* --------------------------------------------------------------------------------------
 *   �v�nement ex�cut� au d�marrage du programme.
 * ----------------------------------------------------------------------------------- */

void OnShow(void) {
}

/* --------------------------------------------------------------------------------------
 *   �v�nement ex�cut� lors d'un click avec la souris souris.
 * --------------------------------------------------------------------------------------
 *         _iX : Position du click sur l'axe des X.
 *         _iY : Position du click sur l'axe des Y.
 *   _ucBouton : Bouton utilis� pour clicker (BOUTON_GAUCHE, BOUTON_DROITE).
 *     _boCTRL : Si la touche Ctrl du clavier est enfonc�e.
 * ----------------------------------------------------------------------------------- */

void OnMouseClick(int _iX, int _iY, unsigned char _ucBouton, bool _boCTRL) {
}

/* --------------------------------------------------------------------------------------
 *   �v�nement ex�cut� lors de l'affichage.
 * ----------------------------------------------------------------------------------- */

void OnRefresh(void) {
}

/* --------------------------------------------------------------------------------------
 *   �v�nement ex�cut� � la fermeture du programme.
 * ----------------------------------------------------------------------------------- */

void OnClose(void) {
}

/* --------------------------------------------------------------------------------------
 *   Fonction principale du programme.
 * --------------------------------------------------------------------------------------
 *      _NbrParams : Nombre de param�tres pass�s au programme.
 *   _tabstrParams : Tableau de cha�ne de caract�res des param�tres pass�s au programme.
 *          return : Code de fin du programme.
 * ----------------------------------------------------------------------------------- */

int main(int _NbrParams, char* _tabstrParams[]) {
	// Initialisation...
	Init(1024, 768);
	dlgNom = new CMSFVTextBox(pSDLRenderer);
	dlgTexte = new CMSFVMemo(pSDLRenderer);
	mnuContextuel = new CMenu();

	// Ex�cution...
	OnShow();
	while (Execution());
	OnClose();

	// Conclusion...
	delete mnuContextuel;
	delete dlgTexte;
	delete dlgNom;
	return 0;
}