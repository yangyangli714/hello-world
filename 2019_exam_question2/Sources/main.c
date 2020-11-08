/* ###################################################################
**     Filename    : main.c
**     Project     : 2019_exam_question2
**     Processor   : MK20DX128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-11-05, 16:17, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "ADC.h"
#include "AdcLdd1.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "RED_LED.h"
#include "BitIoLdd1.h"
#include "GREEN_LED.h"
#include "BitIoLdd2.h"
#include "BLUE_LED.h"
#include "BitIoLdd3.h"
#include "FC321.h"
#include "RealTimeLdd1.h"
#include "TU1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* User includes (#include below this line is not maintained by Processor Expert) */
volatile char buffer[150];
volatile int index;
volatile bool complete_command;
volatile bool sendMode = false;

int rand(void);
void srand(unsigned int seed);

void delay(word delay_ms)
{
	word time;
	FC321_Reset();
	do
	{
		__asm("wfi"); // the micro-controller would be in low power mode

		FC321_GetTimeMS(&time);
	}while(time < delay_ms);
}

void LEDS_off()
{
	RED_LED_SetVal();
	GREEN_LED_SetVal();
	BLUE_LED_SetVal();
}

int three_LEDs(char colour[3], int i) {
	/* Initialize random number generator */
	int r = rand() % 3;
	if (r == 2) {
		BLUE_LED_ClrVal();
		delay(1000);
		LEDS_off();
		delay(500);
		colour[i] = 'b';
	} else if (r == 1) {
		GREEN_LED_ClrVal();
		delay(1000);
		LEDS_off();
		delay(500);
		colour[i] = 'g';
	} else if (r == 0) {
		RED_LED_ClrVal();
		delay(1000);
		LEDS_off();
		delay(500);
		colour[i] = 'r';
	}

	return r;
}
int four_LEDs(char colour1[4], int i) {
	/* Initialize random number generator */
	int r1 = rand() % 3;
	if (r1 == 2) {
		BLUE_LED_ClrVal();
		delay(1000);
		LEDS_off();
		delay(500);
		colour1[i] = 'b';
	} else if (r1 == 1) {
		GREEN_LED_ClrVal();
		delay(1000);
		LEDS_off();
		delay(500);
		colour1[i] = 'g';
	} else if (r1 == 0) {
		RED_LED_ClrVal();
		delay(1000);
		LEDS_off();
		delay(500);
		colour1[i] = 'r';
	}
	else if (r1 == 3) {
			RED_LED_ClrVal();
			GREEN_LED_ClrVal();
			BLUE_LED_ClrVal();
			delay(1000);
			LEDS_off();
			delay(500);
			colour1[i] = 'a';
		}

	return r1;
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	byte err;
	char t;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

  //Calibrate  ADC before use
  ADC_Calibrate(TRUE);
  uint16 adc_result;
  float voltage, time;
  int i, score = 0;
  LEDS_off();
  char colour[3], colour1[4];
  char input1, input2, input3;

  for(;;)
  {
	  while (!complete_command) {
		  __asm ("wfi");
	  }
	  //Processing the received char and complete command
	  complete_command = 0;

	  if ((0 == strcmp((char*) buffer, "t")))
	  {
		  sendMode = 0;
		  Term1_MoveTo(1, 2);
		  Term1_SendStr("Analog Measurement:");
		  ADC_Measure(TRUE);
		  ADC_GetValue16(&adc_result);
		  Term1_MoveTo(1, 3);
		  Term1_SendStr("X = ");
		  Term1_MoveTo(4, 3);
		  Term1_SendStr("           ");
		  Term1_MoveTo(5, 3);
		  Term1_SendNum(adc_result);

		  // Part c
		  //Find voltage based on received adc_result
		  voltage = ((float)0.6/(65536 - adc_result)) * adc_result+ 0.92;

		  // Overflow error
		  if (voltage <0)
		  	  {
			  voltage = 0;
		  	  }
		  Term1_MoveTo(1, 4);
		  Term1_SendStr("v =       V");
		  Term1_MoveTo(4, 4);
		  Term1_SendStr("      ");
		  Term1_MoveTo(5, 4);
		  Term1_SendFloatNum(voltage);

		  // Part d
		  //Find the value of t
		  time = ((float)(30702 - adc_result)/162.8);

		  // Overflow error
		  if (voltage <0)
		  {
			  voltage = 0;
		  }
		  Term1_MoveTo(1, 5);
		  Term1_SendStr("t =       seconds");
		  Term1_MoveTo(4, 5);
		  Term1_SendStr("      ");
		  Term1_MoveTo(5, 5);
		  Term1_SendNum(time);
	  }

	  //Question 4 a, b

	  else if ((0 == strcmp((char*) buffer, "s")))
	  {
		  Term1_MoveTo(1, 7);
		  Term1_SendStr("Colour Game Mode");
		  for (int i = 0; i < 3; i++)
		  {

			  /* Initialize random number generator */

			  int r = three_LEDs(colour, i);
		  }
		 do
		  {
			  sendMode = 1;
					  Term1_MoveTo(1, 8);
					  Term1_SendStr("Type in sequence r for red, g for green and b for blue: ");
					  while (!complete_command) {	//reads the string put into the command prompt
					  		__asm ("wfi");
					  	}
					  complete_command = 0;
					  Term1_MoveTo(57, 8);
					  Term1_SendStr("    ");
					  Term1_MoveTo(57, 8);
					  sscanf((char *)buffer, "%c%c%c", &input1, &input2, &input3);
					  Term1_MoveTo(1, 9);
					  Term1_SendChar(input1);
					  Term1_MoveTo(4, 9);
					  Term1_SendChar(input2);
					  Term1_MoveTo(6, 9);
					  Term1_SendChar(input3);
					  Term1_MoveTo(1, 11);
					  Term1_SendStr("Total score: ");
					  Term1_MoveTo(1, 10);
					  Term1_SendStr("                ");
			  if ((colour[0] == input1) && (colour[1] == input2) && (colour[2] == input3))
			  {
				  score += 1;
				  Term1_MoveTo(1, 10);
				  Term1_SendStr("Correct!");
				  Term1_MoveTo(13, 11);
				  Term1_SendNum(score);

			  }
			  else
			  {
				  score -= 1;
				  Term1_MoveTo(1, 10);
				Term1_SendStr("Incorrect!");
				  Term1_MoveTo(13, 11);
				  Term1_SendNum(score);

			  }
		  }
		 while((-5 < score) && (score < 5));
		 Term1_MoveTo(1, 12);
		 Term1_SendStr("Game finished!");

		 //Part e
		 if (score == 5)
		 {
			 Term1_MoveTo(1, 13);
			 Term1_SendStr("Next level!");
			 index = 0;
			 char input4;
			 Term1_Cls();
			 for (int i = 0; i < 4; i++)
			 {

				 /* Initialize random number generator */

				 int r1 = four_LEDs(colour1, i);
			 }

			 do
			 {
				 sendMode = 1;
				 Term1_MoveTo(1, 8);
				 Term1_SendStr("Type in sequence r for red, g for green and b for blue: ");
				 Term1_MoveTo(1, 15);
				 Term1_SendStr(colour1);

				 while (!complete_command) {	//reads the string put into the command prompt
					 __asm ("wfi");
				 }
				 complete_command = 0;
				 Term1_MoveTo(57, 8);
				 Term1_SendStr("    ");
				 Term1_MoveTo(57, 8);
				 sscanf((char *)buffer, "%c%c%c%c", &input1, &input2, &input3, &input4);
				 Term1_MoveTo(1, 9);
				 Term1_SendChar(input1);
				 Term1_MoveTo(4, 9);
				 Term1_SendChar(input2);
				 Term1_MoveTo(6, 9);
				 Term1_SendChar(input3);
				 Term1_MoveTo(9, 9);
				 Term1_SendChar(input4);
				 Term1_MoveTo(1, 11);
				 Term1_SendStr("Total score: ");
				 Term1_MoveTo(1, 10);
				 Term1_SendStr("                ");
				 if ((colour1[0] == input1) && (colour1[1] == input2) && (colour1[2] == input3) && (colour1[3] == input4))
				 {
					 score += 1;
					 Term1_MoveTo(1, 10);
					 Term1_SendStr("Correct!");
					 Term1_MoveTo(13, 11);
					 Term1_SendNum(score);
				 }
				 else
				 {
					 score -= 1;
					 Term1_MoveTo(1, 10);
					 Term1_SendStr("Incorrect!");
					 Term1_MoveTo(13, 11);
					 Term1_SendNum(score);

				 }
			 } while ((score < 10) && (score > 3));
		 }
		 sendMode = 0;

	  }

  }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
#ifdef PEX_RTOS_START
  PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
#endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.5 [05.21]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
