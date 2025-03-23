/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/custom_stm.c
  * @author  MCD Application Team
  * @brief   Custom Example Service.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "common_blesvc.h"
#include "custom_stm.h"

/* USER CODE BEGIN Includes */
#include "main.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef struct{
  uint16_t  CustomConfigHdle;                    /**< configdata handle */
  uint16_t  CustomDelaiHdle;                  /**< delaicharac handle */
  uint16_t  CustomAcqHdle;                  /**< acqcharac handle */
  uint16_t  CustomIaHdle;                    /**< iadata handle */
  uint16_t  CustomIacHdle;                  /**< iacharac handle */
  uint16_t  CustomAccHdle;                    /**< accdata handle */
  uint16_t  CustomAccxHdle;                  /**< accxcahrac handle */
  uint16_t  CustomAccyHdle;                  /**< accycharac handle */
  uint16_t  CustomAcczHdle;                  /**< acczcharac handle */
  uint16_t  CustomGyrHdle;                    /**< gyrdata handle */
  uint16_t  CustomGyrxHdle;                  /**< gyrxcharac handle */
  uint16_t  CustomGyryHdle;                  /**< gyrycharac handle */
  uint16_t  CustomGyrzHdle;                  /**< gyrzcharac handle */
  uint16_t  CustomTempHdle;                    /**< tempdata handle */
  uint16_t  CustomTempcHdle;                  /**< tempcharac handle */
/* USER CODE BEGIN Context */
  /* Place holder for Characteristic Descriptors Handle*/

/* USER CODE END Context */
}CustomContext_t;

extern uint16_t Connection_Handle;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private defines -----------------------------------------------------------*/
#define UUID_128_SUPPORTED  1

#if (UUID_128_SUPPORTED == 1)
#define BM_UUID_LENGTH  UUID_TYPE_128
#else
#define BM_UUID_LENGTH  UUID_TYPE_16
#endif

#define BM_REQ_CHAR_SIZE    (3)

/* USER CODE BEGIN PD */
//extern bool acq;
// uint32_t delai;

uint32_t delai;
int acq;
/* USER CODE END PD */

/* Private macros ------------------------------------------------------------*/
#define CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET         2
#define CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET              1
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
uint16_t SizeDelai = 1;
uint16_t SizeAcq = 1;
uint16_t SizeIac = 2;
uint16_t SizeAccx = 2;
uint16_t SizeAccy = 2;
uint16_t SizeAccz = 2;
uint16_t SizeGyrx = 2;
uint16_t SizeGyry = 2;
uint16_t SizeGyrz = 2;
uint16_t SizeTempc = 2;

/**
 * START of Section BLE_DRIVER_CONTEXT
 */
static CustomContext_t CustomContext;

/**
 * END of Section BLE_DRIVER_CONTEXT
 */

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static SVCCTL_EvtAckStatus_t Custom_STM_Event_Handler(void *pckt);

static tBleStatus Generic_STM_App_Update_Char_Ext(uint16_t ConnectionHandle, uint16_t ServiceHandle, uint16_t CharHandle, uint16_t CharValueLen, uint8_t *pPayload);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
/* USER CODE BEGIN PFD */

/* USER CODE END PFD */

/* Private functions ----------------------------------------------------------*/

#define COPY_UUID_128(uuid_struct, uuid_15, uuid_14, uuid_13, uuid_12, uuid_11, uuid_10, uuid_9, uuid_8, uuid_7, uuid_6, uuid_5, uuid_4, uuid_3, uuid_2, uuid_1, uuid_0) \
do {\
    uuid_struct[0] = uuid_0; uuid_struct[1] = uuid_1; uuid_struct[2] = uuid_2; uuid_struct[3] = uuid_3; \
    uuid_struct[4] = uuid_4; uuid_struct[5] = uuid_5; uuid_struct[6] = uuid_6; uuid_struct[7] = uuid_7; \
    uuid_struct[8] = uuid_8; uuid_struct[9] = uuid_9; uuid_struct[10] = uuid_10; uuid_struct[11] = uuid_11; \
    uuid_struct[12] = uuid_12; uuid_struct[13] = uuid_13; uuid_struct[14] = uuid_14; uuid_struct[15] = uuid_15; \
}while(0)

#define COPY_CONFIGDATA_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0x00,0x00,0xaa,0xaa,0xcc,0x7a,0x48,0x2a,0x98,0x4a,0x7f,0x2e,0xd5,0xb3,0xe5,0x8f)
#define COPY_DELAICHARAC_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0xaa,0xab,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)
#define COPY_ACQCHARAC_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0xaa,0xac,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)
#define COPY_IADATA_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0x00,0x00,0xbb,0xbb,0xcc,0x7a,0x48,0x2a,0x98,0x4a,0x7f,0x2e,0xd5,0xb3,0xe5,0x8f)
#define COPY_IACHARAC_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0xbb,0xba,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)
#define COPY_ACCDATA_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0x00,0x00,0xcc,0xcc,0xcc,0x7a,0x48,0x2a,0x98,0x4a,0x7f,0x2e,0xd5,0xb3,0xe5,0x8f)
#define COPY_ACCXCAHRAC_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0xcc,0xca,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)
#define COPY_ACCYCHARAC_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0xcc,0xcb,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)
#define COPY_ACCZCHARAC_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0xcc,0xcd,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)
#define COPY_GYRDATA_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0x00,0x00,0xdd,0xdd,0xcc,0x7a,0x48,0x2a,0x98,0x4a,0x7f,0x2e,0xd5,0xb3,0xe5,0x8f)
#define COPY_GYRXCHARAC_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0xdd,0xda,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)
#define COPY_GYRYCHARAC_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0xdd,0xdb,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)
#define COPY_GYRZCHARAC_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0xdd,0xdc,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)
#define COPY_TEMPDATA_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0x00,0x00,0xee,0xee,0xcc,0x7a,0x48,0x2a,0x98,0x4a,0x7f,0x2e,0xd5,0xb3,0xe5,0x8f)
#define COPY_TEMPCHARAC_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0xee,0xea,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)

