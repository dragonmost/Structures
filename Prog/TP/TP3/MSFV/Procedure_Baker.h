void QuickSortDossier(int _iMin, int _iMax, CListDCwCur<CDossier*>* Liste)
{
	int iGauche = _iMin;
	int iDroite = _iMax;
	int iPivot = _iMin;

	while (iDroite != iGauche)
	{
		Liste->AllerA(iGauche);
		string strNomGauche = Liste->Obtenir()->ObtenirNom();
		Liste->AllerA(iDroite);
		string strNomDroite = Liste->Obtenir()->ObtenirNom();
		
		if (strNomGauche > strNomDroite)
		{
			Liste->AllerA(iGauche);
			Liste->Obtenir()->DefinirNom(strNomDroite);
			Liste->AllerA(iDroite);
			Liste->Obtenir()->DefinirNom(strNomGauche);

			iPivot = iGauche + iDroite - iPivot;
		}



		if (iPivot == iGauche)
			iDroite--;
		else
			iGauche++;
	}

	if (_iMin < iPivot - 1)
	{
		 QuickSortDossier(_iMin, iPivot - 1, Liste);
	}
	if (_iMax > iPivot + 1)
	{
		 QuickSortDossier(iPivot + 1, _iMax, Liste);
	}
}

void QuickSortFichier(int _iMin, int _iMax, CListDCwCur<CFichier*>* Liste)
{
	int iGauche = _iMin;
	int iDroite = _iMax;
	int iPivot = _iMin;

	while (iDroite != iGauche)
	{
		Liste->AllerA(iGauche);
		string strNomGauche = Liste->Obtenir()->ObtenirNom();
		Liste->AllerA(iDroite);
		string strNomDroite = Liste->Obtenir()->ObtenirNom();

		if (strNomGauche > strNomDroite)
		{
			Liste->AllerA(iGauche);
			Liste->Obtenir()->DefinirNom(strNomDroite);
			Liste->AllerA(iDroite);
			Liste->Obtenir()->DefinirNom(strNomGauche);

			iPivot = iGauche + iDroite - iPivot;
		}



		if (iPivot == iGauche)
			iDroite--;
		else
			iGauche++;
	}

	if (_iMin < iPivot - 1)
	{
		QuickSortFichier(_iMin, iPivot - 1, Liste);
	}
	if (_iMax > iPivot + 1)
	{
		QuickSortFichier(iPivot + 1, _iMax, Liste);
	}
}