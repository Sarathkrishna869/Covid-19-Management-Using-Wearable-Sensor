#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char loc[10][30]={"Ahmedabad","Bangalore","Chennai","Coimbatore","Delhi","Hyderabad","Kolkata","Mumbai","Pune","Thiruvananthapuram",};
int casesH[10]={0,0,0,0,0,0,0,0,0,0};
int casesM[10]={0,0,0,0,0,0,0,0,0,0};
int casesL[10]={0,0,0,0,0,0,0,0,0,0};

typedef struct{
	int location;
	char cough;
	int temp;
}patient;

void Show_Location(){
	int i;
	printf("\n");
	for(i=0;i<10;i++){
		printf("\n");
		printf("Id %d: %s \n",i,loc+i);
		
	}

}
void Show_Cases(){
	printf("\n--------------- CASE SUMMARY ---------------\n\n");
    printf("\nNumber of cases in every location are: \n");
    int count = 0;
    printf("\nHigh \n \n");
    while(count<10){
        printf("%s: %d \n",loc+count,casesH[count]);
        count++;
    }
    count = 0;
    printf("\nMedium \n \n");
    while(count<10){
        printf("%s: %d \n",loc+count,casesM[count]);
        count++;
    }
    count = 0;
    printf("\nLow \n \n");
    while(count<10){
        printf("%s: %d \n",loc+count,casesL[count]);
        count++;
    }
}

int Check_Choice(char choice){
	
	int flag = 0;
	while(!flag)
	{
		switch(choice){
		    case 1:
			    Show_Location();
			    flag =1;
			    break;
		    case 2:
		        flag =1;
			    break;
		    default:
			    printf("\n");
			    printf("Not a valid input! Try again :");
			    scanf("%d",&choice);
			    break;
			
		}
	}	
}
int Check_Temperature(temp){
	if(!(temp>90 && temp<105)){
		printf("Invalid temperature!! \nEnter temperature again : ");
		scanf("%d",&temp);
		Check_Temperature(temp);
	}
	else{
		return temp;
	}
}
char Check_Cough(cough){
	while(!(cough=='y' || cough=='n')){
		printf("Invalid entry!! \nEnter whether the patient have cough or not? ");
		scanf("%c");
		scanf("%c",&cough);	
	}
	return cough;
}
int Check_Location(location){
	if(!(location>-1 && location<10)){
		printf("Invalid Location code!! \nEnter code again : ");
		scanf("%d",&location);
		Check_Location(location);
	}
	else{
		return location;
	}
}
int Show_Remedials(int index,patient *dynmem){
	int temp = (dynmem+index)->temp;
	char cough = (dynmem+index)->cough;
	int chance;
	if (temp>=100 && cough=='y')
	{
		printf("\nHigh possibility of covid-19 is found.\n");
		printf("Immediately consult a doctor.\n");
		chance = 3;
		return chance;
	}
	else if ((temp>=100 && cough=='n' )|| ((temp>=99 && temp<100 )&& cough=='y'))
	{
		printf("\nMedium possibility of covid-19 is found.\n");
		printf("Try and isolate yourself and book a covid-19 test. \n");
		chance = 2;
		return chance;
	}
	else if ( ((temp>=99 && temp<100 )&& cough=='n') || (temp<99 && cough=='y'))
	{
		printf("\nLow possibilty of covid-19 is found.\n");
		printf("Stay catious and consult a doctor if anymore symptoms are found.\n");
		chance = 1;
		return chance;
	}
	else if (temp<99 && cough=='n')
	{
		printf("\nNo Symptoms of covid-19 is found.\n");
		printf("You do not have covidd-19.\n");
		chance = 0;
		return chance;
	}
	
}

void Get_Details(int size,patient *dynmem){
	int count = 0;
	int choice;
	char cough;
	printf("Do you want to see the location codes for all the locations(1-yes or 2-no):");
	scanf("%d",&choice);
	Check_Choice(choice);
	do{
		printf("\n");
		printf("Enter the temperature of the patient(in Fahrenheit):");
		scanf("%d",&(dynmem + count)->temp);
		(dynmem + count)->temp = Check_Temperature((dynmem + count)->temp);
		printf("Does the patient have cough? \n");
		scanf("%c");
		scanf("%c",&((dynmem + count)->cough));
		(dynmem + count)->cough = Check_Cough((dynmem + count)->cough);
		printf("Enter the location code of the patients(0-9):");
		scanf("%d",&(dynmem + count) ->location);
		(dynmem + count)->location = Check_Location((dynmem + count)->location);
		
		int chance = Show_Remedials(count,dynmem);
		if(chance == 3){
			casesH[((dynmem + count) ->location)]+=1;
		}
		if(chance == 2){
			casesM[((dynmem + count) ->location)]+=1;
		}
		if(chance == 1){
			casesL[((dynmem + count) ->location)]+=1;
		}
		printf("\n");
		count++;
	}while(count<size);
	
}
void Show_Details(int size,patient *dynmem){
	printf("\n--------------- PATIENT RECORDS ---------------\n\n");
	int count = 0;
	do{
		printf("\n");
		printf("Temperature of patient %d is %d degrees Fahrenheit.",count+1,(dynmem + count)->temp);
		printf("\n");
		printf("Cough : %c .\n",(dynmem + count)->cough);
		printf("Location Id of the patient is %d.",(dynmem + count) ->location);
		printf("\n");
		printf("Location is %s.",(loc + ((dynmem + count) ->location)));
		printf("\n");
		count++;
	}while(count<size);
	printf("--------------------------------------------------\n\n"); 
}

int main(){
	int size, days, i;
	printf("--------------------Welcome to COVID-19 Portal--------------------\n");
	printf("Enter number of days taken into this analysis: ");
	scanf("%d",&days);
	for(i=0;i<days;i++)
	{
	printf("\nDay no.%d :",i + 1);
	printf("\nEnter the number of patients for the day: ");
	scanf("%d",&size);
	printf("\n");
	patient *dynmem = (patient*)malloc(size*sizeof(patient));
	//printf("mremomry allocated = %d",sizeof(dynmem));
	Get_Details(size,dynmem);
	Show_Details(size,dynmem);   
	}
	Show_Cases();
	return 0;
}

/*
	GROUP G:
	Covid-19 Management Using Wearable Sensors:-
	STUDENT NAME	STUDENT ROLL NUMBER
	SANJAYAN S	CB.EN.U4CSE20255
	SREEDATH SURESH	CB.EN.U4CSE20262
	KOWSHEK IYYAPPAN T.M	CB.EN.U4CSE20233
	SHAIK ABDUL BASITH	CB.EN.U4CSE20257
	SARATH KRISHNA C K	CB.EN.U4CSE20256
*/