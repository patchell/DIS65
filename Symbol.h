#pragma once


class CSymbol: public CBin
{
	inline static int m_LableCount = 0;
	int m_Address;
	bool m_bPageZero;
	bool m_bUnResolved;
public:
	CSymbol() {
		m_Address = 0;
		m_bPageZero = false;
		m_bUnResolved = true;
	}
	virtual ~CSymbol() {}
	bool Create() { return true; }
	virtual bool Compare(const char* name, int scope);
	virtual void Print(FILE* pOut, const char* s);
	//-----------------------------
	// Accessor Methods
	//-----------------------------
	int GetAddress() { return m_Address; }
	void SetAddress(unsigned A) { m_Address = int(A); }
	void SetAddress(int A) { m_Address = A; }
	bool IsUnResolved() {
		return m_bUnResolved;
	}
	bool IsResolved() {
		return !m_bUnResolved;
	}
	void SetResolved() { m_bUnResolved = false; }
	void SetUnResolved() { m_bUnResolved = true; }
	void SetPageZero(bool tf) { m_bPageZero = tf; }
	bool IsPageZero() { return m_bPageZero; }
	static int GetLabelCount() { return m_LableCount++; }
	char* MakeLabel(bool PageZero);
};

