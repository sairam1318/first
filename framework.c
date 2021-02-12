#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DATA_FILE_NAME "data1.dat"
#define FIELD_FILE_NAME "field1.cfg"
#define MENu_FILE_NAME "menu.cfg"
#define FIELD_NAME_LENGTH 50
#define FIELD_VALUE_LENGTH 20
#define MENU_LINE_LENGTH 50

static int numberOfFields = 0;
void showMenu();
void read();
void create();
void exitMenu();

FILE *fpMenu, *fpField, *fpData;


void main(){
	char fieldName[FIELD_NAME_LENGTH];
	fpField = fopen(FIELD_FILE_NAME, "r");
	if(fpField == NULL){
		perror("Field file read error.");
	}
	else{
		while(fgets(fieldName, FIELD_NAME_LENGTH, fpField) != NULL){
			numberOfFields = numberOfFields + 1;
		}
	}
	
	fclose(fpField);
	showMenu();

}

void showMenu(){
	int choice;
	char menu[MENU_LINE_LENGTH];
	fpMenu = fopen(MENu_FILE_NAME, "r");
	if(fpMenu == NULL){
		perror("Menu file read error.");
		exit(0);
	}
	else
	{
		while(1){
			fseek(fpMenu, 0, SEEK_SET);
			while(fgets(menu, MENU_LINE_LENGTH, fpMenu) != NULL){
				printf("%s", menu);
			}
			printf("Enter your choice: ");
			scanf("%d", &choice);
			switch(choice){
			case 1: create();
					break;
			case 2: read();
					break;
			case 3: exitMenu();
					break;
			default: printf("Entered choice is wrong. ");
					break;
			}
	
		}
	}
		
}

void create(){
	char fieldName[FIELD_NAME_LENGTH], fieldValue[FIELD_VALUE_LENGTH];
	fpField = fopen(FIELD_FILE_NAME, "r");
	fpData = fopen(DATA_FILE_NAME, "w");
	if(fpField == NULL || fpData == NULL){
		perror("File opening error.");
		exit(0);
	}else{
		while(fgets(fieldName, FIELD_NAME_LENGTH, fpField) != NULL){
			fieldName[strlen(fieldName) - 1] = '\0';
			printf("\nEnter the %s: ", fieldName);
			fflush(stdin);
			gets(fieldValue);
			if(fwrite(fieldValue, FIELD_VALUE_LENGTH, 1, fpData) != 1){
				printf("Data is not entered\n");
			}
		}
	}
	fclose(fpData);
	fclose(fpField);
	printf("\n\nData Entered Successfully.\n\n");

}

void read(){

	char fieldName[FIELD_NAME_LENGTH], fieldValue[FIELD_VALUE_LENGTH];
	fpField = fopen(FIELD_FILE_NAME, "r");
	fpData = fopen(DATA_FILE_NAME, "r");
	if(fpField == NULL || fpData == NULL){
		perror("File opening error.");
		exit(0);
	}
	else{
		
		printf("\n");
		while(fgets(fieldName, FIELD_NAME_LENGTH, fpField) != NULL){
			fieldName[strlen(fieldName) - 1] = '\0';
			printf("%s ", fieldName);
		}
		printf("\n");
		int token = 1;
		while(fread(fieldValue, FIELD_VALUE_LENGTH, 1, fpData) == 1){
			printf("%s ", fieldValue);
			if(numberOfFields == token){
				token = 0;
				printf("\n");
			}
			token ++;

		}
	}
	fclose(fpField);
	fclose(fpData);

}
void exitMenu(){
	printf("\n Thanks !");
	exit(0);
}