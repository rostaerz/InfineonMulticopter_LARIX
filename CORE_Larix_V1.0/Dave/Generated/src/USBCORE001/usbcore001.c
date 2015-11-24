/*******************************************************************************
**  DAVE App Name : USBCORE001       App Version: 1.0.18               
**  This file is generated by DAVE, User modification to this file will be    **
**  overwritten at the next code generation.                                  **
*******************************************************************************/





/* CODE_BLOCK_BEGIN[USBCORE001.c] */

/*******************************************************************************
 Copyright (c) 2012, Infineon Technologies AG                                 **
 All rights reserved.                                                         **
                                                                              **
 Redistribution and use in source and binary forms, with or without           **
 modification,are permitted provided that the following conditions are met:   **
                                                                              **
 *Redistributions of source code must retain the above copyright notice,      **
 this list of conditions and the following disclaimer.                        **
 *Redistributions in binary form must reproduce the above copyright notice,   **
 this list of conditions and the following disclaimer in the documentation    **
 and/or other materials provided with the distribution.                       **
 *Neither the name of the copyright holders nor the names of its contributors **
 may be used to endorse or promote products derived from this software without** 
 specific prior written permission.                                           **
                                                                              **
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  **
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    **
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   **
 ARE  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   **
 LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         **
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         **
 SUBSTITUTE GOODS OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    **
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      **
 CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)       **
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   **
 POSSIBILITY OF SUCH DAMAGE.                                                  **
                                                                              **
 To improve the quality of the software, users are encouraged to share        **
 modifications, enhancements or bug fixes with Infineon Technologies AG       **
 dave@infineon.com).                                                          **
                                                                              **
********************************************************************************
**                                                                            **
**                                                                            **
** PLATFORM : Infineon XMC4000 Series                                         **
**                                                                            **
** COMPILER : Compiler Independent                                            **
**                                                                            **
** AUTHOR : App Developer                                                     **
**                                                                            **
** MAY BE CHANGED BY USER [yes/no]: Yes                                       **
**                                                                            **
** MODIFICATION DATE : Aug 20, 2013                                           **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Author(s) Identity                                   **
********************************************************************************
**                                                                            **
** Initials    Name                                                           **
** ---------------------------------------------------------------------------**
** CM          App Developer                                                  **
** ---------------------------------------------------------------------------**
** Version   App Developer Name    Comments                                   **
**                                                                            **
**           NSND         : Updated for usb soft disconnect                   **
**                                                                            **
**                                                                            **
*******************************************************************************/

/* ==========================================================================
 *
 * Synopsys HS OTG Linux Software Driver and documentation (hereinafter,
 * "Software") is an Unsupported proprietary work of Synopsys, Inc. unless
 * otherwise expressly agreed to in writing between Synopsys and you.
 *
 * The Software IS NOT an item of Licensed Software or Licensed Product under
 * any End User Software License Agreement or Agreement for Licensed Product
 * with Synopsys or any supplement thereto. You are permitted to use and
 * redistribute this Software in source and binary forms, with or without
 * modification, provided that redistributions of source code must retain this
 * notice. You may not view, use, disclose, copy or distribute this file or
 * any information contained herein except pursuant to this license grant from
 * Synopsys. If you do not agree with this notice, including the disclaimer
 * below, then you are not authorized to use the Software.
 *
 * THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS" BASIS
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * ========================================================================== */

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/
/**
 * @file  USBCORE001.c
 *
 * @brief This file contains functions related to USB Core Layer.
 *
 */

/*******************************************************************************
**                      Include Files                                         **
*******************************************************************************/
#include <Dave3.h>
#include "../../src/USBLD001/driver/dwc_otg_hcd_if.h"
#include "../../src/USBLD001/driver/dwc_otg_pcd_if.h"
#include "../../src/USBLD001/driver/dwc_otg_adp.h"
#include "../USBLD001/usbld001_delay.h"

