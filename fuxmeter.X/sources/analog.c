/* 
 * File:   analog.c
 * Author: lxmunian
 *
 * Created on 28 dicembre 2019, 22.19
 */

/******************************************************************************
* Includes
******************************************************************************/
#include "variables.h"
#include "init.h"
#include "../mcc_generated_files/mcc.h"
#include "MCCinterface.h"
#include "analog.h"

/******************************************************************************
* Local variables
******************************************************************************/
uint16_t convertedValue;

/******************************************************************************
* Local function prototypes
******************************************************************************/

/**
  @Summary
    ReadAnlog

  @Description
    This routine is used to read the analog channel 
    
  @Preconditions
    ADC_Initialize() function should have been called before calling this function.

  @Returns
    None

  @Param
    None

  @Example
    <code>
    uint16_t convertedValue;

    ADC_StartConversion();
    convertedValue = ADC_GetConversionResult();
    </code>
*/
void ReadAnalog(void)
{
    uint16_t convertedValue;
    ADC_StartConversion();
    convertedValue = ADC_GetConversionResult();
}