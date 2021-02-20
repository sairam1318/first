#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELD_FILE_NAME "fields.cfg"
#define MENU_FILE_NAME "menu.cfg"
#define DATA_FILE_NAME "clientData.dat"
#define MENU_LINE_LENGTH 50
#define FIELD_NAME_LENGTH 20
#define FIELD_VALUE_LENGTH 20

int getFieldCount();
char** stroreFieldName(int);

int getMenuCount();
char** storeMenuLine(int);
void printMenu(int, char**);
void menu(int, char **);

void create(int, char **);
void read(int, char**);
void exitMenu();

void chooseChoice(int, char**, int, char**);

void main(){

	int fieldCount = getFieldCount();

	char **namesOfField = stroreFieldName(fieldCount);
	int menuSize = getMenuCount();
	char **menuLine = storeMenuLine(menuSize);
	chooseChoice(fieldCount, namesOfField, menuSize, menuLine);
}

int getFieldCount(){

	FILE *fpField;
	char filedName[FIELD_NAME_LENGTH];
	int numberOfFields = 0;
	fpField = fopen(FIELD_FILE_NAME, "r");
	if(fpField == NULL){
		perror("\nError");
	}
	else{
		while(fgets(filedName, FIELD_NAME_LENGTH, fpField) > 0){
			numberOfFields ++;
		}
	}
	fclose(fpField);
	return numberOfFields;
}

char** stroreFieldName(int fieldCount){

	char **fieldNames;

	FILE *fpField;
	char tempfieldName[FIELD_NAME_LENGTH];
	fpField = fopen(FIELD_FILE_NAME, "r");
	if(fpField == NULL){
		perror("\nError");
	}
	else{
		int counter = 0;
		fieldNames  = (char **)malloc(fieldCount * FIELD_NAME_LENGTH);
		while(fgets(tempfieldName, FIELD_NAME_LENGTH, fpField) > 0){
			tempfieldName[strlen(tempfieldName) - 1] = '\0';
			fieldNames[counter] = (char *)malloc(FIELD_NAME_LENGTH);
			memcpy(fieldNames[counter], tempfieldName, FIELD_NAME_LENGTH);
			counter ++ ;
		}
	}
	fclose(fpField);
	return fieldNames;
}

int getMenuCount(){
	FILE *fpMenu;
	char menuLine[MENU_LINE_LENGTH];
	int menuCount = 0;
	fpMenu = fopen(MENU_FILE_NAME, "r");
	if(fpMenu == NULL){
		perror("Error");
	}
	else{
		while(fgets(menuLine, MENU_LINE_LENGTH, fpMenu) > 0){
			menuCount ++;
		}
	}
	fclose(fpMenu);
	return menuCount;

}

char** storeMenuLine(int menuSize){
	FILE *fpMenu;
	fpMenu = fopen(MENU_FILE_NAME, "r");
	char **menu;
	char menuLine[MENU_LINE_LENGTH];
	if(fpMenu == NULL){
		perror("Error");
	}
	else{
		menu = (char **)malloc(MENU_LINE_LENGTH * menuSize);
		int counter = 0;
		while(fgets(menuLine, MENU_LINE_LENGTH, fpMenu) > 0){
			menu[counter] = (char *)malloc(MENU_LINE_LENGTH);
			memcpy(menu[counter], menuLine, MENU_LINE_LENGTH);
			counter ++;
		}
	}
	fclose(fpMenu);
	return menu;
}

void printMenu(int menuCount, char** menuLine){
	for(int counter = 0; counter < menuCount; counter++){
		printf("%s", menuLine[counter]);
	}
}


void chooseChoice(int fieldCount, char **namesOfField, int menuCount, char **menuLine){
	int choice;
	while(1){
		printMenu(menuCount, menuLine);
		printf("\nEnter choice: ");
		scanf("%d", &choice);
		switch(choice){
			case 1: create(fieldCount, namesOfField);
			break;
			case 2: read(fieldCount, namesOfField);
			break;
			case 3: exitMenu();
			break;
			default: printf("Entered chioce is wrong. ");
			break;
		}

	}
}

void create(int fieldCount, char **namesOfField){
	FILE *fpData;
	char fieldValue[FIELD_VALUE_LENGTH];
	fpData = fopen(DATA_FILE_NAME, "a");
	if(fpData == NULL){
		perror("Errror");
	}
	else{
		for(int counter = 0; counter < fieldCount; counter ++){
			printf("Enter %s: ", namesOfField[counter]);
			scanf("%s", fieldValue);
			fwrite(fieldValue, FIELD_VALUE_LENGTH, 1, fpData);
		}
	}
	fclose(fpData);
}

void read(int fieldCount, char** namesOfField){
	FILE *fpData;
	char fieldValue[FIELD_VALUE_LENGTH];
	fpData = fopen(DATA_FILE_NAME, "r");
	if(fpData == NULL){
		perror("Error");
	}
	else{
		for(int counter = 0; counter < fieldCount; counter ++){
			printf("%s\t", namesOfField[counter]);
		}
		printf("\n");
		int counter = 1;

		while(fread(fieldValue, FIELD_VALUE_LENGTH, 1, fpData) == 1){

			printf("%s\t", fieldValue);
			if(counter == fieldCount){
				printf("\n");
				counter = 0;
			}
			counter ++;
		}
	}
	fclose(fpData);

}
void exitMenu(){
	exit(0);
}

