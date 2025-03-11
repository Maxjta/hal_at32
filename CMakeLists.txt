# Copyright (c) 2025 Maxjta
# SPDX-License-Identifier: Apache-2.0

if(CONFIG_HAS_AT32_HAL)

string(TOUPPER ${CONFIG_SOC} at32_soc_uc)

set(at32_soc_dir     ${ZEPHYR_HAL_AT32_MODULE_DIR}/${CONFIG_SOC_SERIES})
set(at32_soc_sys_dir   ${at32_soc_dir}/cmsis/cm4/)

set(at32_std_dir     ${at32_soc_dir}/drivers)
set(at32_std_src_dir ${at32_std_dir}/src)

zephyr_library_named(hal_at32)

zephyr_compile_definitions(${at32_soc_uc})

# Global includes to be used outside hal_gigadevice
zephyr_include_directories(${at32_soc_sys_dir}/device_support)
zephyr_include_directories(${at32_std_dir}/inc)
zephyr_include_directories(${ZEPHYR_HAL_AT32_MODULE_DIR}/include)
zephyr_include_directories(${ZEPHYR_HAL_AT32_MODULE_DIR}/common_include)

zephyr_library_sources(${at32_soc_sys_dir}/device_support/system_${CONFIG_SOC_SERIES}.c)

zephyr_library_sources_ifdef(CONFIG_USE_AT32_ADC      ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_adc.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_CAN      ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_can.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_CMP      ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_cmp.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_CRC      ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_crc.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_DAC      ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_dac.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_DBG      ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_debug.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_DCI      ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_dci.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_DMA      ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_dma.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_EMAC     ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_emac.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_XMC      ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_xmc.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_EXINT    ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_exint.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_FLASH    ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_flash.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_WDT      ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_wdt.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_GPIO     ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_gpio.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_I2C      ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_i2c.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_MISC     ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_misc.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_CRM      ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_crm.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_RTC      ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_rtc.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_ERTC     ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_ertc.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_SDIO     ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_sdio.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_SPI      ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_spi.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_SYSCFG   ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_scfg.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_TIMER    ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_tmr.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_USART    ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_usart.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_WWDT     ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_wwdt.c)
zephyr_library_sources_ifdef(CONFIG_USE_AT32_USB      ${at32_std_src_dir}/${CONFIG_SOC_SERIES}_usb.c)

#usb subsys
zephyr_library_sources_ifdef(CONFIG_USE_AT32_USB      ${ZEPHYR_HAL_AT32_MODULE_DIR}/common_source/at32_hal_udc.c)

endif()
