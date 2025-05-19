#pragma once

#include <cstdint>

class Chip8
{
private:
	void step();

public:
	uint8_t registers[16]{};
	uint8_t memory[4096]{};
	uint16_t index{};
	uint16_t programCounter{};
	uint16_t stack[16]{};
	uint8_t stackPointer{};
	uint8_t delayTimer{};
	uint8_t soundTimer{};
	uint8_t keypad[16]{};
	uint32_t video[64 * 32]{};
	uint16_t opcode;
};