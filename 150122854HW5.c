/*
This program creates a playlist in duration time order using the songs given in the input.txt file
It prints a menu that allows user to insert,delete nodes and print the playlist to either standart output or an output file
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//defining struct song and creating variables
typedef struct song {
	char songName[25];
	int duration;
	struct song *next;
}Song;

//shortening the song pointer with typedef keyword
typedef Song *SongPtr;

//creating the input output file variables
FILE *input;
FILE *output;

//this function inserts the given song in the playlist in duration time order
void insertNode(SongPtr *sPtr, Song *song) {
	SongPtr newPtr = malloc(sizeof(Song)); //creating enough space to store struct
		
	if(newPtr != NULL) { //if the space is created
		newPtr->duration=song->duration; //place duration in node
		strcpy(newPtr->songName,song->songName); //place song name in node
		newPtr->next=NULL;
		
		SongPtr previous = NULL; //create previous song pointer and assing it to null
		SongPtr current = *sPtr; //create current song pointer and assing it to start pointer
	
		while(current != NULL && (song->duration > current->duration)) { //find correct location in playlist
			previous = current;
			current = current->next;
		}	
	
			
		if(previous==NULL) { //if there's no previous insert to song to the beginning
			newPtr->next = *sPtr;
			*sPtr = newPtr;
		}
		
		else { //insert song to the correct location
			previous->next = newPtr;
			newPtr->next = current;
		}
	
    }
    
    else 
    	printf("%s is not inserted, no memory available.\n",song->songName);
    	
}

//this function searchs the playlist and deletes the song 
char deleteNode(SongPtr *sPtr, Song *song) {
	
	if(strcmp(song->songName,(*sPtr)->songName) == 0) { //if the first element is what we're looking for delete it
		SongPtr temp = *sPtr;
		*sPtr=(*sPtr)->next;
		free(temp); //free space so it won't cause memory leak
		return song->songName[0];
	}
	
	else {
		SongPtr previous = NULL;
		SongPtr current = (*sPtr)->next;
		
		while (current != NULL && strcmp(current->songName,song->songName) != 0) {  //find correct location in playlist
			previous = current;
			current = current->next;
		}
		
		if(current != NULL) { //delete the current song
			SongPtr temp = current;
			previous->next = current->next;
			free(temp); //free space
			return song->songName[0];
		}
	}
	return '\0';
}

//this function prints the playlist in duration time order
void printList(SongPtr current) {
	int i;
	i=1;
	if(current == NULL) //check if the playlist is empty
		puts("\nList is empty.\n");
	
	else { //else print songs
		puts("The list is in duration-time order: ");
		
		while(current != NULL) { 
			printf("\t%d%s",i,".");
			printf("%s%s%d%s%d\n",current->songName," ",current->duration/60,":",current->duration%60);
			current = current->next;
			i++;
		}
	}
}

//this function prints the songs in an output file
void fprintList(SongPtr current) {
	int i;
	i=1;
	if(current == NULL) //check if the playlist is empty
		puts("\nList is empty.\n");
	
	else { //else print songs to output file
		fprintf(output,"%s\n","The list is in duration-time order: ");
		
		while(current != NULL) {
			fprintf(output,"\t%d%s",i,".");
			fprintf(output,"%s%s%d%s%d\n",current->songName," ",(current->duration)/60,":",(current->duration)%60);
			current = current->next;
			i++;
		}
		
	}
}

int main(void) {
	
	//declaring variables
	SongPtr startPtr=NULL;
	int userChoice;
	int durationMin;
	int durationSec;
	char song[25];
	Song newSong;
	Song tempSong;
	char *tokPtr;
	char filename[25];
	
	int i;
 	i=1;
 	
 	//open input file
	if((input = fopen("songs.txt","r"))==NULL)  
		("Input file could not be opened.");


	while(!feof(input)) { //tokenize the input file line by line and add them to playlist
		fgets(song,100,input);
		tokPtr=strtok(song,"\t");
		tokPtr = strtok(NULL,":");
		durationMin = atoi(tokPtr);
		tokPtr = strtok(NULL,":");
		durationSec = atoi(tokPtr);
		strcpy(tempSong.songName,song);
		tempSong.duration = 60*durationMin + durationSec; //assign the duration in seconds 
		insertNode(&startPtr,&tempSong);
	}
	printList(startPtr); 
			
	while(1) {
		
		while(!feof(input)) {
			
		}
		
		//print instructions
		printf("\nEnter your choice:\n");
		printf("1 to insert a song to the list.\n");
		printf("2 to delete a song from the list.\n");
		printf("3 to print the songs in the list.\n");
		printf("4 to print the songs to an output file.\n");
		printf("5 to end.\n");
		printf("? ");
		
		scanf("%d",&userChoice);
		
		switch(userChoice) {
			case 1:
				printf("\nEnter a song name with duration:\n");
				getchar();
				gets(newSong.songName);
				tokPtr=strtok(newSong.songName,"\t"); //start tokenizing the first line of the input
				tokPtr = strtok(NULL,":");
				durationMin=atoi(tokPtr);
				tokPtr = strtok(NULL,":");
				durationSec=atoi(tokPtr);
				newSong.duration = durationMin * 60 + durationSec;
				insertNode(&startPtr,&newSong); //add the song to the playlist
				
			break;	
			
			case 2:
				printf("\nEnter a song name:\n");
				getchar();
				gets(newSong.songName);
				if(startPtr != NULL) { //if the playlist is not empty
					if(deleteNode(&startPtr,&newSong) != '\0') {
					printf("The song \"%s\" is deleted from the list!\n",newSong.songName); //delete the song
					}
					else
					printf("%s not found\n\n",newSong.songName); 
				}
				else
					puts("List is empty.\n");	
			break;
			
			case 3:
				printf("\n");
				printList(startPtr); //print the list
			break;
			
			case 4:
				printf("Enter a file name:\n"); //get the file name
				getchar();
				gets(filename);
				
				if((output = fopen(filename,"w"))==NULL) //open output file
					puts("Output file could not be opened.");
					
				else {
					fprintList(startPtr);
					fclose(output); //close the file
					printf("Output is printed to the file %s\n",filename);
				}
				
			break;
			case 5:
				exit(1);
			break;
				
		default:
			puts("Invalid choice.\n");
			break;
		}
	}
}

