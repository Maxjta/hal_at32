/*
 * Copyright (c) 2025 Maxjta 
 * SPDX-License-Identifier: Apache-2.0
 */

#if defined(CONFIG_SOC_SERIES_AT32F402_405)
#include <at32f402_405_flash.h>
#define FLASH_WAIT_CYCLE      1
#endif

#if defined(CONFIG_SOC_SERIES_AT32F423)
#include <at32f423_flash.h>
#define FLASH_WAIT_CYCLE      1
#endif

#if defined(CONFIG_SOC_SERIES_AT32F435_437)
#include <at32f435_437_flash.h>
#define FLASH_FDIV
#endif

#if defined(CONFIG_SOC_SERIES_AT32F403A_407)
#include <at32f403a_407_flash.h>
#endif

#if defined(CONFIG_SOC_SERIES_AT32F45X)
#include <at32f45x_flash.h>
#define FLASH_WAIT_CYCLE      1
#endif
