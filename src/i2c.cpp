/*
 * i2c.cpp
 *
 *  Created on: Jan 29, 2019
 *      Author: matt
 */




#include "i2c.h"

extern "C"{

	void I2C1_EV_IRQHandler(void)
	{

	    I2CMaster::handlers[0]-> EV_handler();

	}

	void I2C1_ER_IRQHandler(void)
	{
	    I2CMaster::handlers[0]-> ER_handler();

	}
}

I2CMaster::I2CMaster(I2C::BaseRegisterType baseRegister)
{
		I2CMaster::handlers[0] = this;

    	// Step 1: Initialize I2C
    	//Program the peripheral input clock in the I2C_CR2 register in order to generate the correct timings
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

		clockControlRegister = baseRegister + I2C::ClockControlRegister::RegiserOffset;
		controlRegister1 = baseRegister + I2C::ControlRegister1::RegisterOffset;
		controlRegister2 = baseRegister + I2C::ControlRegister2::RegisterOffset;
		dataRegister = baseRegister + I2C::DataRegister::RegisterOffset;
		filterRegister = baseRegister + I2C::FilterRegister::RegisterOffset;
		ownAddressRegister = baseRegister + I2C::OwnAddressRegister::RegisterOffset;
		ownAddressRegister2 = baseRegister + I2C::OwnAddressRegister2::RegisterOffset;
		statusRegister1 = baseRegister + I2C::StatusRegister1::RegisterOffset;
		statusRegister2 = baseRegister + I2C::StatusRegister2::RegisterOffset;
		triseRegister = baseRegister + I2C::TRiseRegiser::RegisterOffset;

		I2CMaster::init();




}

void I2CMaster::init()
{
    dynamic_access<I2C::BaseRegisterType, I2C::ControlRegister1Type>::reg_not(controlRegister1,
    		I2C::ControlRegister1::SoftwareReset);

    //set frequency bits
    dynamic_access<I2C::BaseRegisterType, I2C::ControlRegister2Type>::reg_or(controlRegister2, 0x10U);

    //configure the clock control registers
    dynamic_access<I2C::BaseRegisterType, I2C::ClockControlRegisterType>::reg_or(0x4000541CU, 0x50U);

    //configure the rise time register
    dynamic_access<I2C::BaseRegisterType, I2C::TRiseRegisterType>::reg_or(triseRegister, 0x11U);

    //program the I2C_CR1 register to enable the peripheral
    dynamic_access<I2C::BaseRegisterType, I2C::ControlRegister2Type>::reg_or(controlRegister2,
    		I2C::ControlRegister2::BufferInterruptEnable |
			I2C::ControlRegister2::ErrorInterruptEnable |
			I2C::ControlRegister2::EventInterruptEnable);



    dynamic_access<I2C::BaseRegisterType, uint16_t>::reg_or(controlRegister1,
    		I2C::ControlRegister1::ACK);

    dynamic_access<I2C::BaseRegisterType, I2C::ControlRegister1Type>::reg_or(controlRegister1,
    		I2C::ControlRegister1::PeripheralEnable);

}

int I2CMaster::sendBytes(I2C::send_buffer_type sendBuffer, uint8_t address)
{

	bytesSent = 0;
	dataSent = false;

	send_buf = sendBuffer;
	slaveAddress = address;
    dynamic_access<I2C::BaseRegisterType, uint16_t>::reg_or(controlRegister1,
    		I2C::ControlRegister1::ACK);

	//Set Start Bit
	//0x40005400U
	dynamic_access<I2C::BaseRegisterType, I2C::ControlRegister1Type> ::reg_or(controlRegister1, I2C::ControlRegister1::Start);




	return 1;
}

void I2CMaster::EV_handler()
{

	uint16_t status;
	uint16_t temp;

	//0x40005414
	status = dynamic_access<I2C::BaseRegisterType, uint16_t>::reg_get(statusRegister1);
	reg_access<GPIOxRegisterType, GPIOxRegisterType, (GPIOxBaseRegisters::GPIO_B + RegisterOffsets::OutputDataRegisterOffset), stm32fxx::bits::BIT12>::reg_xor();

	 if(status & I2C::StatusRegister1::StartBit){

		 //send address
		 //0x40005410
		 dynamic_access<I2C::BaseRegisterType, uint16_t>::reg_set(dataRegister, 0xE0);

	 }

	if(status & I2C::StatusRegister1::Address){

		//read SR2
		//0x40005414
		status = dynamic_access<I2C::BaseRegisterType, uint16_t>::reg_get(statusRegister1);

		//0x40005418
		temp = 	dynamic_access<I2C::BaseRegisterType, uint16_t>::reg_get(statusRegister2);

	}

	if((status & I2C::StatusRegister1::TransmitEmpty)){ 	//& (status & I2C::StatusRegister1::ByteTransferFinished)

		if((bytesSent <= 17) & (!dataSent)){

			//0x40005410
			dynamic_access<I2C::BaseRegisterType, uint8_t>::reg_set(dataRegister, send_buf[bytesSent]);
			bytesSent++;

		}

		if((bytesSent > 17) & (!dataSent)){

			dataSent = true;
			//0x40005400
			dynamic_access<I2C::BaseRegisterType, uint16_t>::reg_or(I2CMaster::controlRegister1, I2C::ControlRegister1::Stop);

		}
	}


}

void I2CMaster::ER_handler()
{

	dynamic_access<I2C::BaseRegisterType, I2C::ControlRegister1Type>::reg_or(I2CMaster::controlRegister1, I2C::ControlRegister1::SoftwareReset);
	I2CMaster::init();

}




