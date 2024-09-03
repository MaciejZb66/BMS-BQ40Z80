/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "can.h"
#include "i2c.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#ifdef USED_I2C1
BQ_data BMS_1 = {0};
#endif
#ifdef USED_I2C2
BQ_data BMS_2 = {0};
#endif
#ifdef USED_I2C3
BQ_data BMS_3 = {0};
#endif
#define KelvinToCelsius 2732

bool status;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == B1_Pin){
	  status = !status;
	  HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
  }
}

VESC_Status_4 stat4;
VESC_Status_5 stat5;
VESC_RawFrame rawFrame;
extern CAN_TxHeaderTypeDef TxHeader;
extern uint32_t TxMailbox;
uint8_t txData[8];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_CAN1_Init();
  /* USER CODE BEGIN 2 */

  status = false;
  uint16_t voltage = 0;
  int16_t current = 0;
  uint8_t percentage[2] = {0};
  uint16_t cells[6] = {0};
  bool fun[5] = {0};
  uint8_t test[11] = {0};
  uint16_t temperature[2] = {0};
  BQ_Init(&hi2c1);
  BQ_ReadMABlockCommand(&BMS_1, BQ40Z80_MFA_FIRMWARE_VERSION, test, 6);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  HAL_Delay(200);
	  BQAction_UpdateData(&BMS_1);
	  voltage = I2CHelper_ReadRegisterAsShort(&BMS_1, BQ40Z80_SBS_Voltage);//works 0x09
//	  current = I2CHelper_ReadRegisterAsShort(&BMS_1, BQ40Z80_SBS_Current);//TODO fix 1A = -400 (enable on 0x0A)
	  current = BMS_1.BQ_outCal.sep.current;//works
	  percentage[0] = I2CHelper_ReadRegisterAsChar(&BMS_1, BQ40Z80_SBS_RelativeStateOfCharge);//ok
	  percentage[1] = I2CHelper_ReadRegisterAsChar(&BMS_1, BQ40Z80_SBS_AbsoluteStateOfCharge);
	  temperature[0] = BMS_1.BQ_daStatus2.sep.ts1_temperature - KelvinToCelsius;
	  temperature[1] = BMS_1.BQ_daStatus2.sep.ts2_temperature - KelvinToCelsius;

	  // -----separated cells-----
	  cells[0] = BMS_1.BQ_daStatus1.sep.cell_voltage_1;
	  cells[1] = BMS_1.BQ_daStatus1.sep.cell_voltage_2;
	  cells[2] = BMS_1.BQ_daStatus1.sep.cell_voltage_3;
	  cells[3] = BMS_1.BQ_daStatus1.sep.cell_voltage_4;
	  cells[4] = BMS_1.BQ_daStatus3.sep.cell_voltage_5;
	  cells[5] = BMS_1.BQ_daStatus3.sep.cell_voltage_6;

	  // -----toggle fets--------
	  if(status){
		  BQAction_EnableDischarging(&BMS_1);
	  }else{
		  BQAction_DisableFets(&BMS_1);
	  }
	  fun[0] = BMS_1.BQ_opStatus.bits.pdsg;
	  fun[1] = BMS_1.BQ_opStatus.bits.xdsg;
	  stat4.pidPos = 0;
	  stat4.currentIn = (float)(BMS_1.BQ_outCal.sep.current) / 1000;
	  stat4.tempFet = (float)(BMS_1.BQ_daStatus2.sep.ts2_temperature - KelvinToCelsius) / 10;
	  stat4.tempMotor = (float)(BMS_1.BQ_daStatus2.sep.ts1_temperature - KelvinToCelsius) / 10;
	  VESC_convertStatus4ToRaw(&rawFrame, &stat4); //guess need vesc2halcan
	  HAL_CAN_AddTxMessage(&hcan1, &TxHeader, txData, &TxMailbox);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 9;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
