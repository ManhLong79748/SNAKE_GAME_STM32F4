
#ifndef INC_STM32F4_RCC_H_
#define INC_STM32F4_RCC_H_

#include "stm32f4.h"

//This returns the APB1 clock value
uint32_t RCC_GetPCLK1Value(void);

//This returns the APB2 clock value
uint32_t RCC_GetPCLK2Value(void);


uint32_t  RCC_GetPLLOutputClock(void);


#endif /* INC_STM32F4_RCC_H_ */
