/*Samuel Baker dragonmost@live.ca
22 octobre 2014
Cellule contenu dans la Liste simplement chaine*/

template <class Type>

class CCelluleListe{
private:
	Type m_pElement;					//donnée membre qui contient les positions
	CCelluleListe<Type>* m_pPrecedent;	//donnée membre qui pointe vers la cellule suivante dans la pile
	CCelluleListe<Type>* m_pSuivant;	//donnée membre qui pointe vers la cellule precedente dans la pile

public:
	CCelluleListe(Type _Element,CCelluleListe<Type>* _Precedent,CCelluleListe<Type>* _Suivant){
		m_pElement = _Element;
		m_pPrecedent = _Precedent;
		m_pSuivant = _Suivant;
	}

	//accesseur du suivant
	CCelluleListe<Type>* ObtenirSuivant(){
		return m_pSuivant;
	}

	//accesseur du precedent
	CCelluleListe<Type>* ObtenirPrecedent()
	{
		return m_pPrecedent;
	}

	//accesseur de l'element
	Type ObtenirElement(){
		return m_pElement;
	}

	//defini la position de l'element precedent
	void DefinirPrecedent(CCelluleListe<Type>* _pSuivant){
		m_pPrecedent = m_pPrecedent;
	}

	//defini la position de l'element suivant
	void DefinirSuivant(CCelluleListe<Type>* _pSuivant){
		m_pSuivant = _pSuivant;
	}

};
