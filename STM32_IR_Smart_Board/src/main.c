/***************************************************************/
/* Author  	: Ahmed Hassan     			 ***********************/
/* Date		: 10 OCT 2022				 ***********************/
/* Layer   	: APP           		   	 ***********************/
/* Version 	: 1.00             			 ***********************/
/***************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "EXTI0_interface.h"
#include "NVIC_interface.h"
#include "STK_interface.h"
#include "AFIO_interface.h"

volatile u8   u8StartFlag       = 0;
volatile u32  u32FrameData[50]  = {0};
volatile u8   u8EdgeCounter     = 0;
volatile u8   u8Data            = 0;

volatile u8 flag[10] = {0};


void voidPlay(void)
{
	u8 i = 0 ;

	/*        Button 1        */
	if((u8Data == 69) && (flag[0] == 0))
	{
		MGPIO_VidSetPinValue(GPIOA,7,HIGH );
		flag[0] = 1 ;
	}
	else if((u8Data == 69) && (flag[0] == 1))
	{
		MGPIO_VidSetPinValue(GPIOA,7,LOW );
		flag[0] = 0 ;
	}

	/*        Button 2        */
	else if((u8Data == 70) && (flag[1] == 0))
	{
		MGPIO_VidSetPinValue(GPIOA,6,HIGH );
		flag[1] = 1 ;
	}
	else if((u8Data == 70) && (flag[1] == 1))
	{
		MGPIO_VidSetPinValue(GPIOA,6,LOW );
		flag[1] = 0 ;
	}

	/*        Button 3        */
	else if((u8Data == 71) && (flag[2] == 0))
	{
		MGPIO_VidSetPinValue(GPIOA,5,HIGH );
		flag[2] = 1 ;
	}

	else if((u8Data == 71) && (flag[2] == 1))
	{
		MGPIO_VidSetPinValue(GPIOA,5,LOW );
		flag[2] = 0;
	}

	/*        Button 4        */
	else if((u8Data == 68) && (flag[3] == 0))
	{
		MGPIO_VidSetPinValue(GPIOA,4,HIGH );
		flag[3] = 1;
	}

	else if((u8Data == 68) && (flag[3] == 1))
	{
		MGPIO_VidSetPinValue(GPIOA,4,LOW );
		flag[3] = 0;
	}

	/*        Button 5        */
	else if((u8Data == 64) && (flag[4] == 0))
	{
		MGPIO_VidSetPinValue(GPIOA,3,HIGH );
		flag[4] = 1;
	}

	else if((u8Data == 64) && (flag[4] == 1))
	{
		MGPIO_VidSetPinValue(GPIOA,3,LOW );
		flag[4] = 0;
	}

	/*        Button 6        */
	else if((u8Data == 67) && (flag[5] == 0))
	{
		MGPIO_VidSetPinValue(GPIOA,2,HIGH );
		flag[5] = 1;
	}
	else if((u8Data == 67) && (flag[0] == 1))
	{
		MGPIO_VidSetPinValue(GPIOA,2,LOW );
		flag[5] = 0;
	}

	/*        Button 7        */
	else if((u8Data == 7) && (flag[6] == 0))
	{
		MGPIO_VidSetPinValue(GPIOA,1,HIGH );
		flag[6] = 1;
	}
	else if((u8Data == 7) && (flag[6] == 1))
	{
		MGPIO_VidSetPinValue(GPIOA,1,LOW );
		flag[6] = 0;
	}

	/*        Button 8        */
	else if((u8Data == 21) && (flag[7] == 0))
	{
		MGPIO_VidSetPinValue(GPIOA,0,HIGH );
		flag[7] = 1;
	}
	else if((u8Data == 21) && (flag[7] == 1))
	{
		MGPIO_VidSetPinValue(GPIOA,0,LOW );
		flag[7] = 0;
	}

	/*        Button ON/OFF     */
	else if((u8Data == 28) && (flag[8] == 0))
	{
		for(i=0;i<8;i++)
		{
			MGPIO_VidSetPinValue(GPIOA,i,HIGH );
		}
		flag[8] = 1;
	}
	else if((u8Data == 28) && (flag[8] == 1))
	{
		for(i=0;i<8;i++)
		{
			MGPIO_VidSetPinValue(GPIOA,i,LOW );
		}

		flag[8] = 0;
	}

	/*        Button 0     */
	else if( u8Data == 25 )
	{
		for(i=0;i<8;i++)
		{
			MGPIO_VidSetPinValue(GPIOA,i,LOW );
		}

	}

	//	switch (u8Data)
	//	{
	//	case 69: TOG_BIT(state_1,0)  ; MGPIO_VidSetPinValue(GPIOA,0,state_1 );  break;
	//	case 70: TOG_BIT(state_2,0)  ; MGPIO_VidSetPinValue(GPIOA,1,state_2 );  break;
	//	}
}

