/**
  **************************************************************************
  * @file     at32f435_437_def.h
  * @brief    at32f435_437 macros header file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F435_437_DEF_H
#define __AT32F435_437_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

/* gnu compiler */
#if defined (__GNUC__)
  #ifndef ALIGNED_HEAD
    #define ALIGNED_HEAD
  #endif
  #ifndef ALIGNED_TAIL
    #define ALIGNED_TAIL                 __attribute__ ((aligned (4)))
  #endif
#endif

/* arm compiler */
#if defined (__CC_ARM)
  #ifndef ALIGNED_HEAD
    #define ALIGNED_HEAD                 __align(4)
  #endif
  #ifndef ALIGNED_TAIL
    #define ALIGNED_TAIL
  #endif
#endif

/* iar compiler */
#if defined (__ICCARM__)
  #ifndef ALIGNED_HEAD
    #define ALIGNED_HEAD
  #endif
  #ifndef ALIGNED_TAIL
    #define ALIGNED_TAIL
  #endif
#endif

#define UNUSED(x)                        (void)x /* to avoid gcc/g++ warnings */

#ifdef __cplusplus
}
#endif

#endif
