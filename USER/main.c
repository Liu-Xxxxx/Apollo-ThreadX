#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "sdram.h"
#include "usmart.h"
#include "pcf8574.h"
#include "touch.h"
#include "tx_api.h"
#include "tx_thread.h"

#define START_APP_STK_SIZE 1024
#define START_APP_PRIO 1
static TX_THREAD start_app_tcb;
static uint64_t start_app_stk[START_APP_STK_SIZE / 8];
static void start_app(ULONG thread_input);

int main(void)
{
	HAL_Init();						//初始化HAL库
	Cache_Enable();
	Stm32_Clock_Init(160, 5, 2, 4); //设置时钟,400Mhz
	printf("kernel entry\n");
	tx_kernel_enter();				/* 进入ThreadX内核 */

	while (1)
	{
	}
}

static void start_app(ULONG thread_input)
{
	bsp_InitDWT();		  //延时初始化
	uart_init(115200);	  //串口初始化
	usmart_dev.init(200); //初始化USMART
	LED_Init();			  //初始化LED
	KEY_Init();			  //初始化按键
	SDRAM_Init();		  //初始化SDRAM
	LCD_Init();			  //初始化LCD
	tp_dev.init();		  //触摸屏初始化
	POINT_COLOR = RED;

	while (1)
	{
		LCD_ShowString(30, 50, 200, 16, 16, "Apollo STM32H7");
		LCD_ShowString(30, 70, 200, 16, 16, "TOUCH TEST");
		LCD_ShowString(30, 90, 200, 16, 16, "ATOM@ALIENTEK");
		LCD_ShowString(30, 110, 200, 16, 16, "2017/8/14");
		tx_thread_sleep(500);
		LCD_Clear(WHITE);
		tx_thread_sleep(500);
	}
}

void tx_application_define(void *first_unused_memory)
{
	tx_thread_create(&start_app_tcb,
					 "start app",
					 start_app,
					 0,
					 &start_app_stk[0],
					 START_APP_STK_SIZE,
					 START_APP_PRIO,
					 START_APP_PRIO,
					 TX_NO_TIME_SLICE,
					 TX_AUTO_START);
}
