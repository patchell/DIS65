#pragma once

class CBin
{
public:
private:
	CBin* m_pNext;
	CBin* m_pPrev;
	CBin* m_pHead;
	CBin* m_pTail;
	char* m_pName;
	char m_strName[MAX_SYMBOL_NAME_LEN];
public:
	CBin() {
		m_pHead = 0;
		m_pTail = 0;
		m_pNext = 0;
		m_pPrev = 0;
		m_pName = new char[MAX_NAME_LEN];
		for (int i = 0; i < MAX_SYMBOL_NAME_LEN; ++i)
			m_strName[i] = 0;
	}
	virtual ~CBin() {
		if (m_pName)
			delete[]m_pName;
	};
	bool Create() { return true; }
	CBin* GetNext() { return m_pNext; }
	void SetNext(CBin* pB) { m_pNext = pB; }
	CBin* GetPrev() { return m_pPrev; }
	void SetPrev(CBin* pB) { m_pPrev = pB; }
	 virtual char* GetName(void) { return m_pName; }
	 virtual void SetName(const char* pName) {
		int l = (int)strlen(pName) + 1;
		if (m_pName) delete m_pName;
		m_pName = new char[l];
		strcpy_s(m_pName, l, pName);
	}
	 virtual bool Compare(const char *name, int aux = 0);
	 virtual void Print(FILE* pOut) = 0;
	 //------------------------------------------
	 // SubList Methods
	 //------------------------------------------
	 void Add(CBin* pSym);
	 void Delete(CBin* pSym);
	 void Unlink(CBin* pSym);
	 inline void SetHead(CBin* pH) { m_pHead = pH; }
	 inline CBin* GetHead() { return m_pHead; }
	 inline void SetTail(CBin* pT) { m_pTail = pT; }
	 inline CBin* GetTail() { return m_pTail; }
};

