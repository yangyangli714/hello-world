/* ###################################################################
**     Filename    : main.c
**     Project     : exam
**     Processor   : MK22FN512VDC12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-11-08, 19:10, # CodeGen: 0
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
#include "Pins1.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "RED.h"
#include "BitIoLdd1.h"
#include "GREEN.h"
#include "BitIoLdd2.h"
#include "BLUE.h"
#include "BitIoLdd3.h"
#include "FC321.h"
#include "RealTimeLdd1.h"
#include "TU1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
volatile char buffer [100];
volatile uint8 index = 0;
volatile bool enter = false;

volatile uint16 raw_adc;
volatile float voltage, t;
volatile char vec[3];
// Delay function - creates a delay period
void delay(int delay_ms) {
	word time;
	FC321_Reset();
	do{
		__asm("wfi");
		FC321_GetTimeMS(&time);
	}while(time < delay_ms);
}
void GUI_main() {
	Term1_MoveTo(3, 2);
	Term1_SetColor(clYellow, clBlack);
	Term1_SendStr("CC2511 Exam 2019");
	Term1_MoveTo(3, 3);
	Term1_SendStr("YangYang Li");
	Term1_MoveTo(1, 5);
	Term1_SendStr("Press 't' for Question 2");
	Term1_MoveTo(1, 6);
	Term1_SendStr("Press 's' for Gaming mode");
	Term1_MoveTo(1, 7);
	Term1_SendStr(">");
}

void GUI_clear() {
	Term1_MoveTo(1, 8);
	Term1_EraseLine();
	Term1_MoveTo(1, 9);
	Term1_EraseLine();
	Term1_MoveTo(1, 10);
	Term1_EraseLine();
	Term1_MoveTo(1, 11);
	Term1_EraseLine();
}


void raw_adc_calc(uint16 raw_adc) {
	AD1_Measure(TRUE);
	AD1_GetValue16(&raw_adc);
	Term1_MoveTo(1,8);
	Term1_SendStr("Analog Measurement:\r\n");
	Term1_SendStr("x = ");
	Term1_SendNum(raw_adc);
	Term1_SendStr("\r\n");
	voltage = ((float)raw_adc * 3.3 / (65536-1));
	Term1_SendStr("v = ");
	Term1_SendFloatNum(voltage);
	Term1_SendStr("V \r\n");
	t = ((float)(30702 - raw_adc) / 162.8);
	Term1_SendStr("t = ");
	Term1_SendFloatNum(t);
	Term1_SendStr("\r\n");
}

int random_LED(char vec[3],int i){
	int rand(void);
	void srand(unsigned int seed);
	int r = rand() % 3;
	// red
	if(r == 0){
		RED_ClrVal();
		delay(1000);
		RED_SetVal();
		BLUE_SetVal();
		GREEN_SetVal();
		delay(500);
		vec[i] = 'r';
		// green
	}else if(r == 1){
		GREEN_ClrVal();
		delay(1000);
		RED_SetVal();
		BLUE_SetVal();
		GREEN_SetVal();
		delay(500);
		vec[i] = 'g';
		// blue
	}else if(r == 2){
		BLUE_ClrVal();
		delay(1000);
		RED_SetVal();
		BLUE_SetVal();
		GREEN_SetVal();
		delay(500);
		vec[i] = 'b';
	}
	return r;
}
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
//  byte err;
  int i, score;
  Term1_Cls();
  GUI_main();
  char input1, input2, input3;
  for(;;) {
	  while(!enter)
	  {
		  __asm ("wfi");
	  }

	  if(enter){
		  if((0 == strcmp((char*) buffer, "t"))){
			  GUI_clear();
			  raw_adc_calc(raw_adc);
			  Term1_MoveTo(1, 7);
			  Term1_SendStr(">");
		  }else if((0 == strcmp((char*) buffer, "s"))){
			  RED_SetVal();
			  BLUE_SetVal();
			  GREEN_SetVal();
			  GUI_clear();
			  Term1_MoveTo(1, 8);
			  Term1_SendStr("Color Game Mode");
			  score = 0;
			  for(int i = 0; i<3;i++){
				  int r = random_LED(vec,i);
			  }
			  Term1_MoveTo(1, 15);
			  Term1_SendStr(vec);
			  enter = false;
			  Term1_SendChar(vec);
			  index = 0;
			  do{
				  Term1_MoveTo(1, 9);
				  Term1_SendStr("Type in sequence r for red, g for green and b for blue: ");
				  Term1_MoveTo(1, 7);
				  Term1_SendStr(">");
				  while(!enter){
					  __asm("wfi");
				  }
				  sscanf((char *)buffer, "%c%c%c", &input1, &input2, &input3);
				  if((vec[0] == input1) && (vec[1] == input2) && (vec[2] == input3)){
					  score += 5;
					  Term1_MoveTo(1, 11);
					  Term1_SendStr("Correct!");
				  }else{
					  score -= 5;
					  Term1_MoveTo(1, 11);
					  Term1_SendStr("Wrong!");
				  }
			  }while((-5 < score) && (score < 5));
			  Term1_MoveTo(1, 12);
			  Term1_SendStr("Game finished!");
		  }
		  enter = false;
		  index = 0;
		  // clear the command prompt
		  Term1_MoveTo(1,7);
		  Term1_EraseLine();
		  Term1_SendStr(">");

	  }
  }


  /* Write your code here */
  /* For example: for(;;) { } */

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
