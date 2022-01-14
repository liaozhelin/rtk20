#include "menu.h"

void helloMenu(u8g2_t *in){
    u8g2_ClearBuffer(in);
    u8g2_SetFont(in,u8g2_font_helvB24_tr);
	u8g2_DrawFrame(in,2,2,124,60);
	u8g2_DrawStr(in,12,45,"RTK20");
	u8g2_SendBuffer(in);
}

void topSurfaceMenu(u8g2_t *in){
    u8g2_ClearBuffer(in);
    u8g2_SetFont(in,u8g2_font_helvB10_tr);

    // u8g2_DrawButtonUTF8(in,20,15,U8G2_BTN_BW2|U8G2_BTN_HCENTER|U8G2_BTN_INV|U8G2_BTN_SHADOW1,0,1,1,"+");
    // u8g2_DrawButtonUTF8(in,20,45,U8G2_BTN_BW2|U8G2_BTN_HCENTER|U8G2_BTN_INV|U8G2_BTN_SHADOW1,0,1,1,"-");
    // u8g2_DrawRBox(in,40,10,20,10,3);

    // u8g2_SetFontRefHeightAll(in);
    // u8g2_UserInterfaceMessage(in,"Title1","Title2","Title3","OK \n CanCel");

    
    
}


void modeFun(u8g2_t *in){

}

void calibration(u8g2_t *in){

}

void monitorFun(u8g2_t *in){
    uint8_t current_selection  = 0;
    current_selection = u8g2_UserInterfaceInputValue(&u8g2,"Voltage","Input=",0,0,5,2,"V");

}

void peripheralFun(u8g2_t *in){
    uint8_t current_selection  = 0;
    const char *string_peripheralFun_title = "Peripheral";
    const char *string_peripheralFun = "VoltageIn\nInCurrent\nBeep\nRGBLed\nUART\n-Restore-Factory-\n>Exit<";
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

            break;
        default:
            break;
    }
}


