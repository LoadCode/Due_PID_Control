#ifndef CONTROLADOR_H
#define CONTROLADOR_H


class Controlador
{
    public:

        Controlador(); //Default constructor
        Controlador(double Ts, int inputPin, int outputPin,\
                               double minOutput, double maxOutput);

        //virtual ~Controlador();
       virtual double Lectura()=0 ; //Lee del pinEntrada y almacena el valor en salidaPlanta (realimentaci�n) //Funcion virtual
       //virtual void Escritura()  = 0; //Escribe el valor calculado por el controlador (salidaControlador) en el pinSalida (DAC usado)   //Funci�n  virutal

        void SetReferencia(double referencia); //lectura externa, definir entrada
        void SetSalidaMaxima(double salidaMaxima);
        void SetSalidaMinima(double salidaMinima);
        void SetSampleTime(double sampleTime);
        void SetInputPin(int inputPin);
        void SetOutputPin(int outputPin);

    protected: //As this class will be inherited, if members aren't in protected mode then may not be accessed
       int pinEntrada; //pin para lectura del ADC para variable de realimentaci�n
       int pinSalida;    //pin que indica el DAC que se usa de salida
      double referencia; //valor deseado
      double salidaPlanta;//salida del la planta hacia el Arduino
      double salidaControlador; //salida del controlador hacia la planta //U
      double salidaMaxima; //Valor m�ximo para la salida del controlador
      double salidaMinima;  //Valor m�nimo para la salida del controlador
      double Ts;    //Sample time
};

#endif // CONTROLADOR_H
