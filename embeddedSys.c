/********************************************************************************
* THIS PROGRAM IS ABOUT REVOLUTION THROUGH EMBEDDED SYSTEMS WITH DATA ANALYTICS.
* DATA STRUCTURE USED IN THIS SOURCE CODE IS : DYNAMIC QUEUES
* PROGRAM READS THE DATA FROM THE TEXT FILE.
* PROGRAM IS SIMULATION OF HOW SENSORS IN EMBEDDED SYSTEM WORKS.
* 
* FEATURES OF THE PROGRAM -
*	1. PROGRAM CAN BE SUSPENDED TO AUTOMATIC MODE.
*	2. STORES THE DATA INTO QUEUE AND PRINTS IT. (ONLY LAST 20 ENTRIES).
*	3. ALERTS THE USER WHEN THE PRE-DEFINED LIMTS ARE CROSEED.
*	4. PRINTS THE NAME OF SENSORS USED
*	5. PRINTS THE PREDEFINED LIMIT SET, FOR PROGRAMMING OF SYSTEM.
*	6. PROVIDE OPTION TO CHANGE OR UPDATE THE SENSOR NAMES.
*	7. PROVIDE OPTION TO REFRESH FOR UPDATING THE READINGS OF SENSORS.
*
* CODED BY : CHETAN S
* DATE : 20/12/21
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

// Predefined Limits.
#define MAX_TEMP 36
#define MAX_GASLEVEL 89
#define MAX_WINDSPEED 430

// Name of the Sensors in Embedded System.
char tempSensor[50] = "AD590";
char gasSensor[50] = "MQ136";
char windSensor[50] = "05103-L";

// Embedded System.
typedef struct{
	float tempData;
	float gasLevel;
	float windSpeed;
	char windDirection[10];
}MicroController;

// Node
typedef struct node{
	MicroController *m;
	struct node *next;
}Node;

// Creating front and rear
Node* front = NULL;
Node* rear = NULL;
	
// Creating front1 and rear1 for printing data in reverse order.
Node* front1 = NULL;
Node* rear1 = NULL;

/*	OPERATIONS ON QUEUE	*/
// Count Total number of Elements in Queue
int count(){
	int count = 1;
	Node *f = front;
	while(f){
		f=f->next;
		++count;
	}
	return count;
}

MicroController* dequeue(){
	MicroController *m = (MicroController*)malloc(sizeof(MicroController));
	Node *n;
	if(front == NULL){
		printf("Queue is Empty.\n");
	}else{
		m = front->m;
		n = front;
		front = front->next;
		free(n);
	}
	return m;
}

void enqueue(MicroController *m,int c){
	Node *n = (Node*)malloc(sizeof(Node));
	n->m = m;
	n->next = NULL;
	
	if(front == NULL){
		front = rear = n;
	}else{
		if(c <= 20){// when size of the entries made into queue are <= 20
			rear->next = n;
			rear = n;
		}else{ // when size of the entries are > 20
			dequeue();
			rear->next = n;
			rear =n;
		}
	}
}

// Reverses the Queue
void reverse(){
	Node *p = front;
	Node *q=NULL,*r=NULL;
	rear1 = front;
	while(p!=NULL){
		r=q;
		q=p;
		p=p->next;
		q->next=r;
	}
	front1=q;
}

// Print the data in queue in reverse order (only last 20 entries)
void printData(){
	reverse();
	Node *f = front1;
	
	printf(" RECENT DATA (LATEST FIRST, MAX UPTO 20 ENTRIES) :-\n\n");
	while(f){
		printf("   TEMPERATURE : %3.2f C   ||   GAS LEVEL : %3.2f  ||   WIND SPEED : %3.2f  ||   WIND DIRECTION : %s\n",f->m->tempData,f->m->gasLevel,f->m->windSpeed,f->m->windDirection);
		f=f->next;
	}
	printf("\n");
	printf(" ENTER ANY KEY TO ENTER MAIN MENU");
	char chr;
	scanf("%c",&chr);
	system("clear");
}

// Get the data pointed by rear pointer in Queue
MicroController* peek(Node *q){
	return q->m;
}

/*	OPERATIONS ON MICRO CONTROLLER.	*/
// Print data of single MicroController data
void printMicroControllerData(MicroController *m){
	printf("\n CURRENT TEMERATURE  		: %3.2f Centigrade",m->tempData);
	printf("\n CURRENT GAS LEVEL   		: %3.2f Percentage",m->gasLevel);
	printf("\n CURRENT WIND SPEED 		: %3.2f Meter/Second",m->windSpeed);
	printf("\n CURRENT WIND DIRECTION   	: %s\n",m->windDirection);
	printf("\n\n");
}

// List Name of Sensors.
void listSensors(){
	printf("\n THE SENSORS IN EMBEDDED SYSTEM ARE :-\n\t TEMPERATURE SENSOR   : %s\n\t GAS SENSOR 	      : %s\n\t WIND SENSOR 	      : %s\n\n",tempSensor,gasSensor,windSensor);
	printf("ENTER ANY KEY TO ENTER MAIN MENU");
	char chr;
	scanf("%c",&chr);
	system("clear");
}