void voidTakeAction(void)
{
	u8 i;
	u8Data = 0;

	if ( (u32FrameData[0] >= 10000) && (u32FrameData[0] <= 16000) )
	{
		for (i=0;i<8;i++)
		{
			if (  (u32FrameData[17+i] >= 2000) && (u32FrameData[17+i] <=2400) )
			{
				SET_BIT(u8Data,i);
			}

			else
			{
				CLR_BIT(u8Data,i);
			}
		}

		voidPlay();
	}

	else
	{
		/* Invalid Frame */
	}

	u8StartFlag     = 0;
	u32FrameData[0] = 0;
	u8EdgeCounter   = 0;
}

void voidGetFrame(void)
{
	if (u8StartFlag == 0)
	{
		/* Start Timer */
		MSTK_voidSetIntervalSingle(1000000,voidTakeAction);
		u8StartFlag = 1;
	}

	else
	{
		u32FrameData[u8EdgeCounter] = MSTK_u32GetElapsedTime();
		MSTK_voidSetIntervalSingle(1000000,voidTakeAction);
		u8EdgeCounter++;
	}
}


void main(void)
{
	/* RCC Initialize */
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,0); /* AFIO Enable Clock */

	RCC_voidEnableClock(RCC_APB2,2); /* GPIOA Enable Clock */
	RCC_voidEnableClock(RCC_APB2,3); /* GPIOB Enable Clock */

	/* IO Pins Initialization */
	MGPIO_VidSetPinDirection(GPIOB,9,0b0100); /* B9 Input Floating        	*/

	MGPIO_VidSetPinDirection(GPIOA,0,0b0010); /* A0 Output PP        		*/
	MGPIO_VidSetPinDirection(GPIOA,1,0b0010); /* A1 Output PP      			*/
	MGPIO_VidSetPinDirection(GPIOA,2,0b0010); /* A2 Output PP      			*/
	MGPIO_VidSetPinDirection(GPIOA,3,0b0010); /* A3 Output PP        		*/
	MGPIO_VidSetPinDirection(GPIOA,4,0b0010); /* A4 Output PP     			*/
	MGPIO_VidSetPinDirection(GPIOA,5,0b0010); /* A5 Output PP       		*/
	MGPIO_VidSetPinDirection(GPIOA,6,0b0010); /* A6 Output PP     			*/
	MGPIO_VidSetPinDirection(GPIOA,7,0b0010); /* A7 Output PP       		*/

	/* EXTI9 mapping to Port B*/
	AFIO_VidSetEXTIConfiguration(EXTI9,1);


	/* EXTI Initializtion */
	MEXTI9_voidSetCallBack(voidGetFrame);

	MEXTI_voidInit(); /* B9 EXTI9 Enabled / Falling Edge */

	/* Enable EXTI0 from NVIC */
	MNVIC_voidInit();
	MNVIC_voidEnableInterrupt(23); /* EXTI9 */

	/* SysTick Init */
	MSTK_voidInit(); /* Enable SysTick AHB/8 = 1MHZ */

	while(1)
	{

	}

}
