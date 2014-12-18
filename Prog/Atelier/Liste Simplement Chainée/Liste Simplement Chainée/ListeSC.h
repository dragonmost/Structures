template <class Type>

class	CListSC
{
private:
	CCelluleListe<Type>* m_pPremier;
	CCelluleListe<Type>* m_pDernier;
	unsigned int m_uiCompte;

public:
	CListSC()
	{
		m_pPremier = nullptr;
		m_pDernier = nullptr;
		m_uiCompte = 0;
	}

	void Ajouter(Type _Element)
	{
		if (m_pPremier != nullptr)
		{
			m_pPremier = new CCelluleListe<Type>(_Element, nullptr);
			m_pDernier = m_pPremier;
		}
		else
		{
			m_pDernier = new CCelluleListe<Type>(_Element, nullptr);
			m_pPremier = m_pDernier;
		}
		m_uiCompte++;
	}

	bool Inserer(Type _Element, int _Position)
	{
		if (_Position <= m_uiCompte+1 && _Position >= 1)
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

	bool retirer(int _Position)
	{
		if (_Position == 1)
		{
			CCelluleListe<Type> pTemp = m_pPremier;
			m_pPremier = m_pPremier->ObtenirSuivant();
			delete pTemp;
		}
		if (_Position <= m_uiCompte && _Position > 1)
		{
			CCelluleListe<Type>* pRunner = m_pPremier;
			for (int ii = 1; ii < _Position - 1; ii++)
				pRunner = pRunner->Obtenirsuivant();
			CCelluleListe<Type>* pTemp = pRunner->ObtenirSuivant();
			pRunner->DefinirSuivant(pTemp->ObtenirSuivant());
			delete pTemp;
			if (_Position == m_uiCompte)
				m_pDernier = pRunner;

			m_uiCompte--;
			return true;
		}
		
		else
			return false;
	}

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