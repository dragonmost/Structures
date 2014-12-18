/*Samuel Baker it.sambaker@gmail.com
1 decembre 2014
Mon beau arbreLineaire roi des forets que j'aime ta tablure e*/

template <class Type>

class CArbreLineaire
{
#define MAXINT 654321		//valeur arbitraire qui represente vide
private:
	Type* m_tabRacine;		//arbre qui est represente par un tableau
	int Grosseur;			//grosseur de l'arbre

public:
	CArbreLineaire(int _Grosseur)
	{
		m_tabRacine = new Type[_Grosseur];
		Grosseur = _Grosseur;
		for (int ii = 0; ii < _Grosseur; ii++)	//boucle pour remplir le tableau de vide
			m_tabRacine[ii] = MAXINT;
	}

	//Ajoute la valeur recu en parametre dans le tableau
	void Ajouter(Type _Element)
	{
		int ii = 0;			//indice pour parcourir le talbeau
		bool Added = false;	//verifie si la valeur a deja ete ajouter
		while ((ii < Grosseur) && (!Added))
		{
			if (m_tabRacine[ii] != MAXINT )
			{
				if (_Element < m_tabRacine[ii])
					ii = ii * 2 + 1;
				else if (_Element > m_tabRacine[ii])
					ii = ii * 2 + 2;
			}
			else
			{
				m_tabRacine[ii] = _Element;
				Added = true;
			}
		}
	}

	//Boolean pour verifier si la valeur recu en parametre est present
	bool Rechercher(Type _Element)
	{
		int ii = 0;		//indice pour parcourir le tableau
		while ((m_tabRacine[ii] != MAXINT) && (ii < Grosseur))
		{
			if (m_tabRacine[ii] != _Element)
			{
				if (_Element < m_tabRacine[ii])
					ii = ii * 2 + 1;
				else if (_Element > m_tabRacine[ii])
					ii = ii * 2 + 2;
			}
			else
				return true;
		}
		return false;
	}

	~CArbreLineaire()
	{
		delete m_tabRacine;
	}
};