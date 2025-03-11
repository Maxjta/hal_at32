/*
 * Copyright (c) 2025 Maxjta 
 * SPDX-License-Identifier: Apache-2.0
 */

#if defined(CONFIG_SOC_SERIES_AT32F402_405)
#include <at32f402_405_tmr.h>
#define IS_TMR_BREAK(TMRX)  ((TMRX==TMR1) || (TMRX==TMR10) || \
                             (TMRX==TMR11) || (TMRX==TMR13) || \
                             (TMRX==TMR14) \
                            )
 #define IS_TMR_SLAVE(TMRX)  ((TMRX==TMR1) || (TMRX==TMR10) || \
                            (TMRX==TMR11) || (TMRX==TMR13) || \
                            (TMRX==TMR14) \
                           )
#endif
