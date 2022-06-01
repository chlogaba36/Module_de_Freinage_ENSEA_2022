/*
 * Encoder.c
 *
 *  Created on: May 31, 2022
 *      Author: chlogaba36
 */

/*
	mode auto: menu = 0
	vmin : menu = 1
	vmax : menu = 2
	mode manuel : menu = 3
 */
#include "Encoder.h"
TIM_HandleTypeDef htim1;

void Encoder_Start(void){
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
}

void Encoder_Reset(int past_incremental_val, int current_incremental_val){
	past_incremental_val = __HAL_TIM_SET_COUNTER(&htim1,32767);
	current_incremental_val = __HAL_TIM_SET_COUNTER(&htim1,32767);
}

void Encoder_Count(int* incremental_val){
	int current_incremental_val = __HAL_TIM_GET_COUNTER(&htim1);
	incremental_val[1] = incremental_val[0];
	incremental_val[0] = current_incremental_val;
}

int Encoder_Switch_Menu(int* incremental_val){
	int menu = incremental_val[0]-incremental_val[1];
	return menu;
}
