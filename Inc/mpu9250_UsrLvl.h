/*
 * mpu9250_UsrLvl.h
 *
 *  Created on: 14 серп. 2019 р.
 *      Author: vitlaiy2034
 */

#ifndef MPU9250_USRLVL_H_
#define MPU9250_USRLVL_H_
#include<mpu9250_RegLvl.h>
#include<mpu9250_SetupParams.h>
#include <math.h>

typedef struct Vector3D{
	float x;
	float y;
	float z;
}Vector3D;

typedef uint8_t AccelCfg;
typedef uint8_t GyroCfg;
typedef uint8_t MagCfg;


//Setup MPU9250 and AK8963
errorCode SetAccelScale(AccelCfg Scale);//Setup accelerometer full scale range*
errorCode SetGyroScale(GyroCfg Scale);//Setup gyroscope full scale range*


//Setup Accelerometer data rate and bandwidth of HARDWARE DIGITAL LOW PASS FILTER(DLPF) or Dec1 or Dec2
errorCode SetupAccelBandwidthAndRate(AccelCfg OutRateParam);//Setup Accelerometer Data Rates and Bandwidths  (Normal Mode)*
errorCode SetupAccelBandwidthAndRateLP(AccelCfg OutRateParam);//Setup Accelerometer Data Rates and Bandwidths (Low Power Mode)*
//*For more information refer to Register Manual of MPU9250 (Registers 28,29,30)

//Setup Gyroscope and Temperature data rate and bandwidth of HARDWARE DIGITAL LOW PASS FILTER(DLPF)(if used)
errorCode SetupGyroBandwidthAndRate(GyroCfg OutRateParam);//Setup Gyroscope and Temperature sensor Data Rates and Bandwidths  *
//*For more information refer to Register Manual of MPU9250 (Registers 26,27)

//Read measurements NO SOFTWARE FILTER
errorCode GetMagMeas(Vector3D * MagMeas);//in uT
errorCode GetAccelMeas(Vector3D * AccelMeas);//in mg
errorCode GetGyroMeas(Vector3D * GyroMeas);//in deg/s
//Read average measurements
errorCode GetMagAMMeas(Vector3D * MagMeas, uint8_t count);
errorCode GetAccelAMMeas(Vector3D * AccelMeas, uint8_t count);
errorCode GetGyroAMMeas(Vector3D * GyroMeas, uint8_t count);
//Is Data ready function


#endif /* MPU9250_USRLVL_H_ */
