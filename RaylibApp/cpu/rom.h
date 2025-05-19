#pragma once

class rom
{
public:
	static void loadROM(const char* filename, char* memory);

protected:
	static const unsigned int START_ADDRESS = 0x200;
};