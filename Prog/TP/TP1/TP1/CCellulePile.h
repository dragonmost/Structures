/*Samuel Baker dragonmost@live.ca
24 septembre 2014
Cellule qui contient une position et un pointeur vers la position precedente*/

class CCellulePile{
private:
	CpPersonne m_pElement = nullptr;	//donnée membre qui contient les positions
	CCellulePile* m_pPrecedent = nullptr;	//donnée membre qui pointe vers la cellule precedente dans la pile
	
public:
	//constructeur
	CCellulePile(CPosition* _Element, CCellulePile* _Precedent){
		m_pElement = _Element;
		m_pPrecedent = _Precedent;
	}

	//accesseur du precedent
	CCellulePile* ObtenirPrecedent(){
		return m_pPrecedent;
	}

	//accesseur de l'element
	CPosition* ObtenirElement(){
		return m_pElement;
	}

};
