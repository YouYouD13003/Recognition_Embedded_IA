/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/custom_app.c
  * @author  MCD Application Team
  * @brief   Custom Example Application (Server)
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
#include "main.h"
#include "app_common.h"
#include "dbg_trace.h"
#include "ble.h"
#include "custom_app.h"
#include "custom_stm.h"
#include "stm32_seq.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  /* configdata */
  /* iadata */
  uint8_t               Iac_Notification_Status;
  /* accdata */
  uint8_t               Accx_Notification_Status;
  uint8_t               Accy_Notification_Status;
  uint8_t               Accz_Notification_Status;
  /* gyrdata */
  uint8_t               Gyrx_Notification_Status;
  uint8_t               Gyry_Notification_Status;
  uint8_t               Gyrz_Notification_Status;
  /* tempdata */
  uint8_t               Tempc_Notification_Status;
  /* USER CODE BEGIN CUSTOM_APP_Context_t */
   uint16_t ia_;
   float accx_;
   float accy_;
   float accz_;
   float gyrx_;
   float gyry_;
   float gyrz_;
   float temp_;
   uint16_t swc;

  /* USER CODE END CUSTOM_APP_Context_t */

  uint16_t              ConnectionHandle;
} Custom_App_Context_t;

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private defines ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint16_t ia;
float accx;
float accy;
float accz;
float gyrx;
float gyry;
float gyrz;
float temp;
/* USER CODE END PD */

/* Private macros -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/**
 * START of Section BLE_APP_CONTEXT
 */

static Custom_App_Context_t Custom_App_Context;

/**
 * END of Section BLE_APP_CONTEXT
 */

uint8_t UpdateCharData[512];
uint8_t NotifyCharData[512];
uint16_t Connection_Handle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* configdata */
/* iadata */
static void Custom_Iac_Update_Char(void);
static void Custom_Iac_Send_Notification(void);
/* accdata */
static void Custom_Accx_Update_Char(void);
static void Custom_Accx_Send_Notification(void);
static void Custom_Accy_Update_Char(void);
static void Custom_Accy_Send_Notification(void);
static void Custom_Accz_Update_Char(void);
static void Custom_Accz_Send_Notification(void);
/* gyrdata */
static void Custom_Gyrx_Update_Char(void);
static void Custom_Gyrx_Send_Notification(void);
static void Custom_Gyry_Update_Char(void);
static void Custom_Gyry_Send_Notification(void);
static void Custom_Gyrz_Update_Char(void);
static void Custom_Gyrz_Send_Notification(void);
/* tempdata */
static void Custom_Tempc_Update_Char(void);
static void Custom_Tempc_Send_Notification(void);

