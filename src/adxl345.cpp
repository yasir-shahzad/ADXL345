#include "ADXL345.h"

ADXL345::ADXL345() {
// Create I2C bus

	char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, ADXL345 I2C address is 0x53(83)
	ioctl(file, I2C_SLAVE, _ADXL345);

}

void ADXL345::enableMeasurement() {

	// Select Bandwidth rate register(0x2C)
	// Normal mode, Output data rate = 100 Hz(0x0A)
	char config[2]={0};
	config[0] = 0x2C;
	config[1] = 0x0A;
	write(file, config, 2);
	// Select Power control register(0x2D)
	// Auto-sleep disable(0x08)
	config[0] = 0x2D;
	config[1] = 0x08;
	write(file, config, 2);
	// Select Data format register(0x31)
	// Self test disabled, 4-wire interface, Full resolution, range = +/-2g(0x08)
	config[0] = 0x31;
	config[1] = 0x08;
	write(file, config, 2);
	sleep(1);

 }

void ADXL345::setAxisOffset(char reg, char offset) {
    write(file, &reg, 1);
    write(file, &offset, 1);
}

void ADXL345::RollandPitch(float& roll, float& pitch) {

	// Read 6 bytes of data from register(0x32)
	// xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
	char reg[1] = {0x32};
	write(file, reg, 1);
	char data[6] ={0};
	if(read(file, data, 6) != 6)
	{
		printf("Erorr : Input/output Erorr \n");
		exit(1);
	}
	else
	{
		// Convert the data to 10-bits
		xAccl = ((data[1] & 0x03) * 256 + (data[0] & 0xFF));
		if(xAccl > 511)
		{
			xAccl -= 1024;
		}

		yAccl = ((data[3] & 0x03) * 256 + (data[2] & 0xFF));
		if(yAccl > 511)
		{
			yAccl -= 1024;
		}

		zAccl = ((data[5] & 0x03) * 256 + (data[4] & 0xFF));
		if(zAccl > 511)
		{
			zAccl -= 1024;
		}
	}
		// Output data to screen
	//	printf("Acceleration in X-Axis : %d \n", xAccl);
	//	printf("Acceleration in Y-Axis : %d \n", yAccl);
	//	printf("Acceleration in Z-Axis : %d \n", zAccl);


        xAccl  = atan(-1 * xAccl / sqrt(pow(yAccl, 2) + pow(zAccl, 2))) * 180 / M_PI;
	    yAccl = atan(yAccl/sqrt(pow(xAccl,2) + pow(zAccl, 2))) * 180 / M_PI;
	

}
ADXL345::~ADXL345() {
}
