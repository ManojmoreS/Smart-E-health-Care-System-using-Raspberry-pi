// Tool chain: CubeSuite+

//--------------------------------------------------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------
// Global VARIABLES
//--------------------------------------------------------------------------------------------------------------------

unsigned int buffer, ADC_Volt, ADC_Data, Volt_Temp;
// unsigned char Volt_Value[10]="00.00V";
unsigned char Volt_Value[6]="000";
unsigned int ADC_Data_Arr[50];

//--------------------------------------------------------------------------------------------------------------------
// Global CONSTANTS
//--------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------
// Function PROTOTYPES
//--------------------------------------------------------------------------------------------------------------------

void ADC30_Start( unsigned char Chan );
void MSDelay( unsigned int Milli_Sec );

//--------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------


void ADC30_Start( unsigned char Chan )
{
	unsigned char i;
	
	ADS = Chan;		// channel selection
	ADC_Data = 0;
	for( i=0; i<50; i++ )
	{
		R_ADC_Start( );
		MSDelay(10);
		R_ADC_Get_Result( &buffer );
		R_ADC_Stop( );

		ADC_Data_Arr[i] = buffer;
		ADC_Data = ADC_Data + ADC_Data_Arr[i];
	}
	ADC_Data = ADC_Data / 50;
	ADC_Volt =(( ADC_Data * 5.0 ) / 1023.0 ) * 1000;		
	Volt_Temp = ADC_Volt;



	Volt_Value[3] = (char)(ADC_Volt%10)+48;
	ADC_Volt = ADC_Volt / 10;
	Volt_Value[2]  = (char)(ADC_Volt%10)+48;
	ADC_Volt = ADC_Volt / 10;
	Volt_Value[1]  = (char)(ADC_Volt%10)+48;
	ADC_Volt = ADC_Volt / 10;
	Volt_Value[0]  = (char)(ADC_Volt%10)+48;

}



void MSDelay( unsigned int Milli_Sec )
{
	unsigned int x,y;

	for(x=0;x<Milli_Sec;x++)
	{
		for(y=0;y<3000;y++)
		{
			;
		}
	}
}


