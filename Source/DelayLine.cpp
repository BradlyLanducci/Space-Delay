#include "DelayLine.h"
#include <iostream>
#include <stdlib.h>

#define BUF_SIZE 2000000

int line, size, mask;

uint32_t nextpow2_u32(uint32_t x) {
	x--;
	x |= x >> 1; x |= x >> 2;
	x |= x >> 4; x |= x >> 8;
	x |= x >> 16;
	return ++x;
}

DelayLine::DelayLine()
{
	setMemory(BUF_SIZE);
	clear();
	writeidx = 0;
}

DelayLine::~DelayLine()
{

}

void DelayLine::setMemory(int buf_size)
{
	delayBuffer = new float[BUF_SIZE];
	size = nextpow2_u32(1000000);
	mask = size - 1;

}

void DelayLine::clear()
{
	std::fill(delayBuffer, delayBuffer + BUF_SIZE, 0);
}

void DelayLine::write(float sample)
{
	delayBuffer[((writeidx--) & mask)] = sample;
	writeidx %= INT_MAX;
}

float DelayLine::read(int offset)
{
	return delayBuffer[(writeidx + offset) & mask];
}
