#include "mpu6050.h"
#include "bsp_bluetooth.h"
#include "bsp_i2c.h"

void MPU6050_Init(void){
    int  i=0,j=0;
    uint8_t data;
    for(i=0;i<1000;i++)
    {
    for(j=0;j<1000;j++)
    {
      ;
    }
    }
    //����MPU6050
    data=0x00;
    Sensor_Write(MPU6050_ADDRESS,MPU6050_RA_PWR_MGMT_1,1,&data);
    
    //д�������
    data=0x07;
    Sensor_Write(MPU6050_ADDRESS,MPU6050_RA_SMPLRT_DIV,1,&data); 
    //MPU����
    data=0x06;
    Sensor_Write(MPU6050_ADDRESS,MPU6050_RA_CONFIG,1,&data);
    //���ٶȼ�����   16G
    data=0x08;
    Sensor_Write(MPU6050_ADDRESS,MPU6050_RA_ACCEL_CONFIG,1,&data);
    //����������   2000
    data=0x18;
    Sensor_Write(MPU6050_ADDRESS,MPU6050_RA_GYRO_CONFIG,1,&data);
    //I2C_MST��
    data=0xC0;
    Sensor_Write(MPU6050_ADDRESS,MPU6050_RA_USER_CTRL,1,&data);  
    //����ͨģʽ
    data=0x82;
    Sensor_Write(MPU6050_ADDRESS,MPU6050_RA_INT_PIN_CFG,1,&data);
    
}

uint8_t MPU6050ReadID(void)
{
	unsigned char Re = 0;
    Sensor_Read(MPU6050_ADDRESS,MPU6050_RA_WHO_AM_I,1,&Re);    //��������ַ
    
	if(Re != 0x68)
	{
		MPU_ERROR("MPU6050 dectected error!\r\n��ⲻ��MPU6050ģ�飬����ģ���뿪����Ľ���");
		return 0;
	}
	else
	{
		MPU_INFO("MPU6050 ID = %d\r\n",Re);
		return 1;
	}		
}

void MPU6050ReadAcc(short *accData)
{
    uint8_t buf[6];
    Sensor_Read(MPU6050_ADDRESS,MPU6050_ACC_OUT,6, buf);//��ȡ���ٶ����ֽ�����
    accData[0] = (buf[0] << 8) | buf[1];   //x�߰�λ���ƺ͵ڰ�λ��ͬ���16λ����
    accData[1] = (buf[2] << 8) | buf[3];   //y
    accData[2] = (buf[4] << 8) | buf[5];   //z
}

void MPU6050ReadGyro(short *gyroData)
{
    u8 buf[6];
    Sensor_Read(MPU6050_ADDRESS,MPU6050_GYRO_OUT,6,buf); //��ȡ���������ֽ�����
    gyroData[0] = (buf[0] << 8) | buf[1];           //x
    gyroData[1] = (buf[2] << 8) | buf[3];           //y 
    gyroData[2] = (buf[4] << 8) | buf[5];           //z
}


void MPU6050_ReturnTemp(float *Temperature)
{
	short temp3;
	u8 buf[2];
	
	Sensor_Read(MPU6050_ADDRESS,MPU6050_RA_TEMP_OUT_H,2,buf);     //��ȡ�¶�ֵ��8λ���8λ�����ֽ�
    temp3= (buf[0] << 8) | buf[1];	//��8λ��8λ��ϳ�16λ����
	*Temperature=((double) temp3/340.0)+36.53;  //�����ֲ���㹫ʽ���¶�

}

