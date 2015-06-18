#include <pid.h>

//falta el anti-windup y la función para manual y automático

int PID::res = 10; ///<Esta variable está declarada como estática, pero aquí se define. Resolución de 10 bits por defecto

/**
*
*Esta función es el corazón del PID, lleva a cabo el cálculo del término integral, el derivativo y el proporcional para finalmente calcular
*la salida del controlador, además hace uso de las funciones Lectura (la cual retorna el valor del voltaje a la entrada del controlador)
*y Escritura (la cual saca el valor del voltaje calculado en el PID a través del DAC que se esté utilizando).
*/
void PID::Compute()
{
    salidaPlanta = Lectura(); //Obtiene el valor actual de la variable a controlar
    error = referencia - salidaPlanta;
    pTerm = kp*error;
    iTerm += (ki*(error+prevError))/2;  //Aproximación bilinal de la integral, Ki es incluido en los cálculos para evitar problemas en los cambios de sintonización
    dTerm = -kd*(salidaPlanta-prevSalidaPlanta); //Derivada de la medición (anti-derivative kick)
    salidaControlador = pTerm + iTerm + dTerm;
    prevError = error;
    prevSalidaPlanta = salidaPlanta; //Almacena el último valor de la variable controlada para cálculos posteriores
    Escritura();  //Escribe el valor calculado por el PID en el DAC
}

void PID::SetSampleTime(double sampleTime)
{
    ///<Este método sobreescribe al de la clase controlador
    ///<Si el periodo de muestreo en el PID es cambiado en tiempo de ejecución, las constantes deben re-ajustarse a dichos cambios
    double tasa;
    tasa = sampleTime/Ts;
    Ts = sampleTime;
    kp = kp; //La proporcional no depende del perido de muestreo
    ki*=tasa;
    kd/=tasa;
}

/**
*@brief Esta función implementa el método virtual Lectura() de la clase base controlador
*
*Lo que hace es capturar el valor del voltaje que esté presente en el ADC (indicado previamente).
*La varible 'res' indica la resolución utilizada por los conversores.
*@return El valor en voltios (valor real) de la variable que se está controlando.
*/
double PID::Lectura()
{
    xen = analogRead(pinEntrada);
    return ((salidaMaxima - salidaMinima) /res)*xen + salidaMinima; //retorna el voltaje
}


/**
    *@brief Esta función implementa el método virtual Escritura definido previamente en la clase base Controlador
    *
    *Lo que hace es verificar que el valor calculado no se encuentre fuera de los rangos límite establecidos
    *y posteriormente enviar dicho valor por el DAC (indicado por pinSalida) hacia la planta que está siendo controlada
    */
void PID::Escritura()
{
    if (salidaControlador > salidaMaxima)
		salidaControlador = salidaMaxima;
	else if (salidaControlador < salidaMinima)
		salidaControlador = salidaMinima;

	ys = (res/(salidaMaxima-salidaMinima))*(salidaControlador-salidaMinima); //Calcula el valor apropiado para el DAC
	analogWrite(pinSalida,ys);
}



/**
*@brief Este es un método estático el cual permite indicar la resolución tanto para los DACs y ADCs
*
*Este método debe ser llamado antes de la puesta en marcha del controlador para evitar posibles comportamientos inconsistentes
*por defecto la resolución utilizada será de 10 bits.
*Se recomiendo hace uso de este método previo a la declaración de cualquier objeto de tipo controlador.
*/
void PID::InitResolution(int rs)
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

/************************************************/
/***** Setters and Getters for the base class ***/
/************************************************/


/**
    *@brief Esta función permite indicar al objeto controlador,cuales será los valores de las ganancias en el sistema
    *
    *Este método recibe el valor de las ganancias calculadas por el diseñador en tiempo contínuo
    *y las digitaliza con respecto al periodo de muestreo indicado previamente.
    *Debe ser llamada antes de cualquier acción de cálculo por parte del controlador.
    *Se recomienda hacer uso de este método inmediatamente después del constructor.
    *@param kp Es la ganancia proporcional del controlador PID
    *@param ki Es la ganancia del término integral del controlador PID
    *@param kd Es la ganancia del término derivativo del controlador PID
    */
void PID::SetPIDParameters(double P, double I, double D)
{
    kp = P;
    ki  = I*Ts;
    kd = D/Ts;
}


PID::~PID()
{
    //dtor
}
