/*
 * Copyright (c) 2025 Maxjta 
 * SPDX-License-Identifier: Apache-2.0
 */

#if defined(CONFIG_SOC_SERIES_AT32F402_405)
#include <at32f402_405_adc.h>
#define AT32_ADC_COMM_PSC
#endif

#if defined(CONFIG_SOC_SERIES_AT32F423)
#include <at32f423_adc.h>
#define AT32_ADC_COMM_PSC
#endif
