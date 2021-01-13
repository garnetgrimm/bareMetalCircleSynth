#ifndef _wavetable_h
#define _wavetable_h

#include <math.h>
#define M_PI 3.14159265358979323846

class WaveTable {
	public:
		WaveTable() {}
		WaveTable(int resolution) {
			this->resolution = resolution;
			values = new int[resolution];
		}
		~WaveTable() {
			delete[] values;
		}
		int valueAt(unsigned position) {
			return values[position % resolution];
		}
	protected:
		int resolution;
		int* values;
};

class SinTable: public WaveTable {
public:
	SinTable(int resolution, int amplitude): WaveTable(resolution) {
		for(int i = 0; i < resolution; i++) {
			this->values[i] = (int)((float)(amplitude/2)*sin(((float)i/resolution)*2*M_PI)+(amplitude/2));
		}
	}
};

class SawTable: public WaveTable {
public:
	SawTable(int resolution, int amplitude): WaveTable(resolution) {
		for(int i = 0; i < resolution; i++) {
			this->values[i] = amplitude*((float)i/resolution);
		}
	}
};

class PulseTable: public WaveTable {
public:
	PulseTable(int resolution, int amplitude): WaveTable(resolution) {
		for(int i = 0; i < resolution; i++) {
			if ((float)i/resolution < 0.5) {
				this->values[i] = 0;
			} else {
				this->values[i] = amplitude;
			}
		}
	}
};

class VelocityTable: public WaveTable {
	public:
		VelocityTable(float steepness): WaveTable(128) {
			float coeff = pow(10, -(2 + 4*(steepness-1))); 
			for(int i = 0; i < 128; i++) {
				float y = coeff * pow((float)i/128, 2 * steepness);
				if(y > 1) y = 1;
				this->values[i] = (int)y*100;
			}
		}
};

#endif