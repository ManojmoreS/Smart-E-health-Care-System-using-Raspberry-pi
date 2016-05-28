#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_serial.h"
#include "r_cg_adc.h"

#include "ADC.c"
#include "GPS.c"

#define Raspberry_Input P5.0
#include "r_cg_userdefine.h"
void Device_Init( void );
void GPS_Read_Send_UART2( void );
extern unsigned char Rx_data_arr0[400], Rx_data_arr1[100],Rx_data_arr2[100];
extern unsigned char Rx_count0, Rx_count1,Rx_count2;
extern unsigned char Rx_ST_Flag0, Rx_ST_Flag1,Rx_ST_Flag2;
extern unsigned char Rx_data0, Rx_data1,Rx_data2;
unsigned char GSM_Tx_Arr[27]="LA000000000LG000000000T00F0@";
void main(void)
{
	MSDelay(200);
	Device_Init( );
	
	GPS_Rx( );
	GPS_Read_Send_UART2( );
	MSDelay(2000);
	
	Rx_ST_Flag1 = 0;
	Rx_count1 = 0;
	Rx_ST_Flag0 = 0;
	Rx_count0 = 0;
	while(1)
	{
		ADC30_Start( 0x00 );
		MSDelay(100);
		Volt_Temp = ((Volt_Temp / 2) - 3) * 2;
		GSM_Tx_Arr[24] = (Volt_Temp%10) + 48;
		Volt_Temp = Volt_Temp / 10;
		GSM_Tx_Arr[23] = (Volt_Temp%10) + 48;
		MSDelay(100);
		
		ADC30_Start( 0x01 );
		MSDelay(100);
		if( (Volt_Temp >= 170) || (Volt_Temp <= 150) )
			GSM_Tx_Arr[26] = '1';
		else 
			GSM_Tx_Arr[26] = '0';
		MSDelay(500);
		if( Raspberry_Input == 1 )
		{
			GPS_Read_Send_UART2( );
			MSDelay(2000);
		}
	}
	
    while (1U)
    {
        ;
    }
}

void Device_Init( void )
{
	R_SAU0_Create( );
	R_UART0_Start( );
	MSDelay(500);
    R_SAU1_Create();
    R_UART2_Start( );
	R_UART2_Send( "UART2 TEST", 10 );	
	R_ADC_Create( );
	R_ADC_Set_OperationOn( );
}
void GPS_Read_Send_UART2( void )
{
	unsigned char i;

	GPS_Rx( );
	for( i=0; i<7 ; i++ )
	{
		GSM_Tx_Arr[i+2] = Latitude_Arr[i];
		GSM_Tx_Arr[i+13] = Longitude_Arr[i];
	}
	GSM_Tx_Arr[28] = '\0';
	MSDelay(500);
	R_UART2_Send( GSM_Tx_Arr , 28 );
	MSDelay(2000);	
	
}