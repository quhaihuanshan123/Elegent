#include "dm_drv.h"
extern CAN_HandleTypeDef hcan1;
CAN_RxHeaderTypeDef rx_header;
uint8_t rx_buff[8];

int float_to_uint(float x,float x_max,float x_min,int bits)
{	float span=x_max-x_min;
	float dea=x-x_min;
	return (int)(dea*(float)((1<<bits)-1)/span);
}

float uint_to_float(int x,float x_max,float x_min,int bits)
{	float span=x_max-x_min;
	return (float)x/((float)((1<<bits)-1))*span+x_min;

}


void Enable_ctr_motor(CAN_HandleTypeDef *hcan,uint16_t ID,uint8_t data[8])
{
	CAN_TxHeaderTypeDef tx_header;
	tx_header.DLC=0x08;
	tx_header.IDE=CAN_ID_STD;
	tx_header.RTR=CAN_RTR_DATA;
	tx_header.StdId=ID;
	
if(HAL_CAN_AddTxMessage(hcan,&tx_header,data,(uint32_t*)CAN_TX_MAILBOX0)!=HAL_OK){
	if(HAL_CAN_AddTxMessage(hcan,&tx_header,data,(uint32_t*)CAN_TX_MAILBOX1)!=HAL_OK){
		HAL_CAN_AddTxMessage(hcan,&tx_header,data,(uint32_t*)CAN_TX_MAILBOX2);
		}
	}
}


void MIT_ctr_Motor(CAN_HandleTypeDef *hcan,uint16_t ID,float p_des,float v_des,float kp,float kd,float torq)
{	CAN_TxHeaderTypeDef tx_header;
	uint16_t temp_p,temp_v,temp_kp,temp_kd,temp_torq;
	tx_header.DLC=0x08;
	tx_header.IDE=CAN_ID_STD;
	tx_header.RTR=CAN_RTR_DATA;
	tx_header.StdId=ID;
	
	temp_p=float_to_uint(p_des,P_MAX,P_MIN,16);
	temp_v=float_to_uint(v_des,V_MAX,V_MIN,12);
	temp_kp=float_to_uint(kp,KP_MAX,KP_MIN,12);
	temp_kd=float_to_uint(kd,KD_MAX,KD_MIN,12);
	temp_torq=float_to_uint(torq,T_MAX,T_MIN,12);
	
	uint8_t tx_buff[8];
	tx_buff[0]=(temp_p>>8);
	tx_buff[1]=temp_p;
	tx_buff[2]=(temp_v>>4);
	tx_buff[3]=((temp_v&0x0F)<<4)|(temp_kp>>8);
	tx_buff[4]=temp_kp;
	tx_buff[5]=(temp_kd>>4);
	tx_buff[6]=((temp_kd&0x0F)<<4)|(temp_torq>>8);
	tx_buff[7]=temp_torq;
	
if(HAL_CAN_AddTxMessage(hcan,&tx_header,tx_buff,(uint32_t*)CAN_TX_MAILBOX0)!=HAL_OK){
	if(HAL_CAN_AddTxMessage(hcan,&tx_header,tx_buff,(uint32_t*)CAN_TX_MAILBOX1)!=HAL_OK){
		HAL_CAN_AddTxMessage(hcan,&tx_header,tx_buff,(uint32_t*)CAN_TX_MAILBOX2);
		}
	}
}
//����
uint32_t can_receive_bsp(CAN_HandleTypeDef *hcan,CAN_RxHeaderTypeDef rx_header,uint8_t rx_buff[8]){
if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header,rx_buff) == HAL_OK){	
	
	return rx_header.DLC;
}
	else return 0;
}

//�ص�
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan==&hcan1){
	can_receive_bsp(hcan,rx_header,rx_buff);
	}

}




