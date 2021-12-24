#include "24cxx.h"

#define AT24CXX_DEV_ADDRESS     0xA0 
#define AT24CXX_DELAY_MS        HAL_Delay


//��ʼ��IIC�ӿ�
uint8_t AT24CXX_Init(void){
	//����I2C��ʼ������HAL�����Ѿ����//
	return(AT24CXX_Check());
}
//��AT24CXXָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
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
		HAL_I2C_Mem_Read(&hi2c1,AT24CXX_DEV_ADDRESS,ReadAddr,I2C_MEMADD_SIZE_8BIT,&date,1,100);//δ����
	}
	return date;
}
//��AT24CXXָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite){				   	  	    																 
	HAL_I2C_Mem_Write(&hi2c1,AT24CXX_DEV_ADDRESS,WriteAddr,I2C_MEMADD_SIZE_16BIT,&DataToWrite,1,100);
  AT24CXX_DELAY_MS(5);    //AT24C64���д��ʱ����5ms
}
//��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
//Len        :Ҫд�����ݵĳ���2,4
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len){  	
	uint8_t t;
	for(t=0;t<Len;t++){
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len){  	
	uint8_t t;
	uint32_t temp=0;
	for(t=0;t<Len;t++){
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//���AT24CXX�Ƿ�����
//��������24XX�����һ����ַ(255)���洢��־��.
//���������24Cϵ��,�����ַҪ�޸�
//����1:���ʧ��
//����0:���ɹ�
uint8_t AT24CXX_Check(void){
	uint8_t temp;
	temp=AT24CXX_ReadOneByte(EE_TYPE);//����ÿ�ο�����дAT24CXX			   
	if(temp==0X55)return 0;		   
	else{   
		AT24CXX_WriteOneByte(EE_TYPE,0X55);//�ų���һ�γ�ʼ�������
	    temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//��AT24CXX�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead){
	while(NumToRead){
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//��AT24CXX�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite){
	while(NumToWrite--){
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
