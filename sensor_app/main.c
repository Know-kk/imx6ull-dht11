#include<stdio.h>
#include<stdlib.h>
#include "sensor.h"

int main()
{
	system("mkdir -p data");
    int choice;
	SensorData temp = {0.0f,0.0f};
	SensorData data = {0.0,0.0};
    printf("Sensor Monitor\n");
    printf("======================\n");
    printf("1.add data\n");
    printf("2.browse data\n");
    printf("3.browse previous data\n");
    printf("4.statistics \n");
    printf("5.clear data\n");
    printf("0.exit\n");
    
    
    while(1)
    {
    	printf("please choose:\n");
    	scanf("%d",&choice);
    	if(choice==0)
    	break;
       switch(choice)
    {
        case(1):
       {
         	add_data(&data);
			break; 
       }
        case(2):
        {
           	browse_data(&data);
		   	break;
        }
        case(3):
        {
			browse_previous_data(&temp);
            break;	
        }
		case(4):
		{
			statistics(&temp);
			break;
		}
		case(5):
		{
			clear_data(&data);
			break;
		}
        default:
            printf("erro\n");
            
    }    

}
		return 0;
}