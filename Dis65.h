#pragma once

class CDis65
{
	char* m_BinaryBuffer;
public:
	enum class AdrModes {
		NONE,
		IMMEDIATE,
		ABSOLUTE,
		ZERO_PAGE,
		IMPLIED,
		INDIRECT,
		ABSOLUTE_X,
		ABSOLUTE_Y,
		ZERO_PAGE_X,
		ZERO_PAGE_Y,
		ZERO_PAGE_INDEXED_INDIRECT_X,
		ZERO_PAGE_INDIRECT_INDEXED_Y,
		RELATIVE,
		ACCUMULATOR
	};
	struct Opcode {
		int m_Opcode;
		const char* m_pName;
		int m_ByteCount;
		const char* m_pArgString;
		AdrModes m_AdressMode;
		Opcode() {
			m_Opcode = 0;
			m_pName = 0;
			m_ByteCount = 0;
			m_pArgString = 0;
			m_AdressMode = AdrModes::NONE;
		}
		Opcode(
			int op,
			const char* pName,
			int ByteCnt,
			const char* pArgStr,
			AdrModes AdrMode
		)
		{
			m_Opcode = op;
			m_pName = pName;
			m_ByteCount = ByteCnt;
			m_pArgString = pArgStr;
			m_AdressMode = AdrMode;
		}
		bool IsTheTheOpcode(int op)
		{
			return (op == m_Opcode);
		}
	};
private:
	inline static Opcode OpcodeLUT[] = {
		{0x69,"ADC",2,"#$%02x", AdrModes::IMMEDIATE},
		{0x65,"ADC",2,"%s", AdrModes::ZERO_PAGE},
		{0x75,"ADC",2,"", AdrModes::ZERO_PAGE_X},
		{0x6D,"ADC",3,"", AdrModes::ABSOLUTE},
		{0x7D,"ADC",3,"", AdrModes::ABSOLUTE_X},
		{0x79,"ADC",3,"", AdrModes::ABSOLUTE_Y},
		{0x61,"ADC",2,"", AdrModes::ZERO_PAGE_INDEXED_INDIRECT_X},
		{0x71,"ADC",2,"", AdrModes::ZERO_PAGE_INDIRECT_INDEXED_Y},
		//-----------------------------------------
		{0x29,"AND",2,"#$%02x", AdrModes::IMMEDIATE},
		{0x25,"AND",2,"", AdrModes::ZERO_PAGE},
		{0x35,"AND",2,"", AdrModes::ZERO_PAGE_X},
		{0x2D,"AND",3,"", AdrModes::ABSOLUTE},
		{0x3D,"AND",3,"", AdrModes::ABSOLUTE_X},
		{0x39,"AND",3,"", AdrModes::ABSOLUTE_Y},
		{0x21,"AND",2,"", AdrModes::ZERO_PAGE_INDEXED_INDIRECT_X},
		{0x31,"AND",2,"", AdrModes::ZERO_PAGE_INDIRECT_INDEXED_Y},
		//-----------------------------------------
		{0x0A,"ASL",1,"", AdrModes::ACCUMULATOR},
		{0x06,"ASL",2,"", AdrModes::ZERO_PAGE},
		{0x16,"ASL",2,"", AdrModes::ZERO_PAGE_X},
		{0x0E,"ASL",3,"", AdrModes::ABSOLUTE},
		{0x1E,"ASL",3,"", AdrModes::ABSOLUTE_X},
		//-----------------------------------------
		{0x90,"BCC",2,"", AdrModes::RELATIVE},
		//-----------------------------------------
		{0xB0,"BCS",2,"", AdrModes::RELATIVE},
		//-----------------------------------------
		{0xF0,"BEQ",2,"", AdrModes::RELATIVE},
		//-----------------------------------------
		{0x24,"BIT",2,"%s", AdrModes::ZERO_PAGE},
		{0x2C,"BIT",3,"", AdrModes::ABSOLUTE},
		//-----------------------------------------
		{0x30,"BMI",2,"", AdrModes::RELATIVE},
		//-----------------------------------------
		{0xD0,"BNE",2,"", AdrModes::RELATIVE},
		//-----------------------------------------
		{0x10,"BPL",2,"", AdrModes::RELATIVE},
		//-----------------------------------------
		{0x00,"BRK",2,"", AdrModes::IMPLIED},
		//-----------------------------------------
		{0x50,"BVC",2,"", AdrModes::RELATIVE},
		//-----------------------------------------
		{0x70,"BVS",2,"", AdrModes::RELATIVE},
		//-----------------------------------------
		{0x18,"CLC",2,"", AdrModes::IMPLIED},
		//-----------------------------------------
		{0xD8,"CLD",2,"", AdrModes::IMPLIED},
		//-----------------------------------------
		{0x58,"CLI",2,"", AdrModes::IMPLIED},
		//-----------------------------------------
		{0xB8,"CLV",2,"", AdrModes::IMPLIED},
		//-----------------------------------------
		{0xC9,"CMP",2,"#$%02x", AdrModes::IMMEDIATE},
		{0xC5,"CMP",2,"", AdrModes::ZERO_PAGE},
		{0xD5,"CMP",2,"", AdrModes::ZERO_PAGE_X},
		{0xCD,"CMP",3,"", AdrModes::ABSOLUTE},
		{0xDD,"CMP",3,"", AdrModes::ABSOLUTE_X},
		{0xD9,"CMP",3,"", AdrModes::ABSOLUTE_Y},
		{0xC1,"CMP",2,"", AdrModes::ZERO_PAGE_INDEXED_INDIRECT_X},
		{0xD1,"CMP",2,"", AdrModes::ZERO_PAGE_INDIRECT_INDEXED_Y},
		//-----------------------------------------
		{0xE0,"CPX",2,"#$%02x", AdrModes::IMMEDIATE},
		{0xE4,"CPX",2,"", AdrModes::ZERO_PAGE},
		{0xEC,"CPX",3,"", AdrModes::ABSOLUTE},
		//-----------------------------------------
		{0xC0,"CPY",2,"#$%02x", AdrModes::IMMEDIATE},
		{0xC4,"CPY",2,"", AdrModes::ZERO_PAGE},
		{0xCC,"CPY",3,"", AdrModes::ABSOLUTE},
		//-----------------------------------------
		{0xC6,"DEC",2,"", AdrModes::ZERO_PAGE},
		{0xD6,"DEC",2,"", AdrModes::ZERO_PAGE_X},
		{0xCE,"DEC",3,"", AdrModes::ABSOLUTE},
		{0xDE,"DEC",3,"", AdrModes::ABSOLUTE_X},
		//-----------------------------------------
		{0xCA,"DEX",2,"", AdrModes::IMPLIED},
		//-----------------------------------------
		{0x88,"DEY",2,"", AdrModes::IMPLIED},
		//-----------------------------------------
		{0x49,"EOR",2,"#$%02x", AdrModes::IMMEDIATE},
		{0x45,"EOR",2,"", AdrModes::ZERO_PAGE},
		{0x55,"EOR",2,"", AdrModes::ZERO_PAGE_X},
		{0x4D,"EOR",3,"", AdrModes::ABSOLUTE},
		{0x5D,"EOR",3,"", AdrModes::ABSOLUTE_X},
		{0x59,"EOR",3,"", AdrModes::ABSOLUTE_Y},
		{0x41,"EOR",2,"", AdrModes::ZERO_PAGE_INDEXED_INDIRECT_X},
		{0x51,"EOR",2,"", AdrModes::ZERO_PAGE_INDIRECT_INDEXED_Y},
		//-----------------------------------------
		{0xE6,"INC",2,"", AdrModes::ZERO_PAGE},
		{0xF6,"INC",2,"", AdrModes::ZERO_PAGE_X},
		{0xEE,"INC",3,"", AdrModes::ABSOLUTE},
		{0xFE,"INC",3,"", AdrModes::ABSOLUTE_X},
		//-----------------------------------------
		{0xE8,"INX",2,"", AdrModes::IMPLIED},
		//-----------------------------------------
		{0xC8,"INY",2,"", AdrModes::IMPLIED},
		//-----------------------------------------
		{0x4C,"JMP",3,"", AdrModes::ABSOLUTE},
		{0x6C,"JMP",3,"", AdrModes::INDIRECT},
		//-----------------------------------------
		{ 0x20,"JSR",3,"", AdrModes::ABSOLUTE },
		//-----------------------------------------
		{0xA9,"LDA",2,"#$%02x", AdrModes::IMMEDIATE},
		{0xA5,"LDA",2,"", AdrModes::ZERO_PAGE},
		{0xB5,"LDA",2,"", AdrModes::ZERO_PAGE_X},
		{0xAD,"LDA",3,"", AdrModes::ABSOLUTE},
		{0xBD,"LDA",3,"", AdrModes::ABSOLUTE_X},
		{0xB9,"LDA",3,"", AdrModes::ABSOLUTE_Y},
		{0xA1,"LDA",2,"", AdrModes::ZERO_PAGE_INDEXED_INDIRECT_X},
		{0xB1,"LDA",2,"", AdrModes::ZERO_PAGE_INDIRECT_INDEXED_Y},
		//-----------------------------------------
		{ 0xA2,"LDX",2,"#$%02x", AdrModes::IMMEDIATE },
		{ 0xA6,"LDX",2,"", AdrModes::ZERO_PAGE },
		{ 0xB6,"LDX",2,"", AdrModes::ZERO_PAGE_Y },
		{ 0xAE,"LDX",3,"", AdrModes::ABSOLUTE },
		{ 0xBE,"LDX",3,"", AdrModes::ABSOLUTE_Y },
		//-----------------------------------------
		{ 0xA0,"LDY",2,"#$%02x", AdrModes::IMMEDIATE },
		{ 0xA4,"LDY",2,"", AdrModes::ZERO_PAGE },
		{ 0xB4,"LDY",2,"", AdrModes::ZERO_PAGE_X },
		{ 0xAC,"LDY",3,"", AdrModes::ABSOLUTE },
		{ 0xBC,"LDY",3,"", AdrModes::ABSOLUTE_X },
		//-----------------------------------------
		{0x4A,"LSR",1,"", AdrModes::ACCUMULATOR},
		{0x46,"LSR",2,"", AdrModes::ZERO_PAGE},
		{0x56,"LSR",2,"", AdrModes::ZERO_PAGE_X},
		{0x4E,"LSR",3,"", AdrModes::ABSOLUTE},
		{0x5E,"LSR",3,"", AdrModes::ABSOLUTE_X},
		//-----------------------------------------
		{ 0xEA,"NOP",2,"", AdrModes::IMPLIED },
		//-----------------------------------------
		{0x09,"ORA",2,"#$%02x", AdrModes::IMMEDIATE},
		{0x05,"ORA",2,"", AdrModes::ZERO_PAGE},
		{0x15,"ORA",2,"", AdrModes::ZERO_PAGE_X},
		{0x0D,"ORA",3,"", AdrModes::ABSOLUTE},
		{0x1D,"ORA",3,"", AdrModes::ABSOLUTE_X},
		{0x19,"ORA",3,"", AdrModes::ABSOLUTE_Y},
		{0x01,"ORA",2,"", AdrModes::ZERO_PAGE_INDEXED_INDIRECT_X},
		{0x11,"ORA",2,"", AdrModes::ZERO_PAGE_INDIRECT_INDEXED_Y},
		//-----------------------------------------
		{ 0x48,"PHA",2,"", AdrModes::IMPLIED },
		//-----------------------------------------
		{ 0x08,"PHP",2,"", AdrModes::IMPLIED },
		//-----------------------------------------
		{ 0x68,"PLA",2,"", AdrModes::IMPLIED },
		//-----------------------------------------
		{ 0x28,"PLP",2,"", AdrModes::IMPLIED },
		//-----------------------------------------
		{0x2A,"ROL",1,"", AdrModes::ACCUMULATOR},
		{0x26,"ROL",2,"", AdrModes::ZERO_PAGE},
		{0x36,"ROL",2,"", AdrModes::ZERO_PAGE_X},
		{0x2E,"ROL",3,"", AdrModes::ABSOLUTE},
		{0x3E,"ROL",3,"", AdrModes::ABSOLUTE_X},
		//-----------------------------------------
		{0x6A,"ROR",1,"", AdrModes::ACCUMULATOR},
		{0x66,"ROR",2,"", AdrModes::ZERO_PAGE},
		{0x76,"ROR",2,"", AdrModes::ZERO_PAGE_X},
		{0x6E,"ROR",3,"", AdrModes::ABSOLUTE},
		{0x7E,"ROR",3,"", AdrModes::ABSOLUTE_X},
		//-----------------------------------------
		{ 0x40,"RTI",2,"", AdrModes::IMPLIED },
		//-----------------------------------------
		{ 0x60,"RTS",2,"", AdrModes::IMPLIED },
		//-----------------------------------------
		{0xE9,"SBC",2,"#$%02x", AdrModes::IMMEDIATE},
		{0xE5,"SBC",2,"", AdrModes::ZERO_PAGE},
		{0xF5,"SBC",2,"", AdrModes::ZERO_PAGE_X},
		{0xED,"SBC",3,"", AdrModes::ABSOLUTE},
		{0xFD,"SBC",3,"", AdrModes::ABSOLUTE_X},
		{0xF9,"SBC",3,"", AdrModes::ABSOLUTE_Y},
		{0xE1,"SBC",2,"", AdrModes::ZERO_PAGE_INDEXED_INDIRECT_X},
		{0xF1,"SBC",2,"", AdrModes::ZERO_PAGE_INDIRECT_INDEXED_Y},
		//-----------------------------------------
		{ 0x38,"SEC",2,"", AdrModes::IMPLIED },
		//-----------------------------------------
		{ 0xF8,"SEC",2,"", AdrModes::IMPLIED },
		//-----------------------------------------
		{ 0x78,"SEI",2,"", AdrModes::IMPLIED },
		//-----------------------------------------
		{0x85,"STA",2,"", AdrModes::ZERO_PAGE},
		{0x95,"STA",2,"", AdrModes::ZERO_PAGE_X},
		{0x8D,"STA",3,"", AdrModes::ABSOLUTE},
		{0x9D,"STA",3,"", AdrModes::ABSOLUTE_X},
		{0x99,"STA",3,"", AdrModes::ABSOLUTE_Y},
		{0x81,"STA",2,"", AdrModes::ZERO_PAGE_INDEXED_INDIRECT_X},
		{0x91,"STA",2,"", AdrModes::ZERO_PAGE_INDIRECT_INDEXED_Y},
		//-----------------------------------------
		{ 0x86,"STX",2,"", AdrModes::ZERO_PAGE },
		{ 0x96,"STX",2,"", AdrModes::ZERO_PAGE_Y },
		{ 0x8E,"STX",3,"", AdrModes::ABSOLUTE },
		//-----------------------------------------
		{ 0x84,"STY",2,"", AdrModes::ZERO_PAGE },
		{ 0x94,"STY",2,"", AdrModes::ZERO_PAGE_X },
		{ 0x8C,"STY",3,"", AdrModes::ABSOLUTE },
		//-----------------------------------------
		{ 0xAA,"TAX",2,"", AdrModes::IMPLIED },
		//-----------------------------------------
		{ 0xA8,"TAY",2,"", AdrModes::IMPLIED },
		//-----------------------------------------
		{ 0xBA,"TSX",2,"", AdrModes::IMPLIED },
		//-----------------------------------------
		{ 0x8A,"TXA",2,"", AdrModes::IMPLIED },
		//-----------------------------------------
		{ 0x9A,"TXS",2,"", AdrModes::IMPLIED },
		//-----------------------------------------
		{ 0x98,"TYA",2,"", AdrModes::IMPLIED },
		{ -1,NULL,2,"", AdrModes::IMPLIED }
	};
public:
	CDis65();
	virtual ~CDis65();
	bool Create();
	int Run();
};