/**
 * @cond INTERNAL_DOCS
 */
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/**
 * @ingroup USBCORE001_privateparam
 * @{
 */





/** Defines USB interrupt priority */
#define USBCORE001_Host_PREEMPTION_PRIORITY          63

/** Defines USB interrupt sub priority */
#define USBCORE001_Host_SUB_PRIORITY                 0

/*!
*@note preserved to limit changes to the HCD part
*/
/**Data structures*/

/** Instance to manage USBCORE001_OtgDevice*/
USBCORE001_OtgDevice *USBCORE001_OtgDevPtr = NULL;

/**
 * @}
 */

/**
 * @ingroup USBCORE001_privatefunc
 * @{
 */
/*******************************************************************************
**                     Private Function Declarations                          **
*******************************************************************************/

/**
 * @brief This function sets the driver parameters based on the global 
 *        structure.  
 * @param [IN] CoreIfPtr    Pointer to the core interface structure
 * @return int 0 if success \n
 */
static int USBCORE001_SetParameters(dwc_otg_core_if_t * CoreIfPtr);


/**
 * @brief This function sets the interrupt priority and enable the interrupt for  
 *        USB.
 * @param void
 * @return void \n
 */
static void USBCORE001_EnableUSBInterrupt(void);

/**
 * @}
 */

static struct USBCORE001_OTGDriverParam USBCORE001_DriverParams = {
  -1,      /** opt*/
  2,      /** otg_cap*/
  0,      /** dma_enable*/
  -1,      /** dma_desc_enable */
  -1,      /** dma_burst_size */
  DWC_SPEED_PARAM_FULL,      /** speed */
  1,      /** host_support_fs_ls_low_power*/
  1,      /** host_ls_low_power_phy_clk */
  -1,      /** enable_dynamic_fifo */
  -1,      /** data_fifo_size */ 
  -1,      /** dev_rx_fifo_size */
  -1,      /** dev_nperio_tx_fifo_size*/
  {
    /* dev_perio_tx_fifo_size_1 */
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1
    /* 15 */
  },
  -1,    /** host_rx_fifo_size */
  -1,    /** host_nperio_tx_fifo_size */
  -1,    /** host_perio_tx_fifo_size */
  -1,    /** max_transfer_size */
  -1,    /** max_packet_count */
  8,    /** host_channels */
  -1,    /** dev_endpoints */
  DWC_PHY_TYPE_PARAM_FS,    /** phy_type */
  -1,    /** phy_utmi_width */
  -1,    /** phy_ulpi_ddr */
  -1,    /** phy_ulpi_ext_vbus */
  -1,    /** i2c_enable */
  -1,    /** ulpi_fs_ls */
  -1,    /** ts_dline */
  -1,    /** en_multiple_tx_fifo */
  {
     /* dev_tx_fifo_size */
     -1,
     -1,
     -1,
     -1,
     -1,
     -1,
     -1,
     -1,
     -1,
     -1,
     -1,
     -1,
     -1,
     -1,
     -1
    /* 15 */
  },
  -1,    /** thr_ctl */
  -1,    /** tx_thr_length */
  -1,    /** rx_thr_length */
  -1,    /** pti_enable */
  -1,    /** mpi_enable */
  -1,    /** lpm_enable */
  -1,    /** ic_usb_cap */
  -1,    /** ahb_thr_ratio */
  -1,    /** power_down */
  -1,    /** reload_ctl */
  -1,    /** otg_ver */
  -1,    /** adp_enable */
};

