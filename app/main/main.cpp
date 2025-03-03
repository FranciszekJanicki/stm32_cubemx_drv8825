#include "main.h"
#include "usart.h"

int main()
{
    HAL_Init();
    SystemClock_Config();

    MX_USART2_UART_Init();

    while (true) {
    }

    return 0;
}
