/*
 *########################################################################
 *                (c) Copyright 2013 Freescale Semiconductor, Inc.
 *                         ALL RIGHTS RESERVED. 
 *########################################################################
 * 
 * Brief Description     : SBC high level driver file
 *
 **************************************************************************
*/
/******************************************************************************
* Includes
******************************************************************************/
#include "sbc_hld.h"

/******************************************************************************
* Constants
******************************************************************************/

/******************************************************************************
* Macros 
******************************************************************************/
#define	SBC_READ_DEV_FLAGS	0x0001DF80
#define SBC_WDOG_REFRESH	0x00015A00
#define SBC_CAN_ENABLE		0x000160C0
/******************************************************************************
* Types
******************************************************************************/

/******************************************************************************
* Local Functions
******************************************************************************/

/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Static variables
******************************************************************************/

/******************************************************************************
* Global functions
******************************************************************************/

/******************************************************************************
*   Function: Init_SBC_DBG
*
*   Description: Set SBC CAN Tx and Rx 
*                Note: This function assumes SBC is in debug mode and watchdog refresh 
*                      is required only once on startup.
*
******************************************************************************/
void SBC_Init_DBG(void)
{
	vuint32_t spi_data;

	spi_data = SBC_Write_Data(SBC_READ_DEV_FLAGS); 

	spi_data = SBC_Write_Data(SBC_WDOG_REFRESH); 

	spi_data = SBC_Write_Data(SBC_CAN_ENABLE);
}

/******************************************************************************
*   Function: WriteDataToSBC
*
*   Description: Sends data to SBC via DSPI 1
*
******************************************************************************/
vuint32_t SBC_Write_Data(uint32_t data) 
{
	uint8_t i;
	vuint32_t read_data = 0; 		/* Data received on master SPI */
	
	DSPI_1.PUSHR.R = data;
	while (DSPI_1.SR.B.RFDF != 1)
	{
		;							/* Wait for Receive FIFO Drain Flag = 1 */
	} 
	read_data = DSPI_1.POPR.R; 		/* Read data received by slave SPI */
	DSPI_1.SR.R = 0x80020000; 			/* Clear TCF, RDRF flags by writing 1 to them */
	for (i=0; i<200; i++) 
	{
		; /* delay */
	}
	return read_data;
}
 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/



