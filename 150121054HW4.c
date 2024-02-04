/* Ceren Eren 150121054 
In this program I implemented my own Strings using C structs and wrote various string functions for finding chars in given index, concatting string, 
searching a string in another string and finding String Score.
*/

//Including libraries to use non restricted functions
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Creating a struct and shortening the name of the struct
typedef struct String {
	char string[50];
	int length;
}String;

String temp; //Creating a temporary String to return in concat function

//This function finds the character in given index and returns it
int charAt(String *s, int index) { 
	int i;
	char val;
		
	for(i=0; i<index+1; i++) 
		val=(*s).string[i];	
	val=toupper(val);
	//if the character value is null or the index is bigger than length or index is negative return -1
	if(val=='\0' || index>=s->length || index<0)
		return -1;
	
	else
		return (int)val;
}

//This function concats the second string at the end of the given string
String *concat(String *s1, String *s2) {
	int i;
	
	for(i=0; i<s1->length; i++) //Storing the first string in temporary string
		temp.string[i]=s1->string[i];
		
	for(i=strlen(s1->string); i<(s1->length + s2->length); i++) //Storing the second string in temporary string and concatting two strings
		temp.string[i]=s2->string[i-(s1->length)];
	
	temp.string[(s1->length + s2->length)]= '\0'; //putting null character at the end of string
	return &temp;
}

//This function searches the string one and returns the first segment that contains only the character of the second string
unsigned int strSearch(String *s1, String *s2) {
	char temp1[s1->length];
	int i;
	int j;
	unsigned int count;
	
	for(i=0;i<(s1->length+1);i++) //storing the first string in a temporary string
		temp1[i]=s1->string[i];
	
	//tokening the temporary string with space characters
	char *ptr=strtok(temp1," ");
	while(ptr != '\0') { //while the pointer is not showing null character searching the second string
		for(i=0; i<(*s2).length; i++) {
			for(j=0; j<strlen(ptr); j++){
				if(ptr[j]==s2->string[i]) {
					count++;
					break;
				}
			}
		}
		
		if(count==(*s2).length) //if the count is equal to the second string's length return the length of the pointer
			return strlen(ptr);
		
		else
			count=0;
		ptr=strtok(NULL," "); //else keep tokening the temporary string
	}
	return 0;
}

//This functions finds the score of given string according to given rules
unsigned int findScore(String *s1) {
	int i;
	unsigned int count;
	count=0;
	for(i=0; i<s1->length; i++) {
		if((*s1).string[i]=='A'||(*s1).string[i]=='a'||(*s1).string[i]=='E'||(*s1).string[i]=='e'||(*s1).string[i]=='I'||(*s1).string[i]=='i'||
		   (*s1).string[i]=='O'||(*s1).string[i]=='o'||(*s1).string[i]=='U'||(*s1).string[i]=='u'||(*s1).string[i]=='L'||(*s1).string[i]=='l'||
		   (*s1).string[i]=='N'||(*s1).string[i]=='n'||(*s1).string[i]=='R'||(*s1).string[i]=='r'||(*s1).string[i]=='S'||(*s1).string[i]=='s'||
		   (*s1).string[i]=='T'||(*s1).string[i]=='t')
			count +=1;
		else if((*s1).string[i]=='D'||(*s1).string[i]=='d'||(*s1).string[i]=='G'||(*s1).string[i]=='g')
			count +=2;
		else if((*s1).string[i]=='B'||(*s1).string[i]=='b'||(*s1).string[i]=='C'||(*s1).string[i]=='c'||(*s1).string[i]=='M'||(*s1).string[i]=='m'||
			    (*s1).string[i]=='P'||(*s1).string[i]=='p')
			count +=3;
		else if((*s1).string[i]=='F'||(*s1).string[i]=='f'||(*s1).string[i]=='H'||(*s1).string[i]=='h'||(*s1).string[i]=='V'||(*s1).string[i]=='v'||
			    (*s1).string[i]=='W'||(*s1).string[i]=='w'||(*s1).string[i]=='Y'||(*s1).string[i]=='y')
			count +=4;
		else if((*s1).string[i]=='K'||(*s1).string[i]=='k')
			count +=5;
		else if((*s1).string[i]=='J'||(*s1).string[i]=='j'||(*s1).string[i]=='X'||(*s1).string[i]=='x')
			count +=8;
		else if((*s1).string[i]=='Q'||(*s1).string[i]=='q'||(*s1).string[i]=='Z'||(*s1).string[i]=='z')
			count +=10;
	}
	return count;	
}

