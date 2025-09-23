/**
  **************************************************************************
  * @file     system_at32f402_405.h
  * @brief    cmsis cortex-m4 system header file.
  **************************************************************************
  *
  * Copyright (c) 2025, Artery Technology.
  *
  * SPDX-License-Identifier: Apache-2.0
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#ifndef __SYSTEM_AT32F402_405_H
#define __SYSTEM_AT32F402_405_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup AT32F402_405_system
  * @{
  */

/** @defgroup AT32F402_405_system_exported_variables 
  * @{
  */
extern unsigned int system_core_clock; /*!< system clock frequency (core clock) */

/**
  * @}
  */

/** @defgroup AT32F402_405_system_exported_functions 
  * @{
  */
  
extern void SystemInit(void);
extern void system_core_clock_update(void);
extern void reduce_power_consumption(void);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif

