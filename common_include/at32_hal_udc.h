/*
 * Copyright (c) 2025 Maxjta 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __HAL_USB_H
#define __HAL_USB_H

#include "at32_usb.h"
//#include "at32f402_405_usb.h"

#define USB_HIGH_SPEED    0
#define USB_FULL_SPEED    1
#define USB_LOW_SPEED     2

typedef struct _hal_udc_config
{
  uint8_t dma_en;
  uint8_t sof_en;
  uint8_t speed;
}hal_udc_config;

typedef struct _hal_udc_handle
{
  usb_reg_type *usb_reg;
  hal_udc_config udc_config;
  
  usb_ept_info                           ept_in[USB_EPT_MAX_NUM];    /*!< usb in endpoint infomation struct */
  usb_ept_info                           ept_out[USB_EPT_MAX_NUM];   /*!< usb out endpoint infomation struct */

  uint32_t setup_buffer[12];                          
  uint32_t usb_address;
  
}hal_udc_handle;




int hal_udc_init(hal_udc_handle *pudc);
int hal_udc_deinit(hal_udc_handle *pudc);
int hal_udc_irq(hal_udc_handle *pudc);
int hal_udc_set_address(hal_udc_handle *pudc, const uint8_t addr);
int hal_udc_start_read(hal_udc_handle *pudc, uint8_t ep, uint8_t *data, uint32_t length);
int hal_udc_get_read_count(hal_udc_handle *pudc, uint8_t ep);
int hal_udc_ep_write(hal_udc_handle *pudc, const uint8_t ep, uint8_t *data, uint32_t length);
int hal_udc_ep_config(hal_udc_handle *pudc, uint8_t ep, uint8_t is_db, uint32_t offset);
int hal_udc_ep_set_stall(hal_udc_handle *pudc, const uint8_t ep);
int hal_udc_ep_clear_stall(hal_udc_handle *pudc, const uint8_t ep);
int hal_udc_ep_open(hal_udc_handle *pudc, const uint8_t ep, uint32_t maxpacket, uint8_t type);
int hal_udc_ep_close(hal_udc_handle *pudc, const uint8_t ep);
int hal_udc_wakeup_enable(hal_udc_handle *pudc);
int hal_udc_wakeup_disable(hal_udc_handle *pudc);
int hal_udc_connect(hal_udc_handle *pudc);
int hal_udc_disconnect(hal_udc_handle *pudc);
int hal_udc_start(hal_udc_handle *pudc);
int hal_udc_stop(hal_udc_handle *pudc);


void hal_udc_data_in_callback(hal_udc_handle *pudc, const uint8_t ep);
void hal_udc_data_out_callback(hal_udc_handle *pudc, const uint8_t ep);
void hal_udc_data_setup_callback(hal_udc_handle *pudc);
void hal_udc_sof_callback(hal_udc_handle *pudc);
void hal_udc_reset_callback(hal_udc_handle *pudc);
void hal_udc_isoincom_callback(hal_udc_handle *pudc);
void hal_udc_isooutcom_callback(hal_udc_handle *pudc);
void hal_udc_resume_callback(hal_udc_handle *pudc);
void hal_udc_suspend_callback(hal_udc_handle *pudc);
void hal_udc_disconnect_callback(hal_udc_handle *pudc);
#endif
