#include "B-L475E-IOT01/stm32l475e_iot01.h"
#include "B-L475E-IOT01/stm32l475e_iot01_gyro.h"
#include "movement/rotation.h"
#include "movement/tracker.h"
#include "stm32l4xx_hal.h"

static void SystemClock_Config();

int main() {
    HAL_Init();

    /* Configure the system clock to 80 MHz */
    SystemClock_Config();

    const uint16_t slow_delay = 10000;
    const uint16_t fast_delay = 500;
    uint16_t current_delay = 10000;

    BSP_LED_Init(LED_GREEN);
    BSP_GYRO_Init();
    BSP_GYRO_LowPower(0);
    tracker_set_range(10);
    tracker_reset_start_position();

    while (1) {
        angle_degree moved_angle =
            calculate_moved_angle(BSP_GYRO_GetXYZ, current_delay);
        tracker_update_position(moved_angle);
        if (tracker_is_within_range(moved_angle)) {
            current_delay = fast_delay;
        } else {
            current_delay = slow_delay;
        }
        BSP_LED_Toggle(LED_GREEN);
        HAL_Delay(current_delay);
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

void assert_failed(char *file, uint32_t line) {
    while (1)
        ;
}