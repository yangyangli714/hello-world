/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : Inhr1.c
**     Project     : 2019_exam_question2
**     Processor   : MK20DX128VLH5
**     Component   : AsynchroSerial
**     Version     : Component 02.611, Driver 01.01, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-11-05, 20:46, # CodeGen: 4
**     Abstract    :
**         This component "AsynchroSerial" implements an asynchronous serial
**         communication. The component supports different settings of
**         parity, word width, stop-bit and communication speed,
**         user can select interrupt or polling handler.
**         Communication speed can be changed also in runtime.
**         The component requires one on-chip asynchronous serial channel.
**     Settings    :
**          Component name                                 : Inhr1
**          Channel                                        : UART0
**          Interrupt service/event                        : Enabled
**            Interrupt RxD                                : INT_UART0_RX_TX
**            Interrupt RxD priority                       : medium priority
**            Interrupt TxD                                : INT_UART0_RX_TX
**            Interrupt TxD priority                       : medium priority
**            Interrupt Error                              : INT_UART0_ERR
**            Interrupt Error priority                     : medium priority
**            Input buffer size                            : 200
**            Output buffer size                           : 200
**            Handshake                                    : 
**              CTS                                        : Disabled
**              RTS                                        : Disabled
**          Settings                                       : 
**            Parity                                       : none
**            Width                                        : 8 bits
**            Stop bit                                     : 1
**            Receiver                                     : Enabled
**              RxD                                        : TSI0_CH9/PTB16/UART0_RX/EWM_IN
**              RxD pin signal                             : 
**            Transmitter                                  : Enabled
**              TxD                                        : TSI0_CH10/PTB17/UART0_TX/EWM_OUT_b
**              TxD pin signal                             : 
**            Baud rate                                    : 9600 baud
**            Break signal                                 : Disabled
**            Wakeup condition                             : Idle line wakeup
**            Transmitter output                           : Not inverted
**            Receiver input                               : Not inverted
**            Stop in wait mode                            : no
**            Idle line mode                               : starts after start bit
**            Break generation length                      : Short
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Events enabled in init.                      : yes
**          CPU clock/speed selection                      : 
**            High speed mode                              : This component enabled
**            Low speed mode                               : This component disabled
**            Slow speed mode                              : This component disabled
**          Referenced components                          : 
**            Serial_LDD                                   : Serial_LDD
**     Contents    :
**         RecvChar        - byte Inhr1_RecvChar(Inhr1_TComData *Chr);
**         SendChar        - byte Inhr1_SendChar(Inhr1_TComData Chr);
**         GetCharsInRxBuf - word Inhr1_GetCharsInRxBuf(void);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file Inhr1.c
** @version 01.01
** @brief
**         This component "AsynchroSerial" implements an asynchronous serial
**         communication. The component supports different settings of
**         parity, word width, stop-bit and communication speed,
**         user can select interrupt or polling handler.
**         Communication speed can be changed also in runtime.
**         The component requires one on-chip asynchronous serial channel.
*/         
/*!
**  @addtogroup Inhr1_module Inhr1 module documentation
**  @{
*/         

/* MODULE Inhr1. */

#include "Inhr1.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


#define OVERRUN_ERR      0x01U         /* Overrun error flag bit    */
#define FRAMING_ERR      0x02U         /* Framing error flag bit    */
#define PARITY_ERR       0x04U         /* Parity error flag bit     */
#define CHAR_IN_RX       0x08U         /* Char is in RX buffer      */
#define FULL_TX          0x10U         /* Full transmit buffer      */
#define RUNINT_FROM_TX   0x20U         /* Interrupt is in progress  */
#define FULL_RX          0x40U         /* Full receive buffer       */
#define NOISE_ERR        0x80U         /* Noise error flag bit      */
#define IDLE_ERR         0x0100U       /* Idle character flag bit   */
#define BREAK_ERR        0x0200U       /* Break detect              */
#define COMMON_ERR       0x0800U       /* Common error of RX       */

