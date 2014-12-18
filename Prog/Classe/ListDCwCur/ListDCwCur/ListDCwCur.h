/*Samuel Baker it.sambaker@gmail.com
derniere modification: 1 decembre 2014
Liste doublement chainée avec curseur implicite*/

template <class Type>

class CListDCwCur
{
private:
	CCelluleListe<Type>* m_pPremier;	//pointeur vers le premier element de la liste
	CCelluleListe<Type>* m_pDernier;	//pointeur vers le dernier element de la liste
	CCelluleListe<Type>* m_pCurseur;	//pointeur qui ce deplace et sert de curseur pour la liste
	unsigned int m_uiCompte;			//compteur du nombre d'element dans la liste

public:
	CListDCwCur()
	{
		m_pPremier = nullptr;
		m_pDernier = nullptr;
		m_pCurseur = nullptr;
		m_uiCompte = 0;
	}

	//deplace le curseur a la premiere indice de la liste
	bool AllerPremier()
	{
		if (m_pPremier != nullptr)
		{
			m_pCurseur = m_pPremier;
			return true;
		}
		else
			return false;
	}

	//deplace le curseur a la derniere indice de la liste
	bool AllerDernier()
	{
		if (m_pDernier != nullptr)
		{
			m_pCurseur = m_pDernier;
			return true;
		}
		else
			return false;
	}

	//deplace le curseur vers l'indice suivant de la liste
	bool AllerSuivant()
	{
		if (m_pCurseur != nullptr && m_pCurseur->ObtenirSuivant() != nullptr)
		{
			m_pCurseur = m_pCurseur->ObtenirSuivant();
			return true;
		}
		else
			return false;
	}

	//deplace le curseur vers l'indice suivant de la liste
	bool AllerPrecedent()
	{
		if (m_pCurseur != nullptr && m_pCurseur->ObtenirPrecedent() != nullptr)
		{
			m_pCurseur = m_pCurseur->ObtenirPrecedent();
			return true;
		}
		else
			return false;
	}

	//deplace le curseur vers l'indice de la liste recu en parametre
	bool AllerA(int _Pos)
	{
		if (_Pos <= (m_uiCompte / 2))
		{
			m_pCurseur = m_pPremier;
			for (int ii = 1; ii < _Pos - 1; i++)
				m_pCurseur = m_pCurseur->ObtenirSuivant();

			return true;
		}
		if (_Pos >(m_uiCompte / 2))
		{
			m_pCurseur = m_pDernier;
			for (int ii = m_uiCompte; ii > _Position; i--)
				m_pCurseur = m_pCurseur->ObtenirPrecedent();

			return true;
		}
		else
			return false;
	}

	/*Ajouter une valeur dans la liste 
	_Element: la valeur a ajouter dans la liste*/
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

	/*Ajouter une valeur dans la liste a l'emplacement du curseur
	_Element: la valeur a ajouter dans la liste*/
	bool Inserer(Type _Element)
	{
		if (m_pCurseur != nullptr)
		{
			CCelluleListe<Type>* pTempP = m_pCurseur->ObtenirPrecedent();
			CCelluleListe<Type>* pTempS = m_pCurseur->ObtenirSuivant();
			if (m_pCurseur == m_pPremier)
			{
				m_pCurseur = new CCelluleListe<Type>(_Element, pTempP, pTempS);
				m_pPremier = m_pCurseur;
				pTempS->DefinirPrecedent(m_pCurseur);
			}

			else if (m_pCurseur == m_pDernier)
			{
				m_pCurseur = new CCelluleListe<Type>(_Element, pTempP, pTempS);
				m_pDernier = m_pCurseur;
				pTempP->DefinirSuivant(m_pCurseur);
			}

			else if (m_pCurseur != m_pPremier && m_pCurseur != m_pDernier)
			{
				m_pCurseur = new CCelluleListe<Type>(_Element, pTempP, pTempS);
				pTempP->DefinirSuivant(m_pCurseur);
				pTempS->DefinirPrecedent(m_pCurseur);
			}
			m_uiCompte++;
			return true;
		}
		else
			return false;
	}

	/*Retirer l'element pointer par le curseur*/
	bool Retirer()
	{
		if (m_pCurseur != nullptr)
		{
			if (m_pCurseur == m_pDernier)
			{
				CCelluleListe<Type>* pTemp = m_pCurseur;
				m_pCurseur = pTemp->ObtenirPrecedent();
				m_pCurseur->DefinirSuivant(nullptr);
				m_pDernier = m_pCurseur;

				delete pTemp;

				return true;
			}
			/*else
			{
				CCelluleListe<Type>* pTemp = m_pCurseur;
				m_pCurseur = m_pCurseur->ObtenirSuivant();
				if (pTemp == m_pPremier)
				{
					m_pCurseur->DefinirPrecedent(nullptr);
					m_pPremier = m_pCurseur;
					delete pTemp;
					return true;
				}
				else
				{
					CCelluleListe<Type>* pTempQ = pTemp->ObtenirPrecedent();
					pTempQ->DefinirSuivant(m_pCurseur);
					m_pCurseur->DefinirPrecedent(pTempQ);
					delete pTemp;
					return true;
				}
			}*/
			else if (m_pCurseur == m_pPremier)
			{
				CCelluleListe<Type>* pTemp = m_pCurseur;
				m_pPremier = m_pPremier->ObtenirSuivant();
				m_pPremier->DefinirPrecedent(nullptr);
				m_pCurseur = m_pPremier;

				delete pTemp;
				return true;
			}
			else
			{
				CCelluleListe<Type>* pTemp = m_pCurseur;
				m_pCurseur->ObtenirPrecedent()->DefinirSuivant(m_pCurseur->ObtenirSuivant());
				m_pCurseur->ObtenirSuivant()->DefinirPrecedent(m_pCurseur->ObtenirPrecedent());
				m_pCurseur = m_pCurseur->ObtenirPrecedent();

				delete pTemp;
				return true;
			}
			m_uiCompte--;
		}
		else
			return false;
	}

	/*Retourne la valeur contenu dans la cellule pointer par le curseur*/
	Type Obtenir()
	{
		if (m_pCurseur != nullptr)
			return m_pCurseur->ObtenirElement();
		else
			return nullptr;
	}

	//retourn le nombre d'element dans la liste
	unsigned int ObtenirCompte()
	{
		return m_uiCompte;
	}

	~CListDCwCur()
	{

	}

};

