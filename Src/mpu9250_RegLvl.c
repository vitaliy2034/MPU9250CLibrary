/*
 * mpu9250.cpp
 *
 *  Created on: 14 лип. 2019 р.
 *      Author: vitaliy2034
 */

#include <mpu9250_RegLvl.h>

void delay_smart_ms(uint32_t ms){
	//TODO: write proper delay function
	//Here is example for stm32f030(you may change it)
	for(uint64_t i=0;i<ms*600 ;i++){
		__NOP();
	}
}

errorCode BeginMPU9250(){
	/*Enable clocking and reset */
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; //enable clocking of GPІО
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;	//enable clocking of SPI

	RCC->AHBRSTR|= RCC_AHBRSTR_GPIOARST;//Reset GPIO
	RCC->APB2RSTR|= RCC_APB2RSTR_SPI1RST;//Reset SPI
	RCC->AHBRSTR&= ~(RCC_AHBRSTR_GPIOARST);
	RCC->APB2RSTR&= ~(RCC_APB2RSTR_SPI1RST);
	/*Configure GPIO*/
	GPIOA->MODER |= //Configure GPIO to  OUT
			GPIO_MODER_MODER4_0 |//NSS
			//Configure GPIO to  AF
			GPIO_MODER_MODER5_1 | //SCK
			GPIO_MODER_MODER6_1 | //MISO
			GPIO_MODER_MODER7_1;  //MOSI
	GPIOA->OSPEEDR|=GPIO_OSPEEDER_OSPEEDR4;//speed choose NSS(MAX)

	SPI1->CR2 = 0x7 << SPI_CR2_DS_Pos |	//Data size
			SPI_CR2_FRXTH;	//fifo rx

	CS_OFF;
	SPI1->CR1 = SPI_CR1_MSTR | //Master mode
			SPI_CR1_SSM |   //Software configure slave management pin for MCU
			SPI_CR1_SSI |	//HI level of slave management pin for MCU
			(0x2 << SPI_CR1_BR_Pos) |	//SPEED
			SPI_CR1_CPHA |	//CPHA=1
			SPI_CR1_CPOL |	//CPOL=1
			SPI_CR1_SPE;

	uint8_t recive;//buffer
	errorCode err=WriteRegisterMPU9250_Polling(PWR_MGMT_1,128);//Reset device
	delay_smart_ms(120);
	err|=ReadRegisterMPU9250_Polling(WHO_AM_I_MPU9250,&recive);
	if(recive == 0x71|| recive ==0x73){
		err|= WriteRegisterMPU9250_Polling(PWR_MGMT_1,0x01);
		/*MPU9250`s I2C MASTER block configure to read/write from AK8963 then read AK8963_WHO_AM_I register*/
		err|=WriteRegisterMPU9250_Polling(I2C_SLV0_ADDR,0xC|128);//I2C address of AK8963 is 0xC.to read, 7 bit must be set
		err|=WriteRegisterMPU9250_Polling(I2C_SLV0_REG,AK8963_WHO_AM_I);//address in AK8963 from where mpu9250 start reading
		err|=WriteRegisterMPU9250_Polling(I2C_MST_CTRL,64);//enable delay the data ready interrupt until external sensor data is loaded - [6] bit
		err|=WriteRegisterMPU9250_Polling(I2C_MST_DELAY_CTRL,128);//Delays shadowing of external sensor data until all data is received - [7] bit
		err|=WriteRegisterMPU9250_Polling(I2C_SLV0_CTRL,128|1);//Enable slave 0 - [7] bit, Number of bytes to be read - [3:0] bits
		err|=WriteRegisterMPU9250_Polling(USER_CTRL,32);//Enable I2C Master of mpu9250
		delay_smart_ms(5);
		err|=ReadRegisterMPU9250_Polling(EXT_SENS_DATA_00,&recive);//read AK8963_WHO_AM_I
		if(recive != 0x48)
			return err|ERR_NOT_CONN_AK8963;
		/*configure AK8963 to 'continuous mode 2(100Hz)'*/
		err|=WriteRegisterMPU9250_Polling(I2C_SLV0_CTRL,0);//disable slave 0
		err|=WriteRegisterMPU9250_Polling(I2C_SLV0_REG,AK8963_CNTL1);//address in AK8963 from where mpu9250 start writing
		err|=WriteRegisterMPU9250_Polling(I2C_SLV0_ADDR,0xC);//I2C address of AK8963 is 0xC.to write, 7 bit must be cleared
		err|=WriteRegisterMPU9250_Polling(I2C_SLV0_DO,22);//Set continuous mode 2, 16 bit mode
		err|=WriteRegisterMPU9250_Polling(I2C_SLV0_CTRL,128|1);//Enable slave 0 - [7] bit, Number of bytes to be written - [3:0] bits
		delay_smart_ms(20);

		/*configure MPU9250 to read from AK8963_XOUT_L to AK8963_ST2*/
		err|=WriteRegisterMPU9250_Polling(I2C_SLV0_CTRL,0);//disable slave 0
		err|=WriteRegisterMPU9250_Polling(I2C_SLV0_ADDR,0xC|128);//I2C address of AK8963 is 0xC.to read, 7 bit must be set
		err|=WriteRegisterMPU9250_Polling(I2C_SLV0_REG,AK8963_XOUT_L);//address in AK8963 from where mpu9250 start reading
		err|=WriteRegisterMPU9250_Polling(I2C_SLV0_CTRL,128|7);//Enable slave 0 - [7] bit, Number of bytes to be read - [3:0] bits
		return err;
	}
	RCC->AHBRSTR|= RCC_AHBRSTR_GPIOARST;
	RCC->APB2RSTR|= RCC_APB2RSTR_SPI1RST;
	RCC->AHBRSTR&= ~(RCC_AHBRSTR_GPIOARST);
	RCC->APB2RSTR&= ~(RCC_APB2RSTR_SPI1RST);
	return err|ERR_NOT_CONN_MPU9250;
}

