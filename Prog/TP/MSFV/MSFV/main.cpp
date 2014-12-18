#include "MSFV.h"

/* --------------------------------------------------------------------------------------
 *   Variables globales
 * ----------------------------------------------------------------------------------- */

CMSFVTextBox* dlgNom;	// Boîte de dialogue pour la saisie de nom.
CMSFVMemo* dlgTexte;	// Boîte de dialogue pour la saisie de contenu de fichier texte.
CMenu* mnuContextuel;	// Menu contextuel.

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
}

/* --------------------------------------------------------------------------------------
 *   Événement exécuté lors de l'affichage.
 * ----------------------------------------------------------------------------------- */

void OnRefresh(void) {
}

/* --------------------------------------------------------------------------------------
 *   Événement exécuté à la fermeture du programme.
 * ----------------------------------------------------------------------------------- */

void OnClose(void) {
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
	return 0;
}