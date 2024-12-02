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
void BQ_and_can(BQ_data *BMS);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#ifdef USED_I2C1
BQ_data BMS_1 = {0};
bool first_transmit_1 = true;
#endif
#ifdef USED_I2C2
BQ_data BMS_2 = {0};
bool first_transmit_2 = true;
#endif
#ifdef USED_I2C3
BQ_data BMS_3 = {0};
bool first_transmit_3 = true;
#endif

bool status;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == B1_Pin) {
		status = !status;
		HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
	}
}
VESC_Status_1 stat1;
VESC_Status_4 stat4;
VESC_Status_6 stat6;
VESC_RawFrame rawFrame;
extern CAN_TxHeaderTypeDef TxHeader;
extern uint32_t TxMailbox;
extern CAN_RxHeaderTypeDef RxHeader;
extern uint8_t RxData[8];
uint8_t TxData[8];
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
  MX_I2C2_Init();
  MX_I2C3_Init();
  /* USER CODE BEGIN 2 */
	status = false;
#ifdef USED_I2C1
	BQ_Init(&hi2c1);
#endif
#ifdef USED_I2C2
  BQ_Init(&hi2c2);
#endif
#ifdef USED_I2C3
  BQ_Init(&hi2c3);
#endif
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
#ifdef USED_I2C1
		BQ_and_can(&BMS_1);
		HAL_Delay(100);
#endif
#ifdef USED_I2C2
		BQ_and_can(&BMS_2);
		HAL_Delay(100);
#endif
#ifdef USED_I2C3
		BQ_and_can(&BMS_3);
		HAL_Delay(100);
#endif
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
  RCC_OscInitStruct.PLL.PLLN = 10;
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
void BQ_and_can(BQ_data *BMS) {
	I2CHelper_CheckAddress(BMS);
	if (BMS->connection == CONNECTED) {
		BQAction_UpdateData(BMS);
		BQ_GetSendData(BMS);
#ifdef USED_I2C1
		if (BMS == &BMS_1) {
			stat4.vescID = 0x90;
			stat6.vescID = 0x90;
		}
#endif
#ifdef USED_I2C2
		if(BMS == &BMS_2){
			stat4.vescID = 0x91;
		  	stat6.vescID = 0x91;
		}
#endif
#ifdef USED_I2C3
		if(BMS == &BMS_3){
			stat4.vescID = 0x92;
			stat6.vescID = 0x92;
		}
#endif
		stat4.pidPos = 0;
		stat4.currentIn = (float) (BMS->data.current) / 1000;
		stat4.tempFet = (float) (BMS->data.fet_temperature) / 10;
		stat4.tempMotor = (float) (BMS->data.cell_temperature) / 10;
		VESC_convertStatus4ToRaw(&rawFrame, &stat4);
		vesc2halcan(&TxHeader, TxData, 8, &rawFrame);
		HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
		HAL_Delay(1);
		stat6.adc1 = (float) (BMS->data.voltage)/1000;
		stat6.adc2 = (float) (BMS->data.balance.Min)/1000;
		stat6.adc3 = (float) (BMS->data.balance.Max)/1000;
		stat6.ppm = (float) (BMS->data.percentage)/100;
		VESC_convertStatus6ToRaw(&rawFrame, &stat6);
		vesc2halcan(&TxHeader, TxData, 8, &rawFrame);
		if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) == HAL_OK){
			HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
		}
		HAL_Delay(1);
	}
	stat1.erpm = 0;
	stat1.dutyCycle = 0;
	stat1.current = 1;
#ifdef USED_I2C1
	if(BMS == &BMS_1 && first_transmit_1){
		first_transmit_1 = false;
		stat1.vescID = 0x90;
		VESC_convertStatus1ToRaw(&rawFrame, &stat1);
		vesc2halcan(&TxHeader, TxData, 8, &rawFrame);
		HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
	}
#endif
#ifdef USED_I2C2
	if(BMS == &BMS_2 && first_transmit_2){
		first_transmit_1 = false;
		stat1.vescID = 0x92;
		VESC_convertStatus1ToRaw(&rawFrame, &stat1);
		vesc2halcan(&TxHeader, TxData, 8, &rawFrame);
		HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
	}
#endif
#ifdef USED_I2C3
	if(BMS == &BMS_3 && first_transmit_3){
		first_transmit_3 = false;
		stat1.vescID = 0x92;
		VESC_convertStatus1ToRaw(&rawFrame, &stat1);
		vesc2halcan(&TxHeader, TxData, 8, &rawFrame);
		HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
	}
#endif
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
	while (1) {
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
