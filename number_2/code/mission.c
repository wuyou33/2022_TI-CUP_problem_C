/*
 * @Author: Ptisak
 * @Date: 2022-07-23 20:02:44
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-07-28 22:14:48
 * @Version: Do not edit
 */
#include "mission.h"
extern float t_a;
extern float t_b;
extern float t_c;
uint8 stop_flag = 0;
uint8 sonic_state = 1;
extern float disLoop_kp ;
void Mission_1(void)
{
	huifdu_flags.trace_mode = RIGHT_FIRST;
	while(1)
	{
		delay_ms(5);
//		OLED_ShowNum(16, 3, (int)ultrasonic_distance, 3, 16);
//		OLED_ShowNum(16, 5, (int)disLoop_speed, 3, 16);
		if(stop_flag == 1) 
			break;
	}
}
void Mission_2(void)
{
	Mission_1();
}
void Mission_3(void)
{
	static float temp_speed_1,temp_speed_2;
	if(basic_speed<=95)
	{
		temp_speed_1 = basic_speed*0.20;
		temp_speed_2 = basic_speed*0.20;
	}
	else if(basic_speed<=105)
	{
		temp_speed_1 = basic_speed*0.30;
		temp_speed_2 = basic_speed*0.20;
	}
	else
	{
		temp_speed_1 = basic_speed*0.30;
		temp_speed_2 = basic_speed*0.20;
	}
	
	huifdu_flags.trace_mode = RIGHT_FIRST;//�ոճ���
	
	until_distance(300);
	
	wait_for_condition(STOP_LINE);//��һȦ����
	// buzzer_bi_flag = 1;
	
	
	//------------------------------------------------------
	huifdu_flags.trace_mode = LEFT_FIRST;//����ѭ������
	until_distance(5);//��Ųһ��
	disLoop_kp = 0.0;
	wait_for_condition(RIGHT_HAVE_LINE);//������ʼ��
	// buzzer_bi_flag = 1;
	
	led_blink_flag = 71;

	until_distance(40);
	
	basic_speed += temp_speed_1;
	wait_for_condition(RIGHT_HAVE_LINE);//������ĩ��
	
	led_blink_flag = 0;//�ص�
	// buzzer_bi_flag = 1;
	
	until_distance(10);
	basic_speed -= temp_speed_1;  //�����ٶ�
	GPIO_SET(6, 0, 1);//��ʱ����Ϊ��������λ�ñջ�
	huifdu_flags.trace_mode = RIGHT_FIRST;//�л���ѭ��ģʽ
//	basic_speed -= 0; //�ָ���ʼ�ٶ�
	//------------------------------------------------------
	//�����ﵽ�����Ȧ
	wait_for_condition(STOP_LINE);
	
	until_distance(50);//��Ųһ��
//	buzzer_bi_flag = 1;
	basic_speed -= temp_speed_2;  //�����ٶ�



	until_distance(190);
	basic_speed += temp_speed_2;  //�ٶȼӻ�ȥ�ٶ�
	disLoop_kp = 1.1;
	
	GPIO_SET(6, 0, 0);//����λ�ñջ�
//	wait_for_condition(LEFT_HAVE_LINE);//������ĩ��
//	buzzer_bi_flag = 1;
	sonic_state = 1;
	until_distance(50);
	
	
	while(1)
	{
		delay_ms(5);
//		OLED_ShowNum(16, 3, (int)ultrasonic_distance, 3, 16);
//		OLED_ShowNum(16, 5, (int)disLoop_speed, 3, 16);
		if(stop_flag == 1) 
			break;
	}
	
	
	
}
extern float target_dis;
uint8 task_state = 0;
void Mission_4(void)
{
    static float temp_basic_speed;
    temp_basic_speed = basic_speed;
    target_dis += 10;
	huifdu_flags.trace_mode = RIGHT_FIRST;
	while(1)
	{
		delay_ms(5);
        if(task_state == 1)
        {
            basic_speed = 0;
            disLoop_kp = 0;
        }
        else if(task_state == 2)
        {
            basic_speed = temp_basic_speed;
            disLoop_kp = 1.1;
        }
        
		if(stop_flag == 1) 
			break;
	}
    task_state = 0;
    basic_speed = 0;
    target_dis -= 10;
}
void Mission_5(void)
{
	led_blink_flag = 0;//�ص�
	
	huifdu_flags.trace_mode = RIGHT_FIRST;
	
	until_distance(300);//��Ųһ��
	huifdu_flags.trace_mode = LEFT_FIRST;
	
	while(1)
	{
		delay_ms(5);
		if(stop_flag == 1) 
			break;
	}
	
}
void Mission_6(void)
{
	disLoop_kp = 1.1;
	target_dis = 38.0;
	
	led_blink_flag = 0;//�ص�
	
	huifdu_flags.trace_mode = RIGHT_FIRST;
	
	until_distance(550);//��Ųһ��
	
	
	wait_for_condition(STOP_LINE);//��һȦ����
	until_distance(5);//��Ųһ��
	
	
	target_dis = 90;
	until_distance(150);//��Ųһ��
	disLoop_kp = 0;
	
	until_distance(150);
	
	wait_for_condition(STOP_LINE);//��һȦ����
	until_distance(20);//��Ųһ��
	huifdu_flags.trace_mode = LEFT_FIRST;
	
	target_dis = 38.0;
	disLoop_kp = 1.1;
	
	while(1)
	{
		delay_ms(5);
		if(stop_flag == 1) 
			break;
	}
	
}

