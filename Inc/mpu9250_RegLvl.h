/*
 * mpu9250.h
 *
 *  Created on: 14 лип. 2019 р.
 *      Author: wbc
 */


#ifndef MPU9250_REGLVL_H_
#define MPU9250_REGLVL_H_

#include <stm32f030x6.h>
#include <RegListMPU9250.h>
#include <stdbool.h>


#define OK_MPU9250 0
#define ERR_NOT_CONN_MPU9250 1
#define ERR_WRONG_PARAM_MPU9250 2
#define ERR_RXFIFO_NOT_EMPTY_STM32 4
#define ERR_NOT_CONN_AK8963 8

#define CS_ON GPIOA->BSRR=GPIO_BSRR_BR_4
#define CS_OFF GPIOA->BSRR=GPIO_BSRR_BS_4

typedef struct VectorRaw{
	int16_t x;
	int16_t y;
	int16_t z;
}  VectorRaw;
typedef uint8_t errorCode;


errorCode BeginMPU9250();
errorCode ReadRegistersMPU9250_Polling(uint8_t RegAdress, uint8_t Cnt0fBytes,uint8_t *Buffer,bool Increm);
errorCode ReadRegisterMPU9250_Polling(uint8_t RegAdress,uint8_t *Val);
//errorCode WriteRegisterAK_Polling(uint8_t RegAdress,uint8_t *Val);
errorCode WriteRegisterMPU9250_Polling(uint8_t RegAdress,uint8_t Data);
errorCode EndMPU9250();


void delay_smart_ms(uint32_t ms);

errorCode ReadRawOutMagAK8963( VectorRaw *RawMagVector);
errorCode ReadRawOutAccelMPU9250( VectorRaw *RawAccelVector);
errorCode ReadRawOutGyroMPU9250(VectorRaw *RawGyroVector);
bool isDataReadyAK8963();
bool isDataReadyMPU9250();
#endif /* MPU9250_REGLVL_H_ */







