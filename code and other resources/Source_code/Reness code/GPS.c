-----------------------------------------------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------
// 16-bit SFR Definitions for "P89V51RD2"
//--------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------
// Global VARIABLES
//--------------------------------------------------------------------------------------------------------------------

unsigned char GPS_Time[10]="";

unsigned char Latitude_Arr[20]="ADSL";
unsigned char Longitude_Arr[20]="FDFS";
unsigned char Latitude_Arr_Store[10]="";
unsigned char Longitude_Arr_Store[10]="";

unsigned char Time_Print[10]="HH:MM:SS";
// data unsigned char Time_Print_Save[10]="HH:MM:SS";
unsigned char Hour=0, Min=0, Sec=0;

unsigned char GPS_Rx_Flag = 0;
unsigned char Module_Stollen_Flag = 0;

//unsigned int Wait_GPS = 0;


extern unsigned char Rx_data_arr0[400];
extern unsigned char Rx_count0;
extern unsigned char Rx_ST_Flag0;


//--------------------------------------------------------------------------------------------------------------------
// Global CONSTANTS
//--------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------
// Function PROTOTYPES
//--------------------------------------------------------------------------------------------------------------------

void GPS_Rx( void );

//--------------------------------------------------------------------------------------------------------------------
// void GPS_Rx( void )
//--------------------------------------------------------------------------------------------------------------------
// Function Name:	void GPS_Rx( void )
// Arguments	:	No arguments
// Return Value	:	No return value
// Description	:	This function 

void GPS_Rx( void )
{
	unsigned char i, j;

	GPS_Rx_Flag = 0;
	
	while( GPS_Rx_Flag == 0 )
	{
		//ALCD_Comm( 0x01 );								// Clear display Screen

		Rx_count0 = 0;									// Start UART Receive array from location zero
		Rx_ST_Flag0 = 0;									// Reset the Receive detection flag
		R_UART0_Start( );
		MSDelay(100);								// 1 sec delay
	
		//ALCD_Message( 0x84 , "2" );		
		Rx_count0 = 0;									// Start UART Receive array from location zero
		Rx_ST_Flag0 = 0;									// Reset the Receive detection flag

//		Wait_GPS = 0;
		while( Rx_ST_Flag0 == 0 )						// Loop untill we receive the first character through UART
		{
/*
			Wait_GPS++;
			MSDelay(1);
			if( Wait_GPS >= 3000 )
				break;
*/     
		}
		//ALCD_Message( 0x82 , "2" );		
		MSDelay(100);								
// Loop untill we receive 50 charachers. This is done because GPS gives more than 100 characters. the data required
// for us will come in first 50 characters.
//		Wait_GPS = 0;
		while( Rx_count0 <= 100 )
		{
/*
			Wait_GPS++;
			MSDelay(1);
			if( Wait_GPS >= 3000 )
			break;
*/
		}
		R_UART0_Stop( );
		//ALCD_Message( 0xC2 , "2" );		
		MSDelay(500);									// 1 sec delay
	
// This condition is to detect that we have received the right data.	
//	for(x=0; x
		for( j=0; j<=20; j++ )
		{
			if( (Rx_data_arr0[j]=='G') && (Rx_data_arr0[j+1]=='P') && (Rx_data_arr0[j+2]=='R') && (Rx_data_arr0[j+3]=='M') )
			{ 
//		if( Rx_data_arr0[1]=='G' && Rx_data_arr0[2]=='P' && Rx_data_arr0[3]=='G' )
//		{ 
//				ALCD_Message( 0xC4 , "2" );		
				GPS_Rx_Flag = 1;
				for( i=0; i<9 ; i++ )
				{
					GPS_Time[i] = Rx_data_arr0[7+i+j];
					Latitude_Arr[i] = Rx_data_arr0[18+i+j];
					Longitude_Arr[i] = Rx_data_arr0[31+i+j];
				}

// Convert character hour to number format
				Hour = 0;
				Hour = Hour + ((GPS_Time[0]-48)*10);
				Hour = Hour + (GPS_Time[1]-48);
				Hour = Hour + 6;
				
				if( Hour >= 24 )
					Hour = Hour - 24;
	
// Convert character minute to number format
				Min = 0;
				Min = Min + ((GPS_Time[2]-48)*10);
				Min = Min + (GPS_Time[3]-48);
				Min = Min + 30;
				if( Min >= 60 )
					Min = Min - 60;
			
		
				Time_Print[0] = (Hour/10)+48;
				Time_Print[1] = (Hour%10)+48;
				Time_Print[3] = (Min/10)+48;
				Time_Print[4] = (Min%10)+48;
				Time_Print[6] = GPS_Time[4];
				Time_Print[7] = GPS_Time[5];
				Time_Print[8] = '\0';
	
				Latitude_Arr[8] = '\0';
				Longitude_Arr[8] = '\0';

// ********* Testing ******************				

				MSDelay(2000);									// 1 sec delay
//				ALCD_Comm( 0x01 );								// Clear display Screen
				//ALCD_Message( 0x80 , Latitude_Arr );		
				//ALCD_Message( 0xC0 , Longitude_Arr );
				MSDelay(2000);									// 1 sec delay
// **********************************			
			}
// ********* Testing ******************				
/*
			else
			{
				ALCD_Comm( 0x01 );								// Clear display Screen
	//			ALCD_Message( 0x80 , "                " );		
				MSDelay(500);									// 1 sec delay
			}
*/
// **********************************			
/*
		if( Wait_GPS >= 3000 )
		{
			GPS_Rx_Flag = 1;

			ALCD_Comm( 0x01 );								// Clear display Screen
			ALCD_Message( 0x80 , Latitude_Arr );		
			ALCD_Message( 0xC0 , Longitude_Arr );
			MSDelay(2000);									// 1 sec delay
		}
*/
		}
	}
}


