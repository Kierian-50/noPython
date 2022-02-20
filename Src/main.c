/* USER CODE BEGIN Header */

/**
 * @mainpage  NoPython
 *
 * Play to a simple snake game with a joystick and some music in background.
 */
 
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stm32l0xx_it.h"
#include "snake.h"
#include "musicTheme.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <retarget.h>
#include <getch.h>
#include <unistd.h>
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
void buzz(long frequency, long length);
void stopBuzz();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART2_UART_Init();
  MX_ADC_Init();
  MX_TIM2_Init();
  MX_TIM22_Init();

  /* USER CODE BEGIN 2 */
  RetargetInit(USART2);
  getchInit();
  LL_USART_EnableIT_RXNE(USART2);
  LL_SYSTICK_EnableIT();

  LL_ADC_Enable(ADC1);
  LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1),LL_ADC_PATH_INTERNAL_VREFINT);

  // init game variable
  unsigned short matrix[M_WIDTH][M_HEIGHT];
  memset(matrix, myCase.EMPTY, M_WIDTH * M_HEIGHT * sizeof(unsigned short));

  unsigned short snake[MAX_SNAKE_LENGTH][2];
  memset(snake, 0, MAX_SNAKE_LENGTH * 2 * sizeof(unsigned short));

  unsigned short newDirection = direction.RIGHT;
  unsigned short gameLoop = state.RUNNING;

  // start snake at (0, 0)
  snake[0][0] = 0;
  snake[0][1] = 0;

  // set random apple coordinates
  srand(time(NULL));
  unsigned short apple[2] = {0};
  apple[0] = rand() % M_WIDTH;
  apple[1] = rand() % M_HEIGHT;
  /* USER CODE END 2 */

  int music;
  printf("1. Mario\r\n2. Megalovania\r\nChoose a music : ");
  scanf("%d", &music);

  LL_TIM_CC_EnableChannel(TIM22, LL_TIM_CHANNEL_CH1);
  LL_TIM_EnableCounter(TIM22);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (gameLoop == state.RUNNING)
  {

      LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_0);
      LL_ADC_REG_StartConversion(ADC1);
      while (!LL_ADC_IsActiveFlag_EOC(ADC1)) {}

      uint16_t x = LL_ADC_REG_ReadConversionData12(ADC1);

      LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_1);
      LL_ADC_REG_StartConversion(ADC1);
      while (!LL_ADC_IsActiveFlag_EOC(ADC1)) {}

      uint16_t y = LL_ADC_REG_ReadConversionData12(ADC1);

      // change direction with joystick
      if ((x>=3300) && (y>=800) && (y<=3300)) {
    	  // go right and set lose if old diretion was inverse direction (left)
    	  if (score > 0 && newDirection != direction.LEFT) {
    		  newDirection = direction.RIGHT;
    	  } else if (score == 0) {
    		  newDirection = direction.RIGHT;
    	  }
      }

      if ((x<=800) && (y>=800) && (y<=3300)) {
    	  // go left and set lose if old diretion was inverse direction (right)
    	  if (score > 0 && newDirection != direction.RIGHT) {
    		  newDirection = direction.LEFT;
    	  } else if (score == 0) {
    		  newDirection = direction.LEFT;
    	  }
      }

      if ((y>=3300) && (x>=800) && (x<=3300)) {
    	  // go down and set lose if old diretion was inverse direction (up)
    	  if (score > 0 && newDirection != direction.UP) {
    		  newDirection = direction.DOWN;
    	  } else if (score == 0) {
    		  newDirection = direction.DOWN;
    	  }
      }

      if ((y<=800) && (x>=800) && (x<=3300)) {
    	  // go up and set lose if old diretion was inverse direction (down)
    	  if (score > 0 && newDirection != direction.DOWN) {
    		  newDirection = direction.UP;
    	  } else if (score == 0) {
    		  newDirection = direction.UP;
    	  }
      }

	// change direction with keyboard
	/*if (kbhit()) {
		uint8_t entered_char = getch();

		if (entered_char == 'z' || entered_char == 'Z') {
			if (score > 0 && newDirection != direction.DOWN) {
				newDirection = direction.UP;
			} else if (score == 0) {
				newDirection = direction.UP;
			}
		} else if (entered_char == 's' || entered_char == 'S') {
			if (score > 0 && newDirection != direction.UP) {
				newDirection = direction.DOWN;
			} else if (score == 0) {
				newDirection = direction.DOWN;
			}
		} else if (entered_char == 'q' || entered_char == 'Q') {
			if (score > 0 && newDirection != direction.RIGHT) {
				newDirection = direction.LEFT;
			} else if (score == 0) {
				newDirection = direction.LEFT;
			}
		} else if (entered_char == 'd' || entered_char == 'D') {
			if (score > 0 && newDirection != direction.LEFT) {
				newDirection = direction.RIGHT;
			} else if (score == 0) {
				newDirection = direction.RIGHT;
			}
		}

	}*/

    // disble music if user have made a bad choice
    if (music != 1 && music != 2) {
    	playNote1 = 0;
    	playNote2 = 0;
    }

    // if play note 1 ok and last note finish to be played, play next note
	if (playNote1 && playNote3) {
		// Play mario or megalovania theme in function of user choice
		if (music == 1) marioTheme();
		else if (music == 2) megalovaniaTheme();
		playNote1 = 0;
		playNote3 = 0;
	}

	// if play note 2, stop buzz
	if (playNote2) {
		stopBuzz();
		playNote2 = 0;
	}

	// If tickGame is true, play a move
	if (tickGame) {
		gameLoop = move(matrix, snake, newDirection, apple);
		tickGame = 0;
	}
  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  LL_TIM_DisableCounter(TIM22);
  printf("Score : %d\r\n", score);
	/* USER CODE END 3 */

}

long waitBeforeNextNote2 = 0;
long waitBeforeNextNote3 = 0;

/**
 * This method allows to play a frequency on the buzzer.
 * @param frequency The frequency to send to the buzzer.
 * @param length The duration of the note.
 */
void buzz(long frequency, long length) {
  waitBeforeNextNote2 = 1000000 / frequency / 2; // calculate the delay value between transitions
  waitBeforeNextNote3 = length;
  waitBeforeNextNote2 *= 0.2;

  // The  updated auto reload to match with the frequency
  long N = 16000000 / (2 * frequency);

  LL_TIM_SetAutoReload(TIM22, N);

  LL_TIM_EnableCounter(TIM22);

}

/**
 * This method allows to stop the sound/buzz of the buzzer.
 */
void stopBuzz() {
  waitBeforeNextNote2 *= 0.1;
  LL_TIM_DisableCounter(TIM22);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_0)
  {
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {

  }
  LL_SetSystemCoreClock(16000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
  LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_PCLK1);
}

/* USER CODE BEGIN 4 */
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
