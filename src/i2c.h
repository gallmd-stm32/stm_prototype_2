/*
 * i2c.h
 *
 *  Created on: Jan 25, 2019
 *      Author: matt
 */

#ifndef I2C_H_
#define I2C_H_

#include "registers.h"




namespace I2C
{

	typedef uint32_t BaseRegisterType;
	typedef uint32_t ControlRegister1Type;
	typedef uint32_t ControlRegister2Type;
	typedef uint32_t OwnAddressRegisterType;
	typedef uint32_t OwnAddressRegister2Type;
	typedef uint32_t DataRegisterType;
	typedef uint32_t StatusRegister1Type;

	namespace BaseRegisters
	{

		constexpr BaseRegisterType I2C1_Base = 0x40005400U;
		constexpr BaseRegisterType I2C2_Base = 0x40005800U;
		constexpr BaseRegisterType I2C3_Base = 0x40005C00U;

	}


	/**
	 * @brief - I2C_CR1 - I2C control register 1
	 *  		Reset State = 0x00000000U;
	 *  		Address Offset = 0x00000000U;
	 *
	 *  		Note: When the STOP, START, or PEC bit is set, the software must
	 *  		not perform any write access to I2C_CR1 before this bit is cleared
	 *  		by hardware. Otherwise a second request may be sent.
	 */
	namespace ControlRegister1
	{

