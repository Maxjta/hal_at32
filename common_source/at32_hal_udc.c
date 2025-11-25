/*
 * Copyright (c) 2025 Maxjta 
 * SPDX-License-Identifier: Apache-2.0
 */
#include "at32_hal_udc.h"
static void hal_usbd_ept_write(hal_udc_handle *pudc, const uint8_t ep, uint8_t *data, uint32_t length);
static void hal_usbd_ept_read(hal_udc_handle *udc, uint8_t ept_addr, uint8_t *buffer, uint16_t len);
static void hal_usbd_ept_config(hal_udc_handle *udc, uint8_t ep, uint8_t is_db, uint32_t offset);
static void hal_usbd_ep_set_stall(hal_udc_handle *udc, const uint8_t ep);
static void hal_usbd_ep_clear_stall(hal_udc_handle *udc, const uint8_t ep);
static void hal_usbd_ept_open(hal_udc_handle *pudc, const uint8_t ep, uint8_t type, uint32_t maxpacket);
static void hal_usbd_ept_close(hal_udc_handle *pudc, const uint8_t ep);
static void hal_usbd_wakeup_enable(hal_udc_handle *pudc);
static void hal_usbd_wakeup_disable(hal_udc_handle *pudc);
static void hal_usbd_deinit(hal_udc_handle *pudc);
static void hal_usbd_init(hal_udc_handle *pudc);
static void hal_usbd_ept_default_init(hal_udc_handle *pudc);
static void hal_usbd_irq(hal_udc_handle *pudc);
static int  udc_dp_flush(hal_udc_handle *pudc, const uint8_t ep);

#ifdef USB
static void usbd_eptn_handler(hal_udc_handle *pudc, usb_ept_number_type ept_num);
static void usbd_ept_loop_handler(hal_udc_handle *pudc);
static void usbd_reset_handler(hal_udc_handle *pudc);
#endif

static void hal_udc_delay(uint32_t delay);
static void hal_udc_delay(uint32_t delay)
{
  /* user can define self delay function */
//  k_msleep(delay);
}

int hal_udc_init(hal_udc_handle *pudc)
{
  hal_usbd_init(pudc);
  return 0;
}

int hal_udc_deinit(hal_udc_handle *pudc)
{
  hal_usbd_deinit(pudc);
  return 0;
}

int hal_udc_irq(hal_udc_handle *pudc)
{
  hal_usbd_irq(pudc);
  return 0;
}

int hal_udc_set_address(hal_udc_handle *pudc, const uint8_t addr)
{
#ifdef USB
  pudc->usb_address = addr;
#else
  usb_set_address(pudc->usb_reg, addr);
#endif
  return 0;
}

int hal_udc_start_read(hal_udc_handle *pudc, uint8_t ep, uint8_t *data, uint32_t length)
{
  hal_usbd_ept_read(pudc, ep, data, length);
  return 0;
}

int hal_udc_get_read_count(hal_udc_handle *pudc, uint8_t ep)
{
  usb_ept_info *ept = &pudc->ept_out[ep & 0x7F];
  return ept->trans_len;
}

int hal_udc_ep_write(hal_udc_handle *pudc, const uint8_t ep, uint8_t *data, uint32_t length)
{
  hal_usbd_ept_write(pudc, ep, data, length); 
  return 0;
}

int hal_udc_ep_config(hal_udc_handle *pudc, uint8_t ep, uint8_t is_db, uint32_t offset)
{
  hal_usbd_ept_config(pudc, ep, is_db, offset);
  return 0;
}

int hal_udc_ep_set_stall(hal_udc_handle *pudc, const uint8_t ep)
{
  hal_usbd_ep_set_stall(pudc, ep);
  return 0;
}

int hal_udc_ep_clear_stall(hal_udc_handle *pudc, const uint8_t ep)
{
  hal_usbd_ep_clear_stall(pudc, ep);
  return 0;
}

int hal_udc_ep_open(hal_udc_handle *pudc, const uint8_t ep, uint32_t maxpacket, uint8_t type)
{
  hal_usbd_ept_open(pudc, ep, type, maxpacket);
  return 0;
}

int hal_udc_ep_close(hal_udc_handle *pudc, const uint8_t ep)
{
  hal_usbd_ept_close(pudc, ep);
  return 0;
}


int hal_udc_wakeup_enable(hal_udc_handle *pudc)
{
  hal_usbd_wakeup_enable(pudc);
  return 0;
}

int hal_udc_wakeup_disable(hal_udc_handle *pudc)
{
  hal_usbd_wakeup_disable(pudc);
  return 0;
}

int hal_udc_connect(hal_udc_handle *pudc)
{
  usb_connect(pudc->usb_reg);
  return 0;
}

int hal_udc_disconnect(hal_udc_handle *pudc)
{
  usb_disconnect(pudc->usb_reg);
  return 0;
}

int hal_udc_start(hal_udc_handle *pudc)
{
  hal_udc_connect(pudc);
	return 0;
}

int hal_udc_stop(hal_udc_handle *pudc)
{
  hal_udc_disconnect(pudc);
	return 0;
}

int hal_udc_dp_flush(hal_udc_handle *pudc, const uint8_t ep)
{
  return udc_dp_flush(pudc, ep);
}

__WEAK void hal_udc_data_in_callback(hal_udc_handle *pudc, const uint8_t ep)
{
  (void)pudc;
}

__WEAK void hal_udc_data_out_callback(hal_udc_handle *pudc, const uint8_t ep)
{
  (void)pudc;
}

__WEAK void hal_udc_data_setup_callback(hal_udc_handle *pudc)
{
  (void)pudc;
}

__WEAK void hal_udc_sof_callback(hal_udc_handle *pudc)
{
  (void)pudc;
}

__WEAK void hal_udc_reset_callback(hal_udc_handle *pudc)
{
  (void)pudc;
}

__WEAK void hal_udc_isoincom_callback(hal_udc_handle *pudc)
{
  (void)pudc;
}

__WEAK void hal_udc_isooutcom_callback(hal_udc_handle *pudc)
{
  (void)pudc;
}

__WEAK void hal_udc_resume_callback(hal_udc_handle *pudc)
{
  (void)pudc;
}

__WEAK void hal_udc_suspend_callback(hal_udc_handle *pudc)
{
  (void)pudc;
}

__WEAK void hal_udc_disconnect_callback(hal_udc_handle *pudc)
{
  (void)pudc;
}

#ifdef USB

