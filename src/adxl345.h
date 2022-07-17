#include <iostream>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <i2c/smbus.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

using namespace std;

#define _ADXL345 0x53

class ADXL345
{
private:
    int file;
    float xAccl, yAccl, zAccl;

public:
    ADXL345();
    void enableMeasurement();
    void setAxisOffset(char, char);
    void RollandPitch(float&, float&);

    ~ADXL345();
};

