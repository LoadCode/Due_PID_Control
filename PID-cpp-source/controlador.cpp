#include "controlador.h"

Controlador::Controlador()
{

}

Controlador::Controlador(double Ts, int inputPin, int outputPin, double minOutput, double maxOutput)
{
    this->Ts = Ts;
    this->pinEntrada      = inputPin;
    this->pinSalida         = outputPin;
    this->salidaMaxima = maxOutput;
    this->salidaMinima  = minOutput;
}

/************************************************/
/***** Setters and getters for the base class *****/
/************************************************/
void Controlador::SetReferencia(double referencia)
{
    this->referencia = referencia;
}

void Controlador::SetSalidaMaxima(double salidaMaxima)
{
    this->salidaMaxima = salidaMaxima;
}

void Controlador::SetSalidaMinima(double salidaMinima)
{
    this->salidaMinima = salidaMinima;
}

void Controlador::SetSampleTime(double sampleTime)
{
    this->Ts = sampleTime;
}

void Controlador::SetInputPin(int inputPin)
{
    this->pinEntrada = inputPin;
}

void Controlador::SetOutputPin(int outputPin)
{
    this->pinSalida = outputPin;
}

/*Controlador::~Controlador()
{
    //dtor
}
*/
