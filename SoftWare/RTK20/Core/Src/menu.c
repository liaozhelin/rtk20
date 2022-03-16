/*
 * @Author: [LiaoZhelin]
 * @Date: 2022-01-13 17:08:37
 * @LastEditors: [LiaoZhelin]
 * @LastEditTime: 2022-01-24 00:29:31
 * @Description: 
 */
#include "menu.h"
#include "string.h"
void helloMenu(u8g2_t *in)
{
    u8g2_ClearBuffer(in);
    u8g2_SetFont(in, u8g2_font_helvB24_tn);
    u8g2_DrawFrame(in, 2, 2, 124, 60);
    u8g2_DrawStr(in, 12, 45, "RTK20");
    u8g2_SendBuffer(in);
}

void manualSurfaceMenu(u8g2_t *in)
{
    char oled_buff[10] = {0};
    u8g2_ClearBuffer(in);

    u8g2_SetFont(in, u8g2_font_helvB24_tn);
    sprintf(oled_buff, "%3d", rtk20s.mannul.TempSet);
    u8g2_DrawStr(in, 36, 27, oled_buff);
		memset(oled_buff,0,sizeof(oled_buff));
		sprintf(oled_buff, "%3.0f", rtk20d.sensor.TempBed);
    u8g2_DrawStr(in, 36, 61, oled_buff);
    u8g2_DrawRFrame(&u8g2, 0, 0, 95, 30, 10);
    u8g2_DrawRFrame(&u8g2, 0, 34, 95, 30, 10);
    u8g2_SetFont(in, u8g2_font_unifont_t_chinese1);
    u8g2_SetFontMode(&u8g2, 0);
    u8g2_DrawUTF8(&u8g2, 3, 20, "设定");
    u8g2_DrawUTF8(&u8g2, 3, 55, "当前");

    u8g2_DrawRFrame(&u8g2, 98, 0, 10, 53, 3);
    u8g2_DrawRBox(&u8g2, 100, 2, 6, 49, 2);
    u8g2_SetFont(in, u8g2_font_helvB10_tr);
    u8g2_DrawStr(in, 98, 65, "P");
    u8g2_SendBuffer(&u8g2);
    if (KEY_OK_RELEASE_L)
    {
        rtk20s.flag.SettingFlag |= 0x01;
        KEY_OK_CLEAR;
    }
    else if (KEY_UP_PUSH)
    {
        rtk20s.mannul.TempSet = ((rtk20s.mannul.TempSet < rtk20s.peripheralFun.MaxTemp) ? (rtk20s.mannul.TempSet + 1) : rtk20s.mannul.TempSet);
        KEY_UP_CLEAR;
    }
    else if (KEY_DOWN_PUSH)
    {
        rtk20s.mannul.TempSet = ((rtk20s.mannul.TempSet > 0) ? (rtk20s.mannul.TempSet - 1) : rtk20s.mannul.TempSet);
        KEY_DOWN_CLEAR;
    }
    // u8g2_DrawButtonUTF8(in,20,15,U8G2_BTN_BW2|U8G2_BTN_HCENTER|U8G2_BTN_INV|U8G2_BTN_SHADOW1,0,1,1,"+");
    // u8g2_DrawButtonUTF8(in,20,45,U8G2_BTN_BW2|U8G2_BTN_HCENTER|U8G2_BTN_INV|U8G2_BTN_SHADOW1,0,1,1,"-");
    // u8g2_DrawRBox(in,40,10,20,10,3);

    // u8g2_SetFontRefHeightAll(in);
    // u8g2_UserInterfaceMessage(in,"Title1","Title2","Title3","OK \n CanCel");
}

void reflowSurfaceMenu(u8g2_t *in)
{
    u8g2_ClearBuffer(in);
    u8g2_SetFont(in, u8g2_font_helvB10_tr);
}

void modeFun(u8g2_t *in)
{
    uint8_t current_selection = 0;
    const char *string_modeFun_title = "Mode";
    const char *string_modeFun = "Reflow\nManual";
    u8g2_SetFont(in, u8g2_font_helvB10_tr);
    current_selection = u8g2_UserInterfaceSelectionList(in, string_modeFun_title, 1, string_modeFun);
    switch (current_selection)
    {
			case 1:
					rtk20s.flag.SurfaceFlag = 0x01;
					rtk20s.flag.SettingFlag = 0X00;
					break;
			case 2:
					rtk20s.flag.SurfaceFlag = 0x00;
					rtk20s.flag.SettingFlag = 0X00;
					break;
    }
}

