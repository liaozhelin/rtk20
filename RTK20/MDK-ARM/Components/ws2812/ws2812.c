#include "ws2812.h"

#define RED_INDEX   0
#define GREEN_INDEX 1
#define BLUE_INDEX  2
#define LED_NUM     2
#define GRB_BIT     24   //3*8

#define TIMING_ONE  40
#define TIMING_ZERO 18

//DMA以半字格式发出数据，避免数据强转使用半字的缓存区
uint16_t LED_BYTE_Buffer[48];

//功能：用于打开PWM，发出数据使灯亮起来
void WS281x_Show(uint16_t send_len)
{
    HAL_TIM_PWM_Start_DMA(&htim17, TIM_CHANNEL_1, (uint32_t *)&LED_BYTE_Buffer, send_len);
}

//传参：需要显示的RGB数据和灯的个数
//功能：把RGB数据转换成WS2812需要的GRB数据，并按照24bit格式打包给每个灯的数据
void WS2812_send(uint8_t *rgb, uint16_t len)
{
	uint8_t i;
	uint16_t memaddr = 0;
	uint16_t buffersize;
	buffersize = len * GRB_BIT;	// number of bytes needed is #LEDs * 24 bytes
    
	while (len)
	{
        for(i=0; i<8; i++) // GREEN data
        {
            LED_BYTE_Buffer[memaddr] = ((rgb[GREEN_INDEX]<<i) & 0x0080) ? TIMING_ONE:TIMING_ZERO;
            memaddr++;
        }
        for(i=0; i<8; i++) // RED
        {
            LED_BYTE_Buffer[memaddr] = ((rgb[RED_INDEX]<<i) & 0x0080) ? TIMING_ONE:TIMING_ZERO;
            memaddr++;
        }
        for(i=0; i<8; i++) // BLUE
        {
            LED_BYTE_Buffer[memaddr] = ((rgb[BLUE_INDEX]<<i) & 0x0080) ? TIMING_ONE:TIMING_ZERO;
            memaddr++;
        }
        len--;
	}
	WS281x_Show(memaddr);
}

volatile int cnt = 0;

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim){
	    HAL_TIM_PWM_Stop_DMA(&htim17,TIM_CHANNEL_1);
   __HAL_TIM_SET_COMPARE(&htim17,TIM_CHANNEL_1,0);
}
