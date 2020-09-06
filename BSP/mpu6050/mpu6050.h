#ifndef  __MPU6050__H
#define __MPU6050__H
#include "stm32f4xx.h"

#define MPU_ERROR 		I2C_ERROR
#define MPU_INFO 		I2C_INFO

#define MPU6050_ADDRESS         0x68
#define MPU6050_RA_WHO_AM_I     0x75     //��ѯ�豸��ַ
#define MPU6050_RA_SMPLRT_DIV   0x19     //������
#define MPU6050_GYRO_OUT        0x43     //MPU6050���������ݼĴ�����ַ
#define MPU6050_ACC_OUT         0x3B     //MPU6050���ٶ����ݼĴ�����ַ
#define MPU6050_RA_PWR_MGMT_1   0x6B     //��Դ����Ĵ�����ַ
#define MPU6050_RA_CONFIG       0x1A     //
#define MPU6050_RA_GYRO_CONFIG  0x1B     //���������üĴ���
#define MPU6050_RA_ACCEL_CONFIG 0x1C     //���ٶ����üĴ���
#define MPU6050_RA_TEMP_OUT_H   0x41     //MPU6050�¶����ݼĴ�����ַ
#define MPU6050_RA_USER_CTRL    0x6A     //�û����ƼĴ���
#define MPU6050_RA_INT_PIN_CFG  0x37     //�ж���·�Ĵ���


void MPU6050_Init(void);
uint8_t MPU6050ReadID(void);
void MPU6050ReadAcc(short *accData);
void MPU6050ReadGyro(short *gyroData);
void MPU6050_ReturnTemp(float *Temperature);

#endif