static void hal_usbd_irq(hal_udc_handle *pudc)
{
  usbd_type *usbx = pudc->usb_reg;
  uint32_t sts_val = usbx->intsts;
  uint32_t sts_ien = usbx->ctrl;

  if(sts_val & USB_TC_FLAG)
  {
    /* endpoint tc interrupt handler */
    usbd_ept_loop_handler(pudc);
  }

  if(sts_val & USB_RST_FLAG)
  {
    /* clear reset flag */
    usb_flag_clear(usbx, USB_RST_FLAG);

    /* reset interrupt handler */
    usbd_reset_handler(pudc);
  }

  if((sts_val & USB_SOF_FLAG) &&
    (sts_ien & USB_SOF_INT))
  {
    /* clear sof flag */
    usb_flag_clear(usbx, USB_SOF_FLAG);

    /* sof interrupt handler */
    hal_udc_sof_callback(pudc);
  }

  if((sts_val & USB_LSOF_FLAG) &&
    (sts_ien & USB_LSOF_INT))
  {
    /* clear lsof flag */
    usb_flag_clear(usbx, USB_LSOF_FLAG);
  }

  if((sts_val & USB_SP_FLAG) &&
    (sts_ien & USB_SP_INT))
  {
    /* clear suspend flag */
    usb_flag_clear(usbx, USB_SP_FLAG);

    usb_enter_suspend(pudc->usb_reg);

    /* usb suspend interrupt handler */
    hal_udc_suspend_callback(pudc);
  }

  if((sts_val & USB_WK_FLAG) &&
    (sts_ien & USB_WK_INT))
  {
    usb_exit_suspend(pudc->usb_reg);

    /* usb wakeup interrupt handler */
    hal_udc_resume_callback(pudc);

    /* clear wakeup flag */
    usb_flag_clear(usbx, USB_WK_FLAG);
  }
}

static void hal_usbd_ept_default_init(hal_udc_handle *pudc)
{
  uint8_t i_index = 0;
  /* init in endpoint info structure */
  for(i_index = 0; i_index < USB_EPT_MAX_NUM; i_index ++)
  {
    pudc->ept_in[i_index].eptn        = i_index;
    pudc->ept_in[i_index].ept_address = i_index;
    pudc->ept_in[i_index].inout         = DATA_TRANS_IN;
    pudc->ept_in[i_index].maxpacket   = 0;
    pudc->ept_in[i_index].trans_buf   = 0;
    pudc->ept_in[i_index].total_len   = 0;
    pudc->ept_in[i_index].tx_addr     = 0;
    pudc->ept_in[i_index].rx_addr     = 0;
  }

  /* init out endpoint info structure */
  for(i_index = 0; i_index < USB_EPT_MAX_NUM; i_index ++)
  {
    pudc->ept_out[i_index].eptn        = i_index;
    pudc->ept_out[i_index].ept_address = i_index;
    pudc->ept_out[i_index].inout         = DATA_TRANS_OUT;
    pudc->ept_out[i_index].maxpacket   = 0;
    pudc->ept_out[i_index].trans_buf   = 0;
    pudc->ept_out[i_index].total_len   = 0;
    pudc->ept_out[i_index].rx_addr     = 0;
    pudc->ept_out[i_index].tx_addr     = 0;
  }
  return;
}

static void hal_usbd_init(hal_udc_handle *pudc)
{
  usb_reg_type *usbx = pudc->usb_reg;

  hal_usbd_ept_default_init(pudc);

  hal_udc_delay(0);

  pudc->usb_address = 0;

  /* clear usb core reset */
  usbx->ctrl_bit.csrst = 0;

  /* clear usb interrupt status */
  usbx->intsts = 0;

  /* set usb packet buffer descirption table address */
  usbx->buftbl = USB_BUFFER_TABLE_ADDRESS;

  /* enable usb core and set device address to 0 */
  usbx->devaddr = 0x80;

  if(pudc->udc_config.sof_en)
  {
    usb_interrupt_enable(usbx, USB_SOF_INT, TRUE);
  }
  usb_interrupt_enable(usbx, USB_RST_INT | USB_SP_INT | USB_WK_INT | USB_TC_INT, TRUE);
}

static void hal_usbd_ept_open(hal_udc_handle *pudc, const uint8_t ep, uint8_t type, uint32_t maxpacket)
{
  usb_reg_type *usbx = pudc->usb_reg;
  usb_ept_info *ept_info;

  if((ep & 0x80) == 0)
  {
    /* out endpoint info */
    ept_info = &pudc->ept_out[ep & 0x7F];
    ept_info->inout = DATA_TRANS_OUT;
  }
  else
  {
    /* in endpoint info */
    ept_info = &pudc->ept_in[ep & 0x7F];
    ept_info->inout = DATA_TRANS_IN;
  }

  /* set endpoint maxpacket and type */
  ept_info->maxpacket = maxpacket + 1;
  ept_info->trans_type = type;

  /* open endpoint */
  usb_ept_open(usbx, ept_info);
}

static void hal_usbd_ep_clear_stall(hal_udc_handle *pudc, const uint8_t ep)
{
  usb_ept_info *ept_info;
  if(ep & 0x80)
  {
    /* in endpoint */
    ept_info = &pudc->ept_in[ep & 0x7F];
    USB_CLEAR_TXDTS(ept_info->eptn);
    if(USB->ept_bit[ept_info->eptn].txsts == USB_TX_STALL)
      USB_SET_TXSTS(ept_info->eptn, USB_TX_NAK);
  }
  else
  {
    /* out endpoint */
    ept_info = &pudc->ept_out[ep & 0x7F];
    USB_CLEAR_RXDTS(ept_info->eptn);
    if(USB->ept_bit[ept_info->eptn].rxsts == USB_RX_STALL)
      USB_SET_RXSTS(ept_info->eptn, USB_RX_VALID);
  }
  ept_info->stall = 0;
}

static void hal_usbd_ep_set_stall(hal_udc_handle *pudc, const uint8_t ep)
{
  usb_ept_info *ept_info;

  if(ep & 0x80)
  {
    /* in endpoint */
    ept_info = &pudc->ept_in[ep & 0x7F];
    USB_SET_TXSTS(ept_info->eptn, USB_TX_STALL);
  }
  else
  {
    /* out endpoint */
    ept_info = &pudc->ept_out[ep & 0x7F];
    USB_SET_RXSTS(ept_info->eptn, USB_RX_STALL);
  }
  ept_info->stall = 1;
}


static void hal_usbd_ept_config(hal_udc_handle *pudc, uint8_t ep, uint8_t is_db, uint32_t offset)
{
  usb_ept_info *ept_info;

  if((ep & 0x80) == 0)
  {
    /* out endpoint info */
    ept_info = &pudc->ept_out[ep & 0x7F];
  }
  else
  {
    /* in endpoint info */
    ept_info = &pudc->ept_in[ep & 0x7F];
  }

  ept_info->is_double_buffer = is_db;

  if(ept_info->is_double_buffer == 0)
  {
    ept_info->is_double_buffer = 0;
    if( ept_info->inout == DATA_TRANS_IN )
    {
      ept_info->tx_addr = offset;
    }
    else
    {
      ept_info->rx_addr = offset;
    }
  }
  else
  {
    ept_info->is_double_buffer = 1;
    /* double buffer malloc */
    ept_info->tx_addr = offset & 0xFFFF;
    ept_info->rx_addr = (offset >> 16) & 0xFFFF;
  }
}

