#include "stm32f2xx_hal.h"

#include "common.h"


static void
logging_handler(const char *message)
{
    static char buf[256];
    strncpy(buf, message, sizeof(buf) - 1);
    buf[255] = 0;
}


static uint32_t
logging_get_time(void)
{
    return HAL_GetTick();
}


/* auto-gen from STM cube. */
void
SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /* Initializes the CPU, AHB and APB busses clocks. */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 240;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    assert(HAL_RCC_OscConfig(&RCC_OscInitStruct) == HAL_OK);

    /* Initializes the CPU, AHB and APB busses clocks. */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_HCLK |
                                   RCC_CLOCKTYPE_SYSCLK |
                                   RCC_CLOCKTYPE_PCLK1 |
                                   RCC_CLOCKTYPE_PCLK2);

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    assert(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) == HAL_OK);
}


int
main(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    logging_init_args_t logging_args;

    HAL_Init();
    SystemClock_Config();

    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    logging_args.handler = logging_handler;
    logging_args.get_time = logging_get_time;
    logging_init(&logging_args);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);

    LOG_ERROR("error\n");
    LOG_WARNING("warning\n");
    LOG_INFO("info\n");
    LOG_DEBUG("debug\n");
    LOG_VERBOSE("verbose\n");

    while (1)
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
        HAL_Delay(500);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
        HAL_Delay(500);
    }

    return 0;
}


void
panic(const char *file, int line)
{
    UNUSED(file);
    UNUSED(line);

    while (1)
        ;
}
