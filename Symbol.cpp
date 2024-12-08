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

char* CSymbol::MakeLabel()
{
	int c = 0;

	switch (m_LabelType)
	{
	case CSymbol::LabelTyype::BRANCH:
		c = 'B';
		break;
	case CSymbol::LabelTyype::DATA:
		c = 'D';
		break;
	case CSymbol::LabelTyype::DATAl_PAGEZERIO:
		c = 'Z';
		break;
	case CSymbol::LabelTyype::JUMP:
		c = 'L';
		break;
	}
	sprintf_s(GetName(), MAX_SYMBOL_NAME_LEN, "%c%06d", c, CSymbol::GetLabelCount());
	return GetName();
}
