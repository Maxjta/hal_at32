/**
  **************************************************************************
  * @file     at32f423_misc.h
  * @brief    at32f423 misc header file
  **************************************************************************
  *
  * Copyright (c) 2025, Artery Technology.
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *
  * 1. Redistributions of source code must retain the above copyright notice, this
  * list of conditions and the following disclaimer.
  *
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  * this list of conditions and the following disclaimer in the documentation and/or
  * other materials provided with the distribution.
  *
  * 3. Neither the name of the copyright holder nor the names of its contributors
  * may be used to endorse or promote products derived from this software without
  * specific prior written permission.
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

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F423_MISC_H
#define __AT32F423_MISC_H

#ifdef __cplusplus
extern "C" {
#endif


/* includes ------------------------------------------------------------------*/
#include "at32f423.h"

/** @addtogroup AT32F423_periph_driver
  * @{
  */

/** @addtogroup MISC
  * @{
  */

/** @defgroup MISC_vector_table_base_address
  * @{
  */

#define NVIC_VECTTAB_RAM                 ((uint32_t)0x20000000) /*!< nvic vector table based ram address */
#define NVIC_VECTTAB_FLASH               ((uint32_t)0x08000000) /*!< nvic vector table based flash address */

/**
  * @}
  */

/** @defgroup MISC_exported_types
  * @{
  */

/**
  * @brief nvic interrupt priority group
  */
typedef enum
{
  NVIC_PRIORITY_GROUP_0                  = ((uint32_t)0x7), /*!< 0 bits for preemption priority, 4 bits for subpriority */
  NVIC_PRIORITY_GROUP_1                  = ((uint32_t)0x6), /*!< 1 bits for preemption priority, 3 bits for subpriority */
  NVIC_PRIORITY_GROUP_2                  = ((uint32_t)0x5), /*!< 2 bits for preemption priority, 2 bits for subpriority */
  NVIC_PRIORITY_GROUP_3                  = ((uint32_t)0x4), /*!< 3 bits for preemption priority, 1 bits for subpriority */
  NVIC_PRIORITY_GROUP_4                  = ((uint32_t)0x3)  /*!< 4 bits for preemption priority, 0 bits for subpriority */
} nvic_priority_group_type;

/**
  * @brief nvic low power mode
  */
typedef enum
{
  NVIC_LP_SLEEPONEXIT                    = 0x02, /*!< enable sleep-on-exit feature */
  NVIC_LP_SLEEPDEEP                      = 0x04, /*!< enable sleep-deep output signal when entering sleep mode */
  NVIC_LP_SEVONPEND                      = 0x10  /*!< send event on pending */
} nvic_lowpower_mode_type;

/**
  * @brief systick clock source
  */
typedef enum
{
  SYSTICK_CLOCK_SOURCE_AHBCLK_DIV8       = ((uint32_t)0x00000000), /*!< systick clock source from core clock div8 */
  SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV      = ((uint32_t)0x00000004)  /*!< systick clock source from core clock */
} systick_clock_source_type;

/**
  * @}
  */

/** @defgroup MISC_exported_functions
  * @{
  */

void nvic_system_reset(void);
void nvic_irq_enable(IRQn_Type irqn, uint32_t preempt_priority, uint32_t sub_priority);
void nvic_irq_disable(IRQn_Type irqn);
void nvic_priority_group_config(nvic_priority_group_type priority_group);
void nvic_vector_table_set(uint32_t base, uint32_t offset);
void nvic_lowpower_mode_config(nvic_lowpower_mode_type lp_mode, confirm_state new_state);
void systick_clock_source_config(systick_clock_source_type source);

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
