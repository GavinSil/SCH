/************************************************************************
 * NASA Docket No. GSC-19,200-1, and identified as "cFS Draco"
 *
 * Copyright (c) 2023 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/*
** File: sch_stepping.c
**
** Subsystem: SCH Stepping Hooks
**
** Description: This file contains stepping synchronization hook implementations
**              for the SCH (Scheduler) application, enabling coordinated step
**              control when CFE_SIM_STEPPING is enabled.
**
*/

#ifdef CFE_SIM_STEPPING

#include "sch_stepping.h"
#include "esa_stepping_shim.h"

/****************************************************************************************
                                    STEPPING HOOK IMPLEMENTATIONS
 ***************************************************************************************/

/**
 * @brief Hook called when SCH waits on the TimeSemaphore
 *
 * Thin fact forwarder: reports scheduler semaphore wait boundary to the unified stepping
 * shim. This occurs at the start of each minor frame processing cycle.
 * The shim dispatches this to the core state machine for stepping synchronization.
 */
void SCH_Stepping_Hook_SemaphoreWait(void)
{
    ESA_Stepping_ShimEvent_t event = {0};

    event.event_kind = ESA_SIM_STEPPING_EVENT_SCH_SEMAPHORE_WAIT;

    ESA_Stepping_Shim_ReportEvent(&event);
}

/**
 * @brief Hook called at each minor frame boundary
 *
 * Thin fact forwarder: reports minor frame boundary to the unified stepping shim.
 * Minor frames are the fundamental scheduling unit and define stepping trigger
 * granularity. The shim dispatches this to the core state machine for stepping
 * synchronization.
 */
void SCH_Stepping_Hook_MinorFrame(void)
{
    ESA_Stepping_ShimEvent_t event = {0};

    event.event_kind = ESA_SIM_STEPPING_EVENT_SCH_MINOR_FRAME;

    ESA_Stepping_Shim_ReportEvent(&event);
}

/**
 * @brief Hook called at major frame boundary
 *
 * Thin fact forwarder: reports major frame boundary to the unified stepping shim.
 * Major frames mark the beginning of a complete scheduling cycle.
 * The shim dispatches this to the core state machine for stepping synchronization.
 */
void SCH_Stepping_Hook_MajorFrame(void)
{
    ESA_Stepping_ShimEvent_t event = {0};

    event.event_kind = ESA_SIM_STEPPING_EVENT_SCH_MAJOR_FRAME;

    ESA_Stepping_Shim_ReportEvent(&event);
}

#endif /* CFE_SIM_STEPPING */
