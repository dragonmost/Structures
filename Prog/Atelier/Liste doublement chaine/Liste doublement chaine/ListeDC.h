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

	void Ajouter(Type _Element)
	{
		if (m_pPremier == nullptr)
		{
			m_pPremier = new CCelluleListe<Type>(_Element, nullptr, nullptr);
			m_pDernier = m_pPremier;
		}
		else
		{
			CCelluleListe<Type>* pTemp = m_pDernier;
			m_pDernier = new CCelluleListe<Type>(_Element, pTemp, nullptr);
			pTemp->DefinirSuivant(m_pDernier);
		}
		m_uiCompte++;
	}

	bool Inserer(Type _Element, int _Position)
	{
		if (_Position <= m_uiCompte + 1 && _Position >= 1)
		{

			if (_Position <= m_uiCompte / 2)
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
			}
			else
			{
				CCelluleListe<Type>* pTemp = m_pDernier;
				if (_Position == m_uiCompte +1){
					m_pDernier = new CCelluleListe<Type>(_Element, pRunner, nullptr);
					if (m_pPremier == nullptr)
						m_pDernier = m_pPremier;
				}
				else{
					for (int ii = m_uiCompte; ii > _Position - 1; ii--)
						pRunner = pRunner->ObtenirPrecedent();
					pRunner->DefinirSuivant(new CCelluleListe<Type>(_Element, pRunner->ObtenirSuivant()));
					if (_Position == m_uiCompte + 1)
						m_pDernier = pRunner->ObtenirSuivant();
				}
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
			if (_Position <= m_uiCompte / 2)
			{
				CCelluleListe<Type>* pRunner = m_pPremier;
				for (int ii = 1; ii <= _Position - 1; ii++)
					pRunner = pRunner->ObtenirSuivant();
				return pRunner->ObtenirElement();
			}
			else
			{
				CCelluleListe<Type>* pRunner = m_pDernier;
				for (int ii = m_uiCompte; ii > _Position ; ii--)
					pRunner = pRunner->ObtenirPrecedent();
				return pRunner->ObtenirElement();
			}
		}
		else
			return nullptr;
	}

	bool retirer(int _Position)
	{
		
		if (_Position == 1)
		{
			CCelluleListe<Type>* pTemp = m_pPremier;
			m_pPremier = m_pPremier->ObtenirSuivant();
			delete pTemp;
			if (_Position == m_uiCompte)
				m_pDernier = nullptr;
			else
			m_pPremier->m_pPrecedent(nullptr);

			m_uiCompte--;
			return true;
		}
		if (_Position < m_uiCompte && _Position <= (m_uiCompte / 2))
		{
			CCelluleListe<Type>* pRunner = m_pPremier;
			for (int ii = 1; ii < _Position - 1; ii++)
				pRunner = pRunner->ObtenirSuivant();
			CCelluleListe<Type>* pTempS = pRunner->ObtenirSuivant();
			CCelluleListe<Type>* pTempP = pRunner->ObtenirPrecedent();
			pTempS->DefinirPrecedent(pTempP);
			pTempP->DefinirSuivant(pTempS);
			delete pRunner;

			m_uiCompte--;
			return true;
		}
		if (_Position < m_uiCompte && _Position > (m_uiCompte / 2))
		{
			CCelluleListe<Type>* pRunner = m_pDernier;
			for (int ii = m_uiCompte; ii > _Position; ii--)
				pRunner = pRunner->ObtenirPrecedent();
			CCelluleListe<Type>* pTempS = pRunner->ObtenirSuivant();
			CCelluleListe<Type>* pTempP = pRunner->ObtenirPrecedent();
			pTempP->DefinirSuivant(pTempS);
			pTempS->DefinirPrecedent(pTempP);
			delete pRunner;

			m_uiCompte--;
			return true;
		}
		if (_Position == m_uiCompte && _Position != 1)
		{
			CCelluleListe<Type>* pRunner = m_pDernier->DefinirPrecedent();
			CCelluleListe<Type>* pTempQ = m_pDernier;
			pRunner->DefinirSuivant(nullptr);
			m_pDernier = pRunner;
			delete pTemp;

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