/* USER CODE BEGIN PFP */
static void Custom_delai_Update_Char();
static void Custom_acq_Update_Char();
/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void Custom_STM_App_Notification(Custom_STM_App_Notification_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_1 */
	memcpy(UpdateCharData,pNotification->DataTransfered.pPayload,pNotification->DataTransfered.Length);
  /* USER CODE END CUSTOM_STM_App_Notification_1 */
  switch (pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_STM_App_Notification_Custom_Evt_Opcode */
    /* USER CODE END CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

    /* configdata */
    case CUSTOM_STM_DELAI_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_DELAI_READ_EVT */

      /* USER CODE END CUSTOM_STM_DELAI_READ_EVT */
      break;

    case CUSTOM_STM_DELAI_WRITE_NO_RESP_EVT:
      /* USER CODE BEGIN CUSTOM_STM_DELAI_WRITE_NO_RESP_EVT */
    	Custom_delai_Update_Char();
      /* USER CODE END CUSTOM_STM_DELAI_WRITE_NO_RESP_EVT */
      break;

    case CUSTOM_STM_ACQ_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_ACQ_READ_EVT */

      /* USER CODE END CUSTOM_STM_ACQ_READ_EVT */
      break;

    case CUSTOM_STM_ACQ_WRITE_NO_RESP_EVT:
      /* USER CODE BEGIN CUSTOM_STM_ACQ_WRITE_NO_RESP_EVT */
    	Custom_acq_Update_Char();
      /* USER CODE END CUSTOM_STM_ACQ_WRITE_NO_RESP_EVT */
      break;

    /* iadata */
    case CUSTOM_STM_IAC_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_IAC_READ_EVT */

      /* USER CODE END CUSTOM_STM_IAC_READ_EVT */
      break;

    case CUSTOM_STM_IAC_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_IAC_NOTIFY_ENABLED_EVT */
    	Custom_App_Context.Iac_Notification_Status = 1;        /* My_Switch_Char notification status has been enabled */
    	    	Custom_Iac_Send_Notification();
      /* USER CODE END CUSTOM_STM_IAC_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_IAC_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_IAC_NOTIFY_DISABLED_EVT */
    	Custom_App_Context.Iac_Notification_Status = 0;        /* My_Switch_Char notification status has been enabled */
      /* USER CODE END CUSTOM_STM_IAC_NOTIFY_DISABLED_EVT */
      break;

    /* accdata */
    case CUSTOM_STM_ACCX_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_ACCX_READ_EVT */

      /* USER CODE END CUSTOM_STM_ACCX_READ_EVT */
      break;

    case CUSTOM_STM_ACCX_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_ACCX_NOTIFY_ENABLED_EVT */
    	Custom_App_Context.Accx_Notification_Status = 1;        /* My_Switch_Char notification status has been enabled */
    	    	Custom_Accx_Send_Notification();
      /* USER CODE END CUSTOM_STM_ACCX_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_ACCX_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_ACCX_NOTIFY_DISABLED_EVT */
    	Custom_App_Context.Accx_Notification_Status = 0;        /* My_Switch_Char notification status has been enabled */
      /* USER CODE END CUSTOM_STM_ACCX_NOTIFY_DISABLED_EVT */
      break;

    case CUSTOM_STM_ACCY_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_ACCY_READ_EVT */

      /* USER CODE END CUSTOM_STM_ACCY_READ_EVT */
      break;

    case CUSTOM_STM_ACCY_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_ACCY_NOTIFY_ENABLED_EVT */
    	Custom_App_Context.Accy_Notification_Status = 1;        /* My_Switch_Char notification status has been enabled */
    	    	Custom_Accy_Send_Notification();
      /* USER CODE END CUSTOM_STM_ACCY_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_ACCY_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_ACCY_NOTIFY_DISABLED_EVT */
    	Custom_App_Context.Accy_Notification_Status = 0;        /* My_Switch_Char notification status has been enabled */
      /* USER CODE END CUSTOM_STM_ACCY_NOTIFY_DISABLED_EVT */
      break;

    case CUSTOM_STM_ACCZ_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_ACCZ_READ_EVT */

      /* USER CODE END CUSTOM_STM_ACCZ_READ_EVT */
      break;

    case CUSTOM_STM_ACCZ_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_ACCZ_NOTIFY_ENABLED_EVT */
    	Custom_App_Context.Accz_Notification_Status = 1;        /* My_Switch_Char notification status has been enabled */
    	    	Custom_Accz_Send_Notification();
      /* USER CODE END CUSTOM_STM_ACCZ_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_ACCZ_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_ACCZ_NOTIFY_DISABLED_EVT */
    	Custom_App_Context.Accz_Notification_Status = 0;        /* My_Switch_Char notification status has been enabled */
      /* USER CODE END CUSTOM_STM_ACCZ_NOTIFY_DISABLED_EVT */
      break;

    /* gyrdata */
    case CUSTOM_STM_GYRX_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_GYRX_READ_EVT */

      /* USER CODE END CUSTOM_STM_GYRX_READ_EVT */
      break;

    case CUSTOM_STM_GYRX_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_GYRX_NOTIFY_ENABLED_EVT */
    	Custom_App_Context.Gyrx_Notification_Status = 1;        /* My_Switch_Char notification status has been enabled */
    	    	Custom_Gyrx_Send_Notification();
      /* USER CODE END CUSTOM_STM_GYRX_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_GYRX_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_GYRX_NOTIFY_DISABLED_EVT */
    	Custom_App_Context.Gyrx_Notification_Status = 0;        /* My_Switch_Char notification status has been enabled */
      /* USER CODE END CUSTOM_STM_GYRX_NOTIFY_DISABLED_EVT */
      break;

    case CUSTOM_STM_GYRY_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_GYRY_READ_EVT */

      /* USER CODE END CUSTOM_STM_GYRY_READ_EVT */
      break;

    case CUSTOM_STM_GYRY_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_GYRY_NOTIFY_ENABLED_EVT */
    	Custom_App_Context.Gyry_Notification_Status = 1;        /* My_Switch_Char notification status has been enabled */
    	    	Custom_Gyry_Send_Notification();
      /* USER CODE END CUSTOM_STM_GYRY_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_GYRY_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_GYRY_NOTIFY_DISABLED_EVT */
    	Custom_App_Context.Gyry_Notification_Status = 0;        /* My_Switch_Char notification status has been enabled */
      /* USER CODE END CUSTOM_STM_GYRY_NOTIFY_DISABLED_EVT */
      break;

    case CUSTOM_STM_GYRZ_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_GYRZ_READ_EVT */

      /* USER CODE END CUSTOM_STM_GYRZ_READ_EVT */
      break;

    case CUSTOM_STM_GYRZ_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_GYRZ_NOTIFY_ENABLED_EVT */
    	Custom_App_Context.Gyrz_Notification_Status = 1;        /* My_Switch_Char notification status has been enabled */
    	    	Custom_Gyrz_Send_Notification();
      /* USER CODE END CUSTOM_STM_GYRZ_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_GYRZ_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_GYRZ_NOTIFY_DISABLED_EVT */
    	Custom_App_Context.Gyrz_Notification_Status = 0;        /* My_Switch_Char notification status has been enabled */
      /* USER CODE END CUSTOM_STM_GYRZ_NOTIFY_DISABLED_EVT */
      break;

    /* tempdata */
    case CUSTOM_STM_TEMPC_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_TEMPC_READ_EVT */

      /* USER CODE END CUSTOM_STM_TEMPC_READ_EVT */
      break;

    case CUSTOM_STM_TEMPC_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_TEMPC_NOTIFY_ENABLED_EVT */
    	Custom_App_Context.Tempc_Notification_Status = 1;        /* My_Switch_Char notification status has been enabled */
    	    	Custom_Tempc_Send_Notification();
      /* USER CODE END CUSTOM_STM_TEMPC_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_TEMPC_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_TEMPC_NOTIFY_DISABLED_EVT */
    	Custom_App_Context.Tempc_Notification_Status = 0;        /* My_Switch_Char notification status has been enabled */
      /* USER CODE END CUSTOM_STM_TEMPC_NOTIFY_DISABLED_EVT */
      break;

    case CUSTOM_STM_NOTIFICATION_COMPLETE_EVT:
      /* USER CODE BEGIN CUSTOM_STM_NOTIFICATION_COMPLETE_EVT */

      /* USER CODE END CUSTOM_STM_NOTIFICATION_COMPLETE_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_STM_App_Notification_default */

      /* USER CODE END CUSTOM_STM_App_Notification_default */
      break;
  }
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_2 */

  /* USER CODE END CUSTOM_STM_App_Notification_2 */
  return;
}

