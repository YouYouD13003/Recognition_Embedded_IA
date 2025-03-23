/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/custom_stm.h
  * @author  MCD Application Team
  * @brief   Header for custom_stm.c module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CUSTOM_STM_H
#define CUSTOM_STM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  /* configdata */
  CUSTOM_STM_DELAI,
  CUSTOM_STM_ACQ,
  /* iadata */
  CUSTOM_STM_IAC,
  /* accdata */
  CUSTOM_STM_ACCX,
  CUSTOM_STM_ACCY,
  CUSTOM_STM_ACCZ,
  /* gyrdata */
  CUSTOM_STM_GYRX,
  CUSTOM_STM_GYRY,
  CUSTOM_STM_GYRZ,
  /* tempdata */
  CUSTOM_STM_TEMPC,
} Custom_STM_Char_Opcode_t;

typedef enum
{
  /* delaicharac */
  CUSTOM_STM_DELAI_READ_EVT,
  CUSTOM_STM_DELAI_WRITE_NO_RESP_EVT,
  /* acqcharac */
  CUSTOM_STM_ACQ_READ_EVT,
  CUSTOM_STM_ACQ_WRITE_NO_RESP_EVT,
  /* iacharac */
  CUSTOM_STM_IAC_READ_EVT,
  CUSTOM_STM_IAC_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_IAC_NOTIFY_DISABLED_EVT,
  /* accxcahrac */
  CUSTOM_STM_ACCX_READ_EVT,
  CUSTOM_STM_ACCX_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_ACCX_NOTIFY_DISABLED_EVT,
  /* accycharac */
  CUSTOM_STM_ACCY_READ_EVT,
  CUSTOM_STM_ACCY_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_ACCY_NOTIFY_DISABLED_EVT,
  /* acczcharac */
  CUSTOM_STM_ACCZ_READ_EVT,
  CUSTOM_STM_ACCZ_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_ACCZ_NOTIFY_DISABLED_EVT,
  /* gyrxcharac */
  CUSTOM_STM_GYRX_READ_EVT,
  CUSTOM_STM_GYRX_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_GYRX_NOTIFY_DISABLED_EVT,
  /* gyrycharac */
  CUSTOM_STM_GYRY_READ_EVT,
  CUSTOM_STM_GYRY_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_GYRY_NOTIFY_DISABLED_EVT,
  /* gyrzcharac */
  CUSTOM_STM_GYRZ_READ_EVT,
  CUSTOM_STM_GYRZ_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_GYRZ_NOTIFY_DISABLED_EVT,
  /* tempcharac */
  CUSTOM_STM_TEMPC_READ_EVT,
  CUSTOM_STM_TEMPC_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_TEMPC_NOTIFY_DISABLED_EVT,
  CUSTOM_STM_NOTIFICATION_COMPLETE_EVT,

  CUSTOM_STM_BOOT_REQUEST_EVT
} Custom_STM_Opcode_evt_t;

typedef struct
{
  uint8_t * pPayload;
  uint8_t   Length;
} Custom_STM_Data_t;

typedef struct
{
  Custom_STM_Opcode_evt_t       Custom_Evt_Opcode;
  Custom_STM_Data_t             DataTransfered;
  uint16_t                      ConnectionHandle;
  uint8_t                       ServiceInstance;
  uint16_t                      AttrHandle;
} Custom_STM_App_Notification_evt_t;

/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
extern uint16_t SizeDelai;
extern uint16_t SizeAcq;
extern uint16_t SizeIac;
extern uint16_t SizeAccx;
extern uint16_t SizeAccy;
extern uint16_t SizeAccz;
extern uint16_t SizeGyrx;
extern uint16_t SizeGyry;
extern uint16_t SizeGyrz;
extern uint16_t SizeTempc;

/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macros -----------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions ------------------------------------------------------- */
void SVCCTL_InitCustomSvc(void);
void Custom_STM_App_Notification(Custom_STM_App_Notification_evt_t *pNotification);
tBleStatus Custom_STM_App_Update_Char(Custom_STM_Char_Opcode_t CharOpcode,  uint8_t *pPayload);
tBleStatus Custom_STM_App_Update_Char_Variable_Length(Custom_STM_Char_Opcode_t CharOpcode, uint8_t *pPayload, uint8_t size);
tBleStatus Custom_STM_App_Update_Char_Ext(uint16_t Connection_Handle, Custom_STM_Char_Opcode_t CharOpcode, uint8_t *pPayload);
/* USER CODE BEGIN EF */

/* USER CODE END EF */

#ifdef __cplusplus
}
#endif

#endif /*CUSTOM_STM_H */
