//calling other functions having no main
#include <stdio.h>
int divideTwoNumbers(int, int);
int multiplyTwoNumbers(int, int);
int addTwoNumbers(int, int);

void main(){

	int sum = addTwoNumbers(5, 6);
	printf("\nSum is: %d", sum);
	int product = multiplyTwoNumbers(5, 6);
	printf("\nproduct is: %d", product);
	int reminder = divideTwoNumbers(6, 10);
	printf("\nReminder is: %d", reminder);
}