		constexpr ControlRegister1Type RegisterOffset = 0x00000000U;
		constexpr ControlRegister1Type RegisterReset = 0x00000000U;
		/**
		  * @brief  When set, I2C is under reset state
		  * 		Before resetting this bit, make sure the I2C lines are released and the bus is free
		  *
		  * 		0: I2C not under Reset
		  * 		1: I2C under Reset
		  *
		  * 		note: this bit can be used to reinitialize the peripheral after an error or a locked state
		  */
		constexpr ControlRegister1Type SoftwareReset = stm32fxx::bits::BIT15;
		/**
		 * @brief This bit is set and cleared by software, and cleared by hardware
		 * 			when PE=0
		 *
		 * 			0: Releases SMBA pin high.  Alert response address header followed by NACK
		 * 			1: Drives SMBA pin low. Alert response address header followed by ACK
		 *
		 */
		constexpr ControlRegister1Type Alert = stm32fxx::bits::BIT13;
		/**
		 * @brief Packet Error Checking - This bit is set and cleared by software,
		 * 			and cleared by hardware when PEC is transferred or by a START
		 * 			or a STOP condition, or when PE = 0
		 *
		 * 			0: No PEC transfer
		 * 			1: PEC transfer (in TX or RX mode)
		 *
		 * 			note: PEC calculation is corrupted by arbitration loss
		 *
		 */
		constexpr ControlRegister1Type PEC = stm32fxx::bits::BIT12;
		/**
		 * @brief POS - Acknowledge/PEC position (for data reception)
		 *
		 * 			this bit is wet and cleared by software, and cleared by hardware
		 * 			when PE =0
		 *
		 * 			0: ACK controls the (N)ACK of the current byte being received in
		 * 			the shift register.  The PEC bit indicates that current byte in the
		 * 			shift register is a PEC.
		 *
		 * 			1: ACK bit controls the (N)ACK of the next byte which will be
		 * 			received in the shift register.  The PEC bit indicates that the next
		 * 			byte in the shift register is a PEC
		 *
		 * 			note: The POS bit must be used only in 2 byte reception configuration in master mode.
		 * 			It must be configured before data reception starts.
		 */
		constexpr ControlRegister1Type POS = stm32fxx::bits::BIT11;
		/**
		 * @brief ACK - Acknowledge Enable
		 *
		 * 			This bit is set and cleared by software, and cleared by
		 * 			hardware when PEC = 0
		 *
		 * 			0: No Acknowledge returned
		 * 			1: Acknowledge returned after a byte is received (matched address
		 * 			or data)
		 *
		 */
		constexpr ControlRegister1Type ACK = stm32fxx::bits::BIT10;
		/**
		 * @brief Stop Generation
		 *
		 * 			This bit is set and cleared by software, and cleared by
		 * 			hardware when a STOP is detected,it is set by hardware
		 * 			when a timeout error is detected.
		 *
		 * 			In Master Mode:
		 * 			0: No Stop generation
		 * 			1: Stop generation after the current byte transfer or after
		 * 			the current START condition is sent
		 *
		 * 			In Slave Mode:
		 * 			0: No Stop generation
		 * 			1: Release the SCL and SDA lines after the current byte transfer
		 */
		constexpr ControlRegister1Type Stop = stm32fxx::bits::BIT9;
		/**
		 * @brief START - Start generation
		 *
		 * 			This bit is set and cleared by software, and cleared by
		 * 			hardware when start is sent or PEC = 0
		 *
		 * 			In Master Mode:
		 * 			0:No START generation
		 * 			1:Repeated START generation
		 *
		 * 			In Slave Mode:
		 * 			0: No START generation
		 * 			1: START generation when the bus is free
		 */
		constexpr ControlRegister1Type Start = stm32fxx::bits::BIT8;
		/**
		 * @brief NO STRETCH - Clock Stretch Disable (Slave Mode)
		 *
		 * 		This bit is used to disable clock stretching in slave mode
		 * 		when ADDR or BTF flags are set, until it is reset by software
		 *
		 * 		0: Clock stretching enabled
		 * 		1: Clock stretching diabled
		 *
		 */
		constexpr ControlRegister1Type NoStretch = stm32fxx::bits::BIT7;
		/**
		 * @brief General Call Enable
		 *
		 * 		0: General call disabled: address 0x00h is NACK'd
		 * 		1: General call enabled: address 0x00h is ACK'd
		 */
		constexpr ControlRegister1Type GeneralCallEnbable = stm32fxx::bits::BIT6;
		/**
		 * @brief ENPEC - PEC Enable
		 *
		 * 			0: PEC calculation disabled
		 * 			1: PEC calculation enabled
		 *
		 */
		constexpr ControlRegister1Type PECEnable = stm32fxx::bits::BIT5;
		/**
		 * @brief ENARP - ARP enable
		 *
		 * 			0: ARP disabled
		 * 			1: ARP enabled
		 *
		 * 			-SMBus device default address recognized if SMBTYPE = 0
		 * 			-SMBus host address recognized if SMBTYPE = 1
		 */
		constexpr ControlRegister1Type ARPEnable = stm32fxx::bits::BIT4;
		/**
		 * @brief SUMBTYPE - SMBus Type
		 *
		 * 			0: SMBus Device
		 * 			1: SMBus Host
		 *
		 */
		constexpr ControlRegister1Type SMBusType = stm32fxx::bits::BIT3;
		/**
		 * @brief SMBus - SMBus Mode
		 *
		 * 			0: I2C Mode
		 * 			1: SMBus Mode
		 */
		constexpr ControlRegister1Type SMBusMode = stm32fxx::bits::BIT1;
		/**
		 * @brief PE - Peripheral Enable
		 *
		 * 		0: Peripheral Disabled
		 * 		1: Peripheral Enabled
		 *
		 * 		note:  If this bit is reset while a communicaiton is on going; the
		 * 		peripheral is disabled at the end of the current communication, when
		 * 		back at the IDLE state.
		 * 		-All bit resets due to PE = 0 occur at the end of the communication.
		 * 		In master mode this bit must not be reset before the end of the
		 * 		communicaiton
		 *
		 */
		constexpr ControlRegister1Type PeripheralEnable = stm32fxx::bits::BIT0;

	}

	/**
	 * @brief - I2C_CR1 - I2C control register 2
	 *  		Reset State = 0x00000000U;
	 *  		Address Offset = 0x00000000U;
	 *
	 *  		Note: Bits 15:13 & 7:6 are reserved; Bits 5:0
	 *  		are for the peripheral clock frequency.  The
	 *  		frequency bits must be configured with the APB clock frequency
	 *  		value (I2C peripheral connected to APB).  The FREQ field is used
	 *  		by the peripheral to generate data setup and hold times compliant
	 *  		with I2C specifications.  The minimum frequency is 2MHz, the maximum
	 *  		frequency is limited by the maximum APB frequency and cannot exceed
	 *  		50 MHz.  Fill this field with a 6 bit number that is between 2 and 50.
	 */
	namespace ControlRegister2
	{
		constexpr ControlRegister2Type RegisterOffset = 0x04U;
		constexpr ControlRegister2Type RegisterReset = 0x00000000U;

