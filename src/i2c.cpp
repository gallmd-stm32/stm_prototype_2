/*
 * i2c.cpp
 *
 *  Created on: Jan 29, 2019
 *      Author: matt
 */




#include "i2c.h"

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

	    // Initialization struct
	    I2C_InitTypeDef I2C_InitStruct;

	    // Step 1: Initialize I2C
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

	    dynamic_access<I2C::ControlRegister2Type, I2C::ControlRegister2Type>::reg_or(controlRegister2,
	    		I2C::ControlRegister2::BufferInterruptEnable |
				I2C::ControlRegister2::ErrorInterruptEnable |
				I2C::ControlRegister2::EventInterruptEnable);

	    dynamic_access<I2C::ClockControlRegisterType, I2C::ClockControlRegisterType>::reg_or(clockControlRegister,
	    		I2C::OwnAddressRegister::AddressMode);

	    dynamic_access<I2C::ControlRegister1Type, I2C::ControlRegister1Type>::reg_not(controlRegister1,
	    		I2C::ControlRegister1::ACK);

	    I2C::ControlRegister1::ACK;



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

	//Set Start Bit
	//Clear Start bit by reading SR1 followed by writing DR with address
	//ADDR = 1, cleared by reading SR1 register followed by reading SR2
	//TxE = 1, write Data1 in DR
	//keep writing data
	//TxE = 1, BTF = 1, program stop request
	I2C::ControlRegister1::Stop;

	return 1;
}

extern "C"{

	void I2C2_EV_IRQHandler(void)
	{

	}

	void I2C2_ER_IRQHandler(void)
	{

	}
}
