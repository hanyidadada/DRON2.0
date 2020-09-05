#include "apps.h"

extern int ticks;

void App_Task0(void *p_arg){
	short Acel[3];
	short Gyro[3];
	short Hmc[3];
	OS_CPU_SysTickInit();	
	while(1){
		OSTimeDly(1000);
		MPU6050ReadAcc(Acel);
		printf("加速度：%8d%8d%8d",Acel[0],Acel[1],Acel[2]);
		MPU6050ReadGyro(Gyro);
		printf("    陀螺仪：%8d%8d%8d",Gyro[0],Gyro[1],Gyro[2]);
		HMC_Read(Hmc);
		printf("    磁力计：%8d%8d%8d\r\n",Hmc[0],Hmc[1],Hmc[2]);
		OSTimeDly(1000);
	}
}
void App_Task1(void *p_arg){
	OS_CPU_SysTickInit();	
	while(1)
	{
		OSTimeDly(100);
		printf("hello,Task1,Ticks:%d\n",ticks);
		OSTimeDly(100);
	}
}
void App_Task2(void *p_arg){
	int i=0;
	OS_CPU_SysTickInit();
	while(1){
		OSTimeDly(200);
		LED_ON;
		printf("LED ON %d times,Ticks:%d\n",i+1,ticks);
		OSTimeDly(200);
		LED_OFF;
		i++;
	}
}

void BSP_Init(void){
	Debug_USART_Config();
	GY_Config();
	MPU6050_Init();
	if(MPU6050ReadID()){
		printf("MPU Init SUCCESS.\n");
	}
	HMC_Init();
	
	LED_Config();
	
}