		/**
		 * @brief LAST - DMA Last Transfer
		 *
		 * 			0: Next DMA EOT is not the last transfer
		 * 			1: Next DMA EOT is the last transfer
		 *
		 * 			Note:  This bit is used in master receiver mode to permit
		 * 			the generation of a NACK on the last received data
		 */
		constexpr ControlRegister2Type DMALast = stm32fxx::bits::BIT12;
		/**
		 * @brief DMAEN - DMA requests Enable
		 *
		 * 			0: DMA requests disabled
		 * 			1: DMA requests enabled when TxE = 1 or RxNE = 1
		 *
		 */
		constexpr ControlRegister2Type DMAEnable = stm32fxx::bits::BIT11;
		/**
		 * @brief ITBUFEN - Buffer Interrupt Enable
		 *
		 * 			0: TxE = 1 or RxNE = 1 does not generate any interrupt
		 * 			1: TxE = 1 or RxNE = 1 generates event interrupt (whatever
		 * 			the state of DMAEN)
		 */
		constexpr ControlRegister2Type BufferInterruptEnable = stm32fxx::bits::BIT10;
		/**
		 * @brief ITEVEN - Event Interrupt Enable
		 *
		 * 		0: Event Interrupt disabled
		 * 		1: Event Interrupt enabled
		 *
		 * 		This interrupt is generated when:
		 * 		SB = 1 (Master)
		 * 		ADDR = 1 (Master/Slave)
		 * 		ADD10 = 1 (Master)
		 * 		STOPF = 1 (Slave)
		 * 		BTF = 1 (with no TxE or RxNE event)
		 * 		TxE event to 1 if ITBUFEN = 1
		 * 		RxNE event to 1 if ITBUFEN = 1
		 *
		 */
		constexpr ControlRegister2Type EventInterruptEnable = stm32fxx::bits::BIT9;
		/**
		 * @brief ITERREN - Error Interrupt Enable
		 *
		 * 		0: Error Interrupt disabled
		 * 		1: Error Interrupt enabled
		 *
		 * 		This interrupt is generated when:
		 * 		BERR = 1
		 * 		ARLO = 1
		 * 		AF = 1
		 * 		OVR = 1
		 * 		PECERR = 1
		 * 		TIMEOUT = 1
		 * 		SMBALERT = 1
		 *
		 */
		constexpr ControlRegister2Type ErrorInterruptEnable = stm32fxx::bits::BIT8;

	}

	/**
	 * @brief I2C_OAR1 - I2C Own Address Register 1
	 *
	 * 			bits9:8
	 * 				7-bit addressing mode - don't care
	 * 				10-bit addressing mode - bits 9:8 of address
	 *
	 * 			bits 7:1
	 * 				bits 7:1 of address
	 *
	 * 			bit 0
	 * 				7-bit addressing mode - don't care
	 * 				10-bit addressing mode - bit 0 of address
	 */
	namespace OwnAddressRegister
	{

		constexpr OwnAddressRegisterType RegisterOffset = 0x08U;
		constexpr OwnAddressRegisterType RegisterReset = 0x00000000U;

		/**
		 * @brief ADDMODE - Addressing Mode (Slave Mode)
		 *
		 * 			0: 7-bit slave address (10-bit addresses not ACK'd)
		 * 			1: 10-bit slave address ( 7-bit addresses not ACK'd)
		 *
		 */
		constexpr OwnAddressRegisterType AddressMode = stm32fxx::bits::BIT15;
		/**
		 * @brief Mystery bit - Manual states that this bit should always be kept
		 * 			at 1 by software.
		 */
		constexpr OwnAddressRegisterType MysteryBit = stm32fxx::bits::BIT14;


	}

	/**
	 * @brief I2C_OAR2 - I2C Own Address Register 2
	 *
	 *			bits 15:8 - Reserved, must be kept at reset value
	 *
	 * 			bits 7:1
	 * 				bits 7:1 of address in dual addressing mode
	 *
	 */
	namespace OwnAddressRegister2
	{

		constexpr OwnAddressRegister2Type RegisterOffset = 0x0CU;
		constexpr OwnAddressRegister2Type RegisterReset = 0x00000000U;

		/**
		 * @brief ENDUAL - Dual Addressing Mode Enable
		 *
		 * 			0: Only OAR1 is recognized in 7-bit addressing mode
		 * 			1: Both OAR1 and OAR2 are recognized in 7-bit addressing mode
		 *
		 */
		constexpr OwnAddressRegister2Type EnableDualAddress = stm32fxx::bits::BIT0;

	}