static void hal_usbd_ept_write(hal_udc_handle *pudc, const uint8_t ep, uint8_t *data, uint32_t length)
{
  /* get endpoint info struct and register */
  usb_ept_info *ept_info = &pudc->ept_in[ep & 0x7F];
  uint16_t trs_len = 0;
  usbd_type *usbx = pudc->usb_reg;

  /* set send data buffer and length */
  ept_info->trans_buf = data;
  ept_info->total_len = length;
  ept_info->trans_len = 0;

  if(ept_info->total_len > ept_info->maxpacket)
  {
    trs_len = ept_info->maxpacket;
    ept_info->total_len -= trs_len;
  }
  else
  {
    trs_len = length;
    ept_info->total_len = 0;
  }

  ept_info->last_len = trs_len;

  if(ept_info->is_double_buffer == 0)
  {
    /* write data to endpoint buffer */
    usb_write_packet(ept_info->trans_buf, ept_info->tx_addr, trs_len);

    /* set send data length */
    USB_SET_TXLEN((ep & 0x7F), trs_len);
  }
  else
  {
    if(usbx->ept_bit[ep & 0x7F].txdts)
    {
      USB_SET_EPT_DOUBLE_BUF1_LEN((ep & 0x7F), trs_len, DATA_TRANS_IN);
      usb_write_packet(ept_info->trans_buf, ept_info->rx_addr, trs_len);
    }
    else
    {
      USB_SET_EPT_DOUBLE_BUF0_LEN((ep & 0x7F), trs_len, DATA_TRANS_IN);
      usb_write_packet(ept_info->trans_buf, ept_info->tx_addr, trs_len);
    }
    USB_FREE_DB_USER_BUFFER((ep & 0x7F), DATA_TRANS_IN);
  }

  /* set tx status valid */
  USB_SET_TXSTS((ep & 0x7F), USB_TX_VALID);
}

static void hal_usbd_ept_close(hal_udc_handle *pudc, const uint8_t ep)
{
  usb_ept_info *ept_info;
  if(ep & 0x80)
  {
    /* in endpoint */
    ept_info = &pudc->ept_in[ep & 0x7F];
  }
  else
  {
    /* out endpoint */
    ept_info = &pudc->ept_out[ep & 0x7F];
  }

  /* close endpoint */
  usb_ept_close(pudc->usb_reg, ept_info);
}

static void hal_usbd_ept_read(hal_udc_handle *pudc, uint8_t ept_addr, uint8_t *buffer, uint16_t len)
{
  /* get endpoint info struct and register */
  usb_ept_info *ept_info = &pudc->ept_out[ept_addr & 0x7F];
  uint32_t trs_len = 0;

   /* set receive data buffer and length */
  ept_info->trans_buf = buffer;
  ept_info->total_len = len;
  ept_info->trans_len = 0;

  if(ept_info->total_len > ept_info->maxpacket)
  {
    trs_len = ept_info->maxpacket;
    ept_info->total_len -= trs_len;
  }
  else
  {
    trs_len = len;
    ept_info->total_len = 0;
  }

  /* set rx status valid */
  USB_SET_RXSTS((ept_addr & 0x7F), USB_RX_VALID);
}


static void hal_usbd_wakeup_enable(hal_udc_handle *pudc)
{
  usb_exit_suspend(pudc->usb_reg);
  /* set remote wakeup */
  usb_remote_wkup_set(pudc->usb_reg);
}

static void hal_usbd_wakeup_disable(hal_udc_handle *pudc)
{
  /* clear remote wakup */
  usb_remote_wkup_clear(pudc->usb_reg);
}


static void hal_usbd_deinit(hal_udc_handle *pudc)
{
  usbd_type *usbx = pudc->usb_reg;

  /* clear usb interrupt status */
  usbx->intsts = 0;

  /* set usb packet buffer descirption table address */
  usbx->buftbl = USB_BUFFER_TABLE_ADDRESS;

  /* enable usb core and set device address to 0 */
  usbx->devaddr = 0x80;

//  void(pudc);
}

static void usbd_eptn_handler(hal_udc_handle *pudc, usb_ept_number_type ept_num)
{
  usbd_type *usbx = pudc->usb_reg;
  usb_ept_info *ept_info;
  uint32_t ept_val = usbx->ept[ept_num];
  uint16_t length;

  /* in interrupt request  */
  if(ept_val & USB_TXTC)
  {
    /* get endpoint register and in transfer info struct */
    ept_info = &pudc->ept_in[ept_num];

     /* clear endpoint tc flag */
    USB_CLEAR_TXTC(ept_num);

    /* get endpoint tx length */
    ept_info->trans_len = USB_GET_TX_LEN(ept_num);

    /* offset the trans buffer */
    ept_info->trans_buf += ept_info->trans_len;

    if(ept_info->total_len == 0 || ept_num == USB_EPT0)
    {
      /* in transfer complete */
      hal_udc_data_in_callback(pudc, ept_num);
    }
    else
    {
      /* endpoint continue send data */
      hal_usbd_ept_write(pudc, ept_num, ept_info->trans_buf, ept_info->total_len);
    }

    if(pudc->usb_address != 0)
    {
      usb_set_address(pudc->usb_reg, pudc->usb_address);
      pudc->usb_address = 0;
    }
  }
  else
  {
    /* setup and out interrupt request */

    /* get endpoint register and out transfer info struct */
    ept_info = &pudc->ept_out[ept_num];

    if((ept_val & USB_SETUPTC) != 0)
    {
      /* endpoint setup interrupt request */

      /* get endpoint received data length */
      ept_info->trans_len = USB_GET_RX_LEN(ept_num);

      /* read endpoint received data */
      usb_read_packet((uint8_t *)pudc->setup_buffer, ept_info->rx_addr, ept_info->trans_len);

      /* clear endpoint rx tc flag */
      USB_CLEAR_RXTC(USB_EPT0);

      /* endpoint setup complete handler */
      hal_udc_data_setup_callback(pudc);
    }
    else if(ept_val & USB_RXTC )
    {
      /* endpoint out interrupt request */
      USB_CLEAR_RXTC(ept_num);

      if(ept_info->is_double_buffer == 0)
      {
        /* get endpoint received data length */
        length = USB_GET_RX_LEN(ept_num);

        /* read endpoint received data */
        usb_read_packet(ept_info->trans_buf, ept_info->rx_addr, length);
      }
      else
      {
        if( ept_val & USB_RXDTS)
        {
          length = USB_DBUF0_GET_LEN(ept_num);
          usb_read_packet(ept_info->trans_buf, ept_info->tx_addr, length);
        }
        else
        {
          length = USB_DBUF1_GET_LEN(ept_num);
          usb_read_packet(ept_info->trans_buf, ept_info->rx_addr, length);
        }
        USB_FREE_DB_USER_BUFFER(ept_num, DATA_TRANS_OUT);
      }

      /* set received data length */
      ept_info->trans_len += length;
      ept_info->trans_buf += length;

      if(ept_info->total_len == 0 || length < ept_info->maxpacket || ept_num == USB_EPT0)
      {
        /* out transfer complete */
        hal_udc_data_out_callback(pudc, ept_num);
      }
      else
      {
        /* endpoint continue receive data  */
        hal_usbd_ept_read(pudc, ept_num, ept_info->trans_buf, ept_info->total_len);
      }
    }
  }
}

