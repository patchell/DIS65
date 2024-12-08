//------------------------------
// Vanilla Disasembler for the
// 6502
//------------------------------
#include "pch.h"

//--------------------------------
// main
//--------------------------------

int main(int argc, char* argv[])
{
	CDis65 Disasembler;
	int rV = 0;

	fprintf(stderr, "DIS65 Version 0.0.1\n");
	fprintf(stderr, "DIS65: The Vanilla 6502 Disasembler\n");
	fprintf(stderr, "December 6, 2024\n");

	if (argc == 3)
	{
		if (Disasembler.Create(argc, argv))
		{
			Disasembler.Run();
		}
		else
		{
			fprintf(stderr, "Aborted\n");
			rV = 2;
		}
	}
	else
	{
		fprintf(stderr, "Usage: DIS65 <infile> <out file>\n");
		rV = 1;
	}
	return rV;
}


CDis65::CDis65()
{
	m_pBinaryBuffer = 0;
	m_BinBuffSize = 0;
	m_InFileSize = 0;
	m_Index = 0;
	m_pInFile = 0;
	m_pOutFile = 0;
	m_pOut = 0;

}

CDis65::~CDis65()
{
	if (m_pBinaryBuffer) delete[] m_pBinaryBuffer;
}

unsigned CDis65::DisGet()
{
	unsigned rV = 0;

	if (m_Index > 60)
		printf("Hi!\n");
	if (m_Index == m_InFileSize)
		rV = unsigned(-1);
	else
		rV = m_pBinaryBuffer[m_Index++];
	return rV;
}

unsigned CDis65::DisGetInt(int &c)
{
	unsigned rV = 0;
	char* pBin = (char*)&m_pBinaryBuffer[m_Index++];

	if (m_Index == m_InFileSize)
		rV = unsigned(-1);
	else
		c = (int)*pBin;
	return rV;
}

bool CDis65::Create(int argc, char* argv[])
{
	bool rV = true;
	FILE* pIn;
	struct _stat32 FileStats;
	int BytesRead = 0;

	m_pInFile = argv[1];
	m_pOutFile = argv[2];

	//---------------------------------
	// Open Input File
	//---------------------------------
	_stat32(m_pInFile, &FileStats);
	m_BinBuffSize = FileStats.st_size;
	fopen_s(&pIn, m_pInFile, "rb");
	m_pBinaryBuffer = new unsigned char[m_BinBuffSize + 1];
	if (m_pBinaryBuffer && pIn)
		BytesRead = fread(m_pBinaryBuffer, 1, m_BinBuffSize, pIn);
	if (pIn) fclose(pIn);
	if (BytesRead)
	{
		m_InFileSize = BytesRead;
		fprintf(stderr, "%d bytes read from %s\n", m_InFileSize, m_pInFile);
	}
	else
		rV = false;

	if (rV)
	{
		m_SymTab.Create(101);
		fopen_s(&m_pOut, m_pOutFile, "w");
		if (m_pOut == 0)
		{
			fprintf(stderr, "Unable to open %s for output\n", m_pOutFile);
			rV = false;
		}
	}
	return rV;
}

CDis65::Opcode* CDis65::IsThisIt(int c)
{
	int i = 0;
	bool Loop = true;
	Opcode* rV = 0;

	while (Loop)
	{
		if (OpcodeLUT[i].IsTheTheOpcode(c))
		{
			rV = &OpcodeLUT[i];
			Loop = false;
		}
		else
		{
			++i;
			if (OpcodeLUT[i].m_Opcode < 0)
			{
				Loop = false;
			}
		}

	}
	return rV;
}