	/**
	 * @brief I2C_DR - I2C Data Register
	 *
	 * 			bits 15:8 - Reserved, must be kept at reset value
	 *
	 * 			bit 7:0 - 8-bit data register
	 * 			-Byte received or to be transmitted to the bus
	 * 			-Transmitter mode: Byte transmission starts automatically when a
	 * 			byte is written in the data register.  A continuous transmit stream
	 * 			can be maintained if the next data to be transmitted is put in the
	 * 			data register once the transmission is started (TxE = 1)
	 * 			-Receiver Mode: Received byte is copied into the data register,
	 * 			RxNE = 1. A continuous transmit stream can be maintained if the data register
	 * 			is read before the next data byte is received (RxNE = 1)
	 *
	 * 			Note:
	 * 			-In slave mode, the address is not copied into the data register
	 * 			-Write collision is not managed (Data register can be written if
	 * 			TxE = 0)
	 * 			-If an ARLO event occurs on ACK pulse, the received byte is not copied
	 * 			into the data register and cannot be read.
	 *
	 */
	namespace DataRegister
	{

		constexpr DataRegisterType RegisterOffset = 0x10U;
		constexpr DataRegisterType RegisterReset = 0x00000000;

	}

	/**
	 * @brief I2C_SR1 - I2C Status Register 1
	 *
	 *			bits 13, 5 - Reserved, must be kept at reset value
	 *
	 */
	namespace StatusRegister1
	{

		constexpr StatusRegister1Type RegisterOffset = 0x14U;
		constexpr StatusRegister1Type RegisterReset = 0x00000000U;

