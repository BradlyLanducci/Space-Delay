#pragma once

class DelayLine
{
public:
	DelayLine();
	~DelayLine();

	// Set buffer memory
	void setMemory(int buf_size);

	// Clear Buffer
	void clear();

	// Write sample and shift all samples
	void write(float sample);

	// Read item at offset location
	float read(int offset);
	int writeidx;
private:
	float* delayBuffer;
};

