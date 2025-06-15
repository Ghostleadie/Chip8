#include "opcodes.h"

#include <stack>

void opcodes::OP_NULL()
{}

void opcodes::OP_00E0()
{
	memset(cpu.video, 0, sizeof(cpu.video));
}

void opcodes::OP_00EE()
{
	--cpu.stackPointer;
	cpu.programCounter = cpu.stack[cpu.stackPointer];
}

void opcodes::OP_1nnn()
{
	uint16_t address = cpu.opcode & 0x0FFFu;

	cpu.programCounter = address;
}

void opcodes::OP_2nnn()
{
	uint16_t address = cpu.opcode & 0x0FFFu;

	cpu.stack[cpu.stackPointer] = cpu.programCounter;
	++cpu.stackPointer;
	cpu.programCounter = address;
}

void opcodes::OP_3xkk()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t byte = cpu.opcode & 0x00FFu;

	if (cpu.registers[Vx] == byte)
	{
		cpu.programCounter += 2;
	}
}

void opcodes::OP_4xkk()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t byte = cpu.opcode & 0x00FFu;

	if (cpu.registers[Vx] != byte)
	{
		cpu.programCounter += 2;
	}
}

void opcodes::OP_5xy0()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (cpu.opcode & 0x00F0u) >> 4u;

	if (cpu.registers[Vx] == cpu.registers[Vy])
	{
		cpu.programCounter += 2;
	}
}

void opcodes::OP_6xkk()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t byte = cpu.opcode & 0x00FFu;

	cpu.registers[Vx] = byte;
}

void opcodes::OP_7xkk()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t byte = cpu.opcode & 0x00FFu;

	cpu.registers[Vx] += byte;
}

void opcodes::OP_8xy0()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (cpu.opcode & 0x00F0u) >> 4u;

	cpu.registers[Vx] = cpu.registers[Vy];
}

void opcodes::OP_8xy1()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (cpu.opcode & 0x00F0u) >> 4u;

	cpu.registers[Vx] |= cpu.registers[Vy];
}

void opcodes::OP_8xy2()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (cpu.opcode & 0x00F0u) >> 4u;

	cpu.registers[Vx] &= cpu.registers[Vy];
}

void opcodes::OP_8xy3()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (cpu.opcode & 0x00F0u) >> 4u;

	cpu.registers[Vx] ^= cpu.registers[Vy];
}

void opcodes::OP_8xy4()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (cpu.opcode & 0x00F0u) >> 4u;

	uint16_t sum = cpu.registers[Vx] + cpu.registers[Vy];

	if (sum > 255U)
	{
		cpu.registers[0xF] = 1;
	}
	else
	{
		cpu.registers[0xF] = 0;
	}

	cpu.registers[Vx] = sum & 0xFFu;
}

void opcodes::OP_8xy5()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (cpu.opcode & 0x00F0u) >> 4u;

	if (cpu.registers[Vx] > cpu.registers[Vy])
	{
		cpu.registers[0xF] = 1;
	}
	else
	{
		cpu.registers[0xF] = 0;
	}

	cpu.registers[Vx] -= cpu.registers[Vy];
}

void opcodes::OP_8xy6()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;

	// Save LSB in VF
	cpu.registers[0xF] = (cpu.registers[Vx] & 0x1u);

	cpu.registers[Vx] >>= 1;
}

void opcodes::OP_8xy7()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (cpu.opcode & 0x00F0u) >> 4u;

	if (cpu.registers[Vy] > cpu.registers[Vx])
	{
		cpu.registers[0xF] = 1;
	}
	else
	{
		cpu.registers[0xF] = 0;
	}

	cpu.registers[Vx] = cpu.registers[Vy] - cpu.registers[Vx];
}

void opcodes::OP_8xyE()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;

	// Save MSB in VF
	cpu.registers[0xF] = (cpu.registers[Vx] & 0x80u) >> 7u;

	cpu.registers[Vx] <<= 1;
}

void opcodes::OP_9xy0()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (cpu.opcode & 0x00F0u) >> 4u;

	if (cpu.registers[Vx] != cpu.registers[Vy])
	{
		cpu.programCounter += 2;
	}
}

void opcodes::OP_Annn()
{
	uint16_t address = cpu.opcode & 0x0FFFu;

	cpu.index = address;
}

void opcodes::OP_Bnnn()
{
	uint16_t address = cpu.opcode & 0x0FFFu;

	cpu.programCounter = cpu.registers[0] + address;
}

void opcodes::OP_Cxkk()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t byte = cpu.opcode & 0x00FFu;

	cpu.registers[Vx] = cpu.randByte(cpu.randGen) & byte;
}