static void usbd_ept_loop_handler(hal_udc_handle *pudc)
{
  usbd_type *usbx = pudc->usb_reg;
  usb_ept_number_type ept_num = USB_EPT0;
  uint32_t sts_val;

  while((sts_val = usbx->intsts) & USB_TC_FLAG)
  {
    /* get the interrupt endpoint number */
    ept_num = (usb_ept_number_type)(sts_val & USB_EPT_NUM_FLAG);

    usbd_eptn_handler(pudc, ept_num);
  }
}

static void usbd_reset_handler(hal_udc_handle *pudc)
{
  /* free usb buffer */
  usb_buffer_free();

  hal_udc_reset_callback(pudc);

  /* set device address to 0 */
  usb_set_address(pudc->usb_reg, 0);

}

static int udc_dp_flush(hal_udc_handle *pudc, const uint8_t ep)
{
  return 0;
}

#endif

#if defined OTG1_GLOBAL || defined OTG2_GLOBAL

static void hal_usbd_ept_close(hal_udc_handle *pudc, const uint8_t ep)
{
  usb_ept_info *ept_info;
  if(ep & 0x80)
  {
    /* in endpoint */
    ept_info = &pudc->ept_in[ep & 0x7F];
  }
  else
  {
    /* out endpoint */
    ept_info = &pudc->ept_out[ep & 0x7F];
  }

  /* close endpoint */
  usb_ept_close(pudc->usb_reg, ept_info);
}

static void hal_usbd_ept_open(hal_udc_handle *pudc, const uint8_t ep, uint8_t type, uint32_t maxpacket)
{
  usb_reg_type *usbx = pudc->usb_reg;
  usb_ept_info *ept_info;

  if((ep & 0x80) == 0)
  {
    /* out endpoint info */
    ept_info = &pudc->ept_out[ep & 0x7F];
    ept_info->inout = EPT_DIR_OUT;
  }
  else
  {
    /* in endpoint info */
    ept_info = &pudc->ept_in[ep & 0x7F];
    ept_info->inout = EPT_DIR_IN;
  }

  /* set endpoint maxpacket and type */
  ept_info->maxpacket = maxpacket;
  ept_info->trans_type = type;

  /* open endpoint */
  usb_ept_open(usbx, ept_info);
}

static void hal_usbd_ep_clear_stall(hal_udc_handle *pudc, const uint8_t ep)
{
  usb_ept_info *ept_info;
  usb_reg_type *usbx = pudc->usb_reg;

  if(ep & 0x80)
  {
    /* in endpoint */
    ept_info = &pudc->ept_in[ep & 0x7F];
  }
  else
  {
    /* out endpoint */
    ept_info = &pudc->ept_out[ep & 0x7F];
  }
  usb_ept_clear_stall(usbx, ept_info);
  ept_info->stall = 0;
}

static void hal_usbd_ep_set_stall(hal_udc_handle *pudc, const uint8_t ep)
{
  usb_ept_info *ept_info;
  usb_reg_type *usbx = pudc->usb_reg;

  if(ep & 0x80)
  {
    /* in endpoint */
    ept_info = &pudc->ept_in[ep & 0x7F];
  }
  else
  {
    /* out endpoint */
    ept_info = &pudc->ept_out[ep & 0x7F];
  }
  usb_ept_stall(usbx, ept_info);
  ept_info->stall = 1;
}

static void hal_usbd_ept_config(hal_udc_handle *pudc, uint8_t ep, uint8_t is_db, uint32_t offset)
{
  (void)pudc;
  (void)ep;
  (void)is_db;
  (void)offset;
}


static void hal_usbd_ept_write(hal_udc_handle *pudc, const uint8_t ep, uint8_t *data, uint32_t length)
{
  usb_reg_type *usbx = pudc->usb_reg;
  usb_ept_info *ept_info = &pudc->ept_in[ep & 0x7F];
  otg_eptin_type *ept_in = USB_INEPT(usbx, ept_info->eptn);
  otg_device_type *dev = OTG_DEVICE(usbx);
  uint32_t timeout = 0xFFFF;
  uint8_t endp = ep & 0x7F;
  uint32_t pktcnt;
  
  /* check endpoint fifo */
  if(USB_INEPT(usbx, endp)->diepctl_bit.eptena == SET && 
    USB_INEPT(usbx, endp)->diepctl_bit.usbacept == SET)
  {
    USB_INEPT(usbx, endp)->diepctl_bit.snak = TRUE;
    USB_INEPT(usbx, endp)->diepctl_bit.eptdis = TRUE;
    USB_INEPT(usbx, endp)->diepctl_bit.snak = TRUE;
    while(USB_INEPT(usbx, endp)->diepctl_bit.eptdis && timeout --);
    usb_flush_tx_fifo(usbx, endp);
  }
  
  /* set send data buffer and length */
  ept_info->trans_buf = data;
  ept_info->total_len = length;
  ept_info->trans_len = 0;

  /* transfer data len is zero */
  if(ept_info->total_len == 0)
  {
    ept_in->dieptsiz_bit.pktcnt = 1;
    ept_in->dieptsiz_bit.xfersize = 0;
  }
  else
  {
    if((ep & 0x7F) == 0) // endpoint 0
    {
      /* endpoint 0 */
      if(ept_info->total_len > ept_info->maxpacket)
      {
        ept_info->total_len = ept_info->maxpacket;
      }

      /* set transfer size  */
      ept_in->dieptsiz_bit.xfersize = ept_info->total_len;

      /* set packet count */
      ept_in->dieptsiz_bit.pktcnt = 1;

      ept_info->last_len = ept_info->total_len;
    }
    else
    {
      /* other endpoint */

      /* packet count */
      pktcnt = (ept_info->total_len + ept_info->maxpacket - 1) / ept_info->maxpacket;

      /* set transfer size  */
      ept_in->dieptsiz_bit.xfersize = ept_info->total_len;

      /* set packet count */
      ept_in->dieptsiz_bit.pktcnt = pktcnt;

      if(ept_info->trans_type == EPT_ISO_TYPE)
      {
        ept_in->dieptsiz_bit.mc = 1;
      }
    }
  }
#ifdef OTG_USE_DMA
  if(pudc->udc_config.dma_en == TRUE)
  {
    if(ept_info->trans_buf != 0)
    {
      ept_in->diepdma = (uint32_t)ept_info->trans_buf;
    }
      /* clear endpoint nak */
    ept_in->diepctl_bit.cnak = TRUE;
  
    /* endpoint enable */
    ept_in->diepctl_bit.eptena = TRUE;
  }
  
  else
#endif
  {
    if(ept_info->trans_type == EPT_ISO_TYPE)
    {
      if((dev->dsts_bit.soffn & 0x1) == 0)
      {
        ept_in->diepctl_bit.setd1pid = TRUE;
      }
      else
      {
        ept_in->diepctl_bit.setd0pid = TRUE;
      }
    }

    /* clear endpoint nak */
    ept_in->diepctl_bit.cnak = TRUE;

    /* endpoint enable */
    ept_in->diepctl_bit.eptena = TRUE;
    
    if(ept_info->trans_type != EPT_ISO_TYPE)
    {
      if(ept_info->total_len > 0)
      {
        /* set in endpoint tx fifo empty interrupt mask */
        dev->diepempmsk |= 1 << ept_info->eptn;
      }
    }
    else
    {
      /* write data to fifo */
      usb_write_packet(usbx, ept_info->trans_buf, ept_info->eptn, ept_info->total_len);
    }
  }
}

