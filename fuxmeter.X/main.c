/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC12F1822
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/*
 *******************************************************************************
 *       Project: Fluxmeter
 *       Target: PIC12F1822
 *       Toolchain: 
 *                  MPlabX_v5.25; 
 *                  XC8_v2.05; 
 *                  Packs:12-16F1xxxx_DFP (1.0.42);
 *                  Mplab Code Configurator: Version: v3.85.1;
 *                                           Core v4.75
 * 
 *       Started: 23/12/2019
 *       
 *       Note =  First release.
 *       lxmunian
 *******************************************************************************
 */

/******************************************************************************
* Includes
******************************************************************************/
#include "mcc_generated_files/mcc.h"
#include "sources/variables.h"
#include "sources/MCCinterface.h"
#include "sources/init.h"
#include "sources/analog.h"


/******************************************************************************
* Local variables
******************************************************************************/

/******************************************************************************
* Local function prototypes
******************************************************************************/
void gen_pulse(void);

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();


    SystemInit();
    CLRWDT();
    while (1)
    {
        /* 100us START */
        if (timebase_flags.time_100us == true)
        {
            timebase_flags.time_100us = false;
        }
        /* 100us END*/

        /* 1ms START */
        if (timebase_flags.time_1ms == true)
        {
            timebase_flags.time_1ms = false;
            
            /* */
            gen_pulse();
        }
        /* 1ms END*/

        /* 10ms START */
        if (timebase_flags.time_10ms == true)
        {
            timebase_flags.time_10ms = false;
            
            /* */
            ReadAnalog();
            
        }
        /* 10ms END*/

        /* 100ms START */
        if (timebase_flags.time_100ms == true)
        {
            timebase_flags.time_100ms = false;
        }
        /* 100ms END*/

        /* 500ms START */
        if (timebase_flags.time_500ms == true)
        {
            timebase_flags.time_500ms = false;
            
            LED_Toggle(); /* toggle led pin */
        }
        /* 500ms END*/

        /* 1s START */
        if (timebase_flags.time_1s == true)
        {
            timebase_flags.time_1s = false;
            CLRWDT();
        }
        /* 1s END*/

    }
}

/**
  @Summary
    gen_pulse

  @Description
    Generate pulse wave to simulate the fluxmeter hall signal
    
  @Preconditions
     Must be called every 1ms   
  
  @Returns
    None

  @Param
    None

  @Example
    <code>
    </code>
*/
void gen_pulse(void)
{
    static uint16_t count_pulse;
    static uint16_t filterTrimmer;
    uint16_t tempThreshold;

	count_pulse++; /* increase conter */
    if (convertedValue > filterTrimmer)
        filterTrimmer ++;
    else if (convertedValue < filterTrimmer)
        filterTrimmer --;        
	
    /* Convert AD to signal modulated in frequency */
	tempThreshold = filterTrimmer;
    if (tempThreshold > OFFSET) /* calculate only if > OFFSET*/
    {
        tempThreshold -= OFFSET;
        tempThreshold *= MULTIPLIER;
        tempThreshold /= DIVIDER;   /* */
    }
    else
    {
       tempThreshold = 0;
    }

	if (count_pulse >= tempThreshold) /* when counter become greater than threshold, toggle the output pin */
    {
		count_pulse= 0;
		OUT_FLUX_Toggle(); /* Toggle pin */	
    }
    
}
/**
 End of File
*/