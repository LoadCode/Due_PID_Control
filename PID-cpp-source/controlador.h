#ifndef CONTROLADOR_H
#define CONTROLADOR_H


/**
*@class Controlador
*@brief Esta clase contiene las definciones de los métodos generales o que resultan comunes
*a los diferentes tipos de controlador desarrollados en el proyecto
*
*Todos los métodos y variables que se proponen en esta clase base se heredan en los controladores más
*específicos como son el PID, RST, y el método de Variables de Estado.
*El contructor de esta clase debe ser invocado por todos los constructores de los controladores que hereden de esta.
*/

class Controlador
{
    public:

         Controlador(double Ts, int inputPin, int outputPin,\
                               double minOutput, double maxOutput);

        //virtual ~Controlador();
       virtual double Lectura() = 0; ///<Realiza la lectura en el ADC indicado por la variable pinEntrada (realiza la realimentación)
       virtual void Escritura() = 0; ///<Escribe el valor calculado por el controlador (salidaControlador) en el DAC indicado en pinSalida

        void SetReferencia(double refer);     ///<Permite poner un valor deseado en el sistema de control
        void SetSalidaMaxima(double salMax); ///<Permite indicarle al controlador cual será el valor máximo que podrá sacar por el DAC
        void SetSalidaMinima(double salMin); ///<Permite indicarle al controlador cual será el valor mínimo que podrá sacar por el DAC
        virtual void SetSampleTime(double sampleTime);     ///<Aunque en el contructor debe indicarse un periodo de muestreo, esta función permite realizar modificaciones al Ts
        void SetInputPin(int inputPin);            ///<Esta función permite decirle al controlador cual será el ADC que utilizará para extraer las muestras de la planta
        void SetOutputPin(int outputPin);          ///<Esta función permite indicar cual será el DAC a utilizar para el proceso de control

    protected:
       int pinEntrada;           ///<Define el pin del ADC que será usado para capturar la variable realimentada
       int pinSalida;            ///<Define el pin del DAC que se usará para la salida del controlador
      double referencia;         ///<Almacena el valor deseado del proceso de control
      double salidaPlanta;       ///<Almacena el valor de la salida de la planta (es decir, el valor de la variable realientada)
      double salidaControlador;  ///<Salida del controlador hacia la planta (es decir la U, o ley de control)
      double salidaMaxima;       ///<Almacena el valor máximo para la salida del controlador
      double salidaMinima;       ///<Almacena el valor mínimo para la salida del controlador
      double Ts;                 ///<Periodo de muestreo
};

 #endif // CONTROLADOR_H
