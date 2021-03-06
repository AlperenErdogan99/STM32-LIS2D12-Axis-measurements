/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

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
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef hlpuart1;

/* USER CODE BEGIN PV */

uint16_t Dev_Add = 0011000;       // Acc Device Address
uint16_t Read_Dev_Add = 0x31;     // Device Read Address (00110001)
uint16_t Write_Dev_Add = 0x30 ;   // Device Write Address (00110000)  
uint8_t Transmit_Data[1] ;        // Transmit buffer
uint8_t Transmit_Data_1[1] ;      // CTRL2 reg transmit buffer       
uint8_t Receive_Data[2] ;         // Receive buffer
uint8_t printData[3];
uint16_t CTRL_Reg_0  =  0x1E ;    // CTRL Reg 0 Register Address
uint16_t CTRL_Reg_1  =  0x20 ;    // CTRL Reg 1 Register Address
uint16_t CTRL_Reg_2 =   0x21 ;    // CTRL Reg 2 Register Address
uint16_t OUT_X_H_Reg =  0x29 ;    // 
uint16_t OUT_Y_H_Reg =  0x2B ; 
uint16_t Status_Reg  =  0x27 ; 
uint16_t OUT_Z_H_Reg     =  0x2D;
uint8_t ctrl_reg_1 = 0x20 ; 

uint8_t status_reg = 0x27 ; 
/*-----------*/
uint8_t transmit_ctrl_1_reg[1] ;
uint8_t transmit_ctrl_2_reg[1]  ;
uint8_t sonuc ; 
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_LPUART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
 set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

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
  MX_LPUART1_UART_Init();
  /* USER CODE BEGIN 2 */

  Receive_Data[0] = 8 ; 
  Receive_Data[1] = 8 ; 
  Transmit_Data[0] = 31 ; 
  Transmit_Data_1[0] = 0 ;
  

  

/*-------------ACC INIT 5(5.376Khz)------------*/  

  Receive_Data[0] = 8 ; 
  Receive_Data[1] = 8 ; 
  Transmit_Data[0] = 159 ; 
  Transmit_Data_1[0] = 0 ;
  do{
      sonuc = HAL_I2C_Mem_Write(&hi2c1, Write_Dev_Add, CTRL_Reg_1, I2C_MEMADD_SIZE_8BIT, (uint8_t *)Transmit_Data, strlen((char *)Transmit_Data), 1000);
      HAL_Delay(200);
      printf("Yazma fonk sonuc = %d\r\n",sonuc);  
    }while(sonuc != HAL_OK);
    
  
    do{
      sonuc = HAL_I2C_Mem_Read(&hi2c1, Read_Dev_Add, CTRL_Reg_1, I2C_MEMADD_SIZE_8BIT, (uint8_t *)Receive_Data, strlen((char *)Receive_Data), 1000);
      printf("CTRL 1 Register Degeri = %d\n\r",Receive_Data[0]);
      printf("Okuma fonk sonuc = %d\r\n",sonuc) ;
    }while(sonuc != HAL_OK); 
    
  /*CTRL_Reg_2 gerekli ayarlama yapiliyor ve okunuyor*/
     do {
      sonuc = HAL_I2C_Mem_Write(&hi2c1, Write_Dev_Add, CTRL_Reg_2, I2C_MEMADD_SIZE_8BIT, (uint8_t *)Transmit_Data_1, strlen((char *)Transmit_Data), 1000);
      HAL_Delay(200);
      printf("Yazma fonk sonuc = %d\r\n",sonuc);
  } while (sonuc != HAL_OK);  
      
  
  do {
    sonuc = HAL_I2C_Mem_Read(&hi2c1, Read_Dev_Add, CTRL_Reg_2, I2C_MEMADD_SIZE_8BIT, (uint8_t *)Receive_Data, strlen((char *)Receive_Data), 1000);
    printf("CTRL Reg 2 Register Degeri = %d\n\r",Receive_Data[0]);
    printf("Okuma fonk sonuc = %d\r\n",sonuc) ;
  } while(sonuc != HAL_OK);
  
  
/*---------------------------------------------*/  

/* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  
    
    /*-----X, Y ve Z axis olcumu icin kullanilan kod parcasi(Delay miktarlarini duruma gore degistirebilirsin)------*/
    
    do{
      sonuc = HAL_I2C_Mem_Read(&hi2c1, Read_Dev_Add, OUT_Z_H_Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t *)Receive_Data, strlen((char *)Receive_Data), 1000);
      if(Receive_Data[0] == 0 ){
      Receive_Data[0]+=1;
      }
      //printf("Out Z Cikis Degerleri = %d\n\r",Receive_Data[0]);
      //printf("Okuma fonk sonuc = %d\r\n",sonuc) ;
      printData[0] = Receive_Data[0];
  
      
    }while(sonuc!= HAL_OK);
  //HAL_Delay(1000);
  
  
      
  do{
      sonuc = HAL_I2C_Mem_Read(&hi2c1, Read_Dev_Add, OUT_Y_H_Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t *)Receive_Data, strlen((char *)Receive_Data), 1000);
      if(Receive_Data[0]==0){
      Receive_Data[0]+=1;
      }
      //printf("Out Y Cikis Degerleri = %d\n\r",Receive_Data[0]);
      //printf("Okuma fonk sonuc = %d\r\n",sonuc) ;
      printData[1] = Receive_Data[0];
  
      
      
    }while(sonuc!= HAL_OK);
//HAL_Delay(1000);
  
    do{
      sonuc = HAL_I2C_Mem_Read(&hi2c1, Read_Dev_Add, OUT_X_H_Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t *)Receive_Data,        strlen((char *)Receive_Data), 1000);
      if(Receive_Data[0] == 0){
      Receive_Data[0]+=1;
      }
      //printf("Out X Cikis Degerleri = %d\n\r",Receive_Data[0]);
      //printf("Okuma fonk sonuc = %d\r\n",sonuc) ;
      printData[2] = Receive_Data[0];
  
      
      
    }while(sonuc!= HAL_OK);
HAL_Delay(50);
/*Butun sonuclar TTL ile gonderiliyor.*/
printf("X axis: %d      Y axis: %d      Z axis: %d\r\n",printData[2], printData[1], printData[0]);
HAL_Delay(1000);
/*--------------------------------------------------------------*/


  
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00000708;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 9600;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_7B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
/**
 * @brief Retargets the C library printf function to the USART.
 * @param None
 * @retval None
 */
PUTCHAR_PROTOTYPE
{
 /* Place your implementation of fputc here */
 /* e.g. write a character to the USART2 and Loop until the end of transmission */
 HAL_UART_Transmit(&hlpuart1, (uint8_t *)&ch, 1, 0xFFFF);

return ch;
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