void opcodes::OP_Dxyn()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (cpu.opcode & 0x00F0u) >> 4u;
	uint8_t height = cpu.opcode & 0x000Fu;

	// Wrap if going beyond screen boundaries
	uint8_t xPos = cpu.registers[Vx] % VIDEO_WIDTH;
	uint8_t yPos = cpu.registers[Vy] % VIDEO_HEIGHT;

	cpu.registers[0xF] = 0;

	for (unsigned int row = 0; row < height; ++row)
	{
		uint8_t spriteByte = cpu.memory[cpu.index + row];

		for (unsigned int col = 0; col < 8; ++col)
		{
			uint8_t spritePixel = spriteByte & (0x80u >> col);
			uint32_t* screenPixel = &cpu.video[(yPos + row) * VIDEO_WIDTH + (xPos + col)];

			// Sprite pixel is on
			if (spritePixel)
			{
				// Screen pixel also on - collision
				if (*screenPixel == 0xFFFFFFFF)
				{
					cpu.registers[0xF] = 1;
				}

				// Effectively XOR with the sprite pixel
				*screenPixel ^= 0xFFFFFFFF;
			}
		}
	}
}

void opcodes::OP_Ex9E()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;

	uint8_t key = cpu.registers[Vx];

	if (cpu.keypad[key])
	{
		cpu.programCounter += 2;
	}
}

void opcodes::OP_ExA1()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;

	uint8_t key = cpu.registers[Vx];

	if (!cpu.keypad[key])
	{
		cpu.programCounter += 2;
	}
}

void opcodes::OP_Fx07()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;

	cpu.registers[Vx] = cpu.delayTimer;
}

void opcodes::OP_Fx0A()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;

	if (cpu.keypad[0])
	{
		cpu.registers[Vx] = 0;
	}
	else if (cpu.keypad[1])
	{
		cpu.registers[Vx] = 1;
	}
	else if (cpu.keypad[2])
	{
		cpu.registers[Vx] = 2;
	}
	else if (cpu.keypad[3])
	{
		cpu.registers[Vx] = 3;
	}
	else if (cpu.keypad[4])
	{
		cpu.registers[Vx] = 4;
	}
	else if (cpu.keypad[5])
	{
		cpu.registers[Vx] = 5;
	}
	else if (cpu.keypad[6])
	{
		cpu.registers[Vx] = 6;
	}
	else if (cpu.keypad[7])
	{
		cpu.registers[Vx] = 7;
	}
	else if (cpu.keypad[8])
	{
		cpu.registers[Vx] = 8;
	}
	else if (cpu.keypad[9])
	{
		cpu.registers[Vx] = 9;
	}
	else if (cpu.keypad[10])
	{
		cpu.registers[Vx] = 10;
	}
	else if (cpu.keypad[11])
	{
		cpu.registers[Vx] = 11;
	}
	else if (cpu.keypad[12])
	{
		cpu.registers[Vx] = 12;
	}
	else if (cpu.keypad[13])
	{
		cpu.registers[Vx] = 13;
	}
	else if (cpu.keypad[14])
	{
		cpu.registers[Vx] = 14;
	}
	else if (cpu.keypad[15])
	{
		cpu.registers[Vx] = 15;
	}
	else
	{
		cpu.programCounter -= 2;
	}
}

void opcodes::OP_Fx15()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;

	cpu.delayTimer = cpu.registers[Vx];
}

void opcodes::OP_Fx18()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;

	cpu.soundTimer = cpu.registers[Vx];
}

void opcodes::OP_Fx1E()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;

	cpu.index += cpu.registers[Vx];
}

void opcodes::OP_Fx29()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t digit = cpu.registers[Vx];

	cpu.index = FONTSET_START_ADDRESS + (5 * digit);
}

void opcodes::OP_Fx33()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;
	uint8_t value = cpu.registers[Vx];

	// Ones-place
	cpu.memory[cpu.index + 2] = value % 10;
	value /= 10;

	// Tens-place
	cpu.memory[cpu.index + 1] = value % 10;
	value /= 10;

	// Hundreds-place
	cpu.memory[cpu.index] = value % 10;
}

void opcodes::OP_Fx55()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;

	for (uint8_t i = 0; i <= Vx; ++i)
	{
		cpu.memory[cpu.index + i] = cpu.registers[i];
	}
}

void opcodes::OP_Fx65()
{
	uint8_t Vx = (cpu.opcode & 0x0F00u) >> 8u;

	for (uint8_t i = 0; i <= Vx; ++i)
	{
		cpu.registers[i] = cpu.memory[cpu.index + i];
	}
}