/* USER CODE BEGIN PF */

/* USER CODE END PF */

/**
 * @brief  Event handler
 * @param  Event: Address of the buffer holding the Event
 * @retval Ack: Return whether the Event has been managed or not
 */
static SVCCTL_EvtAckStatus_t Custom_STM_Event_Handler(void *Event)
{
  SVCCTL_EvtAckStatus_t return_value;
  hci_event_pckt *event_pckt;
  evt_blecore_aci *blecore_evt;
  aci_gatt_attribute_modified_event_rp0 *attribute_modified;
  aci_gatt_notification_complete_event_rp0    *notification_complete;
  Custom_STM_App_Notification_evt_t     Notification;
  /* USER CODE BEGIN Custom_STM_Event_Handler_1 */

  /* USER CODE END Custom_STM_Event_Handler_1 */

  return_value = SVCCTL_EvtNotAck;
  event_pckt = (hci_event_pckt *)(((hci_uart_pckt*)Event)->data);

  switch (event_pckt->evt)
  {
    case HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE:
      blecore_evt = (evt_blecore_aci*)event_pckt->data;
      switch (blecore_evt->ecode)
      {
        case ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE:
          /* USER CODE BEGIN EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_BEGIN */

          /* USER CODE END EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_BEGIN */
          attribute_modified = (aci_gatt_attribute_modified_event_rp0*)blecore_evt->data;
          if (attribute_modified->Attr_Handle == (CustomContext.CustomIacHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_1 */

            /* USER CODE END CUSTOM_STM_Service_2_Char_1 */
            switch (attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_1_attribute_modified */

              /* USER CODE END CUSTOM_STM_Service_2_Char_1_attribute_modified */

              /* Disabled Notification management */
              case (!(COMSVC_Notification)):
                /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_1_Disabled_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_2_Char_1_Disabled_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_IAC_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_1_Disabled_END */

                /* USER CODE END CUSTOM_STM_Service_2_Char_1_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_1_COMSVC_Notification_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_2_Char_1_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_IAC_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_1_COMSVC_Notification_END */

                /* USER CODE END CUSTOM_STM_Service_2_Char_1_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_1_default */

                /* USER CODE END CUSTOM_STM_Service_2_Char_1_default */
              break;
            }
          }  /* if (attribute_modified->Attr_Handle == (CustomContext.CustomIacHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/

          else if (attribute_modified->Attr_Handle == (CustomContext.CustomAccxHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1 */

            /* USER CODE END CUSTOM_STM_Service_3_Char_1 */
            switch (attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1_attribute_modified */

              /* USER CODE END CUSTOM_STM_Service_3_Char_1_attribute_modified */

              /* Disabled Notification management */
              case (!(COMSVC_Notification)):
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1_Disabled_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_3_Char_1_Disabled_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_ACCX_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1_Disabled_END */

                /* USER CODE END CUSTOM_STM_Service_3_Char_1_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1_COMSVC_Notification_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_3_Char_1_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_ACCX_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1_COMSVC_Notification_END */

                /* USER CODE END CUSTOM_STM_Service_3_Char_1_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1_default */

                /* USER CODE END CUSTOM_STM_Service_3_Char_1_default */
              break;
            }
          }  /* if (attribute_modified->Attr_Handle == (CustomContext.CustomAccxHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/

          else if (attribute_modified->Attr_Handle == (CustomContext.CustomAccyHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_2 */

            /* USER CODE END CUSTOM_STM_Service_3_Char_2 */
            switch (attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_2_attribute_modified */

              /* USER CODE END CUSTOM_STM_Service_3_Char_2_attribute_modified */

              /* Disabled Notification management */
              case (!(COMSVC_Notification)):
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_2_Disabled_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_3_Char_2_Disabled_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_ACCY_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_2_Disabled_END */

                /* USER CODE END CUSTOM_STM_Service_3_Char_2_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_2_COMSVC_Notification_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_3_Char_2_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_ACCY_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_2_COMSVC_Notification_END */

                /* USER CODE END CUSTOM_STM_Service_3_Char_2_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_2_default */

                /* USER CODE END CUSTOM_STM_Service_3_Char_2_default */
              break;
            }
          }  /* if (attribute_modified->Attr_Handle == (CustomContext.CustomAccyHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/

          else if (attribute_modified->Attr_Handle == (CustomContext.CustomAcczHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_3 */

            /* USER CODE END CUSTOM_STM_Service_3_Char_3 */
            switch (attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_3_attribute_modified */

              /* USER CODE END CUSTOM_STM_Service_3_Char_3_attribute_modified */

              /* Disabled Notification management */
              case (!(COMSVC_Notification)):
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_3_Disabled_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_3_Char_3_Disabled_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_ACCZ_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_3_Disabled_END */

                /* USER CODE END CUSTOM_STM_Service_3_Char_3_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_3_COMSVC_Notification_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_3_Char_3_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_ACCZ_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_3_COMSVC_Notification_END */

                /* USER CODE END CUSTOM_STM_Service_3_Char_3_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_3_default */

                /* USER CODE END CUSTOM_STM_Service_3_Char_3_default */
              break;
            }
          }  /* if (attribute_modified->Attr_Handle == (CustomContext.CustomAcczHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/

          else if (attribute_modified->Attr_Handle == (CustomContext.CustomGyrxHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_1 */

            /* USER CODE END CUSTOM_STM_Service_4_Char_1 */
            switch (attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_1_attribute_modified */

              /* USER CODE END CUSTOM_STM_Service_4_Char_1_attribute_modified */

              /* Disabled Notification management */
              case (!(COMSVC_Notification)):
                /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_1_Disabled_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_4_Char_1_Disabled_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_GYRX_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_1_Disabled_END */

                /* USER CODE END CUSTOM_STM_Service_4_Char_1_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_1_COMSVC_Notification_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_4_Char_1_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_GYRX_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_1_COMSVC_Notification_END */

                /* USER CODE END CUSTOM_STM_Service_4_Char_1_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_1_default */

                /* USER CODE END CUSTOM_STM_Service_4_Char_1_default */
              break;
            }
          }  /* if (attribute_modified->Attr_Handle == (CustomContext.CustomGyrxHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/

          else if (attribute_modified->Attr_Handle == (CustomContext.CustomGyryHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_2 */

            /* USER CODE END CUSTOM_STM_Service_4_Char_2 */
            switch (attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_2_attribute_modified */

              /* USER CODE END CUSTOM_STM_Service_4_Char_2_attribute_modified */

              /* Disabled Notification management */
              case (!(COMSVC_Notification)):
                /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_2_Disabled_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_4_Char_2_Disabled_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_GYRY_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_2_Disabled_END */

                /* USER CODE END CUSTOM_STM_Service_4_Char_2_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_2_COMSVC_Notification_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_4_Char_2_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_GYRY_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_2_COMSVC_Notification_END */

                /* USER CODE END CUSTOM_STM_Service_4_Char_2_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_2_default */

                /* USER CODE END CUSTOM_STM_Service_4_Char_2_default */
              break;
            }
          }  /* if (attribute_modified->Attr_Handle == (CustomContext.CustomGyryHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/

          else if (attribute_modified->Attr_Handle == (CustomContext.CustomGyrzHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_3 */

            /* USER CODE END CUSTOM_STM_Service_4_Char_3 */
            switch (attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_3_attribute_modified */

              /* USER CODE END CUSTOM_STM_Service_4_Char_3_attribute_modified */

              /* Disabled Notification management */
              case (!(COMSVC_Notification)):
                /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_3_Disabled_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_4_Char_3_Disabled_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_GYRZ_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_3_Disabled_END */

                /* USER CODE END CUSTOM_STM_Service_4_Char_3_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_3_COMSVC_Notification_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_4_Char_3_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_GYRZ_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_3_COMSVC_Notification_END */

                /* USER CODE END CUSTOM_STM_Service_4_Char_3_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_4_Char_3_default */

                /* USER CODE END CUSTOM_STM_Service_4_Char_3_default */
              break;
            }
          }  /* if (attribute_modified->Attr_Handle == (CustomContext.CustomGyrzHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/

          else if (attribute_modified->Attr_Handle == (CustomContext.CustomTempcHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_5_Char_1 */

            /* USER CODE END CUSTOM_STM_Service_5_Char_1 */
            switch (attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_5_Char_1_attribute_modified */

              /* USER CODE END CUSTOM_STM_Service_5_Char_1_attribute_modified */

              /* Disabled Notification management */
              case (!(COMSVC_Notification)):
                /* USER CODE BEGIN CUSTOM_STM_Service_5_Char_1_Disabled_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_5_Char_1_Disabled_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_TEMPC_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_5_Char_1_Disabled_END */

                /* USER CODE END CUSTOM_STM_Service_5_Char_1_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_5_Char_1_COMSVC_Notification_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_5_Char_1_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_TEMPC_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_5_Char_1_COMSVC_Notification_END */

                /* USER CODE END CUSTOM_STM_Service_5_Char_1_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_5_Char_1_default */

                /* USER CODE END CUSTOM_STM_Service_5_Char_1_default */
              break;
            }
          }  /* if (attribute_modified->Attr_Handle == (CustomContext.CustomTempcHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/

          else if (attribute_modified->Attr_Handle == (CustomContext.CustomDelaiHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            Notification.Custom_Evt_Opcode = CUSTOM_STM_DELAI_WRITE_NO_RESP_EVT;
            Notification.DataTransfered.Length=attribute_modified->Attr_Data_Length;
            Notification.DataTransfered.pPayload=attribute_modified->Attr_Data;
            Custom_STM_App_Notification(&Notification);
            /* USER CODE END CUSTOM_STM_Service_1_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
          } /* if (attribute_modified->Attr_Handle == (CustomContext.CustomDelaiHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/
          else if (attribute_modified->Attr_Handle == (CustomContext.CustomAcqHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            Notification.Custom_Evt_Opcode = CUSTOM_STM_ACQ_WRITE_NO_RESP_EVT;
            Notification.DataTransfered.Length=attribute_modified->Attr_Data_Length;
            Notification.DataTransfered.pPayload=attribute_modified->Attr_Data;
            Custom_STM_App_Notification(&Notification);
            /* USER CODE END CUSTOM_STM_Service_1_Char_2_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
          } /* if (attribute_modified->Attr_Handle == (CustomContext.CustomAcqHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/
          /* USER CODE BEGIN EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_END */

          /* USER CODE END EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_END */
          break;

        case ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE :
          /* USER CODE BEGIN EVT_BLUE_GATT_READ_PERMIT_REQ_BEGIN */

          /* USER CODE END EVT_BLUE_GATT_READ_PERMIT_REQ_BEGIN */
          /* USER CODE BEGIN EVT_BLUE_GATT_READ_PERMIT_REQ_END */

          /* USER CODE END EVT_BLUE_GATT_READ_PERMIT_REQ_END */
          break;

        case ACI_GATT_WRITE_PERMIT_REQ_VSEVT_CODE:
          /* USER CODE BEGIN EVT_BLUE_GATT_WRITE_PERMIT_REQ_BEGIN */

          /* USER CODE END EVT_BLUE_GATT_WRITE_PERMIT_REQ_BEGIN */
          /* USER CODE BEGIN EVT_BLUE_GATT_WRITE_PERMIT_REQ_END */

          /* USER CODE END EVT_BLUE_GATT_WRITE_PERMIT_REQ_END */
          break;

		case ACI_GATT_NOTIFICATION_COMPLETE_VSEVT_CODE:
        {
          /* USER CODE BEGIN EVT_BLUE_GATT_NOTIFICATION_COMPLETE_BEGIN */

          /* USER CODE END EVT_BLUE_GATT_NOTIFICATION_COMPLETE_BEGIN */
          notification_complete = (aci_gatt_notification_complete_event_rp0*)blecore_evt->data;
          Notification.Custom_Evt_Opcode = CUSTOM_STM_NOTIFICATION_COMPLETE_EVT;
          Notification.AttrHandle = notification_complete->Attr_Handle;
          Custom_STM_App_Notification(&Notification);
          /* USER CODE BEGIN EVT_BLUE_GATT_NOTIFICATION_COMPLETE_END */

          /* USER CODE END EVT_BLUE_GATT_NOTIFICATION_COMPLETE_END */
          break;
        }

        /* USER CODE BEGIN BLECORE_EVT */

        /* USER CODE END BLECORE_EVT */
        default:
          /* USER CODE BEGIN EVT_DEFAULT */

          /* USER CODE END EVT_DEFAULT */
          break;
      }
      /* USER CODE BEGIN EVT_VENDOR*/

      /* USER CODE END EVT_VENDOR*/
      break; /* HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE */

      /* USER CODE BEGIN EVENT_PCKT_CASES*/

      /* USER CODE END EVENT_PCKT_CASES*/

    default:
      /* USER CODE BEGIN EVENT_PCKT*/

      /* USER CODE END EVENT_PCKT*/
      break;
  }

  /* USER CODE BEGIN Custom_STM_Event_Handler_2 */

  /* USER CODE END Custom_STM_Event_Handler_2 */

  return(return_value);
}/* end Custom_STM_Event_Handler */

