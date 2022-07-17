#include "ADXL345.h"



int main(){
    float rollValue, pitchValue;
    ADXL345 obj;
    obj.enableMeasurement();
    while(true){
        obj.RollandPitch(rollValue, pitchValue);
        usleep(1E6);
    }
    
    return 0;
}