// Printing the predefined Limits
void printSetLimits(){
	printf("\n THE PREDEFINE LIMIT SET ARE :- ");
	printf("\n\tMAX LIMIT FOR TEMPERATURE IS	: %d\n",MAX_TEMP);
	printf("\tMAX LIMIT FOR GAS LEVEL IS 	: %d\n",MAX_GASLEVEL);
	printf("\tMAX LIMIT FOR WIND SPEED IS	: %d\n",MAX_WINDSPEED);
	printf("\n");
	printf("ENTER ANY KEY TO ENTER MAIN MENU");
	char chr;
	scanf("%c",&chr);
	system("clear");
}

// Change the Sensors.
void changeSensors(){
	
	printf("\n ENTER THE NEW TEMPERATURE SENSOR : ");
	scanf("%s",tempSensor);
	printf(" ENTER THE NEW GAS SENSOR : ");
	scanf("%s",gasSensor);
	printf(" ENTER THE NEW WIND SENSOR : ");
	scanf("%s",windSensor);
	printf("\n ALL SENSORS UPDATED ..........\n");
	printf("\n");
	char chr;
	scanf("%c",&chr);
	printf(" ENTER ANY KEY TO ENTER MAIN MENU");
	scanf("%c",&chr);
	system("clear");
}

// Redifining the PreDefined Limits
void setLimits(){
	printf("\n THIS FEATURE IS NOT AVAILABLE YET ..\n");
	printf("\n");
	printf(" ENTER ANY KEY TO ENTER MAIN MENU");
	char chr;
	scanf("%c",&chr);
	system("clear");
}

// Buzzzer
void buzzer(){
	for(int i = 0; i < 5; ++i){
		printf("\a");
		//set correct sleep time
		sleep(0.5);
	}
	printf(" ==================================================================");
	printf("\n             ALERT. ALERT.. ALERT... ALERT.... ALERT.....\n");
	printf(" ==================================================================\n");
	printf(" THE PRE-DEFINED LIMITS REACHED ......\n\n");
}

// Starting the Program. 
void start(Node *n,bool enter){
	MicroController *m = peek(n);
	
	
	printf("\n _______________ WELCOME TO DEVELOPMENT ENVIRONMENT _______________\n\n");
	// When set to Automatic mode.
	if(!enter)
		printf(" NOTE :: THE SYSTEM  AUTOMATICALLY GET REFRESHED EVERY 10 SECONDS\n");
	printMicroControllerData(m);
	
	if((m->tempData > MAX_TEMP) || (m->gasLevel > MAX_GASLEVEL) || (m->windSpeed > MAX_WINDSPEED)){
			buzzer();
	}
	if(enter){
		printf(" MENU :-\n");
		printf("\t1. LIST LATELY UPDATED DATA.\n\t2. LIST SENSORS IN EMBEDDED SYSTEMS.\n\t3. CHECK THE PREDEFINED LIMITS SET FOR SENSORS.\n\t4. UPDATE THE SENSORS.\n\t5. RESET THE PREDEFINED LIMITS FOR SENSORS.\n\t6. REFRESH.\n\t7. SWITCH OFF THE SYSTEM.\n\n\t0. SET SYSTEM INTO AUTOMATIC MODE.\n");
	}
}

// Driver for the Program
int main(){
	Node *n = (Node*)malloc(sizeof(Node));
	n->m = (MicroController*)malloc(sizeof(MicroController));
	Node *n1 = (Node*)malloc(sizeof(Node));
	n1->m = (MicroController*)malloc(sizeof(MicroController));
	Node *n2 = (Node*)malloc(sizeof(Node));
	n2->m = (MicroController*)malloc(sizeof(MicroController));
	
	
// Creating File for Data
	char locationOfData[200] = "/home/chetans/Documents/"; // location of the file.
	char DataFileName[50] = "test"; // name of the text file.
	char str[250] = "";
	
	char fileName[254] = "";
	strcpy(str,locationOfData);
	strcat(str,DataFileName);
	sprintf(fileName,"%s.txt",str);
	

	FILE *fbook = fopen(fileName,"r");
	MicroController *m;
	
	int choice;
	char c;
	bool enter = true;
	while(true){
		m = (MicroController*)malloc(sizeof(MicroController));
		if(!fbook){
			printf("Failed to open the File\n");
			exit(0);
		}
		
// Reading from the file and storing in the queue.
		fscanf(fbook,"%f\t%f\t%f\t%s\n",&m->tempData,&m->gasLevel,&m->windSpeed,m->windDirection);
		enqueue(m,count());
// Index for the Program.		
		start(rear,enter);
		if(enter){
			printf("\n ------->>>>>>>  ");
			scanf("%d",&choice);
			scanf("%c",&c);
		
			switch(choice){
				case 0:
					enter = false;
					break;
				case 1:
					printData();
					break;
				case 2:
					listSensors();
					break;
				case 3:
					printSetLimits();
					break;
				case 4:
					changeSensors();
					break;
				case 5:
					setLimits();
					break;
				case 6:
					system("clear");
					continue;
				default:
					exit(0);
			}
		}
		
		// When set to Automatic Mode.
		if(!enter){
			printf("\n SYSTEM SUSPENDED AUTOMATIC MODE...\n PLEASE RESTART THE SYSTEM TO USE IT NORMALLY...\n");
			sleep(10);
			system("clear");
		}
	}
	return 0;
}

