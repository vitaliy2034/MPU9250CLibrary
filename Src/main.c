/**
 ******************************************************************************
 * @file    main.c
 * @author  vitaliy2034
 * @version V1.0
 * @brief   Default main function.
 ******************************************************************************
 */

#include <mpu9250_UsrLvl.h>
#include <sys/_stdint.h>
#include <malloc.h>

int main(void) {

	errorCode err=BeginMPU9250();
	Vector3D *v=malloc(sizeof(Vector3D));
	err|=SetupAccelBandwidthAndRate(ACCEL_BW_21Hz_Rate_1kHz);
	err|=SetupGyroBandwidthAndRate(GYRO_BW_8800Hz_Rate_32kHz);
	for(;;){
		err|=GetAccelMeas(v);
		//err|=GetGyroMeas(v);
	}
}
