#ifndef __APP_H__
#define __APP_H__

#include "ucos_ii.h"
#include "bsp_bluetooth.h"
<<<<<<< HEAD
=======
#include "bsp_i2c.h"
#include "mpu6050.h"
#include "hmc5883.h"
>>>>>>> dd2629fede7cb2404575abbd2be5e1ad1e7f73d2
#include "bsp_led.h"


#define APP_TASK0_STK_SIZE				512
#define APP_TASK0_PRIO						16
#define APP_TASK1_STK_SIZE				512
#define APP_TASK1_PRIO						14
#define APP_TASK2_STK_SIZE				512
#define APP_TASK2_PRIO						11
extern OS_STK		App_Task0Stack[APP_TASK0_STK_SIZE];
extern OS_STK		App_Task1Stack[APP_TASK1_STK_SIZE];
extern OS_STK		App_Task2Stack[APP_TASK2_STK_SIZE];
void App_Task0(void *p_arg);
void App_Task1(void *p_arg);
void App_Task2(void *p_arg);
void BSP_Init(void);

#endif


