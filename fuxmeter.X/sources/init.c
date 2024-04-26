/* 
 * File:   init.c
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

/******************************************************************************
* Local variables
******************************************************************************/

/******************************************************************************
* Local function prototypes
******************************************************************************/


/**
  @Summary
    SystemInit

  @Description
    Initialize system: registers, variables...

  @Preconditions
    Must be called after functions SYSTEM_Initialize() generated from MCC

  @Returns
    
  @Param
    None

  @Example
    <code>
    </code>
 */
void SystemInit (void)
{
//    WWDT_SoftEnable();
    TimeBaseVarInit();

//    InitAnalogIO();

}

