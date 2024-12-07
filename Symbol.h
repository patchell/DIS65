#pragma once

constexpr auto SYMBOL_SCOPE_ANY = 0;
constexpr auto SYMBOL_SCOPE_GLOBAL = 1;
constexpr auto SYMBOL_SCOPE_LOCAKL = 2;

class CSymbol: public CBin
{
	unsigned m_Address;
	int m_Value;
	int m_Scope;
	bool m_UnResolved;
	//---------------------------
	// Type Chain
	//---------------------------
public:
	CSymbol() {
		m_Address = 0;
		m_Value = 0;
		m_Scope = SYMBOL_SCOPE_ANY;
		m_UnResolved = true;
	}
	virtual ~CSymbol() {}
	bool Create() { return true; }
	virtual bool Compare(const char* name, int scope);
	virtual void Print(FILE* pOut, const char* s);
	//-----------------------------
	// Accessor Methods
	//-----------------------------
	unsigned GetAddress() { return m_Address; }
	void SetAddress(unsigned A) { m_Address = A; }
	int GetValue() { return m_Value; }
	void SetValue(int v) { m_Value = v; }
	int GetScope() { return m_Scope; }
	void SetScope(int S) { m_Scope = S; }
	bool IsUnResolved() {
		return m_UnResolved;
	}
	bool IsResolved() {
		return !m_UnResolved;
	}
	void SetResolved() { m_UnResolved = false; }
	void SetUnResolved() { m_UnResolved = true; }
};