/* Public functions ----------------------------------------------------------*/

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void SVCCTL_InitCustomSvc(void)
{

  Char_UUID_t  uuid;
  tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
  uint8_t max_attr_record;

  /* USER CODE BEGIN SVCCTL_InitCustomSvc_1 */

  /* USER CODE END SVCCTL_InitCustomSvc_1 */

  /**
   *  Register the event handler to the BLE controller
   */
  SVCCTL_RegisterSvcHandler(Custom_STM_Event_Handler);

  /**
   *          configdata
   *
   * Max_Attribute_Records = 1 + 2*2 + 1*no_of_char_with_notify_or_indicate_property + 1*no_of_char_with_broadcast_property
   * service_max_attribute_record = 1 for configdata +
   *                                2 for delaicharac +
   *                                2 for acqcharac +
   *                              = 5
   *
   * This value doesn't take into account number of descriptors manually added
   * In case of descriptors added, please update the max_attr_record value accordingly in the next SVCCTL_InitService User Section
   */
  max_attr_record = 5;

  /* USER CODE BEGIN SVCCTL_InitService */
  /* max_attr_record to be updated if descriptors have been added */

  /* USER CODE END SVCCTL_InitService */

  COPY_CONFIGDATA_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_service(UUID_TYPE_128,
                             (Service_UUID_t *) &uuid,
                             PRIMARY_SERVICE,
                             max_attr_record,
                             &(CustomContext.CustomConfigHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_service command: config, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_service command: config \n\r");
  }

  /**
   *  delaicharac
   */
  COPY_DELAICHARAC_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomConfigHdle,
                          UUID_TYPE_128, &uuid,
                          SizeDelai,
                          CHAR_PROP_READ | CHAR_PROP_WRITE_WITHOUT_RESP,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CustomContext.CustomDelaiHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : DELAI, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : DELAI \n\r");
  }

  /* USER CODE BEGIN SVCCTL_Init_Service1_Char1 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_Init_Service1_Char1 */
  /**
   *  acqcharac
   */
  COPY_ACQCHARAC_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomConfigHdle,
                          UUID_TYPE_128, &uuid,
                          SizeAcq,
                          CHAR_PROP_READ | CHAR_PROP_WRITE_WITHOUT_RESP,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CustomContext.CustomAcqHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : ACQ, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : ACQ \n\r");
  }

  /* USER CODE BEGIN SVCCTL_Init_Service1_Char2 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_Init_Service1_Char2 */

  /**
   *          iadata
   *
   * Max_Attribute_Records = 1 + 2*1 + 1*no_of_char_with_notify_or_indicate_property + 1*no_of_char_with_broadcast_property
   * service_max_attribute_record = 1 for iadata +
   *                                2 for iacharac +
   *                                1 for iacharac configuration descriptor +
   *                              = 4
   *
   * This value doesn't take into account number of descriptors manually added
   * In case of descriptors added, please update the max_attr_record value accordingly in the next SVCCTL_InitService User Section
   */
  max_attr_record = 4;

  /* USER CODE BEGIN SVCCTL_InitService */
  /* max_attr_record to be updated if descriptors have been added */

  /* USER CODE END SVCCTL_InitService */

  COPY_IADATA_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_service(UUID_TYPE_128,
                             (Service_UUID_t *) &uuid,
                             PRIMARY_SERVICE,
                             max_attr_record,
                             &(CustomContext.CustomIaHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_service command: ia, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_service command: ia \n\r");
  }

  /**
   *  iacharac
   */
  COPY_IACHARAC_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomIaHdle,
                          UUID_TYPE_128, &uuid,
                          SizeIac,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_NOTIFICATION_COMPLETION,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CustomContext.CustomIacHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : IAC, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : IAC \n\r");
  }

  /* USER CODE BEGIN SVCCTL_Init_Service2_Char1 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_Init_Service2_Char1 */

  /**
   *          accdata
   *
   * Max_Attribute_Records = 1 + 2*3 + 1*no_of_char_with_notify_or_indicate_property + 1*no_of_char_with_broadcast_property
   * service_max_attribute_record = 1 for accdata +
   *                                2 for accxcahrac +
   *                                2 for accycharac +
   *                                2 for acczcharac +
   *                                1 for accxcahrac configuration descriptor +
   *                                1 for accycharac configuration descriptor +
   *                                1 for acczcharac configuration descriptor +
   *                              = 10
   *
   * This value doesn't take into account number of descriptors manually added
   * In case of descriptors added, please update the max_attr_record value accordingly in the next SVCCTL_InitService User Section
   */
  max_attr_record = 10;

  /* USER CODE BEGIN SVCCTL_InitService */
  /* max_attr_record to be updated if descriptors have been added */

  /* USER CODE END SVCCTL_InitService */

  COPY_ACCDATA_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_service(UUID_TYPE_128,
                             (Service_UUID_t *) &uuid,
                             PRIMARY_SERVICE,
                             max_attr_record,
                             &(CustomContext.CustomAccHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_service command: acc, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_service command: acc \n\r");
  }

  /**
   *  accxcahrac
   */
  COPY_ACCXCAHRAC_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomAccHdle,
                          UUID_TYPE_128, &uuid,
                          SizeAccx,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CustomContext.CustomAccxHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : ACCX, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : ACCX \n\r");
  }

  /* USER CODE BEGIN SVCCTL_Init_Service3_Char1 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_Init_Service3_Char1 */
  /**
   *  accycharac
   */
  COPY_ACCYCHARAC_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomAccHdle,
                          UUID_TYPE_128, &uuid,
                          SizeAccy,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_NOTIFICATION_COMPLETION,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CustomContext.CustomAccyHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : ACCY, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : ACCY \n\r");
  }

  /* USER CODE BEGIN SVCCTL_Init_Service3_Char2 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_Init_Service3_Char2 */
  /**
   *  acczcharac
   */
  COPY_ACCZCHARAC_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomAccHdle,
                          UUID_TYPE_128, &uuid,
                          SizeAccz,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_NOTIFICATION_COMPLETION,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CustomContext.CustomAcczHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : ACCZ, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : ACCZ \n\r");
  }

  /* USER CODE BEGIN SVCCTL_Init_Service3_Char3 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_Init_Service3_Char3 */

  /**
   *          gyrdata
   *
   * Max_Attribute_Records = 1 + 2*3 + 1*no_of_char_with_notify_or_indicate_property + 1*no_of_char_with_broadcast_property
   * service_max_attribute_record = 1 for gyrdata +
   *                                2 for gyrxcharac +
   *                                2 for gyrycharac +
   *                                2 for gyrzcharac +
   *                                1 for gyrxcharac configuration descriptor +
   *                                1 for gyrycharac configuration descriptor +
   *                                1 for gyrzcharac configuration descriptor +
   *                              = 10
   *
   * This value doesn't take into account number of descriptors manually added
   * In case of descriptors added, please update the max_attr_record value accordingly in the next SVCCTL_InitService User Section
   */
  max_attr_record = 10;

  /* USER CODE BEGIN SVCCTL_InitService */
  /* max_attr_record to be updated if descriptors have been added */

  /* USER CODE END SVCCTL_InitService */

  COPY_GYRDATA_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_service(UUID_TYPE_128,
                             (Service_UUID_t *) &uuid,
                             PRIMARY_SERVICE,
                             max_attr_record,
                             &(CustomContext.CustomGyrHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_service command: gyr, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_service command: gyr \n\r");
  }

  /**
   *  gyrxcharac
   */
  COPY_GYRXCHARAC_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomGyrHdle,
                          UUID_TYPE_128, &uuid,
                          SizeGyrx,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_NOTIFICATION_COMPLETION,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CustomContext.CustomGyrxHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : GYRX, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : GYRX \n\r");
  }

  /* USER CODE BEGIN SVCCTL_Init_Service4_Char1 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_Init_Service4_Char1 */
  /**
   *  gyrycharac
   */
  COPY_GYRYCHARAC_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomGyrHdle,
                          UUID_TYPE_128, &uuid,
                          SizeGyry,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_NOTIFICATION_COMPLETION,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CustomContext.CustomGyryHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : GYRY, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : GYRY \n\r");
  }

  /* USER CODE BEGIN SVCCTL_Init_Service4_Char2 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_Init_Service4_Char2 */
  /**
   *  gyrzcharac
   */
  COPY_GYRZCHARAC_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomGyrHdle,
                          UUID_TYPE_128, &uuid,
                          SizeGyrz,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_NOTIFICATION_COMPLETION,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CustomContext.CustomGyrzHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : GYRZ, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : GYRZ \n\r");
  }

  /* USER CODE BEGIN SVCCTL_Init_Service4_Char3 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_Init_Service4_Char3 */

  /**
   *          tempdata
   *
   * Max_Attribute_Records = 1 + 2*1 + 1*no_of_char_with_notify_or_indicate_property + 1*no_of_char_with_broadcast_property
   * service_max_attribute_record = 1 for tempdata +
   *                                2 for tempcharac +
   *                                1 for tempcharac configuration descriptor +
   *                              = 4
   *
   * This value doesn't take into account number of descriptors manually added
   * In case of descriptors added, please update the max_attr_record value accordingly in the next SVCCTL_InitService User Section
   */
  max_attr_record = 4;

  /* USER CODE BEGIN SVCCTL_InitService */
  /* max_attr_record to be updated if descriptors have been added */

  /* USER CODE END SVCCTL_InitService */

  COPY_TEMPDATA_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_service(UUID_TYPE_128,
                             (Service_UUID_t *) &uuid,
                             PRIMARY_SERVICE,
                             max_attr_record,
                             &(CustomContext.CustomTempHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_service command: temp, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_service command: temp \n\r");
  }

  /**
   *  tempcharac
   */
  COPY_TEMPCHARAC_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomTempHdle,
                          UUID_TYPE_128, &uuid,
                          SizeTempc,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_NOTIFICATION_COMPLETION,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CustomContext.CustomTempcHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : TEMPC, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : TEMPC \n\r");
  }

  /* USER CODE BEGIN SVCCTL_Init_Service5_Char1 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_Init_Service5_Char1 */

  /* USER CODE BEGIN SVCCTL_InitCustomSvc_2 */

  /* USER CODE END SVCCTL_InitCustomSvc_2 */

  return;
}