LDD_TDeviceData *ASerialLdd1_DeviceDataPtr; /* Device data pointer */
static word SerFlag;                   /* Flags for serial communication */
                                       /* Bits: 0 - OverRun error */
                                       /*       1 - Framing error */
                                       /*       2 - Parity error */
                                       /*       3 - Char in RX buffer */
                                       /*       4 - Full TX buffer */
                                       /*       5 - Running int from TX */
                                       /*       6 - Full RX buffer */
                                       /*       7 - Noise error */
                                       /*       8 - Idle character  */
                                       /*       9 - Break detected  */
                                       /*      10 - Unused */
                                       /*      11 - Unused */
static word Inhr1_InpLen;              /* Length of input buffer's content */
static word InpIndexR;                 /* Index for reading from input buffer */
static word InpIndexW;                 /* Index for writing to input buffer */
static Inhr1_TComData InpBuffer[Inhr1_INP_BUF_SIZE]; /* Input buffer for SCI communication */
static Inhr1_TComData BufferRead;      /* Input char for SCI communication */
static word Inhr1_OutLen;              /* Length of output bufer's content */
static word OutIndexR;                 /* Index for reading from output buffer */
static word OutIndexW;                 /* Index for writing to output buffer */
static Inhr1_TComData OutBuffer[Inhr1_OUT_BUF_SIZE]; /* Output buffer for SCI communication */

/*
** ===================================================================
**     Method      :  HWEnDi (component AsynchroSerial)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the bean.
**         The method is called automatically as a part of the Enable and 
**         Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void HWEnDi(void)
{
  (void)ASerialLdd1_ReceiveBlock(ASerialLdd1_DeviceDataPtr, &BufferRead, 1U); /* Receive one data byte */
}

/*
** ===================================================================
**     Method      :  Inhr1_RecvChar (component AsynchroSerial)
**     Description :
**         If any data is received, this method returns one character,
**         otherwise it returns an error code (it does not wait for
**         data). This method is enabled only if the receiver property
**         is enabled.
**         [Note:] Because the preferred method to handle error and
**         break exception in the interrupt mode is to use events
**         <OnError> and <OnBreak> the return value ERR_RXEMPTY has
**         higher priority than other error codes. As a consequence the
**         information about an exception in interrupt mode is returned
**         only if there is a valid character ready to be read.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - Pointer to a received character
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_RXEMPTY - No data in receiver
**                           ERR_BREAK - Break character is detected
**                           (only when the <Interrupt service> property
**                           is disabled and the <Break signal> property
**                           is enabled)
**                           ERR_COMMON - common error occurred (the
**                           <GetError> method can be used for error
**                           specification)
** ===================================================================
*/
byte Inhr1_RecvChar(Inhr1_TComData *Chr)
{
  byte Result = ERR_OK;                /* Return error code */

  if (Inhr1_InpLen > 0x00U) {          /* Is number of received chars greater than 0? */
    EnterCritical();                   /* Disable global interrupts */
    Inhr1_InpLen--;                    /* Decrease number of received chars */
    *Chr = InpBuffer[InpIndexR++];     /* Received char */
    if (InpIndexR >= Inhr1_INP_BUF_SIZE) { /* Is the index out of the receive buffer? */
      InpIndexR = 0x00U;               /* Set index to the first item into the receive buffer */
    }
    Result = (byte)((SerFlag & (OVERRUN_ERR|COMMON_ERR|FULL_RX))? ERR_COMMON : ERR_OK);
    SerFlag &= (word)~(word)(OVERRUN_ERR|COMMON_ERR|FULL_RX|CHAR_IN_RX); /* Clear all errors in the status variable */
    ExitCritical();                    /* Enable global interrupts */
  } else {
    return ERR_RXEMPTY;                /* Receiver is empty */
  }
  return Result;                       /* Return error code */
}

