/**
  ******************************************************************************
  * @file           : button.h
  * @brief          : Buttons driver
  * @author         : TQFP (for https://microtechnics.ru/user-blogs/)
  ******************************************************************************
  */

#ifndef BUTTON_H
#define BUTTON_H



/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Declarations and definitions ----------------------------------------------*/

// Configuration

#define GPIO_BUTTON_NOT_PRESSED                              (GPIO_PIN_SET)

#define BUTTONS_SHORT_PRESS_MS                               60
#define BUTTONS_LONG_PRESS_MS                                500
#define BUTTONS_VERY_LONG_PRESS_MS                           1500

typedef enum {
    BUTTON_LEFT,
    BUTTON_MIDDLE,
    BUTTON_RIGHT,
    BUTTONS_NUM,
} ButtonID;

// End of configuration

#define DEBOUNCE_TIME_MS                                     50
#define GPIO_BUTTON_PRESSED                                  (!GPIO_BUTTON_NOT_PRESSED)

typedef struct
{
  GPIO_TypeDef *port;
  uint16_t pin;
} McuPin;

typedef enum
{
  BUTTON_STARTING                      = 0,
  BUTTON_NOT_PRESSED                   = 1,
  BUTTON_WAIT_DEBOUNCE                 = 2,
  BUTTON_PRESSED                       = 3,
} ButtonState;

typedef enum
{
  BUTTON_NONE                          = 0,
  BUTTON_SHORT_PRESS                   = 1,
  BUTTON_LONG_PRESS                    = 2,
  BUTTON_VERY_LONG_PRESS               = 3,
} ButtonAction;



/* Functions -----------------------------------------------------------------*/

extern void BUTTON_Process();
extern void BUTTON_TimerProcess();
extern ButtonAction BUTTON_GetAction(uint8_t index);
extern void BUTTON_ResetActions();
extern void BUTTON_Init();



#endif // #ifndef BUTTON_H