/**
 * @brief  Characteristic update
 * @param  CharOpcode: Characteristic identifier
 * @param  Service_Instance: Instance of the service to which the characteristic belongs
 *
 */
tBleStatus Custom_STM_App_Update_Char(Custom_STM_Char_Opcode_t CharOpcode, uint8_t *pPayload)
{
  tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
  /* USER CODE BEGIN Custom_STM_App_Update_Char_1 */

  /* USER CODE END Custom_STM_App_Update_Char_1 */

  switch (CharOpcode)
  {

    case CUSTOM_STM_DELAI:
      ret = aci_gatt_update_char_value(CustomContext.CustomConfigHdle,
                                       CustomContext.CustomDelaiHdle,
                                       0, /* charValOffset */
                                       SizeDelai, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value DELAI command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value DELAI command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_1_Char_1*/
      if(pPayload[0] == 0x01) {
          	  delai = 100;
      }
      else if(pPayload[0] == 0x02){
    	  delai = 200;
      }
      else if(pPayload[0] == 0x03){
    	  delai = 300;
      }
      else if(pPayload[0] == 0x04){
    	  delai = 400;
      }
      else if(pPayload[0] == 0x05){
    	  delai = 500;
      }
      else if(pPayload[0] == 0x06){
    	  delai = 600;
      }
      else if(pPayload[0] == 0x07){
    	  delai = 700;
      }
      else if(pPayload[0] == 0x08){
    	  delai = 800;
      }
      else if(pPayload[0] == 0x09){
    	  delai = 900;
      }


      /* USER CODE END CUSTOM_STM_App_Update_Service_1_Char_1*/
      break;

    case CUSTOM_STM_ACQ:
      ret = aci_gatt_update_char_value(CustomContext.CustomConfigHdle,
                                       CustomContext.CustomAcqHdle,
                                       0, /* charValOffset */
                                       SizeAcq, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value ACQ command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value ACQ command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_1_Char_2*/
      if(pPayload[0] == 0x10) {
          	  acq = 1;
            }
      else if (pPayload[0] == 0x20){
    	  acq = 0;
      }
      /* USER CODE END CUSTOM_STM_App_Update_Service_1_Char_2*/
      break;

    case CUSTOM_STM_IAC:
      ret = aci_gatt_update_char_value(CustomContext.CustomIaHdle,
                                       CustomContext.CustomIacHdle,
                                       0, /* charValOffset */
                                       SizeIac, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value IAC command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value IAC command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_2_Char_1*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_2_Char_1*/
      break;

    case CUSTOM_STM_ACCX:
      ret = aci_gatt_update_char_value(CustomContext.CustomAccHdle,
                                       CustomContext.CustomAccxHdle,
                                       0, /* charValOffset */
                                       SizeAccx, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value ACCX command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value ACCX command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_3_Char_1*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_3_Char_1*/
      break;

    case CUSTOM_STM_ACCY:
      ret = aci_gatt_update_char_value(CustomContext.CustomAccHdle,
                                       CustomContext.CustomAccyHdle,
                                       0, /* charValOffset */
                                       SizeAccy, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value ACCY command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value ACCY command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_3_Char_2*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_3_Char_2*/
      break;

    case CUSTOM_STM_ACCZ:
      ret = aci_gatt_update_char_value(CustomContext.CustomAccHdle,
                                       CustomContext.CustomAcczHdle,
                                       0, /* charValOffset */
                                       SizeAccz, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value ACCZ command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value ACCZ command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_3_Char_3*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_3_Char_3*/
      break;

    case CUSTOM_STM_GYRX:
      ret = aci_gatt_update_char_value(CustomContext.CustomGyrHdle,
                                       CustomContext.CustomGyrxHdle,
                                       0, /* charValOffset */
                                       SizeGyrx, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value GYRX command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value GYRX command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_4_Char_1*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_4_Char_1*/
      break;

    case CUSTOM_STM_GYRY:
      ret = aci_gatt_update_char_value(CustomContext.CustomGyrHdle,
                                       CustomContext.CustomGyryHdle,
                                       0, /* charValOffset */
                                       SizeGyry, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value GYRY command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value GYRY command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_4_Char_2*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_4_Char_2*/
      break;

    case CUSTOM_STM_GYRZ:
      ret = aci_gatt_update_char_value(CustomContext.CustomGyrHdle,
                                       CustomContext.CustomGyrzHdle,
                                       0, /* charValOffset */
                                       SizeGyrz, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value GYRZ command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value GYRZ command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_4_Char_3*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_4_Char_3*/
      break;

    case CUSTOM_STM_TEMPC:
      ret = aci_gatt_update_char_value(CustomContext.CustomTempHdle,
                                       CustomContext.CustomTempcHdle,
                                       0, /* charValOffset */
                                       SizeTempc, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value TEMPC command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value TEMPC command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_5_Char_1*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_5_Char_1*/
      break;

    default:
      break;
  }

  /* USER CODE BEGIN Custom_STM_App_Update_Char_2 */

  /* USER CODE END Custom_STM_App_Update_Char_2 */

  return ret;
}

/**
 * @brief  Characteristic update
 * @param  CharOpcode: Characteristic identifier
 * @param  pPayload: Characteristic value
 * @param  size: Length of the characteristic value in octets
 *
 */
tBleStatus Custom_STM_App_Update_Char_Variable_Length(Custom_STM_Char_Opcode_t CharOpcode, uint8_t *pPayload, uint8_t size)
{
  tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
  /* USER CODE BEGIN Custom_STM_App_Update_Char_Variable_Length_1 */

  /* USER CODE END Custom_STM_App_Update_Char_Variable_Length_1 */

  switch (CharOpcode)
  {

    case CUSTOM_STM_DELAI:
      ret = aci_gatt_update_char_value(CustomContext.CustomConfigHdle,
                                       CustomContext.CustomDelaiHdle,
                                       0, /* charValOffset */
                                       size, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value DELAI command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value DELAI command\n\r");
      }
      /* USER CODE BEGIN Custom_STM_App_Update_Char_Variable_Length_Service_1_Char_1*/

      /* USER CODE END Custom_STM_App_Update_Char_Variable_Length_Service_1_Char_1*/
      break;

    case CUSTOM_STM_ACQ:
      ret = aci_gatt_update_char_value(CustomContext.CustomConfigHdle,
                                       CustomContext.CustomAcqHdle,
                                       0, /* charValOffset */
                                       size, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value ACQ command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value ACQ command\n\r");
      }
      /* USER CODE BEGIN Custom_STM_App_Update_Char_Variable_Length_Service_1_Char_2*/

      /* USER CODE END Custom_STM_App_Update_Char_Variable_Length_Service_1_Char_2*/
      break;

    case CUSTOM_STM_IAC:
      ret = aci_gatt_update_char_value(CustomContext.CustomIaHdle,
                                       CustomContext.CustomIacHdle,
                                       0, /* charValOffset */
                                       size, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value IAC command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value IAC command\n\r");
      }
      /* USER CODE BEGIN Custom_STM_App_Update_Char_Variable_Length_Service_2_Char_1*/

      /* USER CODE END Custom_STM_App_Update_Char_Variable_Length_Service_2_Char_1*/
      break;

    case CUSTOM_STM_ACCX:
      ret = aci_gatt_update_char_value(CustomContext.CustomAccHdle,
                                       CustomContext.CustomAccxHdle,
                                       0, /* charValOffset */
                                       size, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value ACCX command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value ACCX command\n\r");
      }
      /* USER CODE BEGIN Custom_STM_App_Update_Char_Variable_Length_Service_3_Char_1*/

      /* USER CODE END Custom_STM_App_Update_Char_Variable_Length_Service_3_Char_1*/
      break;

    case CUSTOM_STM_ACCY:
      ret = aci_gatt_update_char_value(CustomContext.CustomAccHdle,
                                       CustomContext.CustomAccyHdle,
                                       0, /* charValOffset */
                                       size, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value ACCY command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value ACCY command\n\r");
      }
      /* USER CODE BEGIN Custom_STM_App_Update_Char_Variable_Length_Service_3_Char_2*/

      /* USER CODE END Custom_STM_App_Update_Char_Variable_Length_Service_3_Char_2*/
      break;

    case CUSTOM_STM_ACCZ:
      ret = aci_gatt_update_char_value(CustomContext.CustomAccHdle,
                                       CustomContext.CustomAcczHdle,
                                       0, /* charValOffset */
                                       size, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value ACCZ command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value ACCZ command\n\r");
      }
      /* USER CODE BEGIN Custom_STM_App_Update_Char_Variable_Length_Service_3_Char_3*/

      /* USER CODE END Custom_STM_App_Update_Char_Variable_Length_Service_3_Char_3*/
      break;

    case CUSTOM_STM_GYRX:
      ret = aci_gatt_update_char_value(CustomContext.CustomGyrHdle,
                                       CustomContext.CustomGyrxHdle,
                                       0, /* charValOffset */
                                       size, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value GYRX command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value GYRX command\n\r");
      }
      /* USER CODE BEGIN Custom_STM_App_Update_Char_Variable_Length_Service_4_Char_1*/

      /* USER CODE END Custom_STM_App_Update_Char_Variable_Length_Service_4_Char_1*/
      break;

    case CUSTOM_STM_GYRY:
      ret = aci_gatt_update_char_value(CustomContext.CustomGyrHdle,
                                       CustomContext.CustomGyryHdle,
                                       0, /* charValOffset */
                                       size, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value GYRY command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value GYRY command\n\r");
      }
      /* USER CODE BEGIN Custom_STM_App_Update_Char_Variable_Length_Service_4_Char_2*/

      /* USER CODE END Custom_STM_App_Update_Char_Variable_Length_Service_4_Char_2*/
      break;

    case CUSTOM_STM_GYRZ:
      ret = aci_gatt_update_char_value(CustomContext.CustomGyrHdle,
                                       CustomContext.CustomGyrzHdle,
                                       0, /* charValOffset */
                                       size, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value GYRZ command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value GYRZ command\n\r");
      }
      /* USER CODE BEGIN Custom_STM_App_Update_Char_Variable_Length_Service_4_Char_3*/

      /* USER CODE END Custom_STM_App_Update_Char_Variable_Length_Service_4_Char_3*/
      break;

    case CUSTOM_STM_TEMPC:
      ret = aci_gatt_update_char_value(CustomContext.CustomTempHdle,
                                       CustomContext.CustomTempcHdle,
                                       0, /* charValOffset */
                                       size, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value TEMPC command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value TEMPC command\n\r");
      }
      /* USER CODE BEGIN Custom_STM_App_Update_Char_Variable_Length_Service_5_Char_1*/

      /* USER CODE END Custom_STM_App_Update_Char_Variable_Length_Service_5_Char_1*/
      break;

    default:
      break;
  }

  /* USER CODE BEGIN Custom_STM_App_Update_Char_Variable_Length_2 */

  /* USER CODE END Custom_STM_App_Update_Char_Variable_Length_2 */

  return ret;
}

/**
 * @brief  Characteristic update
 * @param  Connection_Handle
 * @param  CharOpcode: Characteristic identifier
 * @param  pPayload: Characteristic value
 *
 */
tBleStatus Custom_STM_App_Update_Char_Ext(uint16_t Connection_Handle, Custom_STM_Char_Opcode_t CharOpcode, uint8_t *pPayload)
{
  tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
  /* USER CODE BEGIN Custom_STM_App_Update_Char_Ext_1 */

  /* USER CODE END Custom_STM_App_Update_Char_Ext_1 */

  switch (CharOpcode)
  {

    case CUSTOM_STM_DELAI:
      /* USER CODE BEGIN Updated_Length_Service_1_Char_1*/

      /* USER CODE END Updated_Length_Service_1_Char_1*/
	  Generic_STM_App_Update_Char_Ext(Connection_Handle, CustomContext.CustomConfigHdle, CustomContext.CustomDelaiHdle, SizeDelai, pPayload);

      break;

    case CUSTOM_STM_ACQ:
      /* USER CODE BEGIN Updated_Length_Service_1_Char_2*/

      /* USER CODE END Updated_Length_Service_1_Char_2*/
	  Generic_STM_App_Update_Char_Ext(Connection_Handle, CustomContext.CustomConfigHdle, CustomContext.CustomAcqHdle, SizeAcq, pPayload);

      break;

    case CUSTOM_STM_IAC:
      /* USER CODE BEGIN Updated_Length_Service_2_Char_1*/

      /* USER CODE END Updated_Length_Service_2_Char_1*/
	  Generic_STM_App_Update_Char_Ext(Connection_Handle, CustomContext.CustomIaHdle, CustomContext.CustomIacHdle, SizeIac, pPayload);

      break;

    case CUSTOM_STM_ACCX:
      /* USER CODE BEGIN Updated_Length_Service_3_Char_1*/

      /* USER CODE END Updated_Length_Service_3_Char_1*/
	  Generic_STM_App_Update_Char_Ext(Connection_Handle, CustomContext.CustomAccHdle, CustomContext.CustomAccxHdle, SizeAccx, pPayload);

      break;

    case CUSTOM_STM_ACCY:
      /* USER CODE BEGIN Updated_Length_Service_3_Char_2*/

      /* USER CODE END Updated_Length_Service_3_Char_2*/
	  Generic_STM_App_Update_Char_Ext(Connection_Handle, CustomContext.CustomAccHdle, CustomContext.CustomAccyHdle, SizeAccy, pPayload);

      break;

    case CUSTOM_STM_ACCZ:
      /* USER CODE BEGIN Updated_Length_Service_3_Char_3*/

      /* USER CODE END Updated_Length_Service_3_Char_3*/
	  Generic_STM_App_Update_Char_Ext(Connection_Handle, CustomContext.CustomAccHdle, CustomContext.CustomAcczHdle, SizeAccz, pPayload);

      break;

    case CUSTOM_STM_GYRX:
      /* USER CODE BEGIN Updated_Length_Service_4_Char_1*/

      /* USER CODE END Updated_Length_Service_4_Char_1*/
	  Generic_STM_App_Update_Char_Ext(Connection_Handle, CustomContext.CustomGyrHdle, CustomContext.CustomGyrxHdle, SizeGyrx, pPayload);

      break;

    case CUSTOM_STM_GYRY:
      /* USER CODE BEGIN Updated_Length_Service_4_Char_2*/

      /* USER CODE END Updated_Length_Service_4_Char_2*/
	  Generic_STM_App_Update_Char_Ext(Connection_Handle, CustomContext.CustomGyrHdle, CustomContext.CustomGyryHdle, SizeGyry, pPayload);

      break;

    case CUSTOM_STM_GYRZ:
      /* USER CODE BEGIN Updated_Length_Service_4_Char_3*/

      /* USER CODE END Updated_Length_Service_4_Char_3*/
	  Generic_STM_App_Update_Char_Ext(Connection_Handle, CustomContext.CustomGyrHdle, CustomContext.CustomGyrzHdle, SizeGyrz, pPayload);

      break;

    case CUSTOM_STM_TEMPC:
      /* USER CODE BEGIN Updated_Length_Service_5_Char_1*/

      /* USER CODE END Updated_Length_Service_5_Char_1*/
	  Generic_STM_App_Update_Char_Ext(Connection_Handle, CustomContext.CustomTempHdle, CustomContext.CustomTempcHdle, SizeTempc, pPayload);

      break;

    default:
      break;
  }

  /* USER CODE BEGIN Custom_STM_App_Update_Char_Ext_2 */

  /* USER CODE END Custom_STM_App_Update_Char_Ext_2 */

  return ret;
}

static tBleStatus Generic_STM_App_Update_Char_Ext(uint16_t ConnectionHandle, uint16_t ServiceHandle, uint16_t CharHandle, uint16_t CharValueLen, uint8_t *pPayload)
{
  tBleStatus ret = BLE_STATUS_INVALID_PARAMS;

  ret = aci_gatt_update_char_value_ext(ConnectionHandle,
                                       ServiceHandle,
                                       CharHandle,
                                       0, /* update type:0 do not notify, 1 notify, 2 indicate */
                                       CharValueLen, /* charValueLen */
                                       0, /* value offset */
                                       243, /* value length */
                                       (uint8_t *)  pPayload);
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_update_char_value_ext command, part 1, result : 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_update_char_value_ext command, part 1\n\r");
  }
  /* USER CODE BEGIN Custom_STM_App_Update_Char_Ext_Service_1_Char_1*/

  if (CharValueLen-243<=243)
  {
    ret = aci_gatt_update_char_value_ext(ConnectionHandle,
                                         ServiceHandle,
                                         CharHandle,
                                         1, /* update type:0 do not notify, 1 notify, 2 indicate */
                                         CharValueLen, /* charValueLen */
                                         243, /* value offset */
                                         CharValueLen-243, /* value length */
                                         (uint8_t *)  ((pPayload)+243));
    if (ret != BLE_STATUS_SUCCESS)
    {
      APP_DBG_MSG("  Fail   : aci_gatt_update_char_value_ext command, part 2, result : 0x%x \n\r", ret);
    }
    else
    {
      APP_DBG_MSG("  Success: aci_gatt_update_char_value_ext command, part 2\n\r");
    }
  }
  else
  {
    ret = aci_gatt_update_char_value_ext(ConnectionHandle,
                                         ServiceHandle,
                                         CharHandle,
                                         0, /* update type:0 do not notify, 1 notify, 2 indicate */
                                         CharValueLen, /* charValueLen */
                                         243, /* value offset */
                                         243, /* value length */
                                         (uint8_t *)  ((pPayload)+243));
    if (ret != BLE_STATUS_SUCCESS)
    {
      APP_DBG_MSG("  Fail   : aci_gatt_update_char_value_ext command, part 3, result : 0x%x \n\r", ret);
    }
    else
    {
      APP_DBG_MSG("  Success: aci_gatt_update_char_value_ext command, part 3\n\r");
    }
    ret = aci_gatt_update_char_value_ext(ConnectionHandle,
                                         ServiceHandle,
                                         CharHandle,
                                         1, /* update type:0 do not notify, 1 notify, 2 indicate */
                                         CharValueLen, /* charValueLen */
                                         243+243, /* value offset */
                                         CharValueLen-243-243, /* value length */
                                         (uint8_t *)  ((pPayload)+243+243));
    if (ret != BLE_STATUS_SUCCESS)
    {
      APP_DBG_MSG("  Fail   : aci_gatt_update_char_value_ext command, part 4, result : 0x%x \n\r", ret);
    }
    else
    {
      APP_DBG_MSG("  Success: aci_gatt_update_char_value_ext command, part 4\n\r");
    }
  }
  return ret;
}

