/*
 * Menun.cpp
 *
 *  Created on: Jul 31, 2024
 *      Author: igore
 */

#include "Menu.h"


void screenChange()
{
	if (interruptSource == BUTTON_RIGHT_Pin)
	{
		screenChoose++;
		screenChoose = screenChoose > 1 ? 0 : 1;
	}
	if (interruptSource == BUTTON_LEFT_Pin)
	{
		screenChoose--;
		screenChoose = screenChoose < 0 ? 1 : 0;
	}
}

void settings()
{
	settingsFlag = 5;

	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};
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

	if(screenChoose == 0)
	{
		int seconds, minutes, hours;
		seconds = getTime.Seconds;
		minutes = getTime.Minutes;
		hours = getTime.Hours;

		switch (unitChoose)
		{
		case 0:

			if (interruptSource == BUTTON_RIGHT_Pin) sTime.Hours = hours + 1;
			else if (hours > 0) sTime.Hours = hours - 1;
			else sTime.Hours = 23;
			sTime.Minutes = minutes;
			sTime.Seconds = seconds;
			break;

		case 1:

			sTime.Hours = hours;
			if (interruptSource == BUTTON_RIGHT_Pin) sTime.Minutes = minutes + 1;
			else if (minutes > 0) sTime.Minutes = minutes - 1;
			else sTime.Minutes = 59;
			sTime.Seconds = seconds;
			break;

		case 2:

			sTime.Hours = hours;
			sTime.Minutes = minutes;
			if (interruptSource == BUTTON_RIGHT_Pin) sTime.Seconds = seconds + 1;
			else if (seconds > 0) sTime.Seconds = seconds - 1;
			else sTime.Seconds = 59;
			break;
		}

		if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
		{
			Error_Handler();
		}
	}

	else
	{
		int date, month, year;
		date = getDate.Date;
		month = getDate.Month;
		year = getDate.Year;

		switch (unitChoose)
		{
		case 0:

			sDate.Year = year;
			sDate.Month = month;
			if (interruptSource == BUTTON_RIGHT_Pin)
			{
				if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 \
								|| month == 10 || month == 12) && date < 31) sDate.Date = date + 1;
				else if ((month == 4 || month == 6 || month == 9 || month == 11) && date < 30)
							sDate.Date = date + 1;
				else if ((month == 2) && (year % 4 == 0) && date < 29) sDate.Date = date + 1;
				else sDate.Date = 1;
			}
			else if (date > 1) sDate.Date = date - 1;
			else if ((month == 2) && (year % 4 != 0)) sDate.Date = 28;
			else if ((month == 2) && (year % 4 == 0)) sDate.Date = 29;
			else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 \
							|| month == 10 || month == 12) sDate.Date = 31;
			else sDate.Date = 30;
			break;

		case 1:

			sDate.Year = year;
			if (interruptSource == BUTTON_RIGHT_Pin)
			{
				if (month < 12) sDate.Month = month + 1;
				else sDate.Month = 1;
			}
			else if (month > 1) sDate.Month = month - 1;
			else sDate.Month = 12;
			sDate.Date = 1;
			break;

		case 2:

			if (interruptSource == BUTTON_RIGHT_Pin)
			{
				if (year < 99) sDate.Year = year + 1;
				else sDate.Year = 1;
			}
			else if (year > 0) sDate.Year = year - 1;
			else sDate.Year = 99;
			sDate.Month = month;
			sDate.Date = date;
			break;
		}

		if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
		{
			Error_Handler();
		}
	}
}

