/*
 * LoraProxy.cpp
 *
 *  Created on: Jan 3, 2023
 *      Author: igor
 */

#include "Clock.h"

//set default time and date
void clockStart()
{
	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};
	sTime.Hours = 17;
	sTime.Minutes = 59;
	sTime.Seconds = 45;

	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}

	sDate.WeekDay = RTC_WEEKDAY_WEDNESDAY;
	sDate.Month = RTC_MONTH_JULY;
	sDate.Date = 31;
	sDate.Year = 24;

	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
}

//check time and call setfunction
void clockControl()
{
	 RTC_DateTypeDef getDate = {0};
	 RTC_TimeTypeDef getTime = {0};

	 if (HAL_RTC_GetTime(&hrtc, &getTime, RTC_FORMAT_BIN) != HAL_OK)
	 {
		 Error_Handler();
	 }

	 if (HAL_RTC_GetDate(&hrtc, &getDate, RTC_FORMAT_BIN) != HAL_OK)
	 {
		 Error_Handler();
	 }
	 for(int i = 0; i<11; i++)
	 {
		 tenHour[i] 	= 0;
		 oneHour[i] 	= 0;
		 tenMin[i] 		= 0;
		 oneMin[i] 		= 0;
		 tenSec[i] 		= 0;
		 oneSec[i] 		= 0;

		 tenDay[i] 		= 0;
		 oneDay[i] 		= 0;
		 tenMonth[i] 	= 0;
		 oneMonth[i] 	= 0;
		 tenYear[i] 	= 0;
		 oneYear[i] 	= 0;
	 }

	 tenHour[(getTime.Hours / 10)]		= 1;
	 oneHour[(getTime.Hours % 10)]	 	= 1;
	 tenMin[(getTime.Minutes / 10)] 	= 1;
	 oneMin[(getTime.Minutes % 10)] 	= 1;
	 tenSec[(getTime.Seconds / 10)] 	= 1;
	 oneSec[(getTime.Seconds % 10)] 	= 1;

	 tenDay[(getDate.Date / 10)]		= 1;
	 oneDay[(getDate.Date % 10)] 		= 1;
	 tenMonth[(getDate.Month / 10)] 	= 1;
	 oneMonth[(getDate.Month % 10)] 	= 1;
	 tenYear[(getDate.Year / 10)] 		= 1;
	 oneYear[(getDate.Year % 10)] 		= 1;

	 if (isPowerOn)
	 {
		 if (isSettingsOn)
		 {
			 if ((unitChoose == 0 && currentUnit < 2) || (unitChoose == 1 && currentUnit > 1 && currentUnit < 4) \
														 || (unitChoose == 2 && currentUnit > 3))
			 {
				 if (period < 120)
				 {
					 if (period > 39)
					 {
						 if (screenChoose == 0) timeChoose(currentUnit);
						 else dateChoose(currentUnit);
					 }
					 else
					 {
						 resetTube();
					 }
					 period++;
				 }
				 else {
					 settingsFlag--;
					 period = 0;
					 if (screenChoose == 0) timeChoose(currentUnit);
					 else dateChoose(currentUnit);
				 }
			 }
			 else
			 {
				 if (screenChoose == 0) timeChoose(currentUnit);
				 else dateChoose(currentUnit);
			 }
		 }
		 else
		 {
			 if (screenChoose == 0) timeChoose(currentUnit);
			 else dateChoose(currentUnit);
		 }
		 currentUnit++;
		 if (currentUnit >= 6) currentUnit = 0;
	 }
	 else resetTube();

}

