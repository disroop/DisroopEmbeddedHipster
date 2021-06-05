#include "B-L475E-IOT01/stm32l475e_iot01.h"
#include "B-L475E-IOT01/stm32l475e_iot01_gyro.h"
#include "coordinator/coordinator.h"
#include "eiger/scheduler.h"
#include "indication/indication.h"
#include "movement/movement.h"
#include "stm32l4xx_hal.h"

static void SystemClock_Config();

void platform_init() {
    HAL_Init();
    SystemClock_Config();
    BSP_LED_Init(LED_GREEN);
    BSP_GYRO_Init();
    BSP_GYRO_LowPower(0);
}
int main() {
    platform_init();
    indication indicator =
        indication_create(LED_GREEN, BSP_LED_On, BSP_LED_Off);
    coordinator_init(100, indicator);
    movement_init(BSP_GYRO_GetXYZ);
    scheduler_config_time(HAL_Delay);
    scheduler_add_task(coordinator_run, 100);
    scheduler_add_task(movement_run, 20);
    while (1) {
        scheduler_update();
    }
    return 0;
}

static void SystemClock_Config(void) {
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    /* MSI is enabled after System reset, activate PLL with MSI as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
    RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
    RCC_OscInitStruct.PLL.PLLM = 1;
    RCC_OscInitStruct.PLL.PLLN = 40;
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLP = 7;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        /* Initialization Error */
        while (1)
            ;
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
       clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                   RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
        /* Initialization Error */
        while (1)
            ;
    }
}

void assert_failed(char *file, uint32_t line) {}