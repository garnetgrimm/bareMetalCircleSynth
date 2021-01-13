#include "iirfilter.h"

IIRFilter::IIRFilter()
{
}

IIRFilter::~IIRFilter() {
	delete[] aCs;
	delete[] bCs;
}

//Engineers Guide to DSP page 326 (340 on the PDF)
void IIRFilter::generateBandPass(double sampleRate, double cornerFreq, double bandwidth)
{
		coeffs = 3;
		aCs = new double[coeffs];
		bCs = new double[coeffs];
	
		cornerFreq /= sampleRate;
		bandwidth /= sampleRate;
		
		double R = 1 - 3 * bandwidth;
		double cos2pif = cos(2 * M_PI * cornerFreq);
		double Knum = 1 - (2 * R*cos2pif) + R * R;
		double Kden = 2 - 2 * cos2pif;
		double K = Knum / Kden;

		aCs[0] = 1 - K;
		aCs[1] = 2 * (K - R)*cos2pif;
		aCs[2] = R*R - K;

		bCs[0] = 0;
		bCs[1] = 2*R*cos2pif;
		bCs[2] = -R*R;
}

void IIRFilter::processSamples(u32 *pBuffer, unsigned nChunkSize)
{
	//create outputData array
	double* outputData = new double[nChunkSize];

	//initalize first few outputs
	for (int i = 0; i < coeffs; i++) {
		outputData[i] = 0;
	}

	//process rest of data
	for (unsigned int i = coeffs; i < nChunkSize; i++) {
		double sum = 0;
		for (int j = 0; j < coeffs; j++) {
			sum += aCs[j] * (double)pBuffer[i - j];
			sum += bCs[j] * outputData[i - j];
		}
		outputData[i] = sum;
	}

	//copy all back to input
	for(unsigned int i = 0; i < nChunkSize; i++) {
		pBuffer[i] = (u32)outputData[i];
	}
	delete[] outputData;
}