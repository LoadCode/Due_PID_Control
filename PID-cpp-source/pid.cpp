#include "pid.h"


void PID::Compute()
{
    salidaPlanta = Lectura(); //gets the actual process value
    error = referencia - salidaPlanta;
    pTerm = kp*error;
    iTerm += (ki*(error+prevError))/2;  //integral's bilinear approximation, ki is included in calculation for tuning changes
    dTerm = -kd*(salidaPlanta-prevSalidaPlanta); //Derived from the measurement (anti-derivative kick)
    salidaControlador = pTerm + iTerm + dTerm; //controller output
    prevError = error;
    prevSalidaPlanta = salidaPlanta;
}

void PID::SetSampleTime(double sampleTime)
{
    //this method is override from class controlador.
    //if pid sample time is change in execution time, ths constants must to be adjusted according to that change
    double tasa;
    tasa = sampleTime/Ts;
    Ts = sampleTime;
    kp = kp; //doesn't depend on sample time
    ki*=tasa;
    kd/=tasa;
}

double PID::Lectura()
{
    //converts from ADC value to double?
    //return analogRead(this->pinEntrada);
    return 1; //temporal return for code::blocks debug
}

/************************************************/
/***** Setters and Getters for the base class *****/
/************************************************/

void PID::SetPIDParameters(double kp, double ki, double kd)
{
    //This function sets the values of PID gains
    //these gains are calculated in continuous time by the designer, and here are digitized with sample time Ts
    this->kp = kp;
    this->ki  = ki*Ts;
    this->kd = kd/Ts;
}

double PID::GetSampleTime()
{
    return this->Ts;
}

int PID::GetInputPin()
{
    return this->pinEntrada;
}

int PID::GetOutputPin()
{
    return this->pinSalida;
}

PID::~PID()
{
    //dtor
}
