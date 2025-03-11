/*
 * Copyright (c) 2025 Maxjta 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef DT_BINDINGS_PINCTRL_AT32_IOMUX_H_
#define DT_BINDINGS_PINCTRL_AT32_IOMUX_H_

/**
 * @name AT32 PIN MUX 0~16
 * @{
 */
#define AT32_MUX_0 0U
#define AT32_MUX_1 1U
#define AT32_MUX_2 2U
#define AT32_MUX_3 3U
#define AT32_MUX_4 4U
#define AT32_MUX_5 5U
#define AT32_MUX_6 6U
#define AT32_MUX_7 7U
#define AT32_MUX_8 8U
#define AT32_MUX_9 9U
#define AT32_MUX_10 10U
#define AT32_MUX_11 11U
#define AT32_MUX_12 12U
#define AT32_MUX_13 13U
#define AT32_MUX_14 14U
#define AT32_MUX_15 15U
#define AT32_ANALOG 16U

/** @} */

/**
 * @name AT32 pinmux bit field mask and positions.
 * @{
 */

/** Port field mask. */
#define AT32_PORT_MSK 0xFU
/** Port field position. */
#define AT32_PORT_POS 0U
/** Pin field mask. */
#define AT32_PIN_MSK 0xFU
/** Pin field position. */
#define AT32_PIN_POS 4U
/** MUX field mask. */
#define AT32_MUX_MSK 0x1FU
/** MUX field position. */
#define AT32_MUX_POS 8U

/** @} */

/**
 * Obtain port field from pinmux configuration.
 *
 * @param pinmux Pinmux bit field value.
 */
#define AT32_PORT_GET(pinmux) (((pinmux) >> AT32_PORT_POS) & AT32_PORT_MSK)

/**
 * Obtain pin field from pinmux configuration.
 *
 * @param pinmux Pinmux bit field value.
 */
#define AT32_PIN_GET(pinmux) (((pinmux) >> AT32_PIN_POS) & AT32_PIN_MSK)

/**
 * Obtain MUX field from pinmux configuration.
 *
 * @param pinmux Pinmux bit field value.
 */
#define AT32_MUX_GET(pinmux) (((pinmux) >> AT32_MUX_POS) & AT32_MUX_MSK)

/**
 * @brief iomux configuration bit field.
 *
 * Fields:
 *
 * - bit 0..3: gpio port number(GPIOA, GPIOB...)
 * - bit 4..7: gpio pins number(pin0 ~ pin16)
 * - 8..12: mux gpio pins iomux number(mux0~mux15 or analog)
 *
 * @param port Port ('A'..'P')
 * @param pin Pin (0..15)
 * @param mux multiplexed function (ANALOG, MUX_x, x=0..15).
 */
#define AT32_PIN_MUX(port, pin, mux)                                          \
  (((((port) - 'A') & AT32_PORT_MSK) << AT32_PORT_POS) |                       \
   (((pin)&AT32_PIN_MSK) << AT32_PIN_POS) |                                    \
   (((AT32_##mux) & AT32_MUX_MSK) << AT32_MUX_POS))

#endif /* DT_BINDINGS_PINCTRL_AT32_MUX_H_ */
