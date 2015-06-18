#include <controlador.h>
#include <pid.h>



void setup() 
{
  PID::InitResolution(12); //Define una resolución de 10 bits por defecto para los DACs y ADCs 
}

void loop() 
{
  PID myPID(1.5,A0,DA0,-5,5);
  myPID.SetPIDParameters(10,2,0.5);
  
}
