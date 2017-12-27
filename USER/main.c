#include "sys.h"
//#include "delay.h"
//#include "usart.h"
#include "led.h"
#include "rtthread.h"

//ALIENTEK ̽����STM32F407������ ʵ��1
//�����ʵ�� -�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

static struct rt_thread led0_thread;//�߳̿��ƿ�
static struct rt_thread led1_thread;//�߳̿��ƿ�
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t rt_led0_thread_stack[1024];//�߳�ջ 
static rt_uint8_t rt_led1_thread_stack[1024];//�߳�ջ 

//�߳�LED0
static void led0_thread_entry(void* parameter)
{
	while(1)
	{
		LED0=0;  
		rt_thread_delay(RT_TICK_PER_SECOND/5);                //��ʱ 
        
		LED0=1;   
		rt_thread_delay(RT_TICK_PER_SECOND/5);                //��ʱ1s
	}
}

//�߳�LED1
static void led1_thread_entry(void* parameter)
{
	while(1)
	{
		LED1=0;  
		rt_thread_delay(RT_TICK_PER_SECOND/2);                //��ʱ 
        
		LED1=1;    
		rt_thread_delay(RT_TICK_PER_SECOND/2);                //��ʱ 
	}
}


int main(void)
{
     
    LED_Init();                     //��ʼ��LED  
    
    // ������̬�߳�
    rt_thread_init(&led0_thread,                 	//�߳̿��ƿ�
                   "led0",                       	//�߳����֣���shell������Կ���
                   led0_thread_entry,            	//�߳���ں���
                   RT_NULL,                     	//�߳���ں�������
                   &rt_led0_thread_stack[0],     	//�߳�ջ��ʼ��ַ
                   sizeof(rt_led0_thread_stack),  	//�߳�ջ��С
                   3,    //�̵߳����ȼ�
                   20);                         	//�߳�ʱ��Ƭ
    rt_thread_startup(&led0_thread);             	//�����߳�led0_thread  
				   
	rt_thread_init(&led1_thread,                 	//�߳̿��ƿ�
                   "led1",                      	//�߳����֣���shell������Կ���
                   led1_thread_entry,            	//�߳���ں���
                   RT_NULL,                     	//�߳���ں�������
                   &rt_led1_thread_stack[0],		//�߳�ջ��ʼ��ַ
                   sizeof(rt_led1_thread_stack), 	//�߳�ջ��С
                   2,    //�̵߳����ȼ�
                   20);         				   

	rt_thread_startup(&led1_thread);             //�����߳�led1_thread 
    
 
}


 



