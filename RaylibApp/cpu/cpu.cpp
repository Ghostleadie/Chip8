#include "cpu.h"

static Chip8* Instance = nullptr;

Chip8::Chip8()
{
	Instance = this;
}

Chip8::~Chip8()
{
	Instance = nullptr;
}

void Chip8::init()
{
	programCounter = 0x200;
	opcode = 0;
	index = 0;
	stackPointer = 0;
}

void Chip8::emulateCycle()
{
	// Fetch opcode bitshift so that it becomes a single digit from $0 to $F
	opcode = memory[programCounter] << 8 | memory[programCounter + 1];
}

void Chip8::step()
{

}

Chip8 & Chip8::Get()
{
	return *Instance;
}
