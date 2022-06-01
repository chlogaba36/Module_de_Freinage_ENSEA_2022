/**
 *\file Encoder.c
 *\brief Librairie faites pour utiliser l'encodeur selon nos besoins.
 *\author Chloé GABARREN et Colin PERRET
 *\version 1.0
 *\date 31/05/2022
 *
 * Ensemble des fonctions qui seront utilisé pour notre usage de l'encodeur,
 * donc pour la sélection dans le menu et modifier la valeur des tensions seuils.
 *
 */

/*
	vmin : menu = 0
	vmax : menu = 1
	mode auto : menu = 2
	mode manuel : menu = 3
 */
#include "Encoder.h"
TIM_HandleTypeDef htim1;

/**
 * \fn void Encoder_Start(void)
 * \brief Fonction permettant d'initialiser l'encodeur.
 * \param void
 * \return void.
 */
void Encoder_Start(void){
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
}

/**
 * \fn void Encoder_Reset(int past_incremental_val, int current_incremental_val)
 * \brief Fonction permettant de réinitialiser la valeur lu sur l'encodeur.
 * \param Les valeurs passé et présente lu sur l'encodeur.
 * \return void.
 */
void Encoder_Reset(int past_incremental_val, int current_incremental_val){
	past_incremental_val = __HAL_TIM_SET_COUNTER(&htim1,32767);
	current_incremental_val = __HAL_TIM_SET_COUNTER(&htim1,32767);
}

/**
 * \fn void Encoder_Count(int* incremental_val)
 * \brief Fonction permettant de mettre à jour les valeurs passé et présente de l'encodeur.
 * \param Le tableau contenant les valeurs passé et présente de l'encodeur.
 * \return void.
 */
void Encoder_Count(int* incremental_val){
	int current_incremental_val = __HAL_TIM_GET_COUNTER(&htim1);
	incremental_val[1] = incremental_val[0];
	incremental_val[0] = current_incremental_val;
}

/**
 * \fn void Encoder_Delta(int* incremental_val)
 * \brief Fonction permettant de mettre à jour les valeurs passé et présente de l'encodeur.
 * \param Le tableau contenant les valeurs passé et présente de l'encodeur.
 * \return La différence.
 */
int Encoder_Delta(int* incremental_val){
	int delta = incremental_val[0]-incremental_val[1];
	return delta;
}
