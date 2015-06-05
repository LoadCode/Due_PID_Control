#ifndef PID_H
#define PID_H
#include "controlador.h"

class PID: public Controlador
{
    public:
        PID();
        PID(double Ts, int inputPin, int outputPin, double minOutput, double maxOutput) : Controlador(Ts, inputPin, outputPin, minOutput, maxOutput)
        {
            /**this constructor receives the following parameters:
                 Ts:  Sample time for the controller
            inputPin:  indicates the ADC input pin that will be used to capture the process variable
          outputPin:  indicates the DAC output pin that will be used to control the process variable
        maxOutput:  maximum saturation value for the system (for anti-windup)
         minOutput:  minimum saturation value for the system
        **/
        }

        void Compute();
        void SetSampleTime(double sampleTime); //In pid, if sample time is changed in execution time, kp, ki and kd need to be adapted
        virtual double Lectura(); //Override Lectura which is a pure virtual method
        void SetPIDParameters(double kp, double ki, double kd);
        double GetSampleTime();
        int GetInputPin();
        int GetOutputPin();
        virtual ~PID();
    private:
        double kp;
        double ki;
        double kd;
        double error;         //actual error
        double prevError; //previous error
        double prevSalidaPlanta; // previous plant output to Arduino
        double iTerm;        //Integral term of PID equation
        double dTerm;      //Derivative term of PID equation
        double pTerm;       //Proportional term of PID equation
};

#endif // PID_H
