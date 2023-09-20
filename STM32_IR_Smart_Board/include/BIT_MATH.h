/***************************************************************/
/* Author  	: Ahmed Hassan     			 ***********************/
/* Date		: 11 SEP 2022				 ***********************/
/* Layer   	: LIB           		   	 ***********************/
/* Version 	: 1.00             			 ***********************/
/***************************************************************/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(VAR,BIT_NO) 			(VAR|=(1<<BIT_NO))
#define CLR_BIT(VAR,BIT_NO) 			(VAR&=(~(1<<BIT_NO)))
#define TOGGLE_BIT(VAR,BIT_NO)		 	(VAR^=(1<<BIT_NO))
#define GET_BIT(VAR,BIT_NO) 			((VAR>>BIT_NO)&1)


#endif
