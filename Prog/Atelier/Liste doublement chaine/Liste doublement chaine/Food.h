/*Samuel Baker dragonmost@live.ca
22 octobre 2014
Objet qui contient les informations sur les consommation du snake
position en X et Y	|	Type de consommation
*/

class CFood
{
private:
	int m_iX;		//integer qui represente la position en X de la consommation
	int m_iY;		//integer qui represente la position en Y de la consommation
	char m_chrType;	//integer qui represente le type de la consommation

public:
	CFood(int _iX, int _iY, int _iType)
	{
		m_iX = _iX;
		m_iY = _iY;
		m_chrType = _iType;
	}

	int ObtenirX(){ return m_iX; }
	int ObtenirY(){ return m_iY; }
	char ObtenirType(){ return m_chrType; }
};