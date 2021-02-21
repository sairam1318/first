
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 30
#define FIELD_FILE_NAME "fields.cfg"
#define MENU_FILE_NAME "menu.cfg"
#define DATA_FILE_NAME "data7.dat"

int getLineCount(char*);
char** storelinesIntoArray(char*, int);
void create();
void read();
void exitMenu();
void chooseChoice();

int fieldCount = 0, menuCount = 0;
char **arrField, **arrMenu; 

void main(){
	
	fieldCount = getLineCount(FIELD_FILE_NAME);
	menuCount = getLineCount(MENU_FILE_NAME);
	arrField = storelinesIntoArray(FIELD_FILE_NAME, fieldCount);
	arrMenu = storelinesIntoArray(MENU_FILE_NAME, menuCount);
	chooseChoice();

}
int getLineCount(char *fileName){
	FILE *fpText;
	int lineCounter = 0;
	char line[LINE_LENGTH];
	fpText = fopen(fileName, "r");
	if(fpText == NULL){
		perror("Error");
	}
	else{

		while(fgets(line, LINE_LENGTH, fpText) > 0){
			
			lineCounter ++;
		}
	}
	fclose(fpText);
	return lineCounter;
}

char** storelinesIntoArray(char *fileName, int numberOfLines){

	FILE *fpText;
	int counter = 0;
	char **arrLine;
	char line[LINE_LENGTH];
	fpText = fopen(fileName, "r");
	if(fpText == NULL){
		perror("Error");
	}
	else{

		arrLine = (char **)malloc(numberOfLines * sizeof(char*));
		while(fgets(line, LINE_LENGTH, fpText) > 0){
			line[strlen(line) - 1] = '\0';
			
			arrLine[counter] = (char *)malloc(LINE_LENGTH);
			strcpy(arrLine[counter], line);
			counter ++;	
		}
	}
	fclose(fpText);
	return arrLine;

}
void create(){

	FILE  *fpData;
	fpData = fopen(DATA_FILE_NAME, "a");

	char fieldValue[LINE_LENGTH];
	if(fpData == NULL){
		printf("Error");
	}
	else{
		for(int counter = 0; counter < fieldCount; counter ++){
			printf("Enter %s: ", arrField[counter]);
			scanf("%s", fieldValue);
			if(fwrite(fieldValue, LINE_LENGTH, 1, fpData) != 1){
				printf("Data written unsucessful");
			}
		}
	}
	fclose(fpData);

}
void read(){
	FILE  *fpData;
	fpData = fopen(DATA_FILE_NAME, "r");
	char fieldValue[LINE_LENGTH];
	if(fpData == NULL){
		printf("Error");
	}
	else{
		for(int counter = 0; counter < fieldCount; counter ++){
			printf("%s ", arrField[counter]);
			
		}
		printf("\n");
		int newLineCount = 1;
		while(fread(fieldValue, LINE_LENGTH, 1, fpData) > 0){
			printf("%s ", fieldValue);
			if(newLineCount == fieldCount){
				printf("\n");
				newLineCount = 0;
			}
			newLineCount ++;
		}
	}
	fclose(fpData);

}
void exitMenu(){
	exit(0);
}

void chooseChoice(){
	int choice;
	while(1){
		for(int counter = 0; counter < menuCount; counter ++){
			printf("\n%s", arrMenu[counter]);
		}
		printf("\nChose your choice: ");
		scanf("%d", &choice);
		switch(choice){
			case 1: create();
			break;
			case 2: read();
			break;
			case 3: exitMenu();
			break;
			default: printf("\nEntered choice is wrong.");
			break;

		}
	}
}