/*
** ===================================================================
**     Method      :  Inhr1_SendChar (component AsynchroSerial)
**     Description :
**         Sends one character to the channel. If the component is
**         temporarily disabled (Disable method) SendChar method only
**         stores data into an output buffer. In case of a zero output
**         buffer size, only one character can be stored. Enabling the
**         component (Enable method) starts the transmission of the
**         stored data. This method is available only if the
**         transmitter property is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_TXFULL - Transmitter is full
** ===================================================================
*/
byte Inhr1_SendChar(Inhr1_TComData Chr)
{
  if (Inhr1_OutLen == Inhr1_OUT_BUF_SIZE) { /* Is number of chars in buffer is the same as a size of the transmit buffer */
    return ERR_TXFULL;                 /* If yes then error */
  }
  EnterCritical();                     /* Disable global interrupts */
  Inhr1_OutLen++;                      /* Increase number of bytes in the transmit buffer */
  OutBuffer[OutIndexW++] = Chr;        /* Store char to buffer */
  if (OutIndexW >= Inhr1_OUT_BUF_SIZE) { /* Is the pointer out of the transmit buffer */
    OutIndexW = 0x00U;                 /* Set index to first item in the transmit buffer */
  }
  if ((SerFlag & RUNINT_FROM_TX) == 0U) {
    SerFlag |= RUNINT_FROM_TX;         /* Set flag "running int from TX"? */
    (void)ASerialLdd1_SendBlock(ASerialLdd1_DeviceDataPtr, (LDD_TData *)&OutBuffer[OutIndexR], 1U); /* Send one data byte */
  }
  ExitCritical();                      /* Enable global interrupts */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  Inhr1_GetCharsInRxBuf (component AsynchroSerial)
**     Description :
**         Returns the number of characters in the input buffer. This
**         method is available only if the receiver property is enabled.
**     Parameters  : None
**     Returns     :
**         ---             - The number of characters in the input
**                           buffer.
** ===================================================================
*/
word Inhr1_GetCharsInRxBuf(void)
{
  return Inhr1_InpLen;                 /* Return number of chars in receive buffer */
}

/*
** ===================================================================
**     Method      :  Inhr1_Init (component AsynchroSerial)
**
**     Description :
**         Initializes the associated peripheral(s) and the bean internal 
**         variables. The method is called automatically as a part of the 
**         application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void Inhr1_Init(void)
{
  SerFlag = 0x00U;                     /* Reset flags */
  Inhr1_InpLen = 0x00U;                /* No char in the receive buffer */
  InpIndexR = 0x00U;                   /* Set index on the first item in the receive buffer */
  InpIndexW = 0x00U;
  Inhr1_OutLen = 0x00U;                /* No char in the transmit buffer */
  OutIndexR = 0x00U;                   /* Set index on the first item in the transmit buffer */
  OutIndexW = 0x00U;
  ASerialLdd1_DeviceDataPtr = ASerialLdd1_Init(NULL); /* Calling init method of the inherited component */
  HWEnDi();                            /* Enable/disable device according to status flags */
}

#define ON_ERROR    0x01U
#define ON_FULL_RX  0x02U
#define ON_RX_CHAR  0x04U
/*
** ===================================================================
**     Method      :  Inhr1_ASerialLdd1_OnBlockReceived (component AsynchroSerial)
**
**     Description :
**         This event is called when the requested number of data is 
**         moved to the input buffer.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ASerialLdd1_OnBlockReceived(LDD_TUserData *UserDataPtr)
{
  register byte Flags = 0U;            /* Temporary variable for flags */

  (void)UserDataPtr;                   /* Parameter is not used, suppress unused argument warning */
  if (Inhr1_InpLen < Inhr1_INP_BUF_SIZE) { /* Is number of bytes in the receive buffer lower than size of buffer? */
    Inhr1_InpLen++;                    /* Increase number of chars in the receive buffer */
    InpBuffer[InpIndexW++] = (Inhr1_TComData)BufferRead; /* Save received char to the receive buffer */
    if (InpIndexW >= Inhr1_INP_BUF_SIZE) { /* Is the index out of the receive buffer? */
      InpIndexW = 0x00U;               /* Set index on the first item into the receive buffer */
    }
    Flags |= ON_RX_CHAR;               /* If yes then set the OnRxChar flag */
  } else {
    SerFlag |= FULL_RX;                /* Set flag "full RX buffer" */
  }
  if ((Flags & ON_RX_CHAR) != 0U) {    /* Is OnRxChar flag set? */
    Inhr1_OnRxChar();                  /* Invoke user event */
  }
  (void)ASerialLdd1_ReceiveBlock(ASerialLdd1_DeviceDataPtr, &BufferRead, 1U); /* Receive one data byte */
}

