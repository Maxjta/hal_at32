/*
 * Copyright (c) 2025 Maxjta 
 * SPDX-License-Identifier: Apache-2.0
 */

#if defined(CONFIG_SOC_SERIES_AT32F402_405)
#include <at32f402_405_pwc.h>
#define PWC_LDO_OUTPUT         1
#define PWC_LDO_OUTPUT_MAX     PWC_LDO_OUTPUT_1V3
#endif

#if defined(CONFIG_SOC_SERIES_AT32F423)
#include <at32f423_pwc.h>
#define PWC_LDO_OUTPUT         1
#define PWC_LDO_OUTPUT_MAX     PWC_LDO_OUTPUT_1V3
#endif

#if defined(CONFIG_SOC_SERIES_AT32F435_437)
#include <at32f435_437_pwc.h>
#define PWC_LDO_OUTPUT         1
#define PWC_LDO_OUTPUT_MAX     PWC_LDO_OUTPUT_1V3
#endif
