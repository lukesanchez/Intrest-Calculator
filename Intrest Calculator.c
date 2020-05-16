/*********************************************************************
Program Name: COP 2220 Project 4 (Intrest Calculator)

Description: This program allows              

Created by: n01447425	      	
Created on: Dec. 2, 2019    
Last modified: Dec. 4, 2019	
**********************************************************************/ 
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#define UP_TRM_LIMIT 99
#define LW_TRM_LIMIT 1
#define UP_APR_LIMIT 24.99
#define LW_APR_LIMIT .1
#define UP_DEP_LIMIT 100000
#define LW_DEP_LIMIT 1
#define PERIODS 1
#define MAX_ARRAY_SZ 99

//Function prototypes
bool printinstructions(void);
bool getTermYears(int*, int, int);
bool getAPR(float*, float, float);
bool getInitialBalance(double*, double, double);
bool withinLimits(double value, double upLimit, double lowLimit);
bool produceSavingsSchedule(int, float, double);
void getFileName(char*);        

//get output filename from user
//pass in array of values and file name to print out to file

int main()
{
	//Local Declarations
	int term = 0;
	float APR = 0.0;
	double deposit = 0.0;
    char fileName[80];

	//Local Statements
	if(printinstructions())
	{
		printf("Do the calculations.\n");
		getTermYears(&term, UP_TRM_LIMIT, LW_TRM_LIMIT);
		getAPR(&APR, UP_APR_LIMIT, LW_APR_LIMIT);
		getInitialBalance(&deposit, UP_DEP_LIMIT, LW_DEP_LIMIT);
		produceSavingsSchedule(term, APR, deposit);
		getFileName(fileName);
		printf("%s", fileName);
		printf("\n");
	}
	else
		printf("User wants to quit.\n");

	return 0;
}//end main
//Dont add Commenting here
bool printinstructions()
{
	char input[80]={0};
	char userChoice = ' ';
	printf("This program will create a savings schedule for an annual compounding savings account.\n");
	printf("Enter in 'c' to continue or 'q' to quit.\n");
	do{
		scanf(" %s", &input);
		userChoice = input[0];
		userChoice = tolower(userChoice);
		if(userChoice == 'c')
			return true;
		else if(userChoice == 'q')
			return false;
		else
			printf("The value you entered is invalid, please try again.\n");
	}while(userChoice != 'q' || userChoice != 'c');
}//end function
//Dont add Commenting here
bool getTermYears(int* term, int upLimit, int lowlimit)
{
	do{
		printf("Enter in the term for the savings in years.\n");
		scanf(" %d", *&term);
		if(withinLimits((double)*term, 100.0, 0.0))
			break;
		printf("The input was not correct.\n");
	}while(true);
	return true;
}//end function
//Dont add Commenting here
bool getAPR(float* APR, float upLimit, float lowLimit)
{
	do{
		printf("Enter the Annual Percentage Rate (APR).\n");	
		scanf(" %f", *&APR);
		if(withinLimits((double)*APR, (double)upLimit,(double)lowLimit))
			break;
		printf("The input was not correct.\n");
	}while(true);
	return true;
}//end function
//Dont add Commenting here
bool getInitialBalance(double* principal, double upLimit, double lowLimit)
{
	do{
		printf("Enter in the initial balance (principal).\n");
		scanf(" %lf", *&principal);
		if(withinLimits((double)*principal, (double)upLimit,(double)lowLimit))
			break;
		printf("The input was not correct.\n");
	}while(true);
	return true;
}//end function
//Dont add Commenting here
bool withinLimits(double value, double upLimit, double lowLimit)
{
	printf("The value entered: %10.2lf\n", value);
	if((value <= upLimit) && (value >= lowLimit))
		return true;
	else
		return false;
}
//Dont add Commenting here
bool produceSavingsSchedule(int years, float APR, double principal)
{
	double balance = principal;//The initial starting balance
	double begBalance = 0.0;//Balance at beginning of each term
	double totInt = 0.0;//Accumulated interest
	double earnings = 0.0;//interst earned in period
	float decRate = APR / 100;//decimal value of APR
	FILE* outfile = NULL;
	printf("Rate %4.2f \tBalance $%6.2lf \tTerm: %d years\n\n", decRate,balance, years);
	printf("| Period |  Beginning Balance |");
	printf(" Earned Interest | Ending Balance |");
	printf(" Accrued Interest |\n");
	printf("|________|____________________|_________________|________________|__________________|\n");
	for(int i = 0 ; i < years; i++)
	{	
	
		begBalance = balance;
		earnings = balance * decRate;	
		balance += earnings;
		totInt += earnings;
		printf("|     %3d", i);
		printf("|          %10.2lf", begBalance);
		printf("|       %10.2lf", earnings);
		printf("|      %10.2lf", balance);
		printf("|        %10.2lf", totInt);
		printf("|\n");
	}

	return true;
}//end function

void getFileName(char* Name){
	char fileExt[4] = ".txt";
	printf("Enter the output file name: ");
	fgets(Name, 80, stdin);
	strcat(fileExt, Name);
	printf("%s", Name);


	/*if (Name(strlen(Name) - 1) == '\n'){
		Name(strlen(Name) - 1) = '\0'; //remove newline char
	}*/

	return;
}
