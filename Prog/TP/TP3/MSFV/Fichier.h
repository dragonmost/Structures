class CFichier
{
private:
	string m_strNom;
	string m_strContent;

public:
	CFichier(string _m_strNom, string _m_strContent)
	{
		m_strNom = _m_strNom;
		m_strContent = _m_strContent;
	}

	string ObtenirNom()
	{
		return m_strNom;
	}

	string ObtenirContent()
	{
		return m_strContent;
	}

	void DefinirNom(string _m_strNom)
	{
		m_strNom = _m_strNom;
	}

	void DefinirContent(string _m_strContent)
	{
		m_strContent = _m_strContent;
	}
};