#include <cstdint>

typedef uint8_t BYTE;
typedef uint16_t WORD;

#define C_FLAG 0b00000001;
#define Z_FLAG 0b00000010;
#define I_FLAG 0b00000100;
#define D_FLAG 0b00001000;
#define B_FLAG 0b00010000;
#define V_FLAG 0b00100000;
#define N_FLAG 0b01000000;


class CPU {
public:
	WORD pc;  // program counter
	BYTE sp;  // stack pointer
	BYTE acc; // accumulator
	BYTE x,y; // index registers
	BYTE flags;
	BYTE addr_bus[0x10000];
	void doInstruction(BYTE opcode[3]);
private:

};

void CPU::doInstruction(BYTE opcode[3]) {
	auto update_ld_flags = [this](BYTE val)->void {
		if(val)
				this->flags |= Z_FLAG;
			if( val & 0b10000000)
				this->flags |= N_FLAG;
	};

	#define IMM opcode[1]
	#define ZERO_PAGE addr_bus[opcode[1]]
	#define ZERO_PAGEX addr_bus[opcode[1] + x]
	#define ZERO_PAGEY addr_bus[opcode[1] + y]
	#define ABS addr_bus[0x10*opcode[1] + opcode[2]]
	#define ABS_X addr_bus[0x10*opcode[1] + opcode[2] + x]
	#define ABS_Y addr_bus[0x10*opcode[1] + opcode[2] + y]
	#define IND_X addr_bus[opcode[1] + addr_bus[x]];
	#define IND_Y addr_bus[opcode[1] + addr_bus[y]];

	switch(opcode[0]) {
			
		case 0xA9: // LDA immediate_val
			pc += 2;
			acc = IMM;
			update_ld_flags(acc);
			break;
		case 0xA5: // LDA zero_page
			pc += 2;
			acc = ZERO_PAGE;
			update_ld_flags(acc);
			break;
		case 0xB5: // LDA zero_page, x
			pc += 2;
			acc = ZERO_PAGEX;
			update_ld_flags(acc);
			break;
		case 0xAD:  // LDA abs
			pc += 3;
			acc = ABS;
			update_ld_flags(acc);
			break;
		case 0xBD: // LDA abs, x
			pc += 3;
			acc = ABS_X;
			update_ld_flags(acc);
			break;
		case 0xB9: // LDA abs, y
			pc += 3;
			acc = ABS_Y;
			update_ld_flags(acc);
			break;
		case 0xA1: // LDA (Ind, X)
			pc += 2;
			acc = IND_X;
			update_ld_flags(acc);
			break;
		case 0xB1: // LDA (Ind), Y
			pc += 2;
			acc = IND_Y;
			update_ld_flags(acc);
			break;

		/* LDX BLOCK */
		case 0xA2: // LDX immediate_val
			pc += 2;
			x = IMM;
			update_ld_flags(x);
			break;
		case 0xA6: // LDX zero_page
			pc += 2;
			x = ZERO_PAGE;
			update_ld_flags(x);
			break;
		case 0xB6: // LDX zero_page, y
			pc += 2;
			x = ZERO_PAGEY;
			update_ld_flags(x);
			break;
		case 0xAE:  // LDX abs
			pc += 3;
			x = ABS;
			update_ld_flags(x);
			break;
		case 0xBE: // LDX abs, y
			pc+=3;
			x = ABS_Y;
			update_ld_flags(x);
			break;

		/* LDY BLOCK */

		case 0xA0: // LDY immediate_val
			pc += 2;
			y = IMM;
			update_ld_flags(y);
			break;
		case 0xA4: // LDY zero_page
			pc += 2;
			y = ZERO_PAGE;
			update_ld_flags(y);
			break;
		case 0xB4: // LDY zero_page, x
			pc += 2;
			y = ZERO_PAGEX;
			update_ld_flags(y);
			break;
		case 0xAC:  // LDY abs
			pc += 3;
			y = ABS;
			update_ld_flags(y);
			break;
		case 0xBC: // LDX abs, x
			pc+=3;
			x = ABS_X;
			update_ld_flags(y);
			break;

		case 0xEA: // NOP
			pc += 1;


		case 0x09: // ORA immediate_val
			pc += 2;
			acc |= IMM;
			update_ld_flags(acc);
			break;
		case 0x05: // ORA zero_page
			pc += 2;
			acc |= ZERO_PAGE;
			update_ld_flags(acc);
			break;
		case 0x15: // ORA zero_page + x
			pc += 2;
			acc |= ZERO_PAGEX;
			update_ld_flags(acc);
			break;
		case 0x0D: // ORA abs
			pc += 3;
			acc |= ABS;
			update_ld_flags(acc);
			break;
		case 0x1D: // ORA abs+x
			pc += 3;
			acc |= ABS_X;
			update_ld_flags(acc);
			break;
		case 0x19: // ORA abs+y
			pc += 3;
			acc |= ABS_Y;
			update_ld_flags(acc);
			break;
		case 0x01: // ORA (ind, x)
			pc += 2;
			acc |= IND_X;
			update_ld_flags(acc);
			break;
		case 0x11: // ORA (ind), y
			pc += 2;
			acc |= IND_Y;
			update_ld_flags(acc);
			break;

		case 0x48: //PHA (Push Accumulator)
			addr_bus[sp] = acc;
			--sp;
			break;

		

		};







	}