static void hal_usbd_ept_read(hal_udc_handle *pudc, uint8_t ept_addr, uint8_t *buffer, uint16_t len)
{
  /* get endpoint info struct and register */
  usb_reg_type *usbx = pudc->usb_reg;
  usb_ept_info *ept_info = &pudc->ept_out[ept_addr & 0x7F];
  otg_eptout_type *ept_out = USB_OUTEPT(usbx, ept_info->eptn);
  otg_device_type *dev = OTG_DEVICE(usbx);
  uint32_t pktcnt;

   /* set receive data buffer and length */
  ept_info->trans_buf = buffer;
  ept_info->total_len = len;
  ept_info->trans_len = 0;

  if((ept_addr & 0x7F) == 0 && len > 0)
  {
    /* endpoint 0 */
    ept_info->total_len = ept_info->maxpacket;
  }

  if(ept_info->total_len == 0 || ((ept_addr & 0x7F) == 0))
  {
    /* set transfer size  */
    ept_out->doeptsiz_bit.xfersize = ept_info->maxpacket;

    /* set packet count */
    ept_out->doeptsiz_bit.pktcnt = 1;
  }
  else
  {
    pktcnt = (ept_info->total_len + ept_info->maxpacket - 1) / ept_info->maxpacket;

    /* set transfer size  */
    ept_out->doeptsiz_bit.xfersize = ept_info->maxpacket * pktcnt;

    /* set packet count */
    ept_out->doeptsiz_bit.pktcnt = pktcnt;
  }
#ifdef OTG_USE_DMA
  if(pudc->udc_config.dma_en == TRUE && buffer != 0)
  {
    ept_out->doepdma = (uint32_t)(ept_info->trans_buf);
  }
#endif
  if(ept_info->trans_type == EPT_ISO_TYPE)
  {
   if((dev->dsts_bit.soffn & 0x01) == 0)
   {
     ept_out->doepctl_bit.setd1pid = TRUE;
   }
   else
   {
     ept_out->doepctl_bit.setd0pid = TRUE;
   }
  }

  /* clear endpoint nak */
  ept_out->doepctl_bit.cnak = TRUE;

  /* endpoint enable */
  ept_out->doepctl_bit.eptena = TRUE;
}

static void hal_usbd_wakeup_enable(hal_udc_handle *pudc)
{
  /* open phy clock */
  usb_open_phy_clk(pudc->usb_reg);

  /* set remote wakeup */
  usb_remote_wkup_set(pudc->usb_reg);
}

static void hal_usbd_wakeup_disable(hal_udc_handle *pudc)
{
  /* clear remote wakup */
  usb_remote_wkup_clear(pudc->usb_reg);
}

static void hal_usbd_deinit(hal_udc_handle *pudc)
{
  usb_reg_type *usbx = pudc->usb_reg;
  uint32_t i_index;
  otg_eptin_type *ept_in;
  otg_eptout_type *ept_out;
  otg_device_type *dev;
  
  dev = OTG_DEVICE(usbx);
  
  for(i_index = 0; i_index < USB_EPT_MAX_NUM; i_index ++)
  {
    ept_in = USB_INEPT(usbx, i_index);
    if(ept_in->diepctl_bit.eptena)
    {
      ept_in->diepctl = 0;
      ept_in->diepctl_bit.eptdis = TRUE;
      ept_in->diepctl_bit.snak = TRUE;
    }
    else
    {
      ept_in->diepctl = 0;
    }
    ept_in->dieptsiz = 0;
    ept_in->diepint = 0xFFFF;
  }

  /* disable all out endpoint */
  for(i_index = 0; i_index < USB_EPT_MAX_NUM; i_index ++)
  {
    ept_out = USB_OUTEPT(usbx, i_index);
    if(ept_out->doepctl_bit.eptena)
    {
      ept_out->doepctl = 0;
      ept_out->doepctl_bit.eptdis = TRUE;
      ept_out->doepctl_bit.snak = TRUE;
    }
    else
    {
      ept_out->doepctl = 0;
    }
    ept_out->doeptsiz = 0;
    ept_out->doepint = 0xFFFF;
  }
  
  dev->diepmsk = 0;
  dev->doepmsk = 0;
  dev->daintmsk = 0;
  
  pudc->usb_address = 0;
  
  usb_flush_rx_fifo(usbx);
  usb_flush_tx_fifo(usbx, 0x10);
}

static void hal_usbd_ept_default_init(hal_udc_handle *pudc)
{
  uint8_t i_index = 0;
  /* init in endpoint info structure */
  for(i_index = 0; i_index < USB_EPT_MAX_NUM; i_index ++)
  {
    pudc->ept_in[i_index].eptn        = i_index;
    pudc->ept_in[i_index].ept_address = i_index;
    pudc->ept_in[i_index].inout         = EPT_DIR_IN;
    pudc->ept_in[i_index].maxpacket   = 0;
    pudc->ept_in[i_index].trans_buf   = 0;
    pudc->ept_in[i_index].total_len   = 0;
  }

  /* init out endpoint info structure */
  for(i_index = 0; i_index < USB_EPT_MAX_NUM; i_index ++)
  {
    pudc->ept_out[i_index].eptn        = i_index;
    pudc->ept_out[i_index].ept_address = i_index;
    pudc->ept_out[i_index].inout       = EPT_DIR_OUT;
    pudc->ept_out[i_index].maxpacket   = 0;
    pudc->ept_out[i_index].trans_buf   = 0;
    pudc->ept_out[i_index].total_len   = 0;
  }
}

