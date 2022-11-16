/* ###################################################################
**     Filename    : main.c
**     Project     : ProjectExam
**     Processor   : MK20DX128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-11-10, 17:00, # CodeGen: 0
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
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "Bit1.h"
#include "BitIoLdd1.h"
#include "FC321.h"
#include "RealTimeLdd1.h"
#include "TU1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdlib.h>
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  void send_string(const char *str){
	  int len, i;
	  len = strlen(str);
	  for(i = 0; i < len; i++){
		  Term1_SendChar(str[i]);
	  }

  }
  int quit;
  int score;
  char c;
  int answer;
  uint16 xmeasure;
  float xsmooth;
  int time;
  int a;
  int b;
  int min;
  int value;
  int easy;
  int n;
  score = 0;
  easy = 1;
  xsmooth = 0;
  send_string("CC2511 Exam 2018\r\nAlex Philp");
  AD1_Calibrate(TRUE);
  AD1_Measure(TRUE);
  AD1_GetValue16(&xmeasure);
  srand(xmeasure);
for(;;){
	Term1_ReadChar(&c);
	if(c == 'm'){
		send_string("Monitoring Mode\r\n");
		quit = 0;
		do{
			AD1_Measure(TRUE);
			AD1_GetValue16(&xmeasure);
			xsmooth = 0.9*xsmooth + 0.1*xmeasure;
			Term1_SendFloatNum(xsmooth);
			send_string("\r\n");
			Term1_SendFloatNum(xmeasure);
			send_string("\r\n");
			if(xsmooth > xmeasure){
				Bit1_SetVal();
			}
			else{
				Bit1_ClrVal();
			}
			FC321_Reset();
			FC321_GetTimeMS(&time);
			while(time < 200){
				FC321_GetTimeMS(&time);
				Term1_ReadChar(&c);
				if(Term1_KeyPressed()){
					quit = 1;
					break;
				}
			}
		}while(quit == 0);
	}

	else if(c == 'g'){
		send_string("Entering game mode\r\n");
		while(score < 10){
			send_string("Score:");
			Term1_SendNum(score);
			send_string("\r\n");
			/*if(score >= 0){
				PWM2_SetRatio16(51*score);
				PWM3_SetRatio16(0);
			}
			else if(score < 0){
				PWM3_SetRatio16(-51*score);
				PWM2_SetRatio16(0);
			}*/

			if(easy = 1){
				a = rand() % 1000;
				min = a - 9;
				value = rand() % 9;
				b = min + value;
				Term1_SendNum(a);
				send_string("-");
				Term1_SendNum(b);
				FC321_Reset();
				while(answer == 0){

					//timer
					FC321_GetTimeMS(&time);
					if(time >10000){
						answer = 1;
						score = score - 1;
						send_string("Time out\r\n");
						break;
					}

					//key press
					if(Term1_KeyPressed()){
						answer = 1;
					Term1_ReadChar(&c);  //check typecasting rules
						if((int)c == a-b){
							score++;
							send_string("Correct\r\n");
							if(score = 5){
								easy = 0;
							}
						}
						else{
						score = score - 1;
						send_string("Incorrect\r\n");
						}
					}
				}
			}
			else{
				a = rand() % 1000;
				n = rand() % 1000;
				value = rand() % 9;
				b = ((a+n)-9) + value;
				Term1_SendNum(a);
				send_string("-");
				Term1_SendNum(b);
				FC321_Reset();
				while(answer = 0){

					//timer
					FC321_GetTimeMS(&time);
					if(time >10000){
						answer = 1;
						score = score - 1;
						send_string("Time out\r\n");
						break;
					}

					//key press
					if(Term1_KeyPressed()){
						answer = 1;
					Term1_ReadChar(&c);  //check typecasting rules
						if((int)c == a-b){
							score++;
							send_string("Correct\r\n");
							if(score = 5){
								easy = 0;
							}
						}
						else{
							score = score - 1;
							send_string("Incorrect\r\n");
						}
					}
				}
			}
		}
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

