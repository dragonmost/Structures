/*Samuel Baker dragonmost@live.ca
24 septembre 2014
Pile oriente objet*/

class CPile{
private:
	CCellulePile* m_pDessus;	//une donnée membre qui contient les données du dessus de la pile

public:
	//constructeur
	CPile(){
		m_pDessus = nullptr;
	}

	//Empile la position dans CCellulePile
	void Empiler(CPosition* _Element){
		m_pDessus = new CCellulePile(_Element, m_pDessus);

	}

	//Depile la position du dessus
	CPosition* Depiler(){
		if (m_pDessus != nullptr){
			CCellulePile* pTempPre = m_pDessus;
			CPosition* pTempEle = m_pDessus->ObtenirElement();

			m_pDessus = pTempPre->ObtenirPrecedent();

			delete pTempPre;
			return pTempEle;
		}
		else{
			return nullptr;
		}
	}

	//destructeur
	~CPile(){
		while (m_pDessus != nullptr){
			delete Depiler();
		}
	}
};