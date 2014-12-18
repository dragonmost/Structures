/*Samuel Baker  it.SamBaker@gmail.com
derniere modification 3 decembre 2014
Arbre binaire*/

template <class Type>

class CArbreAVL
{
private:
	CNoeud<Type>* m_pRacine;	//pointeur vers le noeud racine de l'arbre


	void Ajouter(Type _Element, CNoeud<Type>* _pNoeud)
	{
		if (_Element > _pNoeud->ObtenirElement())
			if (_pNoeud->ObtenirEnfantDroite() == nullptr)
				_pNoeud->DefinirEnfantDroite(new CNoeud<Type>(_Element, _pNoeud, nullptr, nullptr));
			else
				Ajouter(_Element, _pNoeud->ObtenirEnfantDroite());

		if (_Element < _pNoeud->ObtenirElement())
			if (_pNoeud->ObtenirEnfantGauche() == nullptr)
				_pNoeud->DefinirEnfantGauche(new CNoeud<Type>(_Element, _pNoeud, nullptr, nullptr));
			else
				Ajouter(_Element, _pNoeud->ObtenirEnfantGauche());

		//		int	iProfondeurGauche = 0;
		//		int iProfondeurDroite = 0;
		//		if (_pNoeud->ObtenirEnfantGauche())
		//			iProfondeurGauche = CalcProfond(_pNoeud->ObtenirEnfantGauche());	//indice de la profondeur de Gauche du noeud
		//		if (_pNoeud->ObtenirEnfantDroite())
		//			iProfondeurDroite = CalcProfond(_pNoeud->ObtenirEnfantDroite());	//indice de la profondeur de Droite du noeud
		//
		//		//Rotation vers la Gauche
		//		if (iProfondeurDroite - iProfondeurGauche == 2)
		//		{
		//			CNoeud<Type>* pNewRacine = _pNoeud->ObtenirEnfantDroite();
		//			pNewRacine->DefinirParent(_pNoeud->ObtenirParent());
		//			if (_pNoeud->ObtenirParent() && _pNoeud->ObtenirParent()->ObtenirEnfantDroite())
		//				_pNoeud->ObtenirParent()->DefinirEnfantDroite(pNewRacine);
		//			else if (_pNoeud->ObtenirParent() && _pNoeud->ObtenirParent()->ObtenirEnfantGauche())
		//				_pNoeud->ObtenirParent()->DefinirEnfantGauche(pNewRacine);
		//			
		//			_pNoeud->DefinirEnfantDroite(pNewRacine->ObtenirEnfantGauche());
		//			if (_pNoeud->ObtenirEnfantDroite())
		//				_pNoeud->ObtenirEnfantDroite()->DefinirParent(_pNoeud);
		//			_pNoeud->DefinirParent(pNewRacine);
		//
		//
		//			//_pNoeud->DefinirParent(pNewRacine);
		//			//_pNoeud->DefinirEnfantDroite(pNewRacine->ObtenirEnfantGauche());
		//			//pNewRacine->DefinirEnfantGauche(_pNoeud);
		//			//pNewRacine->ObtenirEnfantGauche()->DefinirParent(_pNoeud);
		//		}
		//		//Rotation vers la Droite
		//		else if (iProfondeurDroite - iProfondeurGauche == -2)
		//		{
		//			iProfondeurDroite++;
		//		}

	}

	CNoeud<Type>* Rechercher(Type _Element, CNoeud<Type>* pNoeud)
	{
		if (_Element == pNoeud->ObtenirElement())
			return pNoeud;
		if (_Element > pNoeud->ObtenirElement() && pNoeud->ObtenirEnfantDroite() != nullptr)
			return Rechercher(_Element, pNoeud->ObtenirEnfantDroite());
		if (_Element < pNoeud->ObtenirElement() && pNoeud->ObtenirEnfantGauche() != nullptr)
			return Rechercher(_Element, pNoeud->ObtenirEnfantGauche());

		return nullptr;
	}

	CListDCwCur<Type>* RunPrefix(CNoeud<Type>* _pNoeud, CListDCwCur<Type>* _pList)
	{
		_pList->Ajouter(_pNoeud->ObtenirElement());

		if (_pNoeud->ObtenirEnfantGauche())
			RunPrefix(_pNoeud->ObtenirEnfantGauche(), _pList);

		if (_pNoeud->ObtenirEnfantDroite())
			RunPrefix(_pNoeud->ObtenirEnfantDroite(), _pList);

		return _pList;
	}

