/*Samuel Baker dragonmost@live.ca
24 septembre 2014
contient la position d'un curseur ainsi que les directions possible pour un deplacement*/

class CPosition{
private:
	int m_ix;	//position en x stocker sur la pile
	int m_iy;	//position en y stocker sur la pile
	bool m_arrboDirection[4];  // North South East West

public:
	//constructeur
	CPosition(int _ix, int _iy, bool _m_boDirection1, bool _m_boDirection2, bool _m_boDirection3, bool _m_boDirection4){
		m_ix = _ix;
		m_iy = _iy;
		m_arrboDirection[0] = _m_boDirection1;
		m_arrboDirection[1] = _m_boDirection2;
		m_arrboDirection[2] = _m_boDirection3;
		m_arrboDirection[3] = _m_boDirection4;
	}

	//accesseur de la position sur l'axe des X
	int ObtenirPosX(){
		return m_ix;
	}

	//accesseur de la position sur l'axe des Y
	int ObtenirPosY(){
		return m_iy;
	}

	//accesseur des direction possible pour un deplacement
	bool ObtenirDirection(int _ii){
		return m_arrboDirection[_ii];
	}

	

};