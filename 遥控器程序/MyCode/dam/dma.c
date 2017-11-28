#include "dma.h"
#define ADC1_DR_Address    ((uint32_t)0x4001244C)

u8  Uart1_Rx[UART_RX_LEN];
u8  Uart2_Rx[UART_RX_LEN];
u8	Uart1_Send[UART_RX_LEN];
u8	Uart2_Send[UART_RX_LEN];
u16 AD_Value[30][3];
void DMA_USART1_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    DMA_DeInit(DMA1_Channel5); 
 
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR); 
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Uart1_Rx; 
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; 
    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN; 
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; 
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; 	
    DMA_Init(DMA1_Channel5,&DMA_InitStructure); 
    DMA_Cmd(DMA1_Channel5,ENABLE);
	
	//DMA1ͨ��4����  
	DMA_DeInit(DMA1_Channel4);  
	//�����ַ  
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);  
	//�ڴ��ַ  
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Uart1_Send;  
	//dma���䷽����  
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  
	//����DMA�ڴ���ʱ�������ĳ���  
	DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;  
	//����DMA���������ģʽ��һ������  
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
	//����DMA���ڴ����ģʽ  
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	//���������ֳ�  
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
	//�ڴ������ֳ�  
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
	//����DMA�Ĵ���ģʽ  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  
	//����DMA�����ȼ���  
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
	//����DMA��2��memory�еı����������  
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
	DMA_Init(DMA1_Channel4,&DMA_InitStructure);  
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA1_Channel4, DISABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure);
	
}
void Uart1_Start_DMA_Tx(u16 size)
{
    DMA_SetCurrDataCounter(DMA1_Channel4,size);
    DMA_Cmd(DMA1_Channel4, ENABLE);
}
void  DMA1_Channel4_IRQHandler(void)//����1����DMA�ж�
{
    if(DMA_GetITStatus(DMA1_IT_TC4))
    {
		DMA_ClearITPendingBit(DMA1_IT_TC4);
		DMA_Cmd(DMA1_Channel4, DISABLE);
    }
}
void DMA_USART2_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    DMA_DeInit(DMA1_Channel6); 
 
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART2->DR); 
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Uart2_Rx; 
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; 
    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN; 
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; 
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; 	
    DMA_Init(DMA1_Channel6,&DMA_InitStructure); 
    DMA_Cmd(DMA1_Channel6,ENABLE);
	
	//DMA1ͨ��7����  
	DMA_DeInit(DMA1_Channel7);  
	//�����ַ  
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);  
	//�ڴ��ַ  
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Uart2_Send;  
	//dma���䷽����  
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  
	//����DMA�ڴ���ʱ�������ĳ���  
	DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;  
	//����DMA���������ģʽ��һ������  
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
	//����DMA���ڴ����ģʽ  
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	//���������ֳ�  
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
	//�ڴ������ֳ�  
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
	//����DMA�Ĵ���ģʽ  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  
	//����DMA�����ȼ���  
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
	//����DMA��2��memory�еı����������  
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
	DMA_Init(DMA1_Channel7,&DMA_InitStructure);  
	DMA_ITConfig(DMA1_Channel7,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA1_Channel7, DISABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure);
	
}
void Uart2_Start_DMA_Tx(u16 size)
{
    DMA_SetCurrDataCounter(DMA1_Channel7,size);
    DMA_Cmd(DMA1_Channel7, ENABLE);
}
void  DMA1_Channel7_IRQHandler(void)//����2����DMA�ж�
{
    if(DMA_GetITStatus(DMA1_IT_TC7))
    {
		DMA_ClearITPendingBit(DMA1_IT_TC7);
		DMA_Cmd(DMA1_Channel7, DISABLE);
    }
}
void DMA_ADC_Configuration(void)   
{ 
	DMA_InitTypeDef DMA_InitStructure; 
    DMA_DeInit(DMA1_Channel1);   
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;   
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_Value;   
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;   
 
    DMA_InitStructure.DMA_BufferSize = 90;   
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;   
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;   
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;   
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;   
  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;   
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;   
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;   
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);   
 
    DMA_Cmd(DMA1_Channel1, ENABLE);
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);   
} 