int main(int argc, char *argv[]) { //argument taking main method
	static int wordCount; //creating static wordCount and letterCount variables to store values
	static int letterCount;
	FILE *cifPtr; //c input file pointer
	FILE *cofPtr; //c output file pointer
	char *tokPtr; //pointer to token entered strings
	String temp[4]; //creating two arrays to store tokenized strings and their lengths
	int tempInt[4];
	int i; //iteration i
	int j; //iteration j
	
	//if the entered argument from the command line is not 3 print error message
	if(argc !=3) {
		printf("command line arguments: input file name and output file name\n");
		exit(1);
	}
	
	
	else {
		if((cifPtr = fopen(argv[1],"r"))==NULL)  
			puts("Input file could not be opened."); //if the input file with inputs doesn't exist print error message
		
		if((cofPtr = fopen(argv[2],"w"))==NULL) 
			puts("Output file could not be opened."); //if a file with the same name as argument 2 exists print error message
		
		
		else {
			printf("Program ran succesfully! Check the newly created output file.\n");
		
			while(!feof(cifPtr)) { //while the end of file is not entered
				
				//define some variables to use later on
				i=0;
				String inputS;
				fgets(inputS.string,100,cifPtr); //this function reads the input file line by line
			
				//if the given word is quit or exit aborts the program
				if(strcmp(inputS.string,"quit\n")==0 || strcmp(inputS.string,"exit\n")==0){
					fprintf(cofPtr,"%s","Program ends. Bye");
					break;	
				}
				
				//if the given word is stat gives the stats
				if(strcmp(inputS.string,"stat\n")==0){
					fprintf(cofPtr,"%s%d\n","The number of words: ", wordCount);	
					fprintf(cofPtr,"%s%d\n","The number of alphabetic letters: ",letterCount); 		
					continue;
				}
				
				//tokenize given String with :
				tokPtr = strtok(inputS.string,":");
					
				while(tokPtr != '\0'){
					//store tokenized strings in a string array	
					if(i==0)
						strcpy(temp[0].string,tokPtr);
					else if(i==1)
						strcpy(temp[1].string,tokPtr);
					else if(i==2)
						strcpy(temp[2].string,tokPtr);
					else 
						strcpy(temp[3].string,tokPtr);
							
					tokPtr = strtok(NULL,",");
					i++;
				}
				
				//convert the given strings to integer and store them in a integer array
				tempInt[0]=atoi(temp[0].string);
				tempInt[1]=atoi(temp[1].string);
				tempInt[2]=atoi(temp[2].string);
				tempInt[3]=atoi(temp[3].string);
				//assign the length of strings into length values
				temp[0].length=strlen(temp[0].string);
				temp[1].length=strlen(temp[1].string);
				temp[2].length=strlen(temp[2].string);
				temp[3].length=strlen(temp[3].string);
				
				//if the operation is 1 assign needed elements of arrays to null so it won't make a problem later and print the first operation in output file
				if(tempInt[1]==1) {
					temp[2].string[temp[2].length-1]='\0';
					temp[2].string[temp[2].length]='\0';
					temp[2].length=strlen(temp[2].string);
					temp[3].string[0] = '\0';
					fprintf(cofPtr,"%c\n",(char)charAt(&temp[0],tempInt[2]));
				}
				
				//if the operation is 2 assign needed elements of arrays to null so it won't make a problem later and print the second operation in output file
				else if(tempInt[1]==2) {
					temp[2].string[temp[2].length-1]='\0';
					temp[2].length=strlen(temp[2].string);
					temp[3].string[0] = '\0';
					fprintf(cofPtr,"%s\n",*concat(&temp[0],&temp[2]));
				}
				
				//if the operation is 3 assign needed elements of arrays to null so it won't make a problem later and print the third operation in output file
				else if(tempInt[1]==3) {
					temp[2].string[temp[2].length-1]='\0';
					temp[2].length=strlen(temp[2].string);
					temp[3].string[0] = '\0';
					fprintf(cofPtr,"%d\n",strSearch(&temp[0],&temp[2]));
				}
				
				//if the operation is 4 assign needed elements of arrays to null so it won't make a problem later and print the fourth operation in output file
				else if(tempInt[1]==4) {
					temp[1].string[temp[1].length-1]='\0';
					temp[1].length=strlen(temp[1].string);
					temp[2].string[0] = '\0';
					temp[3].string[0] = '\0';
					fprintf(cofPtr,"%d\n",findScore(&temp[0]));
				}
			
	
				//checking the string arrays and incrementing letter and word count
				wordCount++;
				for(i=0; i<4; i++) {
					if(i != 0 && isalpha(temp[i].string[0]) != 0 )
						wordCount++;
					while(temp[i].string[j] != '\0') {
						if(temp[i].string[j]<='z' && temp[i].string[j]>='A')
							letterCount++;
						if(isspace(temp[i].string[j]) !=0)
							wordCount++;
						j++;
					}
					j=0;	
				}				
			}
		fclose(cifPtr); //close the input file
		
 		}
	return 0;
	}	
}
