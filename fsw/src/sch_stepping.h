/*
** $Id: sch_stepping.h 1.0 2026/03/09
**
**  Copyright (c) 2007-2014 United States Government as represented by the
**  Administrator of the National Aeronautics and Space Administration.
**  All Other Rights Reserved.
**
**  This software was created at NASA's Goddard Space Flight Center.
**  This software is governed by the NASA Open Source Agreement and may be
**  used, distributed and modified only pursuant to the terms of that
**  agreement.
**
** Purpose: Scheduler (SCH) application CFE_SIM_STEPPING hooks
**
** Author:
**
** Notes:
**
*/

#ifndef SCH_STEPPING_H
#define SCH_STEPPING_H

/*
** Include Files
*/

/*
** Macro Definitions
*/

/*
** Stepping hook function prototypes
** These hooks are called at key timing boundaries in the SCH application
** when CFE_SIM_STEPPING is enabled (not compiled in when disabled)
*/

#ifdef CFE_SIM_STEPPING

/**
 * @brief Hook called at each minor frame (slot) boundary
 *
 * This hook is called after a minor frame has been processed,
 * providing granular stepping control at the sub-frame level.
 * Minor frames are the basic scheduling unit in SCH.
 */
extern void SCH_Stepping_Hook_MinorFrame(void);

#else

/* Stepping disabled - provide empty inline functions to eliminate overhead */

static inline void SCH_Stepping_Hook_MinorFrame(void) {}

#endif /* CFE_SIM_STEPPING */

#endif /* SCH_STEPPING_H */
