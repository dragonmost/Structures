/*Samuel Baker dragonmost@live.ca
22 octobre 2014
Objet qui contient les informations sur le corps du snake
position en X et Y
*/


class CSnake
{
private:
	int m_iX;	//integer qui represente la position en X du snake 
	int m_iY;	//integer qui represente la position en Y du snake

public:
	CSnake(int _iX, int _iY)
	{
		m_iX = _iX;
		m_iY = _iY;
	}

	//Obtenir la valeur de X 
	int ObtenirX()
	{ 
		return m_iX; 
	}

	//Obtenir la valeur de Y
	int ObtenirY()
	{ 
		return m_iY; 
	}
};