void Custom_APP_Notification(Custom_App_ConnHandle_Not_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_APP_Notification_1 */

  /* USER CODE END CUSTOM_APP_Notification_1 */

  switch (pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_APP_Notification_Custom_Evt_Opcode */

    /* USER CODE END P2PS_CUSTOM_Notification_Custom_Evt_Opcode */
    case CUSTOM_CONN_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_CONN_HANDLE_EVT */

      /* USER CODE END CUSTOM_CONN_HANDLE_EVT */
      break;

    case CUSTOM_DISCON_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_DISCON_HANDLE_EVT */

      /* USER CODE END CUSTOM_DISCON_HANDLE_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_APP_Notification_default */

      /* USER CODE END CUSTOM_APP_Notification_default */
      break;
  }

  /* USER CODE BEGIN CUSTOM_APP_Notification_2 */

  /* USER CODE END CUSTOM_APP_Notification_2 */

  return;
}

void Custom_APP_Init(void)
{
  /* USER CODE BEGIN CUSTOM_APP_Init */
	Custom_App_Context.ia_ = 0;
	Custom_App_Context.accx_ = 0;
	Custom_App_Context.accy_ = 0;
	Custom_App_Context.accz_ = 0;
	Custom_App_Context.gyrx_ = 0;
	Custom_App_Context.gyry_ = 0;
	Custom_App_Context.gyrz_ = 0;
	Custom_App_Context.temp_ = 0;
	UTIL_SEQ_RegTask(1<<CFG_TASK_IA_ID, UTIL_SEQ_RFU, Custom_Iac_Send_Notification);
	UTIL_SEQ_RegTask(1<<CFG_TASK_ACCX_ID, UTIL_SEQ_RFU, Custom_Accx_Send_Notification);
	UTIL_SEQ_RegTask(1<<CFG_TASK_ACCY_ID, UTIL_SEQ_RFU, Custom_Accy_Send_Notification);
	UTIL_SEQ_RegTask(1<<CFG_TASK_ACCZ_ID, UTIL_SEQ_RFU, Custom_Accz_Send_Notification);
	UTIL_SEQ_RegTask(1<<CFG_TASK_GYRX_ID, UTIL_SEQ_RFU, Custom_Gyrx_Send_Notification);
	UTIL_SEQ_RegTask(1<<CFG_TASK_GYRY_ID, UTIL_SEQ_RFU, Custom_Gyry_Send_Notification);
	UTIL_SEQ_RegTask(1<<CFG_TASK_GYRZ_ID, UTIL_SEQ_RFU, Custom_Gyrz_Send_Notification);
	UTIL_SEQ_RegTask(1<<CFG_TASK_TEMP_ID, UTIL_SEQ_RFU, Custom_Tempc_Send_Notification);
	Custom_delai_Update_Char();
	Custom_acq_Update_Char();
  /* USER CODE END CUSTOM_APP_Init */
  return;
}

