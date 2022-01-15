/*
 * @Author: [LiaoZhelin]
 * @Date: 2022-01-13 17:08:37
 * @LastEditors: [LiaoZhelin]
 * @LastEditTime: 2022-01-15 17:24:20
 * @Description: 
 */
#include "menu.h"

void helloMenu(u8g2_t *in){
    u8g2_ClearBuffer(in);
    u8g2_SetFont(in,u8g2_font_helvB24_tn);
	u8g2_DrawFrame(in,2,2,124,60);
	u8g2_DrawStr(in,12,45,"RTK20");
	u8g2_SendBuffer(in);
}

void manualSurfaceMenu(u8g2_t *in){
    uint8_t current_selection  = 0;
    char oled_buff[10]={0};
    u8g2_ClearBuffer(in);

    u8g2_SetFont(in,u8g2_font_helvB24_tn);
    sprintf(oled_buff,"%3d",rtk20s.mannul.TempSet);
	u8g2_DrawStr(in,36,27,oled_buff);
    u8g2_DrawStr(in,36,61,"205");
		u8g2_DrawRFrame(&u8g2,0,0,95,30,10);
		u8g2_DrawRFrame(&u8g2,0,34,95,30,10);
    u8g2_SetFont(in,u8g2_font_unifont_t_chinese1);
    u8g2_SetFontMode(&u8g2,0);
		u8g2_DrawUTF8(&u8g2,3,20,"设定");
		u8g2_DrawUTF8(&u8g2,3,55,"当前");
	
	  u8g2_DrawRFrame(&u8g2,98,0,10,53,3);
	  u8g2_DrawRBox(&u8g2,100,2,6,49,2);
	  u8g2_SetFont(in,u8g2_font_helvB10_tr);
	  u8g2_DrawStr(in,98,65,"P");
	
    u8g2_SendBuffer(&u8g2);
	if(KEY_OK_RELEASE_L){
				
	}
	else if(KEY_UP_RELEASE_S){
        rtk20s.mannul.TempSet = ((rtk20s.mannul.TempSet < rtk20s.peripheralFun.MaxTemp)?(rtk20s.mannul.TempSet+1):rtk20s.mannul.TempSet);
        KEY_UP_CLEAR;
    }
    else if(KEY_DOWN_RELEASE_S){
        rtk20s.mannul.TempSet = ((rtk20s.mannul.TempSet > 0)?(rtk20s.mannul.TempSet-1):rtk20s.mannul.TempSet);
        KEY_DOWN_CLEAR;
    }
    // u8g2_DrawButtonUTF8(in,20,15,U8G2_BTN_BW2|U8G2_BTN_HCENTER|U8G2_BTN_INV|U8G2_BTN_SHADOW1,0,1,1,"+");
    // u8g2_DrawButtonUTF8(in,20,45,U8G2_BTN_BW2|U8G2_BTN_HCENTER|U8G2_BTN_INV|U8G2_BTN_SHADOW1,0,1,1,"-");
    // u8g2_DrawRBox(in,40,10,20,10,3);

    // u8g2_SetFontRefHeightAll(in);
    // u8g2_UserInterfaceMessage(in,"Title1","Title2","Title3","OK \n CanCel");
}

void reflowSurfaceMenu(u8g2_t *in){
    u8g2_ClearBuffer(in);
    u8g2_SetFont(in,u8g2_font_helvB10_tr);

}

void modeFun(u8g2_t *in){
    uint8_t current_selection  = 0;
    const char *string_modeFun_title = "Mode";
    const char *string_modeFun = "Reflow\nManual";
    u8g2_SetFont(in,u8g2_font_helvB10_tr);
    current_selection  = u8g2_UserInterfaceSelectionList(in,string_modeFun_title,1,string_modeFun);
    switch(current_selection){
        case 1:

            break;
        case 2:

            break;
    }
}

void calibration(u8g2_t *in){

}

