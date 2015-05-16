#include <iostream>
#include "pid.h"

using namespace std;

int main()
{
    PID myPID(12,1,2,0,255);
    cout << myPID.GetSampleTime() << endl;
    cout << myPID.GetInputPin() << endl;
    cout << myPID.GetOutputPin() << endl;


    return 0;
}
