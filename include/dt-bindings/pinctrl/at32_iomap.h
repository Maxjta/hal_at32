/*
 * Copyright (c) 2021 Teslabs Engineering S.L.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef DT_BINDINGS_PINCTRL_AT32_IOMAP_H_
#define DT_BINDINGS_PINCTRL_AT32_IOMAP_H_

/**
 * Support AT32F403A/407/415/413 
 **/


/**
 * @name AT32 pin modes
 * @{
 */

/** Analog mode */
#define AT32_MODE_ANALOG 0U
/** GPIO input */
#define AT32_MODE_GPIO_IN 1U
/** Alternate function */
#define AT32_MODE_ALTERNATE 2U

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
/** Mode field mask. */
#define AT32_MODE_MSK 0x3U
/** Mode field position. */
#define AT32_MODE_POS 8U
/** Remap field mask. */
#define AT32_REMAP_MSK 0x3FFFU
/** Remap field position. */
#define AT32_REMAP_POS 10U

/** @} */

/** No remap available */
#define AT32_NORMP 0U

/**
 * Obtain port field from pinmux configuration.
 * 
 * @param pinmux Pinmux bit field value.
 */
#define AT32_PORT_GET(pinmux) \
	(((pinmux) >> AT32_PORT_POS) & AT32_PORT_MSK)

/**
 * Obtain pin field from pinmux configuration.
 * 
 * @param pinmux Pinmux bit field value.
 */
#define AT32_PIN_GET(pinmux) \
	(((pinmux) >> AT32_PIN_POS) & AT32_PIN_MSK)

/**
 * Obtain mode field from pinmux configuration.
 * 
 * @param pinmux Pinmux bit field value.
 */
#define AT32_MODE_GET(pinmux) \
	(((pinmux) >> AT32_MODE_POS) & AT32_MODE_MSK)

/**
 * Obtain pinmux field from pinmux configuration.
 * 
 * @param pinmux Pinmux bit field value.
 */
#define AT32_REMAP_GET(pinmux) \
	(((pinmux) >> AT32_REMAP_POS) & AT32_REMAP_MSK)

/**
 * @brief Remap configuration bit field.
 * 
 * Fields:
 *
 * - 0..3: port
 * - 4..7: pin
 * - 8..9: mode
 * - 10..19: remap
 * 
 * @param port Port ('A'..'P')
 * @param pin Pin (0..15)
 * @param mode Mode (ANALOG, GPIO_IN, ALTERNATE).
 * @param remap Remap value, see #AT32_REMAP.
 */
#define AT32_PIN_MUX(port, pin, mode, remap)			\
	(((((port) - 'A') & AT32_PORT_MSK) << AT32_PORT_POS) |		\
	 (((pin) & AT32_PIN_MSK) << AT32_PIN_POS) |			\
	 (((AT32_MODE_ ## mode) & AT32_MODE_MSK) << AT32_MODE_POS) |	\
	 (((AT32_ ## remap) & AT32_REMAP_MSK) << AT32_REMAP_POS))

/**
 * @name Remap bit field mask and positions.
 * @{
 */

/** Register field mask. 3 bit*/
#define AT32_REMAP_REG_MSK 0x7U
/** Register field position. */
#define AT32_REMAP_REG_POS 0U
/** Position field mask. 5 bit*/
#define AT32_REMAP_POS_MSK 0x1FU
/** Position field position. */
#define AT32_REMAP_POS_POS 3U
/** Mask field mask. */
#define AT32_REMAP_MSK_MSK 0x7U
/** Mask field position. */
#define AT32_REMAP_MSK_POS 8U
/** Value field mask. */
#define AT32_REMAP_VAL_MSK 0xFU
/** Value field position. */
#define AT32_REMAP_VAL_POS 11U

/** @} */

/**
 * Obtain register field from remap configuration.
 * 
 * @param remap Remap bit field value.
 */
#define AT32_REMAP_REG_GET(remap) \
	(((remap) >> AT32_REMAP_REG_POS) & AT32_REMAP_REG_MSK)

/**
 * Obtain position field from remap configuration.
 * 
 * @param remap Remap bit field value.
 */
#define AT32_REMAP_POS_GET(remap) \
	(((remap) >> AT32_REMAP_POS_POS) & AT32_REMAP_POS_MSK)

/**
 * Obtain mask field from remap configuration.
 * 
 * @param remap Remap bit field value.
 */
#define AT32_REMAP_MSK_GET(remap) \
	(((remap) >> AT32_REMAP_MSK_POS) & AT32_REMAP_MSK_MSK)

/**
 * Obtain value field from remap configuration.
 * 
 * @param remap Remap bit field value.
 */
#define AT32_REMAP_VAL_GET(remap) \
	(((remap) >> AT32_REMAP_VAL_POS) & AT32_REMAP_VAL_MSK)

/**
 * @brief Remap configuration bit field.
 * 
 * - 0: 7  reg (0 or 7).
 * - 8..11: bit_addr (0..31).
 * - 12..15: bit_num (0x1, 0x3).
 * - 16..19: val (0..3).
 * 
 * @param reg AFIO_PCFx register (0, 1).
 * @param pos pos within remap.
 * @param msk Mask for the field.
 * @param val Remap value (0, 1, 2 or 3, 4).
 */
#define AT32_REMAP(reg, pos, msk, val)					\
	((((reg) & AT32_REMAP_REG_MSK) << AT32_REMAP_REG_POS) |		\
	 (((pos) & AT32_REMAP_POS_MSK) << AT32_REMAP_POS_POS) |		\
	 (((msk) & AT32_REMAP_MSK_MSK) << AT32_REMAP_MSK_POS) |		\
	 (((val) & AT32_REMAP_VAL_MSK) << AT32_REMAP_VAL_POS))

#endif /* DT_BINDINGS_PINCTRL_GD32_AFIO_H_ */