/*******************************************************************************
**                     Private Function Definitions                           **
*******************************************************************************/
static int USBCORE001_SetParameters(dwc_otg_core_if_t * CoreIfPtr)
{
  int RetVal = 0; 
  int Count; 
  if (USBCORE001_DriverParams.otg_cap != -1) {
    RetVal +=
        dwc_otg_set_param_otg_cap(CoreIfPtr,
                USBCORE001_DriverParams.otg_cap);
  }
  if (USBCORE001_DriverParams.dma_enable != -1) {
    RetVal +=
        dwc_otg_set_param_dma_enable(CoreIfPtr,
             USBCORE001_DriverParams.
             dma_enable);
  }
  if (USBCORE001_DriverParams.dma_desc_enable != -1) {
    RetVal +=
        dwc_otg_set_param_dma_desc_enable(CoreIfPtr,
                  USBCORE001_DriverParams.
                  dma_desc_enable);
  }  
  if (USBCORE001_DriverParams.opt != -1) {
    RetVal +=
        dwc_otg_set_param_opt(CoreIfPtr, 
                              USBCORE001_DriverParams.opt);
  }
  if (USBCORE001_DriverParams.dma_burst_size != -1) {
    RetVal +=
        dwc_otg_set_param_dma_burst_size(CoreIfPtr,
                 USBCORE001_DriverParams.
                 dma_burst_size);
  }
  if (USBCORE001_DriverParams.host_support_fs_ls_low_power != -1) {
    RetVal +=
        dwc_otg_set_param_host_support_fs_ls_low_power(CoreIfPtr,
                   USBCORE001_DriverParams.
                   host_support_fs_ls_low_power);
  }
  if (USBCORE001_DriverParams.enable_dynamic_fifo != -1) {
    RetVal +=
        dwc_otg_set_param_enable_dynamic_fifo(CoreIfPtr,
                USBCORE001_DriverParams.
                enable_dynamic_fifo);
  }
  if (USBCORE001_DriverParams.data_fifo_size != -1) {
    RetVal +=
        dwc_otg_set_param_data_fifo_size(CoreIfPtr,
                 USBCORE001_DriverParams.
                 data_fifo_size);
  }
  if (USBCORE001_DriverParams.dev_rx_fifo_size != -1) {
    RetVal +=
        dwc_otg_set_param_dev_rx_fifo_size(CoreIfPtr,
                   USBCORE001_DriverParams.
                   dev_rx_fifo_size);
  }
  if (USBCORE001_DriverParams.dev_nperio_tx_fifo_size != -1) {
    RetVal +=
        dwc_otg_set_param_dev_nperio_tx_fifo_size(CoreIfPtr,
                    USBCORE001_DriverParams.
                    dev_nperio_tx_fifo_size);
  }
  if (USBCORE001_DriverParams.host_rx_fifo_size != -1) {
    RetVal +=
        dwc_otg_set_param_host_rx_fifo_size(CoreIfPtr,
              USBCORE001_DriverParams.host_rx_fifo_size);
  }
  if (USBCORE001_DriverParams.host_nperio_tx_fifo_size != -1) {
    RetVal +=
        dwc_otg_set_param_host_nperio_tx_fifo_size(CoreIfPtr,
                     USBCORE001_DriverParams.
                     host_nperio_tx_fifo_size);
  }
  if (USBCORE001_DriverParams.host_perio_tx_fifo_size != -1) {
    RetVal +=
        dwc_otg_set_param_host_perio_tx_fifo_size(CoreIfPtr,
                    USBCORE001_DriverParams.
                    host_perio_tx_fifo_size);
  }
  if (USBCORE001_DriverParams.max_transfer_size != -1) {
    RetVal +=
        dwc_otg_set_param_max_transfer_size(CoreIfPtr,
              USBCORE001_DriverParams.
              max_transfer_size);
  }
  if (USBCORE001_DriverParams.max_packet_count != -1) {
    RetVal +=
        dwc_otg_set_param_max_packet_count(CoreIfPtr,
                   USBCORE001_DriverParams.
                   max_packet_count);
  }
  if (USBCORE001_DriverParams.host_channels != -1) {
    RetVal +=
        dwc_otg_set_param_host_channels(CoreIfPtr,
                USBCORE001_DriverParams.
                host_channels);
  }
  if (USBCORE001_DriverParams.dev_endpoints != -1) {
    RetVal +=
        dwc_otg_set_param_dev_endpoints(CoreIfPtr,
                USBCORE001_DriverParams.
                dev_endpoints);
  }  
  if (USBCORE001_DriverParams.phy_type != -1) {
    RetVal +=
        dwc_otg_set_param_phy_type(CoreIfPtr,
                 USBCORE001_DriverParams.phy_type);
  }
  if (USBCORE001_DriverParams.speed != -1) {
    RetVal +=
        dwc_otg_set_param_speed(CoreIfPtr,
              USBCORE001_DriverParams.speed);
  }    
  if (USBCORE001_DriverParams.host_ls_low_power_phy_clk != -1) {
    RetVal +=
        dwc_otg_set_param_host_ls_low_power_phy_clk(CoreIfPtr,
                USBCORE001_DriverParams.
                host_ls_low_power_phy_clk);
  }
  if (USBCORE001_DriverParams.phy_ulpi_ddr != -1) {
    RetVal +=
        dwc_otg_set_param_phy_ulpi_ddr(CoreIfPtr,
               USBCORE001_DriverParams.
               phy_ulpi_ddr);
  }
  if (USBCORE001_DriverParams.phy_ulpi_ext_vbus != -1) {
    RetVal +=
        dwc_otg_set_param_phy_ulpi_ext_vbus(CoreIfPtr,
              USBCORE001_DriverParams.
              phy_ulpi_ext_vbus);
  }
  if (USBCORE001_DriverParams.phy_utmi_width != -1) {
    RetVal +=
        dwc_otg_set_param_phy_utmi_width(CoreIfPtr,
                 USBCORE001_DriverParams.
                 phy_utmi_width);
  }
  if (USBCORE001_DriverParams.ulpi_fs_ls != -1) {
    RetVal +=
        dwc_otg_set_param_ulpi_fs_ls(CoreIfPtr,
             USBCORE001_DriverParams.ulpi_fs_ls);
  }
  if (USBCORE001_DriverParams.ts_dline != -1) {
    RetVal +=
        dwc_otg_set_param_ts_dline(CoreIfPtr,
                 USBCORE001_DriverParams.ts_dline);
  }
  if (USBCORE001_DriverParams.i2c_enable != -1) {
    RetVal +=
        dwc_otg_set_param_i2c_enable(CoreIfPtr,
             USBCORE001_DriverParams.
             i2c_enable);
  }
  if (USBCORE001_DriverParams.en_multiple_tx_fifo != -1) {
    RetVal +=
        dwc_otg_set_param_en_multiple_tx_fifo(CoreIfPtr,
                USBCORE001_DriverParams.
                en_multiple_tx_fifo);
  }
  for (Count = 0; Count < 15; Count++) {
    if (USBCORE001_DriverParams.dev_perio_tx_fifo_size[Count] != -1) {
      RetVal +=
          dwc_otg_set_param_dev_perio_tx_fifo_size(CoreIfPtr,
                     USBCORE001_DriverParams.
                     dev_perio_tx_fifo_size[Count], Count);
    }
  }

  for (Count = 0; Count < 15; Count++) {
    if (USBCORE001_DriverParams.dev_tx_fifo_size[Count] != -1) {
      RetVal += dwc_otg_set_param_dev_tx_fifo_size(CoreIfPtr,
                     USBCORE001_DriverParams.
                     dev_tx_fifo_size
                     [Count], Count);
    }
  }
  if (USBCORE001_DriverParams.thr_ctl != -1) {
    RetVal +=
        dwc_otg_set_param_thr_ctl(CoreIfPtr,
                USBCORE001_DriverParams.thr_ctl);
  }
  if (USBCORE001_DriverParams.mpi_enable != -1) {
    RetVal +=
        dwc_otg_set_param_mpi_enable(CoreIfPtr,
             USBCORE001_DriverParams.mpi_enable);
  }
  if (USBCORE001_DriverParams.pti_enable != -1) {
    RetVal +=
        dwc_otg_set_param_pti_enable(CoreIfPtr,
             USBCORE001_DriverParams.
             pti_enable);
  }
  if (USBCORE001_DriverParams.lpm_enable != -1) {
    RetVal +=
        dwc_otg_set_param_lpm_enable(CoreIfPtr,
             USBCORE001_DriverParams.
             lpm_enable);
  }
  if (USBCORE001_DriverParams.ic_usb_cap != -1) {
    RetVal +=
        dwc_otg_set_param_ic_usb_cap(CoreIfPtr,
             USBCORE001_DriverParams.
             ic_usb_cap);
  }
  if (USBCORE001_DriverParams.tx_thr_length != -1) {
    RetVal +=
        dwc_otg_set_param_tx_thr_length(CoreIfPtr,
                USBCORE001_DriverParams.tx_thr_length);
  }
  if (USBCORE001_DriverParams.rx_thr_length != -1) {
    RetVal +=
        dwc_otg_set_param_rx_thr_length(CoreIfPtr,
                USBCORE001_DriverParams.
                rx_thr_length);
  }
  if (USBCORE001_DriverParams.ahb_thr_ratio != -1) {
    RetVal +=
        dwc_otg_set_param_ahb_thr_ratio(CoreIfPtr,
                USBCORE001_DriverParams.ahb_thr_ratio);
  }
  if (USBCORE001_DriverParams.power_down != -1) {
    RetVal +=
        dwc_otg_set_param_power_down(CoreIfPtr,
             USBCORE001_DriverParams.power_down);
  }
  if (USBCORE001_DriverParams.reload_ctl != -1) {
    RetVal +=
        dwc_otg_set_param_reload_ctl(CoreIfPtr,
             USBCORE001_DriverParams.reload_ctl);
  }
  if (USBCORE001_DriverParams.otg_ver != -1) {
    RetVal +=
        dwc_otg_set_param_otg_ver(CoreIfPtr,
                USBCORE001_DriverParams.otg_ver);
  }
  if (USBCORE001_DriverParams.adp_enable != -1) {
    RetVal +=
        dwc_otg_set_param_adp_enable(CoreIfPtr,
             USBCORE001_DriverParams.
             adp_enable);
  }  
  return RetVal;
}


