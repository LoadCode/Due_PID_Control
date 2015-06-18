#include "EntSal.h"
#include "Arduino.h"
EntSal::EntSal(int pto, float smn, float smx)
{
	smin = smn;
	smax = smx;
	puerto = pto;
}

void EntSal::init(int rs)
{
	switch (rs)
	{
	case 8:
		res = 255;
		break;
	case 10:
		res = 1023;
		break;
	case 12:
		res = 4095;
		break;
	default:
		rs = 10;
		res = 1023;
	}
	analogReadResolution(rs);
	analogWriteResolution(rs);
}

void EntSal::_DAC(float dato)
{
	
	if (dato > smax)
		dato = smax;
	else if (dato < smin)
		dato = smin;

	ys = (res/(smax-smin))*(dato-smin);
	analogWrite(puerto, ys);
}

float EntSal::_ADC()
{
	xen=analogRead(puerto);
	ye = ((smax - smin) / res)*xen + smin;
	return ye;

}


EntSal::~EntSal()
{
	//destructor por defecto
}