CSymbol* CDis65::GenerateLabelCanidate(unsigned op)
{
	CSymbol* pLabel = 0;
	Opcode* pOP;
	unsigned High = 0, Low = 0;
	unsigned Address = 0;
	int BranchData = 0;

	pOP = IsThisIt(op);
	switch (pOP->m_ArgType)
	{
	case ArgType::ACCESS_16BITS:
		Low = DisGet();
		High = DisGet();
		Address = Make16BitWord(Low, High);
		if ((pLabel = (CSymbol *)GetSymbolTabel()->FindAddress(Address)) == 0)
		{
			pLabel = new CSymbol;
			pLabel->Create();
			pLabel->SetLableType(CSymbol::LabelTyype::DATA);
			pLabel->MakeLabel();
			pLabel->SetAddress(Address);
			GetSymbolTabel()->AddSymbol(pLabel);
		}
		printf("%s $%04x\n", pLabel->GetName(), pLabel->GetAddress());
		break;
	case ArgType::ACCESS_8BIT:
		Low = DisGet();
		if ((pLabel = (CSymbol*)GetSymbolTabel()->FindAddress(Low)) == 0)
		{
			pLabel = new CSymbol;
			pLabel->Create();
			pLabel->SetLableType(CSymbol::LabelTyype::DATAl_PAGEZERIO);
			pLabel->MakeLabel();
			pLabel->SetAddress(Low);
			GetSymbolTabel()->AddSymbol(pLabel);
		}
		printf("%s $%02x\n", pLabel->GetName(), pLabel->GetAddress());
		break;
	case ArgType::BRANCH:
		DisGetInt(BranchData);
		printf("Branch Data %d\n", BranchData);
		Address = unsigned(m_Index + BranchData);
		pLabel = (CSymbol*)GetSymbolTabel()->FindAddress(Address);
		if (!pLabel)
		{
			pLabel = new CSymbol;
			pLabel->Create();
			pLabel->SetLableType(CSymbol::LabelTyype::BRANCH);
			pLabel->SetAddress(Address);
			pLabel->MakeLabel();
			pLabel->SetAddress(Address);
			printf("Label:%s Address:%d\n", pLabel->GetName(), pLabel->GetAddress());
			GetSymbolTabel()->AddSymbol(pLabel);
			printf("%s $%02x\n", pLabel->GetName(), pLabel->GetAddress());
		}
		break;
	case ArgType::JUMP:
		Low = DisGet();
		High = DisGet();
		Address = Make16BitWord(Low, High);
		if ((pLabel = (CSymbol*)GetSymbolTabel()->FindAddress(Address)) == 0)
		{
			pLabel = new CSymbol;
			pLabel->Create();
			pLabel->SetLableType(CSymbol::LabelTyype::JUMP);
			pLabel->MakeLabel();
			pLabel->SetAddress(Address);
			GetSymbolTabel()->AddSymbol(pLabel);
			printf("%s $%04x\n", pLabel->GetName(), pLabel->GetAddress());
		}
		break;
	case ArgType::RETURN:
		break;
	default:
		m_Index += pOP->m_ByteCount - 1;
		break;
	}
	return pLabel;
}