static void hal_usbd_init(hal_udc_handle *pudc)
{
  usb_reg_type *usbx;
  otg_device_type *dev;
  otg_eptin_type *ept_in;
  otg_eptout_type *ept_out;
  uint32_t i_index;
  uint32_t hs_phytype;

  usbx = pudc->usb_reg;
  dev = OTG_DEVICE(usbx);

  hs_phytype = *(__IO uint32_t *)((uint32_t)usbx + 0x48) & 0xC0;

  /* set device disconnect */
  usb_disconnect(usbx);

  /* set endpoint to default status */
  hal_usbd_ept_default_init(pudc);

  /* disable usb global interrupt */
  usb_interrupt_disable(usbx);

  /* init global register */
  usb_global_init(usbx);

  if(pudc->udc_config.dma_en == TRUE && hs_phytype)
  {
    usbx->gahbcfg |= 1 << 5 | 3 << 1;
  }
  else
  {
    pudc->udc_config.dma_en = FALSE;
  }

  /* set device mode */
  usb_global_set_mode(usbx, OTG_DEVICE_MODE);
  
  hal_udc_delay(25);
  
  pudc->usb_reg->gccfg_bit.vbusig = TRUE;
  
  /* open phy clock */
  usb_open_phy_clk(pudc->usb_reg);

  /* set periodic frame interval */
  dev->dcfg_bit.perfrint = DCFG_PERFRINT_80;

  /* set device speed to full-speed */
  if( hs_phytype)
  {
    dev->dcfg_bit.devspd = 0; /*high speed*/
  }
  else
  {
    dev->dcfg_bit.devspd = USB_DCFG_FULL_SPEED;
  }
  /* flush all tx fifo */
  usb_flush_tx_fifo(usbx, 16);

  /* flush share rx fifo */
  usb_flush_rx_fifo(usbx);

  /* clear all endpoint interrupt flag and mask */
  dev->daint = 0xFFFFFFFF;
  dev->daintmsk = 0;
  dev->diepmsk = 0;
  dev->doepmsk = 0;

  for(i_index = 0; i_index < USB_EPT_MAX_NUM; i_index ++)
  {
    usbx->dieptxfn[i_index] = 0;
  }

  /* disable all in endpoint */
  for(i_index = 0; i_index < USB_EPT_MAX_NUM; i_index ++)
  {
    ept_in = USB_INEPT(usbx, i_index);
    if(ept_in->diepctl_bit.eptena)
    {
      ept_in->diepctl = 0;
      ept_in->diepctl_bit.eptdis = TRUE;
      ept_in->diepctl_bit.snak = TRUE;
    }
    else
    {
      ept_in->diepctl = 0;
    }
    ept_in->dieptsiz = 0;
    ept_in->diepint = 0xFF;
  }

  /* disable all out endpoint */
  for(i_index = 0; i_index < USB_EPT_MAX_NUM; i_index ++)
  {
    ept_out = USB_OUTEPT(usbx, i_index);
    if(ept_out->doepctl_bit.eptena)
    {
      ept_out->doepctl = 0;
      ept_out->doepctl_bit.eptdis = TRUE;
      ept_out->doepctl_bit.snak = TRUE;
    }
    else
    {
      ept_out->doepctl = 0;
    }
    ept_out->doeptsiz = 0;
    ept_out->doepint = 0xFF;
  }
  dev->diepmsk_bit.txfifoudrmsk = TRUE;

  /* clear global interrupt and mask */
  usbx->gintmsk = 0;
  usbx->gintsts = 0xBFFFFFFF;

  /* enable global interrupt mask */
  usbx->gintmsk = USB_OTG_USBSUSP_INT | USB_OTG_USBRST_INT |
                  USB_OTG_ENUMDONE_INT | USB_OTG_IEPT_INT |
                  USB_OTG_OEPT_INT | USB_OTG_INCOMISOIN_INT |
                  USB_OTG_INCOMPIP_INCOMPISOOUT_INT | USB_OTG_WKUP_INT |
                  USB_OTG_OTGINT_INT;
  if(pudc->udc_config.dma_en == FALSE || hs_phytype == 0)
  {
    usbx->gintmsk |= USB_OTG_RXFLVL_INT;
  }
  
  if(pudc->udc_config.sof_en == TRUE)
  {
    usbx->gintmsk |= USB_OTG_SOF_INT;
  }
  
  pudc->usb_address = 0;
  /* usb connect */
  usb_connect(usbx);

  /* enable global interrupt */
  usb_interrupt_enable(usbx);
}

static void usbd_rxflvl_handler(hal_udc_handle *pudc)
{
  otg_global_type *usbx = pudc->usb_reg;
  uint32_t stsp;
  uint32_t count;
  uint32_t pktsts;
  usb_ept_info *ept_info;

  /* disable rxflvl interrupt */
  usb_global_interrupt_enable(usbx, USB_OTG_RXFLVL_INT, FALSE);

  /* get rx status */
  stsp = usbx->grxstsp;

  /*get the byte count of receive */
  count = (stsp & USB_OTG_GRXSTSP_BCNT) >> 4;

  /* get packet status */
  pktsts = (stsp &USB_OTG_GRXSTSP_PKTSTS) >> 17;

  /* get endpoint infomation struct */
  ept_info = &pudc->ept_out[stsp & USB_OTG_GRXSTSP_EPTNUM];

  /* received out data packet */
  if(pktsts == USB_OUT_STS_DATA)
  {
    if(count != 0)
    {
      /* read packet to buffer */
      usb_read_packet(usbx, ept_info->trans_buf, (stsp & USB_OTG_GRXSTSP_EPTNUM), count);
      ept_info->trans_buf += count;
      ept_info->trans_len += count;

    }
  }
  /* setup data received */
  else if ( pktsts == USB_SETUP_STS_DATA)
  {
    /* read packet to buffer */
    usb_read_packet(usbx, (uint8_t *)pudc->setup_buffer, (stsp & USB_OTG_GRXSTSP_EPTNUM), count);
    ept_info->trans_len += count;
  }

  /* enable rxflvl interrupt */
  usb_global_interrupt_enable(usbx, USB_OTG_RXFLVL_INT, TRUE);

}
#ifdef OTG_USE_DMA
static void usbd_ept0_out_dma_set(hal_udc_handle *pudc)
{
  otg_eptout_type *usb_outept = USB_OUTEPT(pudc->usb_reg, 0);
  
  if(usb_outept->doepctl_bit.eptena == TRUE)
  {
    return;
  }
  USB_OUTEPT(pudc->usb_reg, 0)->doepdma = (uint32_t)pudc->setup_buffer;
  USB_OUTEPT(pudc->usb_reg, 0)->doepctl_bit.usbacept = TRUE;
  USB_OUTEPT(pudc->usb_reg, 0)->doepctl_bit.eptena = TRUE;
}
#endif

static void usb_write_empty_txfifo(hal_udc_handle *pudc, uint32_t ept_num)
{
  otg_global_type *usbx = pudc->usb_reg;
  usb_ept_info *ept_info = &pudc->ept_in[ept_num];
  uint32_t length = ept_info->total_len - ept_info->trans_len;
  uint32_t wlen = 0;

  if(length > ept_info->maxpacket)
  {
    length = ept_info->maxpacket;
  }
  wlen = (length + 3) / 4;

  while((USB_INEPT(usbx, ept_num)->dtxfsts & USB_OTG_DTXFSTS_INEPTFSAV) > wlen &&
    (ept_info->trans_len < ept_info->total_len) && (ept_info->total_len != 0))
  {
    length = ept_info->total_len - ept_info->trans_len;
    if(length > ept_info->maxpacket)
    {
      length = ept_info->maxpacket;
    }
    wlen = (length + 3) / 4;
    usb_write_packet(usbx, ept_info->trans_buf, ept_num, length);

    ept_info->trans_buf += length;
    ept_info->trans_len += length;

  }
  if(length <= 0)
  {
    OTG_DEVICE(usbx)->diepempmsk &= ~(0x1 << ept_num);
  }
}

