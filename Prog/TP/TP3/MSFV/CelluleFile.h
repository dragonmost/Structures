/*Samuel Baker dragonmost@live.ca
6 octobre 2014
Cellule qui contenu dans la File Oriente Objet*/

template <class Type>

class CCelluleFile{
private:
	Type m_pElement;					//donnée membre qui contient les positions
	CCelluleFile<Type>* m_pSuivant;	//donnée membre qui pointe vers la cellule precedente dans la pile

public:
	CCelluleFile(Type _Element, CCelluleFile<Type>* _Suivant){
		m_pElement = _Element;
		m_pSuivant = _Suivant;
	}

	//accesseur du suivant
	CCelluleFile<Type>* ObtenirSuivant(){
		return m_pSuivant;
	}

	//accesseur de l'element
	Type ObtenirElement(){
		return m_pElement;
	}

	//defini la position de l'element suivant
	void DefinirSuivant(CCelluleFile<Type>* _pSuivant){
		m_pSuivant = _pSuivant;
	}

};
