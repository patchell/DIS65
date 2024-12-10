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


void CSymbol::Print(FILE* pOut)
{
	fprintf(pOut, "%s:Address=%08lx  Type=%s\n",
		GetName(),
		GetAddress(),
		LookupLabelType(GetLabelType())
	);
}

char* CSymbol::MakeLabel()
{
	int c = 0;

	switch (m_LabelType)
	{
	case CSymbol::LabelType::BRANCH:
		c = 'B';
		break;
	case CSymbol::LabelType::DATA:
		c = 'D';
		break;
	case CSymbol::LabelType::DATA_PAGEZERO:
		c = 'Z';
		break;
	case CSymbol::LabelType::JUMP:
		c = 'L';
		break;
	}
	sprintf_s(GetName(), MAX_SYMBOL_NAME_LEN, "%c%06d", c, CSymbol::GetLabelCount());
	return GetName();
}

const char* CSymbol::LookupLabelType(LabelType Type)
{
	const char* pTypeName = 0;
	bool Loop = true;
	int Index = 0;

	while (Loop)
	{
		if (LabelTypeLUT[Index].GetName())
		{
			if (LabelTypeLUT[Index].GetType() == Type)
			{
				pTypeName = LabelTypeLUT[Index].GetName();
				Loop = false;
			}
			else
				Index++;
		}
		else
			Loop = false;
	}
    return pTypeName;
}
