#include "hmc5883.h"
#include "bsp_bluetooth.h"
#include "bsp_i2c.h"

void HMC_Init(void){
    int  i=0,j=0;
    uint8_t data=0X00;
    for(i=0;i<1000;i++)
    {
    for(j=0;j<1000;j++)
    {
      ;
    }
    }

    Soft_Dely(0xFFFFF);
    Sensor_Write(HMC5883L_ADDRESS,HMC5883L_MODE,1,&data);
}

void HMC_Read(short* hmc){
    uint8_t buf[6];
    Sensor_Read(HMC5883L_ADDRESS,HMC5883L_DATA,6,buf);//��ȡ����������
    hmc[0]=(buf[0]<<8)|buf[1];  //x
    hmc[1]=(buf[2]<<8)|buf[3];  //y
    hmc[2]=(buf[4]<<8)|buf[5];  //z
}

