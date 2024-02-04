/* Ceren Eren 150121054
This program takes row and column values from the user and calculates how much backweight each person has in a human pyramid using both iteration and recursion.
*/
#include <stdio.h>

//this function calculates backweight using iteration
double calculateWeightBackV1(int row,int col) {
	//declare variables to be used later on
	int i; 
	int j;
	//declare a double array to store values and declare its first element to 0
	double arr[30][31];
	arr[0][0]=0.0;
	
	//store values in array according to pyramid
	for(i=1; i<30; i++) {
		for(j=0; j<=i; j++) {
			if(j==0)
				arr[i][j]=(arr[i-1][j] + 80)/2.0;
			else if(i==j)
				arr[i][j]=(arr[i-1][j-1] + 80)/2.0;
			else
				arr[i][j]=(arr[i-1][j] + arr[i-1][j-1] + 2*80)/2.0;
		}
	}
	return arr[row][col];
	
}

//this function calculates backweight using recursion
double calculateWeightBackV2(int row,int col) {
	//declare the initial value
	if(row==0 && (col)==0)
		return 0.0;
	//calculate values using the initial value and recursion
	else if(col==0)
		return (calculateWeightBackV2(row-1,col) + 80)/2.0;
	else if(row==col)
		return (calculateWeightBackV2(row-1,col-1) + 80)/2.0;
	else
		return (calculateWeightBackV2(row-1,col) + calculateWeightBackV2(row-1,col-1) + 2*80)/2.0;
	
}

//main function
int main(void) {
	//declare values to be used later on
	int row;
	int col;
	//get values from the user and assign them to variables
	printf("Please enter row and column values: \n");
	scanf("%d%d",&row,&col);
	//call each function and display the result
	printf("The weight on person in row %d and column %d calculated with iteration is %f\n",row,col,calculateWeightBackV1(row,col));
	printf("The weight on person in row %d and column %d calculated with recursion is %f\n",row,col,calculateWeightBackV2(row,col));
	
	return 0;
}

