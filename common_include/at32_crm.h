/*
 * Copyright (c) 2025 Maxjta 
 * SPDX-License-Identifier: Apache-2.0
 */

#if defined(CONFIG_SOC_SERIES_AT32F402_405)
#include <at32f402_405_crm.h>
#define CRM_PLL_FU          1
#endif

#if defined(CONFIG_SOC_SERIES_AT32F423)
#include <at32f423_crm.h>
#define CRM_USB_DIV
#endif
