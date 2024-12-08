#include "pch.h"

bool CSymbol::Compare(const char* name, int scope)
{
	bool rV = false;

	if (strcmp(GetName(), name) == 0)
	{
		rV = true;
	}
	return rV;
}


void CSymbol::Print(FILE* pOut, const char* s)
{
	//fprintf(pOut, "%s:Address=%08lx  Value=%04x  Scope=%d\n",
	//	GetName(),
	//	GetAddress(),
	//	GetValue(),
	//	GetScope()
	//);
}

char* CSymbol::MakeLabel( bool PageZero)
{
	m_bPageZero = PageZero;
	sprintf_s(GetName(), MAX_SYMBOL_NAME_LEN, "%c%06d", PageZero ? 'Z' : 'L', CSymbol::GetLabelCount());
	return GetName();
}
