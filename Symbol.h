#pragma once


class CSymbol: public CBin
{
public:
	enum LabelType {
		NONE,
		DATA_PAGEZERO,
		DATA,
		JUMP,
		BRANCH,
		START
	};
private:
	struct LabelTypeData {
		LabelType m_Type;
		const char* m_pName;
		LabelTypeData()
		{
			m_Type = LabelType::NONE;
			m_pName = 0;
		}
		LabelTypeData(LabelType Type, const char* pName)
		{
			m_Type = Type;
			m_pName = pName;
		}
		const char* GetName() { return m_pName; }
		LabelType GetType() { return m_Type; }
	};
	static inline LabelTypeData LabelTypeLUT[] = {
		{LabelType::NONE , "NONE"},
		{LabelType::DATA_PAGEZERO , "DATA PAGE ZERO"},
		{LabelType::DATA , "DATA"},
		{LabelType::JUMP , "JUMP"},
		{LabelType::BRANCH , "BRANCH"},
		{LabelType::START , "START"},
		{LabelType(-1) , NULL}
	};
	inline static int m_LableCount = 0;
	int m_Address;
	bool m_bPageZero;
	bool m_bUnResolved;
	CSymbol::LabelType m_LabelType;
public:
	CSymbol() {
		m_Address = 0;
		m_bPageZero = false;
		m_bUnResolved = true;
		m_LabelType = CSymbol::LabelType::NONE;
	}
	virtual ~CSymbol() {}
	bool Create() { return true; }
	virtual bool Compare(const char* name, int scope);
	virtual void Print(FILE* pOut);
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
	void SetLableType(CSymbol::LabelType Lt) { m_LabelType = Lt; }
	CSymbol::LabelType GetLabelType() { return m_LabelType; }
	void SetResolved() { m_bUnResolved = false; }
	void SetUnResolved() { m_bUnResolved = true; }
	void SetPageZero(bool tf) { m_bPageZero = tf; }
	bool IsPageZero() { return m_bPageZero; }
	static int GetLabelCount() { return m_LableCount++; }
	char* MakeLabel();
	static const char* LookupLabelType(LabelType Type);
};

