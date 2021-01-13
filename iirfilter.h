#ifndef _filter_h
#define _filter_h

#include <math.h>
#include <circle/types.h>

#define M_PI 3.14159265358979323846

class IIRFilter {
private:
	double* aCs;
	double* bCs;
public:
	IIRFilter();
	~IIRFilter();
	int coeffs;
	void generateBandPass(double sampleRate, double cornerFreq, double bandwidth);
	void processSamples(u32 *pBuffer, unsigned nChunkSize);
};

#endif