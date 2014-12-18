/*Samuel Baker  it.SamBaker@gmail.com
19 novembre 2014
Arbre binaire*/

template <class Type>

class CArbreBinaire
{
private:
	CNoeud<Type>* m_pRacine;	//pointeur vers le noeud racine de l'arbre


	void Ajouter(Type _Element, CNoeud<Type>* pNoeud)
	{
		if (_Element > pNoeud->ObtenirElement())
			if (pNoeud->ObtenirEnfantDroite() == nullptr)
				pNoeud->DefinirEnfantDroite(new CNoeud<Type>(_Element, pNoeud, nullptr, nullptr));
			else
				Ajouter(_Element, pNoeud->ObtenirEnfantDroite());

		if (_Element < pNoeud->ObtenirElement())
			if (pNoeud->ObtenirEnfantGauche() == nullptr)
				pNoeud->DefinirEnfantGauche(new CNoeud<Type>(_Element, pNoeud, nullptr, nullptr));
			else
				Ajouter(_Element, pNoeud->ObtenirEnfantGauche());
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

	CListSC*	RunPrefix(CNoeud<Type>* _pNoeud, CListSC* _pList)
	{
		_pList->Ajouter(_pNoeud->ObtenirElement());

		if (_pNoeud->ObtenirEnfantGauche())
			RunPrefix(_pNoeud->ObtenirEnfantGauche(), _pList);

		if (_pNoeud->ObtenirEnfantDroite())
			RunPrefix(_pNoeud->ObtenirEnfantDroite(), _pList);

		return _pList;
	}

	CListSC* RunInfix(CNoeud<Type>* _pNoeud, CListSC* _pList)
	{
		if (_pNoeud->ObtenirEnfantGauche() != nullptr)
			RunInfix(_pNoeud->ObtenirEnfantGauche(), _pList);

		_pList->Ajouter(_pNoeud->ObtenirElement());

		if (_pNoeud->ObtenirEnfantDroite() != nullptr)
			RunInfix(_pNoeud->ObtenirEnfantDroite(), _pList);

		return _pList;
	}

	CListSC* RunPostfix(CNoeud<Type>* _pNoeud, CListSC* _pList)
	{
		if (_pNoeud->ObtenirEnfantGauche())
			RunPostfix(_pNoeud->ObtenirEnfantGauche(), _pList);

		if (_pNoeud->ObtenirEnfantDroite())
			RunPostfix(_pNoeud->ObtenirEnfantDroite(), _pList);

		_pList->Ajouter(_pNoeud->ObtenirElement());

		return _pList;
	}

	CListSC* RunLargeur(CFileCirc<CNoeud<Type>*>* _pFile, CListSC* _pList)
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

public:
	CArbreBinaire()
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
				pNoeud->ObtenirEnfantGauche()->DefinirParent(pNoeud->ObtenirParent());
				if (pNoeud == pNoeud->ObtenirParent()->ObtenirEnfantGauche())
					pNoeud->ObtenirParent()->DefinirEnfantGauche(pNoeud->ObtenirEnfantGauche());
				else
					pNoeud->ObtenirParent()->DefinirEnfantDroite(pNoeud->ObtenirEnfantGauche());
				delete pNoeud;
			}
			else if (pNoeud->ObtenirEnfantGauche() == nullptr && pNoeud->ObtenirEnfantDroite() != nullptr)
			{
				pNoeud->ObtenirEnfantDroite()->DefinirParent(pNoeud->ObtenirParent());
				if (pNoeud == pNoeud->ObtenirParent()->ObtenirEnfantGauche())
					pNoeud->ObtenirParent()->DefinirEnfantGauche(pNoeud->ObtenirEnfantDroite());
				else
					pNoeud->ObtenirParent()->DefinirEnfantDroite(pNoeud->ObtenirEnfantDroite());
				delete pNoeud;
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
	CListSC*	RunPrefix()
	{
		CListSC* pList = new CListSC();
		if (m_pRacine)
			return RunPrefix(m_pRacine, pList);
		else
			return pList;
	}

	//Parcour l'arbre avec l'algorithme Infix
	CListSC* RunInfix()
	{
		CListSC* pList = new CListSC();
		if (m_pRacine)
			return RunInfix(m_pRacine, pList);
		else
			return pList;
	}

	//Parcour l'arbre avec l'algorithme Postfix
	CListSC* RunPostfix()
	{
		CListSC* pList = new CListSC();
		if (m_pRacine)
			return RunPostfix(m_pRacine, pList);
		else
			return pList;
	}

	//Parcour l'arbre avec l'algorithme de largeur
	CListSC* RunLargeur()
	{
		CListSC* pList = new CListSC();
		CFileCirc<CNoeud<Type>*>* pFile = new CFileCirc<CNoeud<Type>*>();

		pFile->Enfiler(m_pRacine);

		if (m_pRacine)
			return RunLargeur(pFile, pList);
		else
			return pList;
	}

	~CArbreBinaire()
	{
		while (m_pRacine != nullptr)
			delete retirer(m_pRacine);
	}
};
