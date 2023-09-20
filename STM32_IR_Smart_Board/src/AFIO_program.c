/***************************************************************/
/* Author  	: Ahmed Hassan     			 ***********************/
/* Date		: 14 FEB 2023				 ***********************/
/* Layer   	: MCAL           		   	 ***********************/
/* SWC      : AFIO           			 ***********************/
/* Version 	: 1.00             			 ***********************/
/***************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "AFIO_interface.h"
#include "AFIO_private.h"
#include "AFIO_config.h"

void AFIO_VidSetEXTIConfiguration( u8 LOC_u8EXTI_Line , u8 LOC_u8PortMap ){

	u8 LOC_u8RegIndex = 0;

	if( LOC_u8EXTI_Line <= 3 ){
		LOC_u8RegIndex = 0 ;
	}
	else if( LOC_u8EXTI_Line <= 7 ){
		LOC_u8RegIndex   = 1 ;
		LOC_u8EXTI_Line -= 4 ;
	}
	else if( LOC_u8EXTI_Line <= 11 ){
		LOC_u8RegIndex   = 2 ;
		LOC_u8EXTI_Line -= 8 ;
	}
	else if( LOC_u8EXTI_Line <= 15 ){
		LOC_u8RegIndex   = 3 ;
		LOC_u8EXTI_Line -= 12 ;
	}

	AFIO->EXTICRx[LOC_u8RegIndex] &= ~ ( ( 0b1111 )    << ( LOC_u8EXTI_Line * 4 ));// R M W
	AFIO->EXTICRx[LOC_u8RegIndex] |= ( LOC_u8PortMap ) << ( LOC_u8EXTI_Line * 4 );

}
