/***************************************************************/
/* Author  	: Ahmed Hassan     			 ***********************/
/* Date		: 20 SEP 2022				 ***********************/
/* Layer   	: MCAL           		   	 ***********************/
/* SWC      : EXTI           		   	 ***********************/
/* Version 	: 1.00             			 ***********************/
/***************************************************************/
#ifndef EXTI0_PRIVATE_H
#define EXTI0_PRIVATE_H


typedef	struct
{
	volatile	u32		IMR;
	volatile	u32		EMR;
	volatile	u32		RTSR;
	volatile	u32		FTSR;
	volatile	u32		SWIER;
	volatile	u32		PR;
	
}EXTI_Type;

#define	EXTI		(( EXTI_Type * )0X40010400)



#endif