	CFileCirc<Type>* RunInfix(CNoeud<Type>* _pNoeud, CFileCirc<Type>* _pFile)
	{
		if (_pNoeud->ObtenirEnfantGauche() != nullptr)
			RunInfix(_pNoeud->ObtenirEnfantGauche(), _pFile);

		_pFile->Enfiler(_pNoeud->ObtenirElement());

		if (_pNoeud->ObtenirEnfantDroite() != nullptr)
			RunInfix(_pNoeud->ObtenirEnfantDroite(), _pFile);

		return _pFile;
	}

	CListDCwCur<Type>* RunPostfix(CNoeud<Type>* _pNoeud, CListDCwCur<Type>* _pList)
	{
		if (_pNoeud->ObtenirEnfantGauche())
			RunPostfix(_pNoeud->ObtenirEnfantGauche(), _pList);

		if (_pNoeud->ObtenirEnfantDroite())
			RunPostfix(_pNoeud->ObtenirEnfantDroite(), _pList);

		_pList->Ajouter(_pNoeud->ObtenirElement());

		return _pList;
	}

	CListDCwCur<Type>* RunLargeur(CFileCirc<CNoeud<Type>*>* _pFile, CListDCwCur<Type>* _pList)
	{

		CNoeud<Type>* pNoeud = _pFile->Defiler();
		if (pNoeud)
		{
			_pList->Ajouter(pNoeud->ObtenirElement());

			if (pNoeud->ObtenirEnfantGauche())
				_pFile->Enfiler(pNoeud->ObtenirEnfantGauche());
			if (pNoeud->ObtenirEnfantDroite())
				_pFile->Enfiler(pNoeud->ObtenirEnfantDroite());

			RunLargeur(_pFile, _pList);
		}

		return _pList;
	}

	int CalcProfond(CNoeud<Type>* _pNoeud)
	{

		int iProfondeurGauche = 0;	//indice de la profondeur de Gauche
		int iProfondeurDroite = 0;	//indice de la profondeur de Droite


		if (_pNoeud->ObtenirEnfantGauche())
			iProfondeurGauche = CalcProfond(_pNoeud->ObtenirEnfantGauche());
		if (_pNoeud->ObtenirEnfantDroite())
			iProfondeurDroite = CalcProfond(_pNoeud->ObtenirEnfantDroite());

		if (iProfondeurGauche > iProfondeurDroite)
			return iProfondeurGauche + 1;
		else if (iProfondeurGauche < iProfondeurDroite)
			return iProfondeurDroite + 1;
		else
			return 1;

	}

public:
	CArbreAVL()
	{
		m_pRacine = nullptr;
	}

	/*Ajoute un element a l'Arbre
	_Element: la valeur de l'element a ajouter*/
	void Ajouter(Type _Element)
	{
		if (m_pRacine == nullptr)
			m_pRacine = new CNoeud<Type>(_Element, nullptr, nullptr, nullptr);
		else
			Ajouter(_Element, m_pRacine);

	}

	/*rechercher dans l'arbre si une valeur existe
	_Element: la valeur rechercher*/
	bool Rechercher(Type _Element)
	{
		if (m_pRacine == nullptr)
			return false;
		else
			if (Rechercher(_Element, m_pRacine) != nullptr)
				return true;
			else
				return false;
	}

