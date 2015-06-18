#ifndef PID_H
#define PID_H
#include <Arduino.h>
#include <controlador.h>

/**
*@class PID
*@brief Esta clase contiene la implementación del controlador PID para el Arduino DUE
*
*La clase PID contiene los métodos:
* - Compute
* - Lectura
* - Escritura
* - SetSampleTime
* - SetPIDParameters
* - InitResolution
*
*Los cuales son suficientes para un correcto desemespeño del PID en un proceso de control basado en la placa Arduino.
*/


class PID: public Controlador
{
    public:
        PID();
        PID(double Ts, int inputPin, int outputPin, double minOutput, double maxOutput) : Controlador(Ts, inputPin, outputPin, minOutput, maxOutput)
        {
            /**Este constructor recibe los sigueintes parámetros:
         *-        Ts:  Periodo de muestreo para el controlador en cuestión
         *-  inputPin:  Indica el ADC que será usado por el controlador para capturar los valores de la variable controlada
         *- outputPin:  Indica el DAC que usará el controlador
         *- maxOutput:  Valor de saturación (máximo) que presenta el sistema (voltios)
         *- minOutput:  Valor de saturación (mínimo) quepodrá presentar el sistema (voltios)
        */

        }

        void Compute();///<Este método realiza el cálculo de la salida del controlador PID y lo almacena en la variable salidaControlador
        virtual double Lectura();   ///<Sobreescribe el método Lectura que es un método Virtual Puro de la clase Controlador
        virtual void   Escritura(); ///<Sobreescribe el método Escritura que es un método Virtual Puro de la clase Controlador
        virtual void SetSampleTime(double sampleTime); ///<Este método cambia el periodo de muestreo, además adapta las ganancia Ki, Kd y Kp con respecto al nuevo Ts
        void SetPIDParameters(double kp, double ki, double kd); ///<Introduce los valores de las ganancias en el objeto PID
        static void InitResolution(int res);  ///<Este método define la resolución de los DACs y ADCs utilizados (10 bits por defecto)
        virtual ~PID();
        static int res;            ///<Resolución para los DACs y ADCs
    protected:
        double kp;                 ///<Ganancia proporcional del controlador
        double ki;                  ///<Ganancia integral del controlador
        double kd;                 ///<Ganancia derivativa del controlador
        double error;            ///<Error actual
        double prevError;    ///<Error anterior (se tiene en cuenta para el cálculo de la integral)
        double prevSalidaPlanta; ///<Salida anterior, la cual le entregó la planta al Arduino en la última iteración
        double iTerm;            ///<Término integral para la ecuación del PID
        double dTerm;           ///<Término derivativo para la ecuación del PID
        double pTerm;           ///<Término proporcional para la ecuación del PID
        int ys;                         ///<Almacena el valor que se desea sacar por el DAC
        int xen;                       ///<Almacena el valor que entrega el ADC utilizado
};

#endif // PID_H