		/**
		 * @brief SMBALERT - SMBus ALert
		 *
		 * 			In SMBus Host Mode:
		 * 			0: No SMBALERT
		 * 			1: SMBALERT event occurred on pin
		 *
		 * 			In SMBus Slave Mode:
		 * 			0: No SMBALERT response header
		 * 			1: SMBALERT response address header to SMBALERT low received
		 *
		 * 			-cleared by software writing 0, or by hardware when PE = 0
		 */
		constexpr StatusRegister1Type SMBusAlert = stm32fxx::bits::BIT15;
		/**
		 * @brief TIMEOUT - Timeout or Tlow error
		 *
		 * 			0: no TIMEOUT error
		 * 			1: SCL remained low for 25ms (Timeout)
		 * 				or
		 * 			Master cumulative clock low extend time more than 10ms (Tlow:mext)
		 * 				or
		 * 			Slave cumulative clock low extend time more than 25ms (Tlow:sext)
		 *
		 * 			Note:
		 * 			-when set in slave mode: slave resets the communication and lines are
		 * 			released by hardware
		 * 			-When set in master mode: stop condition sent by hardware
		 * 			- cleared by software writing 0, or by hardware when PE = 0
		 */
		constexpr StatusRegister1Type Timeout = stm32fxx::bits::BIT14;
		/**
		 * @brief PECERR - PEC Error in Reception
		 *
		 * 		0: No PEC error: receiver returns ACK after PEC reception (if ACK = 1)
		 * 		1: PEC error: receiver return NACK after PEC reception (whatever ACK)
		 *
		 * 		-Cleared by software writing 0, or by hardware when PE = 0
		 *
		 * 		Note: When the received CRC is wrong, PECERR is not set in slave mode if the
		 * 		PEC control bit is not set before the end of the CRC reception.  Nevertheless,
		 * 		reading the PEC value determines whether the received PEC is right or wrong.
		 *
		 */
		constexpr StatusRegister1Type PECError = stm32fxx::bits::BIT12;
		/**
		 * @brief OVR - Overrun/Under run
		 *
		 * 		0: No overrun/under run
		 * 		1: Overrun or under run
		 *
		 * 		-Set by hardware in slave mode when NOSTRETCH = 1 and:
		 * 		-In reception, a new byte is received (including ACK pulse)
		 * 			and the data register has not been read yet.  New
		 * 			received byte is lost.
		 * 		-In transmissino when a new byte should be sent and the data
		 * 			register has not been written yet.  The same byte is sent
		 * 			twice.
		 *
		 * 		-Cleared by software writing 0, or by hardware when PE = 0.
		 *
		 * 		Note:  If the Data Register write occurs very close to the
		 * 		SCL rising edge, the sent data is unspecified and a hold timing
		 * 		error occurs.
		 */
		constexpr StatusRegister1Type OverrunUnderrun = stm32fxx::bits::BIT11;
		/**
		 * @brief AF - Acknowledge Failure
		 *
		 * 			0: No acknowledge failure
		 * 			1: Acknowledge failure
		 *
		 * 			-Set by hardware when no acknowledge is returned
		 * 			-Cleared by software writing 0, or by hardware when PE = 0
		 *
		 */
		constexpr StatusRegister1Type AcknowledgFailure = stm32fxx::bits::BIT10;
		/**
		 * @brief ARLO - Arbitration Lost (Master Mode)
		 *
		 * 			0: No arbitration lost detected
		 * 			1: Arbitration lost detected
		 *
		 * 			-Set by hardware when the interface loses the arbitration of the bus to another master
		 * 			-Cleared by software writing 0, or by hardware when PE = 0.
		 * 			-After an ARLO event, the interface switches back automatically to Slave mode (MSL=0).
		 * 			Note: In SMBUS, the arbitration on the data in slave mode occurs only during
		 * 			the data phase, or the acknowledge transmission (not on the address acknowledge)
		 */
		constexpr StatusRegister1Type ArbitrationLost = stm32fxx::bits::BIT9;
		/**
		 * @brief BERR - Bus Error
		 *
		 * 			0: No misplaced START or STOP condition
		 * 			1: Misplaced START or STOP condition
		 * 			-Set by hardware when the interface detects an SDA rising or falling edge while SCL is high,
		 * 			occurring in a non-valid position during a byte transfer.
		 * 			-Cleared by software writing 0, or by hardware when PE = 0.
		 *
		 */
		constexpr StatusRegister1Type BusError = stm32fxx::bits::BIT8;
		/**
		 * @brief TxE - Data Register Empty (transmitters)
		 *
		 * 			0: Data register not empty
		 * 			1: Data register empty
		 *
		 * 			-Set when DR is empty in transmission.  TxE is not set
		 * 			during the address phase.
		 * 			-Cleared by software writing to the DR register or by hardware
		 * 			after a START or STOP condition or when PE = 0.
		 * 			-TxE is not set if either a NACK is receive, or if next byte to be
		 * 			transmitted is PEC (PEC = 1).
		 * 			Note: TxE is not cleared by writing the first data being transmitted,
		 * 			or by writing data when BTF is set, as in both cases, the DR register
		 * 			is still empty.
		 *
		 */
		constexpr StatusRegister1Type TransmitEmpty = stm32fxx::bits::BIT7;
		/**
		 * @brief RxNE - Data register not empty (receivers)
		 *
		 * 			0: Data register empty
		 * 			1: Data register not empty
		 *
		 * 			-Set when data register is not empty in receiver mode. RxNE is
		 * 			not set during the address phase.
		 * 			-Cleared by software reading or writing the DR register,
		 * 			or by hardware when PE = 0.
		 * 			-RxNE is not set in case of ARLO event.
		 * 			Note: RxNE is not cleared by reading data when BTF is set, as
		 * 			the data register is still full.
		 *
		 */
		constexpr StatusRegister1Type ReceiveNotEmpty = stm32fxx::bits::BIT6;
		/**
		 * @brief STOPF - Stop detection (slave mode)
		 *
		 * 			0: No STOP detection detected
		 * 			1: STOP condition detected
		 *
		 * 			-Set by hardware when a STOP condition is detected on the bus
		 * 			by the slave after an acknowledge (if ACK = 1).
		 * 			-Cleared by software reading the SR1 register followed by a write
		 * 			to the CR1 register, or by the hardware when PE = 0.
		 *
		 * 			Note: The STOPF bit is not set after a NACK reception.
		 * 			It is recommended to perform the complete clearing sequence (READ SR1,
		 * 			then WRITE CR1) after the STOPF is set.
		 *
		 */
		constexpr StatusRegister1Type StopDetected = stm32fxx::bits::BIT4;
		/**
		 * @brief ADD10 - 10-bit header sent (Master mode)
		 *
		 * 			0: No ADD10 event occurred.
		 * 			1: Master has sent first address byte (header).
		 *
		 * 			-Set by hardware when the master has sent the first byte in
		 * 			10-bit address mode.
		 * 			-Cleared by software reading the SR1 register followed by a
		 * 			write in the DR register of the second address byte, or by
		 * 			hardware when PE = 0.
		 *
		 * 			Note: ADD10 bit is not set after a NACK reception.
		 *
		 */
		constexpr StatusRegister1Type ADD10 = stm32fxx::bits::BIT3;
		constexpr StatusRegister1Type ByteTransferFinished = stm32fxx::bits::BIT2;
		constexpr StatusRegister1Type Address = stm32fxx::bits::BIT1;
		constexpr StatusRegister1Type StartBit = stm32fxx::bits::BIT0;

	}

}



#endif /* I2C_H_ */
