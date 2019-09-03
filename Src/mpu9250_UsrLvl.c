/*
 * mpu9250_UsrLvl.cpp
 *
 *  Created on: 18 серп. 2019 р.
 *      Author: vitlaiy2034
 */
#include <mpu9250_UsrLvl.h>

AccelCfg cfgAccelScale=0;	//Copy of ACCEL_CONFIG (Register 28)
GyroCfg cfgGyroScale=0;		//Copy of GYRO_CONFIG (Register 27)

//Accelerometer Functions
errorCode SetAccelScale(AccelCfg Scale){
	if(Scale<ACCEL_FS_2G||ACCEL_FS_16G<Scale)//check is parameters wrong
		return ERR_WRONG_PARAM_MPU9250;
	cfgAccelScale=Scale;//save to global variable Scale
	return WriteRegisterMPU9250_Polling(ACCEL_CONFIG, Scale);//write Scale to Accelerometer
}

errorCode SetupAccelBandwidthAndRate(AccelCfg OutRateParam){
	if(OutRateParam>ACCEL_BW_1046Hz_Rate_4kHz||OutRateParam<ACCEL_BW_218Hz_Rate_1kHz)//check is parameters wrong
		return ERR_WRONG_PARAM_MPU9250;
	return WriteRegisterMPU9250_Polling(ACCEL_CONFIG2, OutRateParam);//write Parameter to Accelerometer
}

errorCode SetupAccelBandwidthAndRateLP(AccelCfg OutRateParam){
	if(OutRateParam>ACCEL_LP_500Hz||OutRateParam<ACCEL_LP_0Hz26)//check is parameters wrong
		return ERR_WRONG_PARAM_MPU9250;
	return WriteRegisterMPU9250_Polling(LP_ACCEL_ODR, OutRateParam)|WriteRegisterMPU9250_Polling(ACCEL_CONFIG2, OutRateParam);
}

errorCode GetAccelMeas(Vector3D * AccelMeas){
	VectorRaw Mes;
	errorCode err=ReadRawOutAccelMPU9250(&Mes);
	if(err)
		return err;
	AccelMeas->x=(float)Mes.x/(16.368f/(1<<(cfgAccelScale>>3)));
	AccelMeas->y=(float)Mes.y/(16.368f/(1<<(cfgAccelScale>>3)));
	AccelMeas->z=(float)Mes.z/(16.368f/(1<<(cfgAccelScale>>3)));
	return err;
}

errorCode GetAccelAMMeas(Vector3D * AccelMeas, uint8_t count){
	uint32_t x,y,z;
	errorCode err;
	VectorRaw Mes;
	for (uint8_t i = 0; i < count; ++i) {
		err=ReadRawOutAccelMPU9250(&Mes);
		if(err)return err;
		x+=Mes.x;
		y+=Mes.y;
		z+=Mes.z;
	}
	AccelMeas->x=((float)Mes.x/count)/(16.368f/(1<<(cfgAccelScale>>3)));
	AccelMeas->y=((float)Mes.y/count)/(16.368f/(1<<(cfgAccelScale>>3)));
	AccelMeas->z=((float)Mes.z/count)/(16.368f/(1<<(cfgAccelScale>>3)));
	return err;
}

//Gyroscope Functions
errorCode SetGyroScale(GyroCfg Scale){
	if(GYRO_FS_250DPS>Scale||Scale>GYRO_FS_2000DPS)//check is parameters wrong
		return ERR_WRONG_PARAM_MPU9250;
	cfgGyroScale&=~(GYRO_FS_2000DPS);//this two commands need to write only Scale parameter, and don`t change another bits, like Fchoice_b
	cfgGyroScale|=Scale;
	return WriteRegisterMPU9250_Polling(GYRO_CONFIG, cfgGyroScale);//write Scale to Gyroscope
}
errorCode SetupGyroBandwidthAndRate(GyroCfg OutRateParam){
	if(OutRateParam<GYRO_BW_250Hz_Rate_8kHz||GYRO_BW_8800Hz_Rate_32kHz<OutRateParam)//check is parameters wrong
			return ERR_WRONG_PARAM_MPU9250;
		//cfgGyroScale=OutRateParam;
		cfgGyroScale&=(~3);//this command clear Fchoise_b in buffer
		if(OutRateParam<GYRO_BW_8800Hz_Rate_32kHz){
			return WriteRegisterMPU9250_Polling(MPU_CONFIG, OutRateParam)|WriteRegisterMPU9250_Polling(GYRO_CONFIG, cfgGyroScale);
		}
		else{
			OutRateParam=OutRateParam>>3;
			cfgGyroScale|=OutRateParam;
			return WriteRegisterMPU9250_Polling(GYRO_CONFIG, cfgGyroScale);
		}
}
errorCode GetGyroMeas(Vector3D * GyroMeas){
		VectorRaw Mes;
		errorCode err=ReadRawOutGyroMPU9250(&Mes);
		if(err)
			return err;
		GyroMeas->x=(float)Mes.x/(16.368f/(1<<(cfgGyroScale>>3)));
		GyroMeas->y=(float)Mes.y/(16.368f/(1<<(cfgGyroScale>>3)));
		GyroMeas->z=(float)Mes.z/(16.368f/(1<<(cfgGyroScale>>3)));
		return err;
}
//Magnetometer functions

