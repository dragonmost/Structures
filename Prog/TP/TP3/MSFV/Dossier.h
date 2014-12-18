class CDossier
{
private:
	CDossier* m_pParent;
	CListDCwCur<CDossier*>* m_pDossier;
	CListDCwCur<CFichier*>* m_pFichier;
	string m_strNom;

public:
	CDossier(CDossier* _m_pParent, CListDCwCur<CDossier*>* _m_pDossier, 
			CListDCwCur<CFichier*>* _m_pFichier, string _m_strNom)
	{
		m_pParent = _m_pParent;
		m_pDossier = _m_pDossier;
		m_pFichier = _m_pFichier;
		m_strNom = _m_strNom;
	}

	CDossier* ObtenirParent()
	{
		return m_pParent;
	}

	CListDCwCur<CDossier*>* ObtenirListeDossier()
	{
		return m_pDossier;
	}

	CListDCwCur<CFichier*>* ObtenirListeFichier()
	{
		return m_pFichier;
	}

	string ObtenirNom()
	{
		return m_strNom;
	}

	void DefinirParent(CDossier* _m_pParent)
	{
		m_pParent = _m_pParent;
	}

	void DefinirDossier(CListDCwCur<CDossier*>* _m_pDossier)
	{
		m_pDossier = _m_pDossier;
	}

	void DefinirFichier(CListDCwCur<CFichier*>* _m_pFichier)
	{
		m_pFichier = _m_pFichier;
	}

	void DefinirNom(string _m_strNom)
	{
		m_strNom = _m_strNom;
	}

};