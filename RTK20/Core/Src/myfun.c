#include "myfun.h"

void All_Init(void){
	u8g2Init(&u8g2);
	u8g2_SetFont(&u8g2,u8g2_font_helvB24_tr);
	u8g2_ClearBuffer(&u8g2);
	u8g2_DrawStr(&u8g2,10,50,"RTK20");
	u8g2_SendBuffer(&u8g2);
	
	HAL_DMA_Init(&hdma_adc);
	__HAL_LINKDMA(&hadc,DMA_Handle,hdma_adc);
	HAL_ADC_Start_DMA(&hadc,(uint32_t*)&ADC_ConvertedValue,80);
	
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);//MOS管信号-开启
	

	
	
	AT24CXX_Init();   //24CXX初始化
	
	
}


void ON_Fun(void){
	  static uint32_t Sys_Tick = 0;
	  uint8_t color_green[3],i=0;
	  POWER_ON;
		Sys_Tick = HAL_GetTick();
		if(KEY_OK_PUSH){
			while(1){
				if((HAL_GetTick() - Sys_Tick) > 1000){
					POWER_OFF;
					while(1);
				}
				if(KEY_OK_RELEASE)break;
			}
		}
		color_green[1]=10;
		WS2812_send(color_green,2);
		color_green[1]=0;
		Sys_Tick = HAL_GetTick();
		while(1){
			if((HAL_GetTick() - Sys_Tick) > 800){
				POWER_OFF;
				while(1);
			}
			if(KEY_OK_PUSH)break;
		}
		KEY_OK_CLEAR;
		Sys_Tick = HAL_GetTick();
		while(1){
			if((HAL_GetTick() - Sys_Tick) > 1500){
				for(i=0;i<255;i++){
					color_green[1]+=1;
					HAL_Delay(1);
					WS2812_send(color_green,2);
				}
				break;
			}
			if(KEY_OK_RELEASE && ((HAL_GetTick() - Sys_Tick)<1500)){
				POWER_OFF;
				while(1);
			}
		}
		KEY_OK_CLEAR;
}
	
