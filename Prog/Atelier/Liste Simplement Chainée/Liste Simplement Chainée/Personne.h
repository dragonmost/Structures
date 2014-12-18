/*Samuel Baker dragonmost@live.ca
6 octobre 2014
Objet qui contient des informations sur des personnes. Utilise pour tester la File Orienter Objet*/

class CPersonne{
private:
	char* m_arrchrNom;		//nom d'une personne
	char* m_arrchrPrenom;	//prenom d'une personne
	int m_iAge;				//age d'une personne

public:
	CPersonne(char* _arrchrNom, char* _arrchrPrenom, int _iAge){
		m_arrchrNom = _arrchrNom;
		m_arrchrPrenom = _arrchrPrenom; 
		m_iAge = _iAge;
	}

	//accesseur du nom
	char* ObtenirNom(){
		return m_arrchrNom;
	}

	//accesseur du prenom
	char* ObtenirPrenom(){
		return m_arrchrPrenom;
	}

	//accesseur de lage
	int ObtenirAge(){
		return m_iAge;
	}

};