void monitorFun(u8g2_t *in){
    uint8_t current_selection  = 0;
    u8g2_ClearBuffer(&u8g2);

    u8g2_DrawUTF8(in,67, 14,"TB:");
    u8g2_DrawUTF8(in,67, 30,"VI:");
    u8g2_DrawUTF8(in,67, 46,"II:");
    u8g2_DrawUTF8(in,67, 62,"TM:");
    
    u8g2_SendBuffer(&u8g2);

    for(;;){
        char oled_buff[10]={0};

        u8g2_ClearBuffer(&u8g2);
        u8g2_DrawLine(&u8g2,0,16,127,16);
        u8g2_DrawLine(&u8g2,0,32,127,32);
        u8g2_DrawLine(&u8g2,0,48,127,48);
        u8g2_DrawLine(&u8g2,64,0,64,63);
		sprintf(oled_buff,"A1: %d",ADC_AvergedValue[0]);
		u8g2_DrawStr(&u8g2,0,14,oled_buff); 
		sprintf(oled_buff,"A2: %d",ADC_AvergedValue[1]);
		u8g2_DrawStr(&u8g2,0,30,oled_buff);
		sprintf(oled_buff,"A3: %d",ADC_AvergedValue[2]);
		u8g2_DrawStr(&u8g2,0,46,oled_buff);
		sprintf(oled_buff,"A4: %d",ADC_AvergedValue[3]);
		u8g2_DrawStr(&u8g2,0,62,oled_buff);
        u8g2_SendBuffer(&u8g2);

        current_selection = u8x8_GetMenuEvent(u8g2_GetU8x8(&u8g2));
        if( current_selection == U8X8_MSG_GPIO_MENU_SELECT){
            break;
        }
    }
}

void peripheralFun(u8g2_t *in){
    uint8_t current_selection  = 0;
    const char *string_peripheralFun_title = "Peripheral";
    const char *string_peripheralFun = "InVoltage\nInCurrent\nBeep\nRGBLed\nUART\nMaxTemp\n-Restore-Factory-\n>Exit<";
    u8g2_SetFont(in,u8g2_font_helvB10_tr);
    current_selection  = u8g2_UserInterfaceSelectionList(in,string_peripheralFun_title,1,string_peripheralFun);
    switch(current_selection){
        case 1:
            
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;  
        default:
            break;                                                      
    }
}

void aboutFun(u8g2_t *in){
    uint8_t current_selection  = 0;
    u8g2_ClearBuffer(&u8g2); 
    u8g2_SetFont(in,u8g2_font_helvB10_tr);  
    const char *string_aboutFun1 = "RTK20 HeatBed";
    const char *string_aboutFun2 = "LiaoZheLin";
    const char *string_aboutFun3 = "github:londonlove";
    const char *string_aboutFun4 = "2022-1-14";
    u8g2_DrawStr(&u8g2,15,16,string_aboutFun1);
    u8g2_DrawStr(&u8g2,30,32,string_aboutFun2);
    u8g2_DrawStr(&u8g2,0,48,string_aboutFun3);
    u8g2_DrawStr(&u8g2,35,64,string_aboutFun4);
    u8g2_SendBuffer(&u8g2);
    for(;;){
        current_selection = u8x8_GetMenuEvent(u8g2_GetU8x8(&u8g2));
        if( current_selection == U8X8_MSG_GPIO_MENU_SELECT){
            break;
        }
    }
}

void settingMenu(u8g2_t *in){
    uint8_t current_selection  = 0;
    const char *string_settingMenu_title = "RTK20 Setting";
    const char *string_settingMenu = "Mode\nCalibration\nMonitor\nPeripheral\nAbout\n>Exit<";
    u8g2_SetFont(in,u8g2_font_helvB10_tr);
    current_selection  = u8g2_UserInterfaceSelectionList(in,string_settingMenu_title,1,string_settingMenu);
    switch(current_selection){
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
            loopFunFlag &= 0X7F;
            break;
        default:
            break;
    }
}