void calibration(u8g2_t *in)
{
		const char *string_interfaceMessage1="Start\n Cancel ";
		const char *string_titile1 = "It has 20 Points";
		const char *string_titile2 = "Using TempMeter";
	  const char *string_titile3 = "Follow Guidance";

		uint8_t current_selection = 0;  
		for(;;){
			current_selection = u8g2_UserInterfaceMessage(in,string_titile1,string_titile2,string_titile3,string_interfaceMessage1,0,0);
			if(current_selection==1){
					for(;;){
						float Kout[rank_+1],Yin[20];
						static uint8_t tempRuleNum = 0;
						static uint8_t cur = 0;
						static uint16_t conRef = 1600;
						char buf_title1[30],buf_title3[30];
						const char *buf_title2 ="RareAD :          ";
						sprintf(buf_title1,"Desire : %.1f C",tempRule[tempRuleNum]);
						sprintf(buf_title3,"ConRef : %d",conRef);
						current_selection = u8g2_UserInterfaceMessage(in,buf_title1,buf_title2,buf_title3," + \n - \n save \n quit ",cur,1);
						switch(current_selection){
							//increase
							case 1:
								cur = 0;
								conRef = (conRef>4094?4094:conRef+10);
								break;
							//decrease
							case 2:
								cur = 1;
								conRef = (conRef<1?1:conRef-10);
								break;
							//save
							case 3:
								Yin[tempRuleNum] = (float)conRef;
								tempRuleNum = (tempRuleNum>19?19:tempRuleNum+1);
								memset(buf_title1,0,sizeof(buf_title1));
							  memset(buf_title3,0,sizeof(buf_title3));
							  if(tempRuleNum==20){
									 for(;;){
										 const char *buf_title_cal = "Cal-K\nSave\nquit";
										 current_selection = u8g2_UserInterfaceMessage(in,"Calibrate-Cal",buf_title1,buf_title3,buf_title_cal,cur,0);
										 switch(current_selection){
											 //Calculate L
											 case 1:
												 FUN_Linear_Fitting(Yin,Kout);
											   HAL_Delay(100);
												 sprintf(buf_title1,"%.04f %.04f",Kout[0],Kout[1]);
												 sprintf(buf_title3,"%.04f %.04f",Kout[2],Kout[3]);
//											   u8g2_DrawStr(in,0,16, buf_title1);
//											   u8g2_DrawStr(in,0,32, buf_title3);
//				                 u8g2_SendBuffer(in);
												 break;
											 //Save K to EEPROM
											 case 2:
												 rtk20s.tempCalibrate.K0 = Kout[0];
												 rtk20s.tempCalibrate.K1 = Kout[1];
												 rtk20s.tempCalibrate.K2 = Kout[2];
												 rtk20s.tempCalibrate.K3 = Kout[3];
											   AT24CXX_Save();
												 HAL_Delay(500); //wait date to save
												 memset(buf_title1,0,sizeof(buf_title1));
							           memset(buf_title3,0,sizeof(buf_title3));
											   sprintf(buf_title1,"Save Success!");
												 sprintf(buf_title3,"Please Quit");
												 break;
											 
										 }
										 //Exit
										 if(current_selection==3)
												 break;
									 }
								}
								cur = 0;
								break;
						}
						//exit
						if(current_selection==4)
							break;
					}
			}
			//exit
			if(current_selection==2)
				break;
		}
}

void monitorFun(u8g2_t *in)
{
    uint8_t current_selection = 0;
    u8g2_ClearBuffer(&u8g2);

    //    u8g2_DrawUTF8(in, 67, 14, "TB:");
    //    u8g2_DrawUTF8(in, 67, 30, "VI:");
    //    u8g2_DrawUTF8(in, 67, 46, "II:");
    //    u8g2_DrawUTF8(in, 67, 62, "TM:");

    u8g2_SendBuffer(&u8g2);

    for (;;)
    {
        char oled_buff[10] = {0};

        u8g2_ClearBuffer(&u8g2);
        u8g2_DrawLine(&u8g2, 0, 16, 127, 16);
        u8g2_DrawLine(&u8g2, 0, 32, 127, 32);
        u8g2_DrawLine(&u8g2, 0, 48, 127, 48);
        u8g2_DrawLine(&u8g2, 64, 0, 64, 63);
        sprintf(oled_buff, "A1: %d", ADC_AvergedValue[0]);
        u8g2_DrawStr(&u8g2, 0, 14, oled_buff);
        sprintf(oled_buff, "A2: %d", ADC_AvergedValue[1]);
        u8g2_DrawStr(&u8g2, 0, 30, oled_buff);
        sprintf(oled_buff, "A3: %d", ADC_AvergedValue[2]);
        u8g2_DrawStr(&u8g2, 0, 46, oled_buff);
        sprintf(oled_buff, "A4: %d", ADC_AvergedValue[3]);
        u8g2_DrawStr(&u8g2, 0, 62, oled_buff);

        sprintf(oled_buff, "Tb:%04.1fC", rtk20d.sensor.TempBed);
        u8g2_DrawStr(&u8g2, 67, 14, oled_buff);
        sprintf(oled_buff, "V:%05.2fV", rtk20d.sensor.Vbus);
        u8g2_DrawStr(&u8g2, 67, 30, oled_buff);
        sprintf(oled_buff, "I: %.3fA", rtk20d.sensor.Ibus);
        u8g2_DrawStr(&u8g2, 67, 46, oled_buff);
        sprintf(oled_buff, "Tm:%04.1fC", rtk20d.sensor.TempMcu);
        u8g2_DrawStr(&u8g2, 67, 62, oled_buff);

        u8g2_SendBuffer(&u8g2);

        current_selection = u8x8_GetMenuEvent(u8g2_GetU8x8(&u8g2));
        if (current_selection == U8X8_MSG_GPIO_MENU_SELECT)
        {
            break;
        }
    }
}

