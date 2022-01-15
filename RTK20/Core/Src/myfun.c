#include "myfun.h"

RTK20_Static rtk20s;
RTK20_Dynamic rtk20d;

uint8_t loopFunFlag = 0x01;

void All_Init(void){
	u8g2Init(&u8g2);
  	helloMenu(&u8g2);
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
		WS2812_send(color_green,6);
		color_green[1]=0;
		Sys_Tick = HAL_GetTick();
		while(1){
			if((HAL_GetTick() - Sys_Tick) > 500){
				POWER_OFF;
				while(1);
			}
			if(KEY_OK_PUSH)break;
		}
		KEY_OK_CLEAR;
		Sys_Tick = HAL_GetTick();
		while(1){
			if((HAL_GetTick() - Sys_Tick) > 1200){
				for(i=0;i<255;i++){
					color_green[1]+=1;
					HAL_Delay(1);
					WS2812_send(color_green,6);
				}
				break;
			}
			if(KEY_OK_RELEASE && ((HAL_GetTick() - Sys_Tick)<1200)){
				POWER_OFF;
				while(1);
			}
		}
		KEY_OK_CLEAR;
}

void loopFun(u8g2_t *in){
  if(loopFunFlag & 0X80){
    settingMenu(in);
  }
  else if(loopFunFlag &0X01){
    manualSurfaceMenu(in);
  }
  else if(loopFunFlag &0X02){
    reflowSurfaceMenu(in);
  }
}

