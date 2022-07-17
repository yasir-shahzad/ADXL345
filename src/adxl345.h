// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADXL345
// This code is designed to work with the ADXL345_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=ADXL345_I2CS#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

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

