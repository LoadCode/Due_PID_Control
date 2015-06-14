#pragma once
#include "Arduino.h"
class EntSal
{
public:
	EntSal(int pto, float smn, float smx);
	static void init(int rs);
	void _DAC(float dato);
	float _ADC();
private:
	int puerto;
	static int res;
	int smin, smax;
	int ys,xen;
	float ye;
public:
	~EntSal();
};