static void usbd_inept_handler(hal_udc_handle *pudc)
{
  otg_global_type *usbx = pudc->usb_reg;
  uint32_t ept_num = 0, ept_int;
  uint32_t intsts;
#ifdef OTG_USE_DMA
  usb_ept_info *ept_info;
#endif

  /*get all endpoint interrut */
  intsts = usb_get_all_in_interrupt(usbx);
  while(intsts)
  {
    if(intsts & 0x1)
    {
      /* get endpoint interrupt flag */
      ept_int = usb_ept_in_interrupt(usbx, ept_num);

      /* transfer completed interrupt */
      if(ept_int & USB_OTG_DIEPINT_XFERC_FLAG)
      {
        OTG_DEVICE(usbx)->diepempmsk &= ~(1 << ept_num);
        usb_ept_in_clear(usbx, ept_num , USB_OTG_DIEPINT_XFERC_FLAG);
#ifdef OTG_USE_DMA
        if(pudc->udc_config.dma_en == TRUE)
        {
          ept_info = &pudc->ept_in[ept_num];
          ept_info->trans_buf += ept_info->maxpacket;

          if((ept_num == 0) && (pudc->ept_in[ept_num].total_len == 0))
          {
            usb_ept0_start(pudc->usb_reg);
            usbd_ept0_out_dma_set(pudc);
          }
        }
#endif
        hal_udc_data_in_callback(pudc, ept_num);
      }

      /* timeout condition interrupt */
      if(ept_int & USB_OTG_DIEPINT_TIMEOUT_FLAG)
      {
        usb_ept_in_clear(usbx, ept_num , USB_OTG_DIEPINT_TIMEOUT_FLAG);
      }

      /* in token received when tx fifo is empty */
      if(ept_int & USB_OTG_DIEPINT_INTKNTXFEMP_FLAG)
      {
        usb_ept_in_clear(usbx, ept_num , USB_OTG_DIEPINT_INTKNTXFEMP_FLAG);
      }

      /* in endpoint nak effective */
      if(ept_int & USB_OTG_DIEPINT_INEPTNAK_FLAG)
      {
        usb_ept_in_clear(usbx, ept_num , USB_OTG_DIEPINT_INEPTNAK_FLAG);
      }

      /* endpoint disable interrupt */
      if(ept_int & USB_OTG_DIEPINT_EPTDISD_FLAG)
      {
        usb_ept_in_clear(usbx, ept_num , USB_OTG_DIEPINT_EPTDISD_FLAG);
      }

      /* transmit fifo empty interrupt */
      if(ept_int & USB_OTG_DIEPINT_TXFEMP_FLAG)
      {
        usb_write_empty_txfifo(pudc, ept_num);
      }
    }
    ept_num ++;
    intsts >>= 1;
  }
}

static void usbd_outept_handler(hal_udc_handle *pudc)
{
  otg_global_type *usbx = pudc->usb_reg;
  uint32_t ept_num = 0, ept_int;
  uint32_t intsts, epsts;
  usb_ept_info *ept_info;

  /* get all out endpoint interrupt */
  intsts = usb_get_all_out_interrupt(usbx);

  while(intsts)
  {
    if(intsts & 0x1)
    {
      /* get out endpoint interrupt */
      ept_int = usb_ept_out_interrupt(usbx, ept_num);

      ept_info = &pudc->ept_out[ept_num];
			
      /* transfer completed interrupt */
      if(ept_int & USB_OTG_DOEPINT_XFERC_FLAG)
      {
        usb_ept_out_clear(usbx, ept_num , USB_OTG_DOEPINT_XFERC_FLAG);
        epsts = USB_OUTEPT(usbx, ept_num)->doepint;
#ifdef OTG_USE_DMA    
        if (pudc->udc_config.dma_en == TRUE)
        {
          if((epsts & USB_OTG_DOEPINT_SETUP_FLAG) == USB_OTG_DOEPINT_SETUP_FLAG)
          {
            if((epsts & 0x00008000) == 0x00008000)
            {
              usb_ept_out_clear(usbx, ept_num , 0x00008000);
            }
          }
          else if((epsts & 0x00000020) == 0x00000020)
          {
            usb_ept_out_clear(usbx, ept_num , 0x00000020);
          }
          else if((epsts & (USB_OTG_DOEPINT_SETUP_FLAG | 0x00000020)) == 0)
          {
            if((epsts & 0x00008000) == 0x00008000)
            {
              usb_ept_out_clear(usbx, ept_num , 0x00008000);
            }
            else
            {
              if(ept_info->total_len > ept_info->maxpacket)
              {
                ept_info->trans_len = ept_info->total_len - USB_OUTEPT(usbx, ept_num)->doeptsiz_bit.xfersize;
              }
              else
              { 
                ept_info->trans_len = ept_info->maxpacket - USB_OUTEPT(usbx, ept_num)->doeptsiz_bit.xfersize;
              }
              ept_info->trans_buf += ept_info->trans_len;
              if((ept_num == 0) && (pudc->ept_out[ept_num].total_len == 0))
              {
                usb_ept0_start(pudc->usb_reg);
                usbd_ept0_out_dma_set(pudc);
              }
              hal_udc_data_out_callback(pudc, ept_num);
            }
            
          }
        }
        else
  #endif
        {
          if((ept_num == 0) && (pudc->ept_out[ept_num].total_len == 0))
          {
            usb_ept0_start(pudc->usb_reg);
          }
          hal_udc_data_out_callback(pudc, ept_num);          
        }
      }

      /* setup phase done interrupt */
      if(ept_int & USB_OTG_DOEPINT_SETUP_FLAG)
      {
        usb_ept_out_clear(usbx, ept_num , USB_OTG_DOEPINT_SETUP_FLAG);
        epsts = USB_OUTEPT(usbx, ept_num)->doepint;
#ifdef USB_OTG_DOEPINT_STUPPKTRCVD_FLAG  
        if((epsts & USB_OTG_DOEPINT_STUPPKTRCVD_FLAG) == USB_OTG_DOEPINT_STUPPKTRCVD_FLAG)
        {
          usb_ept_out_clear(usbx, ept_num , USB_OTG_DOEPINT_STUPPKTRCVD_FLAG);
        }
#endif 
        hal_udc_data_setup_callback(pudc);
 #ifdef OTG_USE_DMA             
        if(pudc->udc_config.dma_en == TRUE)
        {
          usb_ept0_start(pudc->usb_reg);
          usbd_ept0_out_dma_set(pudc);
        }
#endif
      }

      /* endpoint disable interrupt */
      if(ept_int & USB_OTG_DOEPINT_OUTTEPD_FLAG)
      {
        usb_ept_out_clear(usbx, ept_num , USB_OTG_DOEPINT_OUTTEPD_FLAG);
      }
#ifdef USB_OTG_DOEPINT_STSPHRCVD_FLAG  
      if(ept_int & USB_OTG_DOEPINT_STSPHRCVD_FLAG)
      {
        usb_ept_out_clear(usbx, ept_num , USB_OTG_DOEPINT_STSPHRCVD_FLAG);
      }
#endif
      if(ept_int & USB_OTG_DOEPINT_EPTDISD_FLAG)
      {
        usb_ept_out_clear(usbx, ept_num , USB_OTG_DOEPINT_EPTDISD_FLAG);
      }

    }
    ept_num ++;
    intsts >>= 1;
  }
}

