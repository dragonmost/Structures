template <class Type>

class CFileCirc{
private:
	CCelluleFile<Type>* m_pQueue;

public:
	CFileCirc(){
		//m_pTete = nullptr;
		m_pQueue = nullptr;
	}

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

	Type Defiler(){
		if (m_pQueue != nullptr){
			CCelluleFile<Type>* pTemp = m_pQueue->ObtenirSuivant();
			Type pTempEle = pTemp->ObtenirElement();
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

	void EnfilerTete(Type _Element){
		if (m_pQueue != nullptr){
			CCelluleFile<Type>* pTemp = m_pQueue->ObtenirSuivant();
			m_pQueue->DefinirSuivant(new CCelluleFile<Type>(_Element, pTemp));
			//m_pQueue->ObtenirSuivant()->DefinirSuivant(pTemp);
		}
		else{
			m_pQueue = new CCelluleFile<Type>(_Element, m_pQueue);
			m_pQueue->DefinirSuivant(m_pQueue);
		}
	}

	Type DefilerQueue(){
		if (m_pQueue != nullptr){
			CCelluleFile<Type>* pRunner = m_pQueue->ObtenirSuivant();
			while (pRunner->ObtenirSuivant() != m_pQueue)
				pRunner = pRunner->ObtenirSuivant();
			Type pTempEle = m_pQueue->ObtenirElement();
			CCelluleFile<Type>* pTempDestroy = m_pQueue;
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
			return nullptr;
	}

	~CFileCirc(){
		while (m_pQueue != nullptr)
			delete Defiler();
	}

};


	
