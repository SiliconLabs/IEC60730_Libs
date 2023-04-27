/**************************************************************************//**
 * Copyright (c) 2021 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/

#ifndef IEC60730_SEGGER_H_
#define IEC60730_SEGGER_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "SEGGER_SYSVIEW.h"

#define TASK_BIST_ID        (10)

#define TASK_DECLARE(x) \
  SEGGER_SYSVIEW_OnTaskCreate((x))
#define TASK_STARTEXEC(x) \
  SEGGER_SYSVIEW_OnTaskStartExec((x))
#define TASK_TERMINATE(x) \
  SEGGER_SYSVIEW_OnTaskTerminate((x))

#define DECLARE_BENMARK_BIST()    TASK_DECLARE(TASK_BIST_ID)
#define STARTEXEC_BENMARK_BIST()  TASK_STARTEXEC(TASK_BIST_ID)
#define TERMINATE_BENMARK_BIST()  TASK_TERMINATE(TASK_BIST_ID)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IEC60730_SEGGER_H_ */
