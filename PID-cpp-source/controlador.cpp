#include "controlador.h"

Controlador::Controlador()
{

}

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




Controlador::~Controlador()
{
    //dtor
}
