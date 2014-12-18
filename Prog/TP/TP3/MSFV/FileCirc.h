/*Samuel Baker dragonmost@live.ca
6 Octobre 2014
File Circulaire*/


template <class Type>

class CFileCirc{
private:
	CCelluleFile<Type>* m_pQueue;						//pointeur vers le dernier objet de la file

public:
	CFileCirc(){
		m_pQueue = nullptr;
	}

	/*Enfile une nouvelle cellule dans la file
	_Element: un nouveau Type a mettre dans un CCellule*/
	void Enfiler(Type _Element){
		if (m_pQueue == nullptr){
			m_pQueue = new CCelluleFile<Type>(_Element, m_pQueue);
			m_pQueue->DefinirSuivant(m_pQueue);
		}
		else{
			CCelluleFile<Type>* pTemp = m_pQueue->ObtenirSuivant();		//temporaire de tete
			CCelluleFile<Type>* pTempQ = m_pQueue;						//temporaire de queue
			m_pQueue = new CCelluleFile<Type>(_Element, pTemp);
			pTempQ->DefinirSuivant(m_pQueue);
		}
	}

	//Defile et retourne le Type contenu dans le CCellule
	Type Defiler(){
		if (m_pQueue != nullptr){
			CCelluleFile<Type>* pTemp = m_pQueue->ObtenirSuivant();	//temporaire de tete
			Type pTempEle = pTemp->ObtenirElement();				//contient l'element temporairement
			if (m_pQueue->ObtenirSuivant() == m_pQueue)
				m_pQueue = nullptr;
			else
			m_pQueue->DefinirSuivant(pTemp->ObtenirSuivant());
			

			delete pTemp;
			return pTempEle;
		}
		else
			return nullptr;
	}

	/*Enfile à la tête une nouvelle cellule dans la file
	_Element: un nouveau Type a mettre dans un CCellule*/
	void EnfilerTete(Type _Element){
		if (m_pQueue != nullptr){
			CCelluleFile<Type>* pTemp = m_pQueue->ObtenirSuivant();				//temporaire de queue
			m_pQueue->DefinirSuivant(new CCelluleFile<Type>(_Element, pTemp));
			//m_pQueue->ObtenirSuivant()->DefinirSuivant(pTemp);
		}
		else{
			m_pQueue = new CCelluleFile<Type>(_Element, m_pQueue);
			m_pQueue->DefinirSuivant(m_pQueue);
		}
	}

	//Defiler a la tête retourne le type dans la CCellule
	Type DefilerQueue(){
		if (m_pQueue != nullptr){
			CCelluleFile<Type>* pRunner = m_pQueue->ObtenirSuivant();		//temporaire pour parcourir les objets
			while (pRunner->ObtenirSuivant() != m_pQueue)
				pRunner = pRunner->ObtenirSuivant();
			Type pTempEle = m_pQueue->ObtenirElement();						//contient temporairement l'element
			CCelluleFile<Type>* pTempDestroy = m_pQueue;					//temporaire de la queue
			if (m_pQueue == m_pQueue->ObtenirSuivant())
				m_pQueue = nullptr;
			else{
				pRunner->DefinirSuivant(m_pQueue->ObtenirSuivant());
				m_pQueue = pRunner;
			}

			delete pTempDestroy;
			return pTempEle;
		}
		else
			return -1;
	}

	~CFileCirc(){
		while (m_pQueue != nullptr)
			delete Defiler();
	}

};


	