char* CDis65::CreateAsmInstruction(char* pBuff, int BuffLen, unsigned op)
{
	unsigned LowByte = 0;
	unsigned HighByte = 0;
	unsigned AWord = 0;
	Opcode* pOP;
	CSymbol* pSym = 0;
	char* pS = new char[256];
	int Adr = 0, RelAdr = 0;;

	pOP = IsThisIt(op);
	if (pOP)
	{
		switch (pOP->m_AdressMode)
		{
		case AdrModes::ABSOLUTE:
			LowByte = DisGet();
			HighByte = DisGet();
			AWord = Make16BitWord(LowByte, HighByte);
			if ((pSym = (CSymbol *)GetSymbolTabel()->FindAddress(AWord)) == 0)
			{
				printf("error");
			}
			else
				sprintf_s(pBuff, BuffLen, "\t%s %s", pOP->m_pName, pSym->GetName());
			break;
		case AdrModes::ABSOLUTE_X:
			LowByte = DisGet();
			HighByte = DisGet();
			AWord = Make16BitWord(LowByte, HighByte);
			if ((pSym = (CSymbol*)GetSymbolTabel()->FindAddress(AWord)) == 0)
			{
				printf("error");
			}
			else
				sprintf_s(pBuff, BuffLen, "\t%s %s,X", pOP->m_pName, pSym->GetName());
			break;
		case AdrModes::ABSOLUTE_Y:
			LowByte = DisGet();
			HighByte = DisGet();
			AWord = Make16BitWord(LowByte, HighByte);
			if ((pSym = (CSymbol*)GetSymbolTabel()->FindAddress(AWord)) == 0)
			{
				printf("error");
			}
			else
				sprintf_s(pBuff, BuffLen, "\t%s %s,Y", pOP->m_pName, pSym->GetName());
			break;
		case AdrModes::ZERO_PAGE:
			LowByte = DisGet();
			if ((pSym = (CSymbol*)GetSymbolTabel()->FindAddress(LowByte)) == 0)
			{
				sprintf_s(pBuff, BuffLen, "\t%s $%02x", pOP->m_pName, LowByte);
			}
			else
				sprintf_s(pBuff, BuffLen, "\t%s %s", pOP->m_pName, pSym->GetName());
			break;
		case AdrModes::ZERO_PAGE_X:
			LowByte = DisGet();
			if ((pSym = (CSymbol*)GetSymbolTabel()->FindAddress(AWord)) == 0)
			{
				sprintf_s(pBuff, BuffLen, "\t%s $%02x,X", pOP->m_pName, LowByte);
			}
			else
				sprintf_s(pBuff, BuffLen, "\t%s %s,X", pOP->m_pName, pSym->GetName());
			break;
		case AdrModes::ZERO_PAGE_Y:
			LowByte = DisGet();
			if ((pSym = (CSymbol*)GetSymbolTabel()->FindAddress(LowByte)) == 0)
			{
				sprintf_s(
					pBuff, 
					BuffLen, 
					"\t%s %s,Y", 
					pOP->m_pName, 
					LowByte);
			}
			else
			{
				sprintf_s(pBuff, BuffLen, "\t%s %s,Y", pOP->m_pName, pSym->GetName());
			}
			break;
		case AdrModes::ZERO_PAGE_INDEXED_INDIRECT_X:
			LowByte = DisGet();
			if ((pSym = (CSymbol*)GetSymbolTabel()->FindAddress(LowByte)) == 0)
			{
				sprintf_s(pBuff, BuffLen, "\t%s ($%02x,X)", pOP->m_pName, LowByte);
			}
			else
			{
				sprintf_s(pBuff, BuffLen, "\t%s (%s,X)", pOP->m_pName, pSym->GetName());
			}
			break;
		case AdrModes::ZERO_PAGE_INDIRECT_INDEXED_Y:
			LowByte = DisGet();
			if ((pSym = (CSymbol*)GetSymbolTabel()->FindAddress(LowByte)) == 0)
			{
				sprintf_s(pBuff, BuffLen, "\t%s ($%02x),Y", pOP->m_pName, LowByte);
			}
			else
			{
				sprintf_s(pBuff, BuffLen, "\t%s (%s),y", pOP->m_pName, pSym->GetName());
			}
			break;
		case AdrModes::IMMEDIATE:
			LowByte = DisGet();
			sprintf_s(pBuff, BuffLen, "\t%s #%02x", pOP->m_pName, LowByte);
			break;
		case AdrModes::IMPLIED:
			sprintf_s(pBuff, BuffLen, "\t%s", pOP->m_pName);
			break;
		case AdrModes::INDIRECT:
			LowByte = DisGet();
			HighByte = DisGet();
			AWord = Make16BitWord(LowByte, HighByte);
			sprintf_s(pBuff, BuffLen, "\t%s ($%04x)", pOP->m_pName, AWord);
			break;
		case AdrModes::RELATIVE:
//			Adr = m_Index;
			DisGetInt(RelAdr);
			Adr =  m_Index + RelAdr;
			printf("Relative Address %d\n", Adr);
			pSym = (CSymbol*)GetSymbolTabel()->FindAddress(Adr);
			if (pSym)
			{
				sprintf_s(pBuff, BuffLen, "\t%s %s", pOP->m_pName, pSym->GetName());
			}
			else
			{
				sprintf_s(pBuff, BuffLen, "\t%s $%02x", pOP->m_pName, RelAdr);
			}
			break;
		case AdrModes::ACCUMULATOR:
			sprintf_s(pBuff, BuffLen, "\t%s A", pOP->m_pName);
			break;
		case AdrModes::NONE:
			break;
		default:
			break;
		}
	}
	delete[] pS;
	return pBuff;
}

int CDis65::Run()
{
	int c;
	bool Loop = true;
	char* pOutString = 0;
	int Adr = 0;
	CSymbol* pLabel = 0;

	while ((c = DisGet()) != EOF)
	{
		GenerateLabelCanidate(c);
	}
	m_Index = 0;
	pOutString = new char[256];
	while (Loop)
	{
		Adr = m_Index;
		pLabel = (CSymbol*)GetSymbolTabel()->FindAddress(Adr);
		c = DisGet();
		if (c == EOF)
			Loop = false;
		else
		{
			if (pLabel)
				fprintf(m_pOut, "%s %s\n", pLabel->GetName(), CreateAsmInstruction(pOutString, 256, c));
			else
				fprintf(m_pOut, "%s\n", CreateAsmInstruction(pOutString, 256, c));
		}
	}
	delete[] pOutString;

	return 0;
}