/** This Enables and sets the priority of USB Interrupt */
static void USBCORE001_EnableUSBInterrupt(void)
{
  NVIC_SetPriority(USB0_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),\
                                           USBCORE001_Host_PREEMPTION_PRIORITY,\
                                           USBCORE001_Host_SUB_PRIORITY));
  NVIC_ClearPendingIRQ(USB0_0_IRQn);
  NVIC_EnableIRQ(USB0_0_IRQn);
}

/**
 * @endcond
 */

/*******************************************************************************
**                     Public Function Definitions                            **
*******************************************************************************/

/** This is Module init function. */
void USBCORE001_Init(void)
{
  RESET001_DeassertReset(PER2_USB);
  USB0->DCTL |= USB_DCTL_SftDiscon_Msk; 
  /* Disconnect device, so that we have time to initialize. */
}


/** Core initialization function. */
int USBCORE001_Initialize(USBCORE001_OtgDevice **OtgDevPtr)
{
  int RetVal = 0;

  *OtgDevPtr = NULL;
                 
  SCU_POWER->PWRSET |= 
               SCU_POWER_PWRSTAT_USBOTGEN_Msk | SCU_POWER_PWRSTAT_USBPHYPDQ_Msk; 
  #ifdef DWC_DEVICE_ONLY
   SET_BIT(USB0->GUSBCFG,USB_GUSBCFG_ForceDevMode_Pos);
  #endif
  #ifdef DWC_HOST_ONLY
   SET_BIT(USB0->GUSBCFG,USB_GUSBCFG_ForceHstMode_Pos);
  #endif
    
    
  USBCORE001_EnableUSBInterrupt();

  if(!USBCORE001_OtgDevPtr)
  {
    /**Allocate memory to hold the global data*/
    USBCORE001_OtgDevPtr = DWC_ALLOC(sizeof(USBCORE001_OtgDevice));

    if(!USBCORE001_OtgDevPtr)
    {
      RetVal = -DWC_E_NO_MEMORY;
      goto end;
    }
    DWC_MEMSET(USBCORE001_OtgDevPtr,0,sizeof(USBCORE001_OtgDevice));
  }

  /** Step 1: Initialize the base address */
  USBCORE001_OtgDevPtr->RegBasePtr = (void *)USBCORE001_USB_OTG_BASE_ADDRESS;

  /**Step 2: Initialize core interface layer of the otg */
  USBCORE001_OtgDevPtr->CoreIfPtr = 
                             dwc_otg_cil_init(USBCORE001_OtgDevPtr->RegBasePtr);

  if(!USBCORE001_OtgDevPtr->CoreIfPtr)
  {
    RetVal = -DWC_E_UNKNOWN;
    goto end;
  }

  /*
   * Step 3: Attempt to ensure this device is really a DWC_otg Controller.
   * Read and verify the SNPSID register contents. The value should be
   * 0x45F42XXX, which corresponds to "OT2", as in "OTG version 2.XX".
   */
  if ((dwc_otg_get_gsnpsid(USBCORE001_OtgDevPtr->CoreIfPtr) & 0xFFFFF000) !=
      0x4F542000) {
    RetVal = -EINVAL;
    goto end;
  }

  /**Step 4:  Initialize the params*/
  RetVal = USBCORE001_SetParameters(USBCORE001_OtgDevPtr->CoreIfPtr);
  if(0 != RetVal)
  {
    RetVal = -EINVAL;
    goto end;
  }

  /*
   * Step 5: Disable the global interrupts until all interrupt routines
   * are installed
  */
  dwc_otg_disable_global_interrupts(USBCORE001_OtgDevPtr->CoreIfPtr);

  /**Step 5: Enable else init HCD/PCD */
  /** Initialize the DWC_otg core.*/
    dwc_otg_core_init(USBCORE001_OtgDevPtr->CoreIfPtr);

#ifndef DWC_HOST_ONLY
    if (RetVal != 0) {
      USBCORE001_OtgDevPtr->PcdData.PCDPtr = NULL;
      goto end;
    }
#endif
  
  dwc_otg_enable_global_interrupts(USBCORE001_OtgDevPtr->CoreIfPtr);
  
  *OtgDevPtr = USBCORE001_OtgDevPtr;

end:
  if(0 != RetVal)
  {
    /**Perform appropriate cleanup*/
    if(USBCORE001_OtgDevPtr)
    {
      if(USBCORE001_OtgDevPtr->CoreIfPtr)
      {
        dwc_otg_cil_remove(USBCORE001_OtgDevPtr->CoreIfPtr);
        USBCORE001_OtgDevPtr->CoreIfPtr = NULL;
      }
      DWC_FREE(USBCORE001_OtgDevPtr);
      USBCORE001_OtgDevPtr = NULL;
    }
  }
  return RetVal;
}


/** Global interrupt routine */
void USBCORE001_Intr(void)
{
  if(NULL != USBCORE001_OtgDevPtr)
  {
#ifdef DWC_DEVICE_ONLY
    dwc_otg_pcd_handle_intr(USBCORE001_OtgDevPtr->PcdData.PCDPtr);
#endif
#ifdef DWC_HOST_ONLY
    dwc_otg_hcd_handle_intr(USBCORE001_OtgDevPtr->HCDPtr);
#endif
  }
}

/** USB interrupt Handler  */
void USB0_0_IRQHandler()
{
  USBCORE001_Intr();
}

/*CODE_BLOCK_END*/

