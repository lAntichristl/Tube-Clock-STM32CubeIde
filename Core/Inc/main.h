/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include "string.h"
#include "stdio.h"

extern int screenChoose;
extern int unitChoose;
extern bool isSettingsOn;
extern bool isPowerOn;
extern bool veryLongPressFlag;
extern int settingsFlag;
extern int interruptSource;
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUTTON_LEFT_Pin GPIO_PIN_12
#define BUTTON_LEFT_GPIO_Port GPIOB
#define BUTTON_MIDDLE_Pin GPIO_PIN_13
#define BUTTON_MIDDLE_GPIO_Port GPIOB
#define BUTTON_RIGHT_Pin GPIO_PIN_14
#define BUTTON_RIGHT_GPIO_Port GPIOB
#define DATA_Pin GPIO_PIN_8
#define DATA_GPIO_Port GPIOA
#define CLOCK_PERIPH_Pin GPIO_PIN_9
#define CLOCK_PERIPH_GPIO_Port GPIOA
#define L6_Pin GPIO_PIN_15
#define L6_GPIO_Port GPIOA
#define L5_Pin GPIO_PIN_3
#define L5_GPIO_Port GPIOB
#define L4_Pin GPIO_PIN_4
#define L4_GPIO_Port GPIOB
#define L3_Pin GPIO_PIN_5
#define L3_GPIO_Port GPIOB
#define L2_Pin GPIO_PIN_6
#define L2_GPIO_Port GPIOB
#define L1_Pin GPIO_PIN_7
#define L1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
