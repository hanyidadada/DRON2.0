#include "bsp_i2c.h"

void GY_Config(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;
    
    GY_I2C_ClockCmd(GY_I2C_CLK,ENABLE);
    
    GY_SCL_CLOCKCMD(GY_SCL_GPIO_CLK,ENABLE);
    GY_SDA_CLOCKCMD(GY_SDA_GPIO_CLK,ENABLE);
    GPIO_PinAFConfig(GY_SCL_GPIO_PORT,GY_SCL_PINSOURCE,GY_SCL_AF);
    GPIO_PinAFConfig(GY_SDA_GPIO_PORT,GY_SDA_PINSOURCE,GY_SDA_AF);
    
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    
    GPIO_InitStructure.GPIO_Pin=GY_SCL_GPIO_PIN;
    GPIO_Init(GY_SCL_GPIO_PORT,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin=GY_SDA_GPIO_PIN;
    GPIO_Init(GY_SDA_GPIO_PORT,&GPIO_InitStructure);
    

    
    I2C_InitStructure.I2C_Ack=I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed=GY_Speed;
    I2C_InitStructure.I2C_DutyCycle=I2C_DutyCycle_2;
    I2C_InitStructure.I2C_Mode=I2C_Mode_I2C;
    I2C_InitStructure.I2C_OwnAddress1=STM32_OWN_ADRESS7;
    
    
    I2C_Cmd(GY_I2C,ENABLE);
		I2C_Init(GY_I2C,&I2C_InitStructure);
    I2C_AcknowledgeConfig(GY_I2C, ENABLE);  
}

int GY_Byte_Write(unsigned char slave_addr,unsigned char reg_addr,unsigned short lens,const unsigned char* data){
    uint32_t count_wait=I2Cx_LONG_TIMEOUT;
    uint32_t i=0;
    int value=0;
   //�ȴ�I2C�˳�æ
    while(I2C_GetFlagStatus(GY_I2C,I2C_FLAG_BUSY)!= RESET){
        if(count_wait--==0) return I2Cx_TIMEOUT_UserCallback(1);
    } 
    
    //������ʼ�ź�
    I2C_GenerateSTART(GY_I2C,ENABLE);
    //�ȴ�EV5
    count_wait=I2Cx_LONG_TIMEOUT;
     while(I2C_GetFlagStatus(GY_I2C,I2C_FLAG_SB)!=SET){
            if(count_wait--==0){ return I2Cx_TIMEOUT_UserCallback(2);}
    }
    
    //�����豸��ַ
    I2C_Send7bitAddress(GY_I2C,(slave_addr<<1),I2C_Direction_Transmitter);
    //���EV6�¼�
    count_wait=I2Cx_LONG_TIMEOUT;
    while(I2C_CheckEvent(GY_I2C,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!=SUCCESS){
        if(count_wait--==0) return  I2Cx_TIMEOUT_UserCallback(3);
    }
    
    //���ADDR��־λ
    I2C_ReadRegister(GY_I2C,I2C_Register_SR1);
    I2C_ReadRegister(GY_I2C,I2C_Register_SR2);
    //�ȴ�����
    count_wait=I2Cx_LONG_TIMEOUT;
    while(I2C_GetFlagStatus(GY_I2C,I2C_FLAG_TXE)!=SUCCESS){
        if(count_wait--==0){ return I2Cx_TIMEOUT_UserCallback(4);}
    }
    //����д��Ĵ洢��Ԫ��ַ
    I2C_SendData(GY_I2C,reg_addr);

    
    for(i=0;i<lens;i++){
          //���EV8_2
        count_wait=I2Cx_LONG_TIMEOUT;
        while(I2C_CheckEvent(GY_I2C,I2C_EVENT_MASTER_BYTE_TRANSMITTED)!=SUCCESS){
            if(count_wait--==0) 
            {    return  I2Cx_TIMEOUT_UserCallback(5);
            }
        }
        //����д�������
        I2C_SendData(GY_I2C,data[i]);
    }
    //���EV8_2
    count_wait=I2Cx_LONG_TIMEOUT;
    while(I2C_CheckEvent(GY_I2C,I2C_EVENT_MASTER_BYTE_TRANSMITTED)!=SUCCESS){
        if(count_wait--==0) return  I2Cx_TIMEOUT_UserCallback(6);
    }
    //���������ź�
    I2C_GenerateSTOP(GY_I2C,ENABLE);
    
    return value;
}

int GY_Byte_Read(unsigned char slave_addr,unsigned char reg_addr,unsigned short lens,unsigned char* data){
    uint32_t count_wait=I2Cx_LONG_TIMEOUT;
    uint32_t i=0;
    int value=0;
    //�ȴ�I2C�˳�æ
    while(I2C_GetFlagStatus(GY_I2C,I2C_FLAG_BUSY)!=RESET){
        if(count_wait--==0) return I2Cx_TIMEOUT_UserCallback(7);
    } 
    
    //��һ�β�����ʼ�ź�
    I2C_GenerateSTART(GY_I2C,ENABLE);
    
    //�ȴ�EV5
    count_wait=I2Cx_LONG_TIMEOUT;
    while(I2C_GetFlagStatus(GY_I2C,I2C_FLAG_SB)!=SET){
            if(count_wait--==0) return I2Cx_TIMEOUT_UserCallback(8);
    }
    
    //�����豸��ַ
    I2C_Send7bitAddress(GY_I2C,(slave_addr<<1),I2C_Direction_Transmitter);
    //���EV6�¼�
    count_wait=I2Cx_LONG_TIMEOUT;
    while(I2C_CheckEvent(GY_I2C,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!=SUCCESS){
        if(count_wait--==0) return  I2Cx_TIMEOUT_UserCallback(9);
    }
    
    //���ADDR��־λ
    I2C_ReadRegister(GY_I2C,I2C_Register_SR1);
    I2C_ReadRegister(GY_I2C,I2C_Register_SR2);
    //�ȴ�����
    count_wait=I2Cx_LONG_TIMEOUT;
    while(I2C_GetFlagStatus(GY_I2C,I2C_FLAG_TXE)!=SUCCESS){
        if(count_wait--==0) return I2Cx_TIMEOUT_UserCallback(10);
    }
    
    //����д��Ĵ洢��Ԫ��ַ
    I2C_SendData(GY_I2C,reg_addr);
    //���EV8_2
    count_wait=I2Cx_LONG_TIMEOUT;
    while(I2C_CheckEvent(GY_I2C,I2C_EVENT_MASTER_BYTE_TRANSMITTED)!=SUCCESS){
        if(count_wait--==0) return  I2Cx_TIMEOUT_UserCallback(11);
    }
    
     //�ڶ��β�����ʼ�ź�
    I2C_GenerateSTART(GY_I2C,ENABLE);
    
    //�ȴ�EV5
    count_wait=I2Cx_LONG_TIMEOUT;
    while(I2C_CheckEvent(GY_I2C,I2C_EVENT_MASTER_MODE_SELECT)!=SUCCESS){
            if(count_wait--==0) return I2Cx_TIMEOUT_UserCallback(12);
    }
    
     //�����豸��ַ
    I2C_Send7bitAddress(GY_I2C,(slave_addr<<1),I2C_Direction_Receiver);
    //���EV6�¼�
    count_wait=I2Cx_LONG_TIMEOUT;
    while(I2C_CheckEvent(GY_I2C,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)!=SUCCESS){
        if(count_wait--==0) return  I2Cx_TIMEOUT_UserCallback(13);
    }
    
    if(lens == 1){
        //�����һ������֮ǰ���ر�Ӧ��
        I2C_AcknowledgeConfig(GY_I2C, DISABLE);
        
        //���ADDR��־λ
        I2C_ReadRegister(GY_I2C,I2C_Register_SR1);
        I2C_ReadRegister(GY_I2C,I2C_Register_SR2);
        
        //����ֹͣλ
        I2C_GenerateSTOP(GY_I2C, ENABLE);
        
        //RXNEλ���
        count_wait=I2Cx_LONG_TIMEOUT;
        while(I2C_GetFlagStatus(GY_I2C,I2C_FLAG_RXNE)!=SET){
                if(count_wait--==0) return I2Cx_TIMEOUT_UserCallback(14);
        }
        
        data[0]=I2C_ReceiveData(GY_I2C);
    }
    else if(lens == 2){
        //�ر�Ӧ��
        I2C_AcknowledgeConfig(GY_I2C, DISABLE);
        //��POSλ
        GY_I2C->CR1 |= I2C_CR1_POS;
        //���ADDR��־λ
        I2C_ReadRegister(GY_I2C,I2C_Register_SR1);
        I2C_ReadRegister(GY_I2C,I2C_Register_SR2);
        //���BTF��־λ
        count_wait=I2Cx_LONG_TIMEOUT;
        while(I2C_GetFlagStatus(GY_I2C,I2C_FLAG_BTF)!=SET){
                if(count_wait--==0) return I2Cx_TIMEOUT_UserCallback(15);
        }
        //����ֹͣλ
        I2C_GenerateSTOP(GY_I2C, ENABLE);
        
        data[0]=I2C_ReceiveData(GY_I2C);
        data[1]=I2C_ReceiveData(GY_I2C);
    }
    else if(lens == 3){
        //���ADDR��־λ
        I2C_ReadRegister(GY_I2C,I2C_Register_SR1);
        I2C_ReadRegister(GY_I2C,I2C_Register_SR2);
        //���BTF��־λ
        count_wait=I2Cx_LONG_TIMEOUT;
        while(I2C_GetFlagStatus(GY_I2C,I2C_FLAG_BTF)!=SET){
                if(count_wait--==0) return I2Cx_TIMEOUT_UserCallback(16);
        }
        //�ر�Ӧ��
        I2C_AcknowledgeConfig(GY_I2C, DISABLE);
        data[0]=I2C_ReceiveData(GY_I2C);
        //����ֹͣλ
        I2C_GenerateSTOP(GY_I2C, ENABLE);
        data[1]=I2C_ReceiveData(GY_I2C);
        //RXNEλ���
        count_wait=I2Cx_LONG_TIMEOUT;
        while(I2C_GetFlagStatus(GY_I2C,I2C_FLAG_RXNE)!=SET){
                if(count_wait--==0) return I2Cx_TIMEOUT_UserCallback(17);
        }
        data[2]=I2C_ReceiveData(GY_I2C);
    }
    else{
        //���ADDR��־λ
        I2C_ReadRegister(GY_I2C,I2C_Register_SR1);
        I2C_ReadRegister(GY_I2C,I2C_Register_SR2);
        
        for(i=0; i<(lens); i++)
        {
          if(i==(lens-3))
          {
            //���BTF��־λ
            count_wait=I2Cx_LONG_TIMEOUT;
            while(I2C_GetFlagStatus(GY_I2C,I2C_FLAG_BTF)!=SET){
                    if(count_wait--==0) return I2Cx_TIMEOUT_UserCallback(16);
            }
            //�ر�Ӧ��
            I2C_AcknowledgeConfig(GY_I2C, DISABLE);
            data[i++] = I2C_ReceiveData(GY_I2C);
            
            //����ֹͣλ
            I2C_GenerateSTOP(GY_I2C, ENABLE);        
            data[i++] = I2C_ReceiveData(GY_I2C);
            
            //RXNEλ���
        count_wait=I2Cx_LONG_TIMEOUT;
        while(I2C_GetFlagStatus(GY_I2C,I2C_FLAG_RXNE)!=SET){
                if(count_wait--==0) return I2Cx_TIMEOUT_UserCallback(17);
        }
            /* Read 1 bytes */
            data[i++] = I2C_ReceiveData(GY_I2C);  
            goto end;
          }
                
          //RXNEλ���
        count_wait=I2Cx_LONG_TIMEOUT;
        while(I2C_GetFlagStatus(GY_I2C,I2C_FLAG_RXNE)!=SET){
                if(count_wait--==0) return I2Cx_TIMEOUT_UserCallback(18);
        }
          data[i] = I2C_ReceiveData(GY_I2C); 
        }  
        
    }
end:
    //���BTF��־λ
    I2C_ClearFlag(GY_I2C, I2C_FLAG_BTF);
    //�ȴ�I2C�˳�æ
    while(I2C_GetFlagStatus(GY_I2C,I2C_FLAG_BUSY)!=RESET){
        if(count_wait--==0) return I2Cx_TIMEOUT_UserCallback(19);
    } 

    //Ϊ��һ����׼��
    I2C_AcknowledgeConfig(GY_I2C, ENABLE);
      //�ر�POS��־
    GY_I2C->CR1 &= ~I2C_CR1_POS;
    
    return value;
}


static uint32_t I2Cx_TIMEOUT_UserCallback(char value){

  I2C_InitTypeDef I2C_InitStructure;
  
  I2C_GenerateSTOP(GY_I2C, ENABLE);
  I2C_SoftwareResetCmd(GY_I2C, ENABLE);
  I2C_SoftwareResetCmd(GY_I2C, DISABLE);
  
  I2C_DeInit(GY_I2C);
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = STM32_OWN_ADRESS7;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = GY_Speed;
    
  /* Enable the I2C peripheral */
  I2C_Cmd(GY_I2C, ENABLE);  
    
  /* Initialize the I2C peripheral */
  I2C_Init(GY_I2C, &I2C_InitStructure);
	
    I2C_ERROR("I2C callback error code = %d",value);

  return 1;
}

int Sensor_Write(uint8_t slave_addr,uint8_t reg_addr,unsigned short lens,uint8_t* data){
    int ret=0,retries=0;
    static unsigned int NUM  = 55;
Again:  
    ret = 0;
    ret = GY_Byte_Write( slave_addr, reg_addr, lens, data);

    if(ret && NUM)
    {
       if( retries++ > 4 )
          return ret;
        
       Soft_Dely(0XFFFFF);
       goto Again;
    } 
    return ret;
    
}

int Sensor_Read(uint8_t slave_addr,uint8_t reg_addr,unsigned short lens,uint8_t* data){
    int ret=0,retries=0;
    static unsigned int NUM  = 55;
Again:  
    ret = 0;
    ret = GY_Byte_Read( slave_addr, reg_addr, lens, data);

    if(ret && NUM)
    {
        if( retries++ > 4 )
            return ret;
    
        Soft_Dely(NUM);
        goto Again;
    } 
    return ret;
}


void Soft_Dely(uint32_t num){
    while(num)
        num--;
}
