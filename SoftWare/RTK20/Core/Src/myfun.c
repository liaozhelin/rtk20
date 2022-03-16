/*
 * @Author: [LiaoZhelin]
 * @Date: 2021-12-24 10:20:34
 * @LastEditors: [LiaoZhelin]
 * @LastEditTime: 2022-01-15 22:27:45
 * @Description: 
 */
#include "myfun.h"

RTK20_Static rtk20s;
RTK20_Dynamic rtk20d;


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
				if(KEY_UP_RELEASE_S)break;
			}
		}
		color_green[0]=15;
		color_green[1]=40;
		WS2812_send(color_green,6);
		color_green[0]=0;
		color_green[1]=0;
		KEY_OK_CLEAR;
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
			if((KEY_OK_RELEASE_S||KEY_OK_RELEASE_L) && ((HAL_GetTick() - Sys_Tick)<1200)){
				POWER_OFF;
				while(1);
			}
		}
		KEY_OK_CLEAR;
}

static void TimeTask(void){
	if(rtk20d.timetask.Time1000ms == 1){
		AT24CXX_Save();
		rtk20d.timetask.Time1000ms = 0;
	}
}

void loopFun(u8g2_t *in){
  if(rtk20s.flag.SettingFlag & 0X01){
    settingMenu(in);
  }
  else if(rtk20s.flag.SurfaceFlag == 0X00){
    manualSurfaceMenu(in);
  }
  else if(rtk20s.flag.SurfaceFlag == 0X01){
    reflowSurfaceMenu(in);
  }
  TimeTask();
} 

static void USER_ADC_TEMP_CAL(void){
	switch(rank_){
		case 1:
			rtk20d.sensor.TempBed = rtk20s.tempCalibrate.K0 + (rtk20s.tempCalibrate.K1*ADC_AvergedValue[0]);
			break;
		case 2:
			rtk20d.sensor.TempBed = rtk20s.tempCalibrate.K0 + (rtk20s.tempCalibrate.K1*ADC_AvergedValue[0]) + (rtk20s.tempCalibrate.K2*pow_m(ADC_AvergedValue[0],2));
			break;
		case 3:
			rtk20d.sensor.TempBed = rtk20s.tempCalibrate.K0 + (rtk20s.tempCalibrate.K1*ADC_AvergedValue[0]) + (rtk20s.tempCalibrate.K2*pow_m(ADC_AvergedValue[0],2)) +  (rtk20s.tempCalibrate.K2*pow_m(ADC_AvergedValue[0],3));
			break;
		default:
			break;
	}
	
}

static void USER_ADC_CAL(void){
	rtk20d.sensor.Vbus = (float)ADC_AvergedValue[1]*0.0088623;
	rtk20d.sensor.Ibus = (float)ADC_AvergedValue[2]*0.0004833;
	rtk20d.sensor.TempMcu = (357.558 - ((float)ADC_AvergedValue[3]*0.187209));  
	USER_ADC_TEMP_CAL();
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	static uint16_t timeCount = 0;
	if(htim == &htim16){
		//10MS任务
		if(!(timeCount%10)){
			//100MS任务
			rtk20d.timetask.Time100ms = 1;
			USER_ADC_CAL();
			
		}
		if(!(timeCount %100)){
			//1000MS任务
			rtk20d.timetask.Time1000ms = 1;
			//printf("TimeTask1s\r\n");
		}
		timeCount = (timeCount<1000?timeCount+1:0);//10S
	}
	if(htim == &htim1){
		//timetask
	}
}