//
errorCode ReadRegisterMPU9250_Polling(uint8_t RegAdress,uint8_t *Val){
	while ((SPI1->SR & SPI_SR_BSY));
	if(SPI1->SR & SPI_SR_RXNE)
		return ERR_RXFIFO_NOT_EMPTY_STM32;
	if(RegAdress>126||RegAdress<0)
		return ERR_WRONG_PARAM_MPU9250;
	RegAdress|=128;
	CS_ON;
	*(uint8_t*)&SPI1->DR=RegAdress;
	while (!(SPI1->SR & SPI_SR_RXNE));
	*Val=*(uint8_t*)&SPI1->DR;
	*(uint8_t*)&(SPI1->DR) = 0;
	while (!(SPI1->SR & SPI_SR_RXNE));
	CS_OFF;
	*Val=*(uint8_t*)&(SPI1->DR);
	return OK_MPU9250;
}
errorCode ReadRegistersMPU9250_Polling(uint8_t RegAdress, uint8_t Cnt0fBytes,uint8_t *Buffer,bool Increm){
	while ((SPI1->SR & SPI_SR_BSY));
	if(SPI1->SR & SPI_SR_RXNE)
		return ERR_RXFIFO_NOT_EMPTY_STM32;
	if(RegAdress>126||RegAdress<0)
		return ERR_WRONG_PARAM_MPU9250;
	if(Increm&&(Cnt0fBytes+RegAdress>127)){
		return ERR_WRONG_PARAM_MPU9250;
	}else{
		if(Increm==false&&(RegAdress-Cnt0fBytes)<=0)
			return ERR_WRONG_PARAM_MPU9250;
	}
	RegAdress|=128;
	for(;Cnt0fBytes>0;Cnt0fBytes--,Buffer++){
		CS_ON;
		*(uint8_t*)&SPI1->DR=RegAdress;
		while (!(SPI1->SR & SPI_SR_RXNE));
		*Buffer=*(uint8_t*)&SPI1->DR;
		*(uint8_t*)&(SPI1->DR) = 0;
		while (!(SPI1->SR & SPI_SR_RXNE));
		CS_OFF;
		*Buffer=*(uint8_t*)&(SPI1->DR);
		(Increm)?RegAdress++:RegAdress--;
	}
	return OK_MPU9250;
}

errorCode WriteRegisterMPU9250_Polling(uint8_t RegAdress,uint8_t Data){
	//TODO: write proper write function
	//Here is example for stm32f030(you may change it)
	while ((SPI1->SR & SPI_SR_BSY));
	if(SPI1->SR & SPI_SR_RXNE)
		return ERR_RXFIFO_NOT_EMPTY_STM32;

	if(RegAdress>126||RegAdress<0)
		return ERR_WRONG_PARAM_MPU9250;

	CS_ON;//Chip Select pin of mpu9250 is set to low
	*(uint8_t*)&SPI1->DR=RegAdress;
	*(uint8_t*)&SPI1->DR=Data;
	while (SPI1->SR & SPI_SR_BSY);
	CS_OFF;//Chip Select pin of mpu9250 is set to low
	while(SPI1->SR&SPI_SR_RXNE)
		Data=*(uint8_t*) &(SPI1->DR);
	return OK_MPU9250;
}


//
inline errorCode ReadRawOutMagAK8963( VectorRaw *RawMagVector){
	return ReadRegistersMPU9250_Polling(EXT_SENS_DATA_00, 6, (uint8_t*)RawMagVector,true);
}
inline errorCode ReadRawOutGyroMPU9250(VectorRaw *RawGyroVector){
	errorCode err = ReadRegistersMPU9250_Polling(GYRO_ZOUT_L, 6, (uint8_t*)RawGyroVector,false);
	int16_t temp=RawGyroVector->x;
	RawGyroVector->x=RawGyroVector->z;
	RawGyroVector->z=temp;
	return err;
}
inline errorCode ReadRawOutAccelMPU9250( VectorRaw *RawAccelVector){
	errorCode err = ReadRegistersMPU9250_Polling(ACCEL_ZOUT_L, 6, (uint8_t*)RawAccelVector,false);
	int16_t temp=RawAccelVector->x;
	RawAccelVector->x=RawAccelVector->z;
	RawAccelVector->z=temp;
	return err;
}

bool isMagDataReady(){
	static VectorRaw PrevData;
	VectorRaw CurData;
	ReadRawOutMagAK8963(&CurData);
	if(CurData.x==PrevData.x && CurData.y==PrevData.y&&CurData.z==PrevData.z)
		return false;
	else{
		PrevData=CurData;
		return true;
	}
}
