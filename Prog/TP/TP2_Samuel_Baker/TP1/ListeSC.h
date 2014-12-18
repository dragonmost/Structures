/*Samuel Baker dragonmost@live.ca
22 octobre 2014
modification 26 octobre 2014: correction de la methode retirer
Liste Simplement chainer*/


template <class Type>

class	CListSC
{
private:
	CCelluleListe<Type>* m_pPremier;			//pointeur vers le premier objet de la liste
	CCelluleListe<Type>* m_pDernier;			//pointeur vers le dernier objet de la liste
	unsigned int m_uiCompte;					//le nombre d'objet dans la liste

public:
	CListSC()
	{
		m_pPremier = nullptr;
		m_pDernier = nullptr;
		m_uiCompte = 0;
	}

	/*Ajoute un nouvelle element dans la liste
	_Element: le type a mettre dans la liste*/
	void Ajouter(Type _Element)
	{
		if (m_pPremier == nullptr)
		{
			m_pPremier = new CCelluleListe<Type>(_Element, nullptr);
			m_pDernier = m_pPremier;
		}
		else
		{
			CCelluleListe<Type>* pTemp = m_pDernier;
			m_pDernier = new CCelluleListe<Type>(_Element, nullptr);
			pTemp->DefinirSuivant(m_pDernier);
		}
		m_uiCompte++;
	}

	/*Insere une nouvelle element a une position donne dans la liste
	_Element: le type a mettre dans la liste
	_Position: la position ou mettre l'element dans la liste
	retourne une bool pour savoir si on a reussi a inserer*/
	bool Inserer(Type _Element, int _Position)
	{
		if (_Position <= m_uiCompte + 1 && _Position >= 1)
		{

			CCelluleListe<Type>* pRunner = m_pPremier;
			if (_Position == 1){
				m_pPremier = new CCelluleListe<Type>(_Element, pRunner);
				if (pRunner == nullptr)
					m_pDernier = m_pPremier;
			}
			else{
				for (int ii = 1; ii < _Position - 1; ii++)
					pRunner = pRunner->ObtenirSuivant();
				pRunner->DefinirSuivant(new CCelluleListe<Type>(_Element, pRunner->ObtenirSuivant()));
				if (_Position == m_uiCompte + 1)
					m_pDernier = pRunner->ObtenirSuivant();
			}

			m_uiCompte++;
			return true;
		}
		else
			return false;
	}

	/*Obtenir l'element a une position donne
	_Position: la position ou obtenir l'element dans la liste
	retourne un type qui represente l'element dans la liste*/
	Type Obtenir(int _Position)
	{
		if (_Position <= m_uiCompte && _Position >= 1)
		{
			CCelluleListe<Type>* pRunner = m_pPremier;
			for (int ii = 1; ii <= _Position - 1; ii++)
				pRunner = pRunner->ObtenirSuivant();
			return pRunner->ObtenirElement();
		}
		else
			return nullptr;
	}

	/*Retirer l'element a une position donne
	_Position: la position ou retirer l'element dans la liste
	retourne une bool pour savoir si l'element a vraiment été retirer*/
	bool retirer(int _Position)
	{
		
		if (_Position == 1)
		{
			CCelluleListe<Type>* pTemp = m_pPremier;
			m_pPremier = m_pPremier->ObtenirSuivant();
			delete pTemp;
			if (_Position == m_uiCompte)
				m_pDernier = nullptr;

			m_uiCompte--;
			return true;
		}
		if (_Position < m_uiCompte)
		{
			CCelluleListe<Type>* pRunner = m_pPremier;
			for (int ii = 1; ii < _Position - 1; ii++)
				pRunner = pRunner->ObtenirSuivant();
			CCelluleListe<Type>* pTemp = pRunner->ObtenirSuivant();
			pRunner->DefinirSuivant(pTemp->ObtenirSuivant());
			delete pTemp;

			m_uiCompte--;
			return true;
		}
		if (_Position == m_uiCompte && _Position != 1)
		{
			CCelluleListe<Type>* pRunner = m_pPremier;
			while (pRunner->ObtenirSuivant() != m_pDernier)
				pRunner = pRunner->ObtenirSuivant();
			CCelluleListe<Type>* pTemp = pRunner->ObtenirSuivant();
			pRunner->DefinirSuivant(nullptr);
			m_pDernier = pRunner;
			delete pTemp;

			m_uiCompte--;
			return true;
		}

		else
			return false;
	}

	/*retourne le le nombre de cellule dans la liste*/
	unsigned int ObtenirCompte()
	{
		return m_uiCompte;
	}

	~CListSC()
	{
		while (m_pPremier != nullptr)
			retirer(1);
	}
};