void Mission_fahui(void)
{

    huifdu_flags.trace_mode = LEFT_FIRST;//����ѭ������
    GPIO_SET(6, 0, 1);//��ʱ����Ϊ��������λ�ñջ�
    disLoop_kp = 0;//��ʼ��ʱ�򲻿�λ�ñջ�
    until_distance(60);//���ٲ����м�
    disLoop_kp = 1.1;//��λ�ñջ�
    until_distance(100);

    wait_for_condition(STOP_LINE);//��һȦ
    until_distance(60);//��Ųһ��

    basic_speed = 0;
}

uint8 task_number = 0;
extern float basic_speed;
uint8 task_start_flag = 0;

void slave_task(void)
{
	led_blink_flag = 1000;
	task_start_flag = 0;
	stop_flag = 0;
	
	while(1)
	{
		delay_ms(10);
//		OLED_ShowNum(16, 3, (int)ultrasonic_distance, 3, 16);
//		OLED_ShowNum(16, 5, (int)disLoop_speed, 3, 16);
		if(basic_speed>0) 
			break;
	}
	
	task_start_flag = 1;
	led_blink_flag = 0;//�ص�
	
	switch(task_number)
	{
		case 0x01:
			Mission_1();
			break;
		case 0x02:
			Mission_2();
			break;
		case 0x03:
			Mission_3();
			break;
		case 0x04:
			Mission_4();
			break;
		case 0x05:
			Mission_5();
			break;
		case 0x06:
			Mission_6();
			break;
	}
	
	led_blink_flag = 71;
	
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);

}

void fahui_task(void)
{
	led_blink_flag = 1000;
	task_start_flag = 0;
	stop_flag = 0;
	
	while(1)
	{
		delay_ms(10);
//		OLED_ShowNum(16, 3, (int)ultrasonic_distance, 3, 16);
//		OLED_ShowNum(16, 5, (int)disLoop_speed, 3, 16);
		if(basic_speed>0) 
			break;
	}
	
	task_start_flag = 1;
	led_blink_flag = 0;//�ص�
	
	switch(task_number)
	{
		case 0x01:
			Mission_1();
			break;
		case 0x02:
			Mission_2();
			break;
		case 0x03:
			Mission_3();
			break;
		case 0x04:
			Mission_4();
			break;
		case 0x05:
			Mission_5();
			break;
        case 0x06:
			Mission_fahui();
			break;
	}
	
	led_blink_flag = 71;
	
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);

}



