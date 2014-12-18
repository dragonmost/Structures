/*Samuel Baker  it.SamBaker@gmail.com
19 novembre 2014
Noeud d'arbre binaire*/

template <class Type>

class CNoeud
{
private:
	Type m_Element;					//valeur du noeud
	CNoeud<Type>* m_pParent;		//pointeur sur le noeud du parent
	CNoeud<Type>* m_pEnfantGauche;	//pointeur sur le noeud de l'enfant de gauche
	CNoeud<Type>* m_pEnfantDroite;	//pointeur sur le noeud de l'enfant de droite 

public:
	/*inialisation des donnée membre de l'Arbre
	_m_Element:	valeur du noeud	
	_m_pParent:	Noeud du parent 
	_m_pEnfantGauche: Noeud de l'Enfant de Gauche
	_m_pEnfantDroite: Noeud de l'Enfant de Droite*/
	CNoeud(Type _m_Element, CNoeud<Type>* _m_pParent, CNoeud<Type>* _m_pEnfantGauche, CNoeud<Type>* _m_pEnfantDroite)
	{
		m_Element = _m_Element;
		m_pParent = _m_pParent;
		m_pEnfantGauche = _m_pEnfantGauche;
		m_pEnfantDroite = _m_pEnfantDroite;
	}

	//Accesseur de l'element
	Type ObtenirElement()
	{
		return m_Element;
	}

	//Accesseur du parent
	CNoeud<Type>* ObtenirParent()
	{
		return m_pParent;
	}

	//Accesseur de l'enfant de gauche
	CNoeud<Type>* ObtenirEnfantGauche()
	{
		return m_pEnfantGauche;
	}

	//Accesseur de l'enfant de droite
	CNoeud<Type>* ObtenirEnfantDroite()
	{
		return m_pEnfantDroite;
	}

	/*Donne une nouvelle valeur a l'element
	_Element: nouvelle valeur de l'element*/
	void DefinirElement(Type _Element)
	{
		m_Element = _Element;
	}

	/*Donne une nouvelle valeur au pointeur du noeud parent
	_Parent: Nouveau parent*/
	void DefinirParent(CNoeud<Type>* _Parent)
	{
		m_pParent = _Parent;
	}

	/*Donne une nouvelle valeur au pointeur du noeud de l'enfant de gauche
	_ElementGauche: nouveau enfant de gauche*/
	void DefinirEnfantGauche(CNoeud<Type>* _EnfantGauche)
	{
		m_pEnfantGauche = _EnfantGauche;
	}

	/*Donne une nouvelle valeur au pointeur du noeud de l'enfant de droite
	_ElementGauche: nouveau enfant de droite*/
	void DefinirEnfantDroite(CNoeud<Type>* _EnfantDroite)
	{
		m_pEnfantDroite = _EnfantDroite;
	}
};