	/*retire un Noeud de l'arbre sans defaire sa structure
	_Element: la valeur du noeud a retirer*/
	void Retirer(Type _Element)
	{
		CNoeud<Type>* pNoeud = Rechercher(_Element, m_pRacine);	//le noeud a retirer

		if (pNoeud != nullptr)	//verifie si le noeud existe
		{
			//retirer avec aucun enfant
			if (pNoeud->ObtenirEnfantGauche() == nullptr && pNoeud->ObtenirEnfantDroite() == nullptr)
			{
				if (pNoeud == m_pRacine)
				{
					m_pRacine = nullptr;
					delete pNoeud;
				}
				else
				{
					if (pNoeud->ObtenirParent()->ObtenirEnfantGauche() == pNoeud)
						pNoeud->ObtenirParent()->DefinirEnfantGauche(nullptr);
					else
						pNoeud->ObtenirParent()->DefinirEnfantDroite(nullptr);
					delete pNoeud;
				}
			}

			//retirer avec 1 enfant			
			else if (pNoeud->ObtenirEnfantGauche() != nullptr && pNoeud->ObtenirEnfantDroite() == nullptr)
			{
				if (pNoeud == m_pRacine)
				{
					m_pRacine->DefinirElement(pNoeud->ObtenirEnfantGauche()->ObtenirElement());
					pNoeud = pNoeud->ObtenirEnfantGauche();
					Retirer(pNoeud->ObtenirElement());
				}
				else
				{
					pNoeud->ObtenirEnfantGauche()->DefinirParent(pNoeud->ObtenirParent());
					if (pNoeud == pNoeud->ObtenirParent()->ObtenirEnfantGauche())
						pNoeud->ObtenirParent()->DefinirEnfantGauche(pNoeud->ObtenirEnfantGauche());
					else
						pNoeud->ObtenirParent()->DefinirEnfantDroite(pNoeud->ObtenirEnfantGauche());
					delete pNoeud;
				}
			}
			else if (pNoeud->ObtenirEnfantGauche() == nullptr && pNoeud->ObtenirEnfantDroite() != nullptr)
			{
				if (pNoeud == m_pRacine)
				{
					m_pRacine->DefinirElement(pNoeud->ObtenirEnfantDroite()->ObtenirElement());
					pNoeud = pNoeud->ObtenirEnfantDroite();
					Retirer(pNoeud->ObtenirElement());
				}
				else
				{
					pNoeud->ObtenirEnfantDroite()->DefinirParent(pNoeud->ObtenirParent());
					if (pNoeud == pNoeud->ObtenirParent()->ObtenirEnfantGauche())
						pNoeud->ObtenirParent()->DefinirEnfantGauche(pNoeud->ObtenirEnfantDroite());
					else
						pNoeud->ObtenirParent()->DefinirEnfantDroite(pNoeud->ObtenirEnfantDroite());
					delete pNoeud;
				}
			}


			//retirer avec 2 enfants
			else
			{
				CNoeud<Type>* pTemp = pNoeud;	//valeur temporaire qui va prendre la place de la valeur a retirer
				while (pTemp->ObtenirEnfantDroite() != nullptr)
					pTemp = pTemp->ObtenirEnfantDroite();

				pNoeud->DefinirElement(pTemp->ObtenirElement());

				/*if (pTemp->ObtenirParent()->ObtenirEnfantGauche() == pTemp)
					pTemp->ObtenirParent()->DefinirEnfantGauche(nullptr); //a corriger
					else
					pTemp->ObtenirParent()->DefinirEnfantDroite(nullptr);*/

				if (pTemp->ObtenirParent()->ObtenirEnfantGauche() == pTemp)
					pTemp->ObtenirParent()->DefinirEnfantGauche(nullptr);
				if (pTemp->ObtenirParent()->ObtenirEnfantGauche())
					pTemp->ObtenirParent()->DefinirEnfantGauche(pTemp->ObtenirEnfantGauche());

				pTemp->ObtenirParent()->DefinirEnfantDroite(nullptr);

				delete pTemp;
			}
		}
	}

	//Parcour l'arbre avec l'algorithme Prefix
	CListDCwCur<Type>*	RunPrefix()
	{
		CListDCwCur* pList = new CListSC();
		if (m_pRacine)
			return RunPrefix(m_pRacine, pList);
		else
			return pList;
	}

	//Parcour l'arbre avec l'algorithme Infix
	CFileCirc<Type>* RunInfix()
	{
		CFileCirc<Type>* pFile = new CFileCirc<Type>();
		if (m_pRacine)
			return RunInfix(m_pRacine, pFile);
		else
			return pFile;
	}

	//Parcour l'arbre avec l'algorithme Postfix
	CListDCwCur<Type>* RunPostfix()
	{
		CListDCwCur* pList = new CListDCwCur();
		if (m_pRacine)
			return RunPostfix(m_pRacine, pList);
		else
			return pList;
	}

	//Parcour l'arbre avec l'algorithme de largeur
	CListDCwCur<Type>* RunLargeur()
	{
		CListDCwCur* pList = new CListDCwCur();
		CFileCirc<CNoeud<Type>*>* pFile = new CFileCirc<CNoeud<Type>*>();

		pFile->Enfiler(m_pRacine);

		if (m_pRacine)
			return RunLargeur(pFile, pList);
		else
			return pList;
	}

	~CArbreAVL()
	{
		while (m_pRacine != nullptr)
		{
			Retirer(m_pRacine->ObtenirElement());
		}
	}
};
