#include "controlador.h"


/**
*@brief Método de inicialización de las variables del controlador básico
*
*Esta función es al encargada de indicar al controlador el periodo de muestreo, el ADC y DAC que se usarán y los valores de voltaje
*máximos y mínimos presentes en el sistema.
*/
Controlador::Controlador(double T, int inputPin, int outputPin, double minOutput, double maxOutput)
{
    Ts = T;
    pinEntrada   = inputPin;
    pinSalida    = outputPin;
    salidaMaxima = maxOutput;
    salidaMinima = minOutput;
}


/************************************************/
/***** Setters and getters for the base class *****/
/************************************************/
void Controlador::SetReferencia(double refer)
{
    referencia = refer;
}

void Controlador::SetSalidaMaxima(double salMax)
{
    salidaMaxima = salMax;
}

void Controlador::SetSalidaMinima(double salMin)
{
    salidaMinima = salMin;
}

void Controlador::SetSampleTime(double sampleTime)
{
    Ts = sampleTime;
}

void Controlador::SetInputPin(int inputPin)
{
    pinEntrada = inputPin;
}

void Controlador::SetOutputPin(int outputPin)
{
    pinSalida = outputPin;
}

/*Controlador::~Controlador()
{
    //dtor
}
*/