//call setdata function and choose tube for calendar
void dateChoose(int unit)
{
	switch (unit)
	{
	case 0:
		dataSend(tenDay);
		HAL_GPIO_WritePin(L6_GPIO_Port, L6_Pin, RESET);
		HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, SET);
		break;

	case 1:
		dataSend(oneDay);
		HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, RESET);
		HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, SET);
		break;

	case 2:
		dataSend(tenMonth);
		HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, RESET);
		HAL_GPIO_WritePin(L3_GPIO_Port, L3_Pin, SET);
		break;

	case 3:
		dataSend(oneMonth);
		HAL_GPIO_WritePin(L3_GPIO_Port, L3_Pin, RESET);
		HAL_GPIO_WritePin(L4_GPIO_Port, L4_Pin, SET);
		break;

	case 4:
		dataSend(tenYear);
		HAL_GPIO_WritePin(L4_GPIO_Port, L4_Pin, RESET);
		HAL_GPIO_WritePin(L5_GPIO_Port, L5_Pin, SET);
		break;

	case 5:
		dataSend(oneYear);
		HAL_GPIO_WritePin(L5_GPIO_Port, L5_Pin, RESET);
		HAL_GPIO_WritePin(L6_GPIO_Port, L6_Pin, SET);
		break;
	}
}

//call setdata function and choose tube for clock
void timeChoose(int unit)
{
	switch (unit)
	{
	case 0:
		dataSend(tenHour);
		HAL_GPIO_WritePin(L6_GPIO_Port, L6_Pin, RESET);
		HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, SET);
		break;

	case 1:
		dataSend(oneHour);
		HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, RESET);
		HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, SET);
		break;

	case 2:
		dataSend(tenMin);
		HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, RESET);
		HAL_GPIO_WritePin(L3_GPIO_Port, L3_Pin, SET);
		break;

	case 3:
		dataSend(oneMin);
		HAL_GPIO_WritePin(L3_GPIO_Port, L3_Pin, RESET);
		HAL_GPIO_WritePin(L4_GPIO_Port, L4_Pin, SET);
		break;

	case 4:
		dataSend(tenSec);
		HAL_GPIO_WritePin(L4_GPIO_Port, L4_Pin, RESET);
		HAL_GPIO_WritePin(L5_GPIO_Port, L5_Pin, SET);
		break;

	case 5:
		dataSend(oneSec);
		HAL_GPIO_WritePin(L5_GPIO_Port, L5_Pin, RESET);
		HAL_GPIO_WritePin(L6_GPIO_Port, L6_Pin, SET);
		break;
	}
}

void resetTube()
{
		HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, RESET);
		HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, RESET);
		HAL_GPIO_WritePin(L3_GPIO_Port, L3_Pin, RESET);
		HAL_GPIO_WritePin(L4_GPIO_Port, L4_Pin, RESET);
		HAL_GPIO_WritePin(L5_GPIO_Port, L5_Pin, RESET);
		HAL_GPIO_WritePin(L6_GPIO_Port, L6_Pin, RESET);
}


//set data
void dataSend(int arr[])
{
	for (int n = 0; n < 11; n++)
	{
		if (arr[n] == 1)
		{
			if (n == 0)
				{
					arr[10] = 1;
					HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, SET);
					delayUS_ASM(delay);
					HAL_GPIO_TogglePin(CLOCK_PERIPH_GPIO_Port, CLOCK_PERIPH_Pin);
					delayUS_ASM(delay);
				}
			else
			{
				HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, RESET);
				delayUS_ASM(delay);
				HAL_GPIO_TogglePin(CLOCK_PERIPH_GPIO_Port, CLOCK_PERIPH_Pin);
				delayUS_ASM(delay);
			}
		}
		else
		{
			HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, SET);
			delayUS_ASM(delay);
			HAL_GPIO_TogglePin(CLOCK_PERIPH_GPIO_Port, CLOCK_PERIPH_Pin);
			delayUS_ASM(delay);
		}
		if (n < 10)
		{
			HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, RESET);
			delayUS_ASM(delay);
			HAL_GPIO_TogglePin(CLOCK_PERIPH_GPIO_Port, CLOCK_PERIPH_Pin);
			delayUS_ASM(delay);
		}
		else
		{
			HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, SET);
			delayUS_ASM(delay);
			HAL_GPIO_TogglePin(CLOCK_PERIPH_GPIO_Port, CLOCK_PERIPH_Pin);
			delayUS_ASM(delay);
		}
	}
}