#define ON_FREE_TX  0x01U
#define ON_TX_CHAR  0x02U
/*
** ===================================================================
**     Method      :  Inhr1_ASerialLdd1_OnBlockSent (component AsynchroSerial)
**
**     Description :
**         This event is called after the last character from the output 
**         buffer is moved to the transmitter.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ASerialLdd1_OnBlockSent(LDD_TUserData *UserDataPtr)
{
  (void)UserDataPtr;                   /* Parameter is not used, suppress unused argument warning */
  OutIndexR++;
  if (OutIndexR >= Inhr1_OUT_BUF_SIZE) { /* Is the index out of the transmit buffer? */
    OutIndexR = 0x00U;                 /* Set index on the first item into the transmit buffer */
  }
  Inhr1_OutLen--;                      /* Decrease number of chars in the transmit buffer */
  if (Inhr1_OutLen != 0U) {            /* Is number of bytes in the transmit buffer greater then 0? */
    SerFlag |= RUNINT_FROM_TX;         /* Set flag "running int from TX"? */
    (void)ASerialLdd1_SendBlock(ASerialLdd1_DeviceDataPtr, (LDD_TData *)&OutBuffer[OutIndexR], 1U); /* Send one data byte */
  } else {
    SerFlag &= (byte)~(RUNINT_FROM_TX); /* Clear "running int from TX" and "full TX buff" flags */
  }
}

/*
** ===================================================================
**     Method      :  Inhr1_ASerialLdd1_OnError (component AsynchroSerial)
**
**     Description :
**         This event is called when a channel error (not the error 
**         returned by a given method) occurs.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ASerialLdd1_OnError(LDD_TUserData *UserDataPtr)
{
  LDD_SERIAL_TError SerialErrorMask;   /* Serial error mask variable */

  (void)UserDataPtr;                   /* Parameter is not used, suppress unused argument warning */
  (void)ASerialLdd1_GetError(ASerialLdd1_DeviceDataPtr, &SerialErrorMask); /* Get error state */
  if (SerialErrorMask != 0U) {
    SerFlag |= (((SerialErrorMask & LDD_SERIAL_PARITY_ERROR) != 0U ) ? PARITY_ERR : 0U);
    SerFlag |= (((SerialErrorMask & LDD_SERIAL_NOISE_ERROR) != 0U ) ? NOISE_ERR : 0U);
    SerFlag |= (((SerialErrorMask & LDD_SERIAL_RX_OVERRUN) != 0U ) ? OVERRUN_ERR : 0U);
    SerFlag |= (((SerialErrorMask & LDD_SERIAL_FRAMING_ERROR) != 0U ) ? FRAMING_ERR : 0U);
  }
}

/*
** ===================================================================
**     Method      :  Inhr1_ASerialLdd1_OnBreak (component AsynchroSerial)
**
**     Description :
**         This event is called when a break occurs on the input channel.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ASerialLdd1_OnBreak(LDD_TUserData *UserDataPtr)
{
  (void)UserDataPtr;                   /* Parameter is not used, suppress unused argument warning */
  SerFlag |= FRAMING_ERR;              /* Set framing error flag */
}


/* END Inhr1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