/* USER CODE BEGIN FD */

/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/

/* configdata */
/* iadata */
__USED void Custom_Iac_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Iac_UC_1*/

  /* USER CODE END Iac_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_IAC, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Iac_UC_Last*/

  /* USER CODE END Iac_UC_Last*/
  return;
}

void Custom_Iac_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Iac_NS_1*/
  if (Custom_App_Context.Iac_Notification_Status == 1)
  	{
  	  updateflag = 1;

  	//if (Custom_App_Context.swc == 1)
  	  //{
  		  Custom_App_Context.ia_ = ia;
  		  memcpy(&NotifyCharData[0],&Custom_App_Context.ia_,sizeof(Custom_App_Context.ia_));
  		  APP_DBG_MSG("-- CUSTOM APPLICATION SERVER  : INFORM CLIENT BUTTON 3 PUSHED \n");
  	  //}
  	}
  	else
  	{
  	  APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  NOTIFICATION DISABLED\n");
  	}
  /* USER CODE END Iac_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_IAC, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Iac_NS_Last*/

  /* USER CODE END Iac_NS_Last*/

  return;
}

/* accdata */
__USED void Custom_Accx_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Accx_UC_1*/

  /* USER CODE END Accx_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_ACCX, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Accx_UC_Last*/

  /* USER CODE END Accx_UC_Last*/
  return;
}

