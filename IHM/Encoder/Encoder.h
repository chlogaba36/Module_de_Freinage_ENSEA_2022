/*
 * Encoder.h
 *
 *  Created on: May 31, 2022
 *      Author: chlogaba36
 */

#ifndef SRC_ENCODER_H_
#define SRC_ENCODER_H_

#include "stm32f4xx_hal.h"

void Encoder_Start(void);
void Encoder_Reset(int past_incremental_val, int current_incremental_val);
void Encoder_Count(int* incremental_val);
int Encoder_Switch_Menu(int* incremental_val);

#endif /* SRC_ENCODER_H_ */
