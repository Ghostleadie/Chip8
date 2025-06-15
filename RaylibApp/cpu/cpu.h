#pragma once

#include <cstdint>
#include <random>

#include "rom.h"

class Chip8
{
public:
	Chip8();
	~Chip8();

	static Chip8& Get();
private:
	void init();
	void emulateCycle();
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

	std::default_random_engine randGen;
	std::uniform_int_distribution<uint8_t> randByte;

private:
	std::unique_ptr<rom> rom;
};
