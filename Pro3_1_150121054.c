/* Ceren Eren 150121054
This program takes an integer pointer and an integer N. It reverses the number's last N digits then prints it
*/

#include <stdio.h>

//this function calculates a to the power of b and returns it
int power(int a, int b) {
	int i;
	int sum;
	sum=1;
	for(i=0; i<b; i++)
		sum *= a;
	return sum;	
}

//this function calculates how many digits the given number has and returns it
int digitNum(int a) {
	int num;
	num=0;
	
	while(a>0) {
		a=a/10;
		num++;
	}
	return num;
}

//this function reverses the given numbers in the last N digits
void reverseN(int *number, int N) {
	//declare variables to be used later on
	int reversedBit;
	int i;
	int temp;
		
	//reverse the N bits and assign it to a variable
	for(i=0; i<N; i++) {
	reversedBit	+= *number%power(10,i+1)/power(10,i)*power(10,N-i-1);
	}
	//subtract the last N digits
	*number -= *number%power(10,N);
	//add the reversed bit
	*number += reversedBit;
	
}


int main(void) {
	//declare variables to be used later on
	int number;
	int N;
	
	//take inputs from the user
	scanf("%d%d",&number,&N);
	
	//if the N value given is bigger than the input's digit number give an error message
	if(N>digitNum(number)) 
		printf("N must be less than %d\n", digitNum(number)+1);
	
	//else call the reverseN function		 
	else {
		reverseN(&number,N);
		printf("%d\n",number);
	}	
}
