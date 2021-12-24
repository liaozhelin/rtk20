#include "24cxx.h"

#define AT24CXX_DEV_ADDRESS     0xA0 
#define AT24CXX_DELAY_MS        HAL_Delay


//初始化IIC接口
uint8_t AT24CXX_Init(void){
	//··I2C初始化··HAL库中已经完成//
	return(AT24CXX_Check());
}
//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr)
{				  
	uint8_t date=0;
	if(EE_TYPE>AT24C16){
		uint8_t temp[2];
		temp[0] = ReadAddr>>8;
		temp[1] = ReadAddr;
		HAL_I2C_Mem_Read(&hi2c1,AT24CXX_DEV_ADDRESS,ReadAddr,I2C_MEMADD_SIZE_16BIT,&date,2,100);
	}
	else{
		HAL_I2C_Mem_Read(&hi2c1,AT24CXX_DEV_ADDRESS,ReadAddr,I2C_MEMADD_SIZE_8BIT,&date,1,100);//未测试
	}
	return date;
}
//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite){				   	  	    																 
	HAL_I2C_Mem_Write(&hi2c1,AT24CXX_DEV_ADDRESS,WriteAddr,I2C_MEMADD_SIZE_16BIT,&DataToWrite,1,100);
  AT24CXX_DELAY_MS(5);    //AT24C64的最长写入时间是5ms
}
//在AT24CXX里面的指定地址开始写入长度为Len的数据
//该函数用于写入16bit或者32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
//Len        :要写入数据的长度2,4
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len){  	
	uint8_t t;
	for(t=0;t<Len;t++){
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//在AT24CXX里面的指定地址开始读出长度为Len的数据
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据
//Len        :要读出数据的长度2,4
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len){  	
	uint8_t t;
	uint32_t temp=0;
	for(t=0;t<Len;t++){
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//检查AT24CXX是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功
uint8_t AT24CXX_Check(void){
	uint8_t temp;
	temp=AT24CXX_ReadOneByte(EE_TYPE);//避免每次开机都写AT24CXX			   
	if(temp==0X55)return 0;		   
	else{   
		AT24CXX_WriteOneByte(EE_TYPE,0X55);//排除第一次初始化的情况
	    temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//在AT24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead){
	while(NumToRead){
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//在AT24CXX里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite){
	while(NumToWrite--){
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
