#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define LCD_ADDRESS     (0x7c>>1)

#define LCD_WRT 0x40
#define LCD_CMD 0x80

#define LCD_SET 0x38
#define LCD_SET3C 0x3c
#define LCD_DISPONF 0x0e
#define LCD_DISPOFF 0x08
#define LCD_DISPCLEAR 0x01
#define LCD_MODESET 0x06
#define LCD_HOME 0x02

#define CURSOR_RETURNLIGNE 0xc0

#define CHAR_POINT 0xa5

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void LCD_transmit_cmd(char c);
void LCD_Init(void);
void LCD_set_Cursor(int ligne, int colonne);
void LCD_PrintChar(char c);
void LCD_PrintStr(char* str, int len);
void LCD_Home(void);
void LCD_Clear(void);
void LCD_YNCursorBlink(int i);
void LCD_Menu(int vmin, int vmax, int cursor);
void LCD_Manuel(void);
void LCD_PrintInt(int i);
void LCD_vmin_menu(int vmin);
void LCD_vmin_actualisation(int vmin);
void LCD_vmax_menu(int vmax);
void LCD_vmax_actualisation(int vmax);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LD2_Pin_Pin GPIO_PIN_6
#define LD2_Pin_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