void Custom_Accx_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Accx_NS_1*/
  if (Custom_App_Context.Accx_Notification_Status == 1)
  	{
  	  updateflag = 1;
  	//acq=1;
  	//if (acq == 1)
  	  //{
  	//if (Custom_App_Context.swc == 1)
  	  //	  {s
  		  Custom_App_Context.accx_ = accx;
  		  memcpy(&NotifyCharData[0],&Custom_App_Context.accx_,sizeof(Custom_App_Context.accx_));
  		  APP_DBG_MSG("-- CUSTOM APPLICATION SERVER  : INFORM CLIENT BUTTON 3 PUSHED \n");
  	  //}
  	//}
  	//else
  	//{
  	  //APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  NOTIFICATION DISABLED\n");
  	//}
  /* USER CODE END Accx_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_ACCX, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Accx_NS_Last*/
  	}
  /* USER CODE END Accx_NS_Last*/

  return;
}

__USED void Custom_Accy_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Accy_UC_1*/

  /* USER CODE END Accy_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_ACCY, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Accy_UC_Last*/

  /* USER CODE END Accy_UC_Last*/
  return;
}

void Custom_Accy_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Accy_NS_1*/
  if (Custom_App_Context.Accy_Notification_Status == 1)
  	{
  	  updateflag = 1;

  	//if (acq == 1)
  	  //{
  		  Custom_App_Context.accy_ = accy;
  		  memcpy(&NotifyCharData[0],&Custom_App_Context.accy_,sizeof(Custom_App_Context.accy_));
  		  APP_DBG_MSG("-- CUSTOM APPLICATION SERVER  : INFORM CLIENT BUTTON 3 PUSHED \n");
  	  //}
  	}
  	else
  	{
  	  APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  NOTIFICATION DISABLED\n");
  	}
  /* USER CODE END Accy_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_ACCY, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Accy_NS_Last*/

  /* USER CODE END Accy_NS_Last*/

  return;
}

__USED void Custom_Accz_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Accz_UC_1*/

  /* USER CODE END Accz_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_ACCZ, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Accz_UC_Last*/

  /* USER CODE END Accz_UC_Last*/
  return;
}

void Custom_Accz_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Accz_NS_1*/
  if (Custom_App_Context.Accz_Notification_Status == 1)
  	{
  	  updateflag = 1;

  	//if (acq == 1)
  	  //{
  		  Custom_App_Context.accz_ = accz;
  		  memcpy(&NotifyCharData[0],&Custom_App_Context.accz_,sizeof(Custom_App_Context.accz_));
  		  APP_DBG_MSG("-- CUSTOM APPLICATION SERVER  : INFORM CLIENT BUTTON 3 PUSHED \n");
  	  //}
  	}
  	else
  	{
  	  APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  NOTIFICATION DISABLED\n");
  	}
  /* USER CODE END Accz_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_ACCZ, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Accz_NS_Last*/

  /* USER CODE END Accz_NS_Last*/

  return;
}

/* gyrdata */
__USED void Custom_Gyrx_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Gyrx_UC_1*/

  /* USER CODE END Gyrx_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_GYRX, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Gyrx_UC_Last*/

  /* USER CODE END Gyrx_UC_Last*/
  return;
}

void Custom_Gyrx_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Gyrx_NS_1*/
  if (Custom_App_Context.Gyrx_Notification_Status == 1)
  	{
  	  updateflag = 1;

  	//if (acq == 1)
  	  //{
  		  Custom_App_Context.gyrx_ = gyrx;
  		  memcpy(&NotifyCharData[0],&Custom_App_Context.gyrx_,sizeof(Custom_App_Context.gyrx_));
  		  APP_DBG_MSG("-- CUSTOM APPLICATION SERVER  : INFORM CLIENT BUTTON 3 PUSHED \n");
  	  //}
  	}
  	else
  	{
  	  APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  NOTIFICATION DISABLED\n");
  	}
  /* USER CODE END Gyrx_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_GYRX, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Gyrx_NS_Last*/

  /* USER CODE END Gyrx_NS_Last*/

  return;
}

