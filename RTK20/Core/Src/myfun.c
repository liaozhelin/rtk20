/*
 * @Author: [LiaoZhelin]
 * @Date: 2021-12-24 10:20:34
 * @LastEditors: [LiaoZhelin]
 * @LastEditTime: 2022-01-15 21:20:07
 * @Description: 
 */
#include "myfun.h"

#define rank_ 2  //����
#define maxn 10  //��������(�궨������)

RTK20_Static rtk20s;
RTK20_Dynamic rtk20d;


void All_Init(void){
	u8g2Init(&u8g2);
  	helloMenu(&u8g2);
	HAL_DMA_Init(&hdma_adc);
	__HAL_LINKDMA(&hadc,DMA_Handle,hdma_adc);
	HAL_ADC_Start_DMA(&hadc,(uint32_t*)&ADC_ConvertedValue,80);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);//MOS���ź�-����
	AT24CXX_Init();   //24CXX��ʼ��
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
		color_green[1]=10;
		WS2812_send(color_green,6);
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
}



//*********************��С���˷���������㷨 2021-08-03*********************//
	
// void FUN_Linear_Fitting(void){
	
//     double atemp[2 * (rank_ + 1)] = { 0 }, b[rank_ + 1] = { 0 }, a[rank_ + 1][rank_ + 1];
// 	double btemp;
//     int i, j, k;
//     for (i = 0; i < maxn; i++) {  
//         atemp[1] += x[i];
//         atemp[2] += pow(x[i], 2);
//         atemp[3] += pow(x[i], 3);
//         atemp[4] += pow(x[i], 4);
//         atemp[5] += pow(x[i], 5);
//         atemp[6] += pow(x[i], 6);
//         b[0] += y[i];
//         b[1] += x[i] * y[i];
//         b[2] += pow(x[i], 2) * y[i];
//         b[3] += pow(x[i], 3) * y[i];
//     }
//     atemp[0] = maxn;
//     for (i = 0; i < rank_ + 1; i++) {  //�������Է�����ϵ������b[]����
//         k = i;
//         for (j = 0; j < rank_ + 1; j++)  a[i][j] = atemp[k++];
//     }
//     //����Ϊ��˹����Ԫ��ȥ�������Է�����
//     for (k = 0; k < rank_ + 1 - 1; k++) {  //n - 1��
//         int column = k;
//         double mainelement = a[k][k];
//         for (i = k; i < rank_ + 1; i++)  //����Ԫ��
//             if (fabs(a[i][k]) > mainelement) {
//                 mainelement = fabs(a[i][k]);
//                 column = i;
//             }
//         for (j = k; j < rank_ + 1; j++) {  //��������
//             double atemp = a[k][j];
//             a[k][j] = a[column][j];
//             a[column][j] = atemp;
//         }
//         btemp = b[k];
//         b[k] = b[column];
//         b[column] = btemp;
//         for (i = k + 1; i < rank_ + 1; i++) {  //��Ԫ����
//             double Mik = a[i][k] / a[k][k];
//             for (j = k; j < rank_ + 1; j++)  a[i][j] -= Mik * a[k][j];
//             b[i] -= Mik * b[k];
//         }
//     }

//     b[rank_ + 1 - 1] /= a[rank_ + 1 - 1][rank_ + 1 - 1];  //�ش�����
//     for (i = rank_ + 1 - 2; i >= 0; i--) {
//         double sum = 0;
//         for (j = i + 1; j < rank_ + 1; j++)  sum += a[i][j] * b[j];
//         b[i] = (b[i] - sum) / a[i][i];
//     }
// 	k0 = b[0];//ƫ��
// 	k1 = b[1];//һ����ϵ��
// 	k2 = b[2];//������ϵ��
// 	k3 = b[3];//������ϵ��
// 	printf("P(x) = %f%+fx%+fx^2%+fx^3\n\n", b[0], b[1], b[2], b[3]);
	
// }
