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
#define ADC12_ORDINARY_TRIG_SOFTWARE  0x1F
#define AT32_ADC_5M
#define ADC_CCE_INT ADC_OCCE_INT
#define ADC_CCE_FLAG ADC_OCCE_FLAG
#endif

#if defined(CONFIG_SOC_SERIES_AT32F435_437)
#include <at32f435_437_adc.h>
#define AT32_ADC_COMM_PSC
#define ADC12_ORDINARY_TRIG_SOFTWARE  0x1F
#define AT32_ADC_5M
#define ADC_CCE_INT ADC_OCCE_INT
#define ADC_CCE_FLAG ADC_OCCE_FLAG
#endif

#if defined(CONFIG_SOC_SERIES_AT32F403A_407)
#include <at32f403a_407_adc.h>
#define AT32_ADC_COMM_PSC
#define AT32_ADC_CRM_DIV
#endif
