/*
 * mpu9250_SetupParams.h
 *
 *  Created on: 23 серп. 2019 р.
 *      Author: vitlaiy2034
 */

#ifndef MPU9250_SETUPPARAMS_H_
#define MPU9250_SETUPPARAMS_H_
//Accelerometer Full Scale :
#define ACCEL_FS_2G (0<<3) //+-2g
#define ACCEL_FS_4G (1<<3) //+-4g
#define ACCEL_FS_8G (2<<3) //+-8g
#define ACCEL_FS_16G (3<<3)//+-16g

//Accelerometer Data Rates and Bandwidths (Normal Mode)
//Structure:ACCEL_Bandwidth(Hz)_DataRate(kHz)

#define ACCEL_BW_1046Hz_Rate_4kHz (1<<3)	//Filter:Dec1  delay:O.503 ms
#define ACCEL_BW_218Hz_Rate_1kHz 0			//Filter:DLPF* delay:1.88  ms
#define ACCEL_BW_99Hz_Rate_1kHz  2			//Filter:DLPF* delay:2.88  ms
#define ACCEL_BW_45Hz_Rate_1kHz  3			//Filter:DLPF* delay:4.88  ms
#define ACCEL_BW_21Hz_Rate_1kHz  4			//Filter:DLPF* delay:8.87  ms
#define ACCEL_BW_10Hz_Rate_1kHz  5			//Filter:DLPF* delay:16.83 ms
#define ACCEL_BW_5Hz_Rate_1kHz	 6			//Filter:DLPF* delay:32.48 ms
#define ACCEL_BW_420Hz_Rate_1kHz  7			//Filter:Dec2  delay:1.38  ms
//For more information refer to Register Manual 9250 register 29
//*Digital Low Pass Filter

/*Accelerometer Data Rates and Bandwidths (Low-Power Mode)
Structure:ACCEL_LP_DataRate(Hz) Bandwidth:1.1kHz*/
#define ACCEL_LP_0Hz26	0
#define ACCEL_LP_0Hz49	1
#define ACCEL_LP_0Hz98	2
#define ACCEL_LP_1Hz95	3
#define ACCEL_LP_3Hz91	4
#define ACCEL_LP_7Hz81	5
#define ACCEL_LP_15Hz63	6
#define ACCEL_LP_31Hz25	7
#define ACCEL_LP_62Hz50	8
#define ACCEL_LP_125Hz	9
#define ACCEL_LP_250Hz	10
#define ACCEL_LP_500Hz	11

//Gyroscope Full Scale:
#define GYRO_FS_250DPS (0<<3) //+-250 deg/s
#define GYRO_FS_500DPS (1<<3) //+-500 deg/s
#define GYRO_FS_1000DPS (2<<3) //+-1000 deg/s
#define GYRO_FS_2000DPS (3<<3)//+-2000 deg/s

//Gyroscope and Temperature sensor Data Rates and Bandwidths. Filter:DLPF*
//Structure:GYRO_Bandwidth(Hz)_DataRate(kHz)
#define GYRO_BW_250Hz_Rate_8kHz 0	//Delay:O.97 ms 	BW(TempSens):4000Hz Delay(TempSens):0.04 ms
#define GYRO_BW_184Hz_Rate_1kHz 1	//Delay:2.9 ms 		BW(TempSens):188Hz 	Delay(TempSens):1.9 ms
#define GYRO_BW_92Hz_Rate_1kHz 2	//Delay:3.9 ms 		BW(TempSens):98Hz 	Delay(TempSens):2.8 ms
#define GYRO_BW_41Hz_Rate_1kHz 3	//Delay:5.9 ms 		BW(TempSens):42Hz 	Delay(TempSens):4.8 ms
#define GYRO_BW_20Hz_Rate_1kHz 4	//Delay:9.9 ms 		BW(TempSens):20Hz 	Delay(TempSens):8.3 ms
#define GYRO_BW_10Hz_Rate_1kHz 5	//Delay:17.85 ms 	BW(TempSens):10Hz 	Delay(TempSens):13.4 ms
#define GYRO_BW_5Hz_Rate_1kHz 6		//Delay:33.48 ms 	BW(TempSens):5Hz 	Delay(TempSens):18.6 ms
#define GYRO_BW_3600Hz_Rate_8kHz 7	//Delay:O.17 ms		BW(TempSens):4000Hz Delay(TempSens):0.04 ms

#define GYRO_BW_3600Hz_Rate_32kHz 16	//Delay:O.11 ms 	BW(TempSens):4000Hz Delay(TempSens):0.04 ms
#define GYRO_BW_8800Hz_Rate_32kHz 8		//Delay:O.064 ms 	BW(TempSens):4000Hz Delay(TempSens):0.04 ms
//For more information refer to Register Manual 9250 register 27,26
//*Digital Low Pass Filter

#endif /* MPU9250_SETUPPARAMS_H_ */