static void usbd_reset_handler(hal_udc_handle *pudc)
{
  otg_global_type *usbx = pudc->usb_reg;
  otg_device_type *dev = OTG_DEVICE(usbx);
  uint32_t i_index = 0;

  /* disable remote wakeup singal */
  dev->dctl_bit.rwkupsig = FALSE;

  /* flush all tx fifo */
  usb_flush_tx_fifo(usbx, 0x10);

  /* clear in and out endpoint interrupt flag */
  for(i_index = 0; i_index < USB_EPT_MAX_NUM; i_index ++)
  {
    USB_INEPT(usbx, i_index)->diepint = 0xFFFF;
    USB_INEPT(usbx, i_index)->diepctl_bit.stall = FALSE;
    USB_INEPT(usbx, i_index)->diepctl_bit.snak = TRUE;
    USB_OUTEPT(usbx, i_index)->doepint = 0xFFFF;
    USB_OUTEPT(usbx, i_index)->doepctl_bit.stall = FALSE;
    USB_OUTEPT(usbx, i_index)->doepctl_bit.snak = TRUE;
  }

  /* clear endpoint flag */
  dev->daint = 0xFFFFFFFF;

  /*clear endpoint interrupt mask */
  dev->daintmsk = 0x10001;

  /* enable out endpoint xfer, eptdis, setup interrupt mask */
  dev->doepmsk_bit.xfercmsk = TRUE;
  dev->doepmsk_bit.eptdismsk = TRUE;
  dev->doepmsk_bit.setupmsk = TRUE;

  /* enable in endpoint xfer, eptdis, timeout interrupt mask */
  dev->diepmsk_bit.xfercmsk = TRUE;
  dev->diepmsk_bit.eptdismsk = TRUE;
  dev->diepmsk_bit.timeoutmsk = TRUE;

#ifdef USB_SUPPORT_EPT1_INTERRUPT
  dev->diepeachmsk1_bit.xfercmsk = TRUE;
  dev->diepeachmsk1_bit.eptdismsk = TRUE;
  dev->diepeachmsk1_bit.timeoutmsk = TRUE;
  
  dev->doepeachmsk1_bit.xfercmsk = TRUE;
  dev->doepeachmsk1_bit.eptdismsk = TRUE;
#endif
  /* set device address to 0 */
  usb_set_address(usbx, 0);

  /* enable endpoint 0 */
  usb_ept0_start(usbx);
#ifdef OTG_USE_DMA
  if(pudc->udc_config.dma_en == TRUE)
  {
    usbd_ept0_out_dma_set(pudc);
  }
#endif
}

static void usbd_enumdone_handler(hal_udc_handle *pudc)
{
  otg_global_type *usbx = pudc->usb_reg;
  
  if(OTG_DEVICE(usbx)->dsts_bit.enumspd == 0)
  {
    usbx->gusbcfg_bit.usbtrdtim = USB_TRDTIM_8;
  }
  else
  {
    usbx->gusbcfg_bit.usbtrdtim = USB_TRDTIM_16;
  }
  usb_ept0_setup(usbx);
  
  hal_udc_reset_callback(pudc);
}


static void hal_usbd_irq(hal_udc_handle *pudc)
{
  usb_reg_type *usbx = pudc->usb_reg;
  uint32_t intsts = usb_global_get_all_interrupt(usbx);
  
  /* mode mismatch interrupt */
    if(intsts & USB_OTG_MODEMIS_FLAG)
    {
      usb_global_clear_interrupt(usbx, USB_OTG_MODEMIS_FLAG);
    }

    /* rx non-empty interrupt, indicates that there is at least one
      data packet pending to be read in rx fifo */
    if(intsts & USB_OTG_RXFLVL_FLAG)
    {
      usbd_rxflvl_handler(pudc);
    }
    
    /* in endpoint interrupt */
    if(intsts & USB_OTG_IEPT_FLAG)
    {
      usbd_inept_handler(pudc);
    }
    
    /* out endpoint interrupt */
    if(intsts & USB_OTG_OEPT_FLAG)
    {
      usbd_outept_handler(pudc);
    }

    /* usb reset interrupt */
    if(intsts & USB_OTG_USBRST_FLAG)
    {
      usbd_reset_handler(pudc);
      usb_global_clear_interrupt(usbx, USB_OTG_USBRST_FLAG);
    }

    /* sof interrupt */
    if(intsts & USB_OTG_SOF_FLAG)
    {
      hal_udc_sof_callback(pudc);
      usb_global_clear_interrupt(usbx, USB_OTG_SOF_FLAG);
    }

    /* enumeration done interrupt */
    if(intsts & USB_OTG_ENUMDONE_FLAG)
    {
      usbd_enumdone_handler(pudc);
      usb_global_clear_interrupt(usbx, USB_OTG_ENUMDONE_FLAG);
    }

    /* incomplete isochronous in transfer interrupt */
    if(intsts & USB_OTG_INCOMISOIN_FLAG)
    {
      hal_udc_isoincom_callback(pudc);
      usb_global_clear_interrupt(usbx, USB_OTG_INCOMISOIN_FLAG);
    }
    /* disconnect detected interrupt  */
    if(intsts & USB_OTG_OTGINT_FLAG)
    {
      uint32_t tmp = pudc->usb_reg->gotgint;
      if(pudc->usb_reg->gotgint_bit.sesenddet)
        hal_udc_disconnect_callback(pudc);
      pudc->usb_reg->gotgint = tmp;
      usb_global_clear_interrupt(usbx, USB_OTG_OTGINT_FLAG);
    }
    /* incomplete isochronous out transfer interrupt */
    if(intsts & USB_OTG_INCOMPIP_INCOMPISOOUT_FLAG)
    {
      hal_udc_isooutcom_callback(pudc);
      usb_global_clear_interrupt(usbx, USB_OTG_INCOMPIP_INCOMPISOOUT_FLAG);
    }

    /* resume/remote wakeup interrupt */
    if(intsts & USB_OTG_WKUP_FLAG)
    {
      /* clear remote wakeup bit */
      OTG_DEVICE(usbx)->dctl_bit.rwkupsig = FALSE;

       /* exit suspend mode */
      usb_open_phy_clk(pudc->usb_reg);
      hal_udc_resume_callback(pudc);
      usb_global_clear_interrupt(usbx, USB_OTG_WKUP_FLAG);
    }

    /* usb suspend interrupt */
    if(intsts & USB_OTG_USBSUSP_FLAG)
    {
      if(OTG_DEVICE(usbx)->dsts_bit.suspsts)
      {
        hal_udc_suspend_callback(pudc);
      }
      usb_global_clear_interrupt(usbx, USB_OTG_USBSUSP_FLAG);
    }
  
}

static int udc_dp_flush(hal_udc_handle *pudc, const uint8_t ep)
{
  if((ep & 0x80) == 0x80)
  {
    usb_flush_tx_fifo(pudc->usb_reg, ep & 0x7F);
  }
  else
  {
    usb_flush_rx_fifo(pudc->usb_reg);
  }
  return 0;
}
#endif