void peripheralFun(u8g2_t *in)
{
    uint8_t current_selection = 0;
    const char *string_peripheralFun_title = "Peripheral";
    const char *string_peripheralFun = "InVoltage\nInCurrent\nMaxTemp\nBEEP\nRGB_LED\nUART\n-Restore-Factory-\n>Exit<";
    u8g2_SetFont(in, u8g2_font_helvB10_tr);
    current_selection = u8g2_UserInterfaceSelectionList(in, string_peripheralFun_title, 1, string_peripheralFun);
    switch (current_selection)
    {
			case 1:
					break;
			case 2:
					break;
			case 3:
					break;
			case 4:
					for (;;)
					{
							const char *string_beepFun_title = "BEEP";
							const char *string_beepFun = "ON\nOFF";
							current_selection = u8g2_UserInterfaceSelectionList(in, string_beepFun_title, 1, string_beepFun);
							if (current_selection == 1)
							{
									rtk20s.peripheralFun.BeepMode = 1;
									break;
							}
							else if (current_selection == 2)
							{
									rtk20s.peripheralFun.BeepMode = 0;
									break;
							}
					}
					break;
			case 5:
					for (;;)
					{
							const char *string_rgbFun_title = "RGB_LED";
							const char *string_rgbFun = "ON\nOFF";
							current_selection = u8g2_UserInterfaceSelectionList(in, string_rgbFun_title, 1, string_rgbFun);
							if (current_selection == 1)
							{
									rtk20s.peripheralFun.RGBledMode = 1;
									break;
							}
							else if (current_selection == 2)
							{
									rtk20s.peripheralFun.RGBledMode = 0;
									break;
							}
					}
					break;
			case 6:
					for (;;)
					{
						const char *string_uartFun_title = "UART";
						const char *string_uartFun = "SEND_ON\nSEND_OFF";
						current_selection = u8g2_UserInterfaceSelectionList(in, string_uartFun_title, 1, string_uartFun);
						if (current_selection == 1)
						{
								rtk20s.peripheralFun.UARTMode = 1;
								break;
						}
						else if (current_selection == 2)
						{
								rtk20s.peripheralFun.UARTMode = 0;
								break;
						}
					}
					break;
			case 7:
					break;
			default:
					break;
			}
	}

void aboutFun(u8g2_t *in)
{
    uint8_t current_selection = 0;
    u8g2_ClearBuffer(&u8g2);
    u8g2_SetFont(in, u8g2_font_helvB10_tr);
    const char *string_aboutFun1 = "RTK20 HeatBed";
    const char *string_aboutFun2 = "LiaoZheLin";
    const char *string_aboutFun3 = "github:londonlove";
    const char *string_aboutFun4 = "2022-1-14";
    u8g2_DrawStr(&u8g2, 15, 16, string_aboutFun1);
    u8g2_DrawStr(&u8g2, 30, 32, string_aboutFun2);
    u8g2_DrawStr(&u8g2, 0, 48, string_aboutFun3);
    u8g2_DrawStr(&u8g2, 35, 64, string_aboutFun4);
    u8g2_SendBuffer(&u8g2);
    for (;;)
    {
        current_selection = u8x8_GetMenuEvent(u8g2_GetU8x8(&u8g2));
        if (current_selection == U8X8_MSG_GPIO_MENU_SELECT)
        {
            break;
        }
    }
}

void settingMenu(u8g2_t *in)
{
    uint8_t current_selection = 0;
    const char *string_settingMenu_title = "RTK20 Setting";
    const char *string_settingMenu = "Mode\nCalibration\nMonitor\nPeripheral\nAbout\n>Exit<\nShutdown";
    u8g2_SetFont(in, u8g2_font_helvB10_tr);
    current_selection = u8g2_UserInterfaceSelectionList(in, string_settingMenu_title, 0, string_settingMenu);
    switch (current_selection)
    {
    case 1:
        modeFun(in);
        break;
    case 2:
        calibration(in);
        break;
    case 3:
        monitorFun(in);
        break;
    case 4:
        peripheralFun(in);
        break;
    case 5:
        aboutFun(in);
        break;
    case 6:
        rtk20s.flag.SettingFlag = 0X00;
        break;
		//ShutDown Power
		case 7:
			  AT24CXX_Save();
		    TIM14->PSC = 600;
				HAL_TIM_PWM_Start(&htim14,TIM_CHANNEL_1);
				HAL_Delay(100);
				TIM14->PSC = 800;
				HAL_Delay(100);
				TIM14->PSC = 1000;
				HAL_Delay(100);
				HAL_TIM_PWM_Stop(&htim14,TIM_CHANNEL_1);
		    HAL_Delay(100);
		    POWER_OFF;
				while(1);
				break;
    default:
        break;
    }
}
