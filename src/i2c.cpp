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

	    I2CMaster::handlers[1]-> EV_handler();

	}

	void I2C1_ER_IRQHandler(void)
	{
	    I2CMaster::handlers[1]-> ER_handler();

	}
}

I2CMaster::I2CMaster(I2C::BaseRegisterType baseRegister)
{

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

		I2CMaster::handlers[1] = this;

	    // Step 1: Initialize I2C
	    //Program the peripheral input clock in the I2C_CR2 register in order to generate the correct timings
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

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



	    dynamic_access<I2C::BaseRegisterType, I2C::ControlRegister1Type>::reg_or(controlRegister1,
	    		I2C::ControlRegister1::ACK);

	    dynamic_access<I2C::BaseRegisterType, I2C::ControlRegister1Type>::reg_or(controlRegister1,
	    		I2C::ControlRegister1::PeripheralEnable);




	    // Initialization struct
//	    I2C_InitTypeDef I2C_InitStruct;
//	    I2C_InitStruct.I2C_ClockSpeed = 100000;
//	    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
//	    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
//	    I2C_InitStruct.I2C_OwnAddress1 = 0x00;
//	    I2C_InitStruct.I2C_Ack = I2C_Ack_Disable;
//	    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
//	    I2C_Init(I2Cx, &I2C_InitStruct);
//	    I2C_Cmd(I2Cx, ENABLE);



}

int I2CMaster::sendBytes(send_buffer_type sendBuffer, uint8_t address)
{

	bytesSent = 0;

	send_buf = sendBuffer;
	slaveAddress = address;

	//Set Start Bit
	dynamic_access<I2C::BaseRegisterType, I2C::ControlRegister1Type> ::reg_or(0x40005400U, I2C::ControlRegister1::Start);

//	//Clear Start bit by reading SR1 followed by writing DR with address
//	//send address with LSB reset to enter transmit mode
//	dynamic_access<I2C::StatusRegister1Type, I2C::StatusRegister1Type>::reg_get(statusRegister1);
//	dynamic_access<I2C::DataRegisterType, uint8_t>::reg_set(dataRegister, (address << 1));
//
//	//ADDR = 1, cleared by reading SR1 register followed by reading SR2
//	dynamic_access<I2C::StatusRegister1Type, I2C::StatusRegister1Type>::reg_get(statusRegister1);
//	dynamic_access<I2C::StatusRegister2Type, I2C::StatusRegister2Type>::reg_get(statusRegister2);
//
//	//TxE = 1, write Data1 in DR
//	dynamic_access<I2C::DataRegisterType, uint8_t>::reg_set(dataRegister, send_buf[bytesSent]);
//	bytesSent++;
//
//	//keep writing data
//	//TxE = 1, BTF = 1, program stop request


	return 1;
}

void I2CMaster::EV_handler()
{

//	reg_access<GPIOxRegisterType, GPIOxRegisterType, (GPIOxBaseRegisters::GPIO_B + RegisterOffsets::OutputDataRegisterOffset), stm32fxx::bits::BIT12>::reg_xor();

	uint16_t status;
	uint16_t temp;

	status = dynamic_access<I2C::BaseRegisterType, uint16_t>::reg_get(0x40005414);
		reg_access<GPIOxRegisterType, GPIOxRegisterType, (GPIOxBaseRegisters::GPIO_B + RegisterOffsets::OutputDataRegisterOffset), stm32fxx::bits::BIT12>::reg_xor();



	 if(status && I2C::StatusRegister1::StartBit){
		dynamic_access<I2C::BaseRegisterType, uint16_t>::reg_or(0x40005410, 0xE0);
	 }

	if(status && I2C::StatusRegister1::Address){
		//read SR2
		status = dynamic_access<I2C::BaseRegisterType, uint16_t>::reg_get(0x40005414);
		temp = 	dynamic_access<I2C::BaseRegisterType, I2C::StatusRegister1Type>::reg_get(0x40005418);
	}

	if(status && I2C::StatusRegister1::TransmitEmpty){
		if(bytesSent < 17){
			dynamic_access<I2C::BaseRegisterType, uint16_t>::reg_or(0x40005410, 0x00);
			bytesSent++;
		}
		if(bytesSent = 17){
//			dynamic_access<I2C::BaseRegisterType, uint16_t>::reg_or(0x40005410, 0x01);
			dynamic_access<I2C::BaseRegisterType, uint16_t>::reg_or(0x40005400, I2C::ControlRegister1::Stop);

		}
	}



//	if((dynamic_access<I2C::StatusRegister1Type, I2C::StatusRegister1Type>::reg_get(statusRegister1) & I2C::StatusRegister1::TransmitEmpty) && (bytesSent < 17)){
//		dynamic_access<I2C::DataRegisterType, uint8_t>::reg_set(dataRegister, send_buf[bytesSent]);
//		bytesSent++;
//	}
//
//	if((dynamic_access<I2C::StatusRegister1Type, I2C::StatusRegister1Type>::reg_get(statusRegister1) & I2C::StatusRegister1::TransmitEmpty) && (bytesSent = 17)){
//		dynamic_access<I2C::DataRegisterType, uint8_t>::reg_set(dataRegister, send_buf[bytesSent]);
//		dynamic_access<I2C::ControlRegister1Type, I2C::ControlRegister1Type>::reg_or(controlRegister1, I2C::ControlRegister1::Stop);
//		bytesSent++;
//	}

}

void I2CMaster::ER_handler()
{

	reg_access<GPIOxRegisterType, GPIOxRegisterType, (GPIOxBaseRegisters::GPIO_B + RegisterOffsets::OutputDataRegisterOffset), stm32fxx::bits::BIT12>::reg_xor();
	  uint8_t nCount = 0xFFFF;
		while(nCount--)
	  {
	  }
	reg_access<GPIOxRegisterType, GPIOxRegisterType, (GPIOxBaseRegisters::GPIO_B + RegisterOffsets::OutputDataRegisterOffset), stm32fxx::bits::BIT12>::reg_xor();


}




