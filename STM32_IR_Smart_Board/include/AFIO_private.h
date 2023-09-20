/***************************************************************/
/* Author  	: Ahmed Hassan     			 ***********************/
/* Date		: 14 FEB 2023				 ***********************/
/* Layer   	: MCAL           		   	 ***********************/
/* SWC      : AFIO           			 ***********************/
/* Version 	: 1.00             			 ***********************/
/***************************************************************/
#ifndef AFIO_PRIVATE_H_
#define AFIO_PRIVATE_H_

typedef struct{

	volatile u32 EVCR;
	volatile u32 MAPR;
	volatile u32 EXTICRx[4];
	volatile u32 MAPR2;

}AFIO_Type;


#define AFIO ((volatile AFIO_Type *) 0x40010000)


#endif	/* AFIO_PRIVATE_H_ */