/*
 * LoraProxy.h
 *
 *  Created on: Jan 3, 2023
 *      Author: igor
 */

#ifndef INC_CLOCK_H_
#define INC_CLOCK_H_

#include "main.h"

#define delayUS_ASM(us) do { \
 asm volatile ("MOV R0,%[loops]\n \
1: \n \
SUB R0, #1\n \
CMP R0, #0\n \
BNE 1b \t" \
: : [loops] "r" (us) : "memory" \
); \
} while(0)

  void clockControl();
  void clockStart();
  void dateChoose(int unit);
  void timeChoose(int unit);
  void resetTube();
  void dataSend(int arr[]);

  int currentUnit = 0;
  int period = 0;

  int delay 		= 10; //us

  int tenHour[12] 	= {0};
  int oneHour[12] 	= {0};
  int tenMin[12] 	= {0};
  int oneMin[12] 	= {0};
  int tenSec[12] 	= {0};
  int oneSec[12] 	= {0};

  int tenDay[12] 	= {0};
  int oneDay[12] 	= {0};
  int tenMonth[12] 	= {0};
  int oneMonth[12] 	= {0};
  int tenYear[12] 	= {0};
  int oneYear[12] 	= {0};

#endif /* INC_CLOCK_H_ */