__USED void Custom_Gyry_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Gyry_UC_1*/

  /* USER CODE END Gyry_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_GYRY, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Gyry_UC_Last*/

  /* USER CODE END Gyry_UC_Last*/
  return;
}

void Custom_Gyry_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Gyry_NS_1*/
  if (Custom_App_Context.Gyry_Notification_Status == 1)
  	{
  	  updateflag = 1;

  	//if (acq == 1)
  	  //{
  		  Custom_App_Context.gyry_ = gyry;
  		  memcpy(&NotifyCharData[0],&Custom_App_Context.gyry_,sizeof(Custom_App_Context.gyry_));
  		  APP_DBG_MSG("-- CUSTOM APPLICATION SERVER  : INFORM CLIENT BUTTON 3 PUSHED \n");
  	  //}
  	}
  	else
  	{
  	  APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  NOTIFICATION DISABLED\n");
  	}
  /* USER CODE END Gyry_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_GYRY, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Gyry_NS_Last*/

  /* USER CODE END Gyry_NS_Last*/

  return;
}

__USED void Custom_Gyrz_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Gyrz_UC_1*/

  /* USER CODE END Gyrz_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_GYRZ, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Gyrz_UC_Last*/

  /* USER CODE END Gyrz_UC_Last*/
  return;
}

void Custom_Gyrz_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Gyrz_NS_1*/
  if (Custom_App_Context.Gyrz_Notification_Status == 1)
  	{
  	  updateflag = 1;

  	//if (acq == 1)
  	  //{
  		  Custom_App_Context.gyrz_ = gyrz;
  		  memcpy(&NotifyCharData[0],&Custom_App_Context.gyrz_,sizeof(Custom_App_Context.gyrz_));
  		  APP_DBG_MSG("-- CUSTOM APPLICATION SERVER  : INFORM CLIENT BUTTON 3 PUSHED \n");
  	  //}
  	}
  	else
  	{
  	  APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  NOTIFICATION DISABLED\n");
  	}
  /* USER CODE END Gyrz_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_GYRZ, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Gyrz_NS_Last*/

  /* USER CODE END Gyrz_NS_Last*/

  return;
}

/* tempdata */
__USED void Custom_Tempc_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Tempc_UC_1*/

  /* USER CODE END Tempc_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_TEMPC, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Tempc_UC_Last*/

  /* USER CODE END Tempc_UC_Last*/
  return;
}

void Custom_Tempc_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Tempc_NS_1*/
  if (Custom_App_Context.Tempc_Notification_Status == 1)
  	{
  	  updateflag = 1;
  	  //acq=1;
  	//if (acq == 1)
  	  //{
  		  Custom_App_Context.temp_ = temp;
  		  memcpy(&NotifyCharData[0],&Custom_App_Context.temp_,sizeof(Custom_App_Context.temp_));
  		  APP_DBG_MSG("-- CUSTOM APPLICATION SERVER  : INFORM CLIENT BUTTON 3 PUSHED \n");
  	  //}
  	}
  	else
  	{
  	  APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  NOTIFICATION DISABLED\n");
  	}
  /* USER CODE END Tempc_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_TEMPC, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Tempc_NS_Last*/

  /* USER CODE END Tempc_NS_Last*/

  return;
}

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS*/
void Custom_delai_Update_Char() /* Property writed */
{
  Custom_STM_App_Update_Char(CUSTOM_STM_DELAI, (uint8_t *)UpdateCharData);
  return;
}
void Custom_acq_Update_Char() /* Property writed */
{
  Custom_STM_App_Update_Char(CUSTOM_STM_ACQ, (uint8_t *)UpdateCharData);
  return;
}
/* USER CODE END FD_LOCAL_FUNCTIONS*/
