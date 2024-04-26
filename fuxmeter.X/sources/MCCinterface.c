/*
 * File:   interrupt.c
 * Author: lxmunian
 *
 * Created on 28 dicembre 2019, 22.19
 */

/******************************************************************************
* Includes
******************************************************************************/
#include "MCCinterface.h"
#include "../mcc_generated_files/mcc.h"
#include "variables.h"


/******************************************************************************
* Local variables
******************************************************************************/
typedef struct
{
    uint8_t timer_1ms;
    uint8_t timer_10ms;
    uint8_t timer_100ms;
    uint8_t timer_500ms;
    uint8_t timer_1s;
    uint8_t timer_1minute;
    uint8_t timer_1hour;
    uint8_t timer_1day;
} timebase_timers_t;

volatile timebase_flags_t timebase_flags;        /* flags for timebase */
static volatile timebase_timers_t timebase_timers;      /* timers for timebase */

/******************************************************************************
* Local function prototypes
******************************************************************************/

/**
  @Summary
    TimeBaseVarInit

  @Description
    Initialize all vars related to timebase

  @Preconditions
    Must be called inside interrupt service routine every 100us

  @Returns
    None    
  @Param
    None

  @Example
    <code>
    </code>
 */
void TimeBaseVarInit(void)
{
    timebase_flags.time_100ms=false;
    timebase_flags.time_100us=false;
    timebase_flags.time_10ms=false;
    timebase_flags.time_1day=false;
    timebase_flags.time_1hour=false;
    timebase_flags.time_1minute=false;
    timebase_flags.time_1ms=false;
    timebase_flags.time_1s=false;
    timebase_flags.time_500ms=false;
    
    timebase_timers.timer_100ms=0;
    timebase_timers.timer_10ms=0;
    timebase_timers.timer_1day=0;
    timebase_timers.timer_1hour=0;
    timebase_timers.timer_1minute=0;
    timebase_timers.timer_1ms=0;
    timebase_timers.timer_1s=0;
    timebase_timers.timer_500ms=0;
}

/**
  @Summary
    TimeBase

  @Description
    Generate the timebase

  @Preconditions
    Must be called inside interrupt service routine every 100us

  @Returns
     None

  @Param
    None

  @Example
    <code>
    </code>
 */
void TimeBase(void)
{
    timebase_flags.time_100us = true;
    
    if (++timebase_timers.timer_1ms == 10) /* every 1 ms */
    {
        timebase_timers.timer_1ms = 0;
        
        if (++timebase_timers.timer_10ms == 10) /* every 10 ms */
        {
            timebase_timers.timer_10ms = 0;
            timebase_flags.time_10ms = true;

            if (++timebase_timers.timer_100ms == 10) /* every 100 ms */
            {
                timebase_timers.timer_100ms = 0;
                timebase_flags.time_100ms = true;
                
                if (++timebase_timers.timer_500ms == 5) /* every 500 ms */
                {
                    timebase_timers.timer_500ms = 0;
                    timebase_flags.time_500ms = true;
                    
                    if (++timebase_timers.timer_1s == 10) /* every 1000 ms */
                    {
                        timebase_timers.timer_1s = 0;
                        timebase_flags.time_1s = true;
                        
                        if (++timebase_timers.timer_1minute == 60) /* every 1 minute */
                        {
                            timebase_timers.timer_1minute = 0;
                            timebase_flags.time_1minute = true;
                            
                            if (++timebase_timers.timer_1hour == 60) /* every 1 hour */
                            {
                                timebase_timers.timer_1hour = 0;
                                timebase_flags.time_1hour = true;
                                
                                if (++timebase_timers.timer_1day == 24) /* every 1 day */
                                {
                                    timebase_timers.timer_1day = 0;
                                    timebase_flags.time_1day = true;

                                }
                            }
                        }
                    }
                }
            }
        }
    }
}