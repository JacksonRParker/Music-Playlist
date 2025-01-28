/******************************************************************************
#Author:		Jackson Parker
#Project:       Project 1
#Date:          10/19/2023
#Description:   This program is a music playlist. It uses a dynamically
#				allocated linked list to keep track of a songs, their artist,
#				the songs length, and the songs likes
#Input:         A command in the menu, the artist name, song, length and likes,
#				and the position of a song in the list
#Output:        The contents of the list; the artist name, the song title, the
#               song length, and the song likes
#Sources:       I got help from classmates at school
#*****************************************************************************/
#include "util.h"
#include "song.h"
#include "songlist.h"

//Helper function declarations
void displayMenu();
char readInCmd();
void executeCmd(char cmd, SongList& aList);
void add(SongList& aList);
void readInName(char * name);
void readInTitle(char * title);
float readInLength();
int readInLikes();
void editLikes(SongList& aList);
int readInPosition();
void search(SongList& aList);
void remove(SongList& aList);

//Main calls the constructor function for the list and calls the menu functions
int main()
{
	SongList aList("song.txt");
	char cmd;
	displayMenu();
	cmd = readInCmd();
	while(cmd != 'q')
	{
		executeCmd(cmd, aList);
		displayMenu();
		cmd = readInCmd();
	}
	aList.saveToFile("song.txt");
	cout << "Thank you for using this program!" << endl;
	return 0;
}

//Displays the menu
void displayMenu()
{
	cout << "Welcome to your music library" << endl;
	cout << "\ta: adds a song" << endl;
	cout << "\te: edits the number of likes for a song" << endl;
	cout << "\tp: lists all the songs in the library" << endl;
	cout << "\ts: searchs for songs by a given artist" << endl;
	cout << "\tr: removes songs with less likes than the given amount" << endl;
	cout << "\tq: quit" << endl;
	cout << endl;
}

//Reads command from the user
char readInCmd()
{
	char cmd;
	cout << "Enter command" << endl;
	cin >> cmd;
	cin.ignore(MAX, '\n');
	return cmd;
}

//This function calls the functions needed to execute the command
void executeCmd(char cmd, SongList& aList)
{
	switch(cmd)
	{
		case 'a':
			add(aList);
			break;
		case 'e':
			editLikes(aList);
			break;
		case 'p':
			aList.print(cout);
			break;
		case 's':
			search(aList);
			break;
		case 'r':
			remove(aList);
			break;
		default:
			cout << "Wrong command" << endl;
			break;
	}
}

//This function calls functions to get input from the user
void add(SongList & aList)
{
	Song aSong;
	char name[MAX];
	char title[MAX];
	float length;
	int likes;

	readInName(name);
	readInTitle(title);
	length = readInLength();
	likes = readInLikes();
	aSong.setName(name);
	aSong.setTitle(title);
	aSong.setLength(length);
	aSong.setLikes(likes);
	
	aList.add(likes, aSong);
}

//Gets a name from the user
void readInName(char * name)
{
	cout << "Enter the name of the artist: ";
	cin.get(name, MAX, '\n');
	cin.ignore(MAX, '\n');
}

//Gets a title from the user
void readInTitle(char * title)
{
	cout << "Enter the title of the song: ";
	cin.get(title, MAX, '\n');
	cin.ignore(MAX, '\n');
}

//Gets the length from the user
float readInLength()
{
	float length;
	cout << "Enter length: ";
	cin >> length;
	while(!cin)
	{
		cin.clear();
		cin.ignore(MAX, '\n');
		cout << "Invalid input. Enter length as 0.00: ";
		cin >> length;
	}
	cin.ignore(MAX, '\n');
	return length;
}

//Gets the likes from the user
int readInLikes()
{	
	int likes;
	cout << "Enter likes: ";
	cin >> likes;
	while(!cin)
	{
		cin.clear();
		cin.ignore(MAX, '\n');
		cout << "Invalid input. Please try again: ";
		cin >> likes;
	}
	cin.ignore(MAX, '\n');
	return likes;
}

//Gets a position from the user
int readInPosition()
{	
	int pos;
	cout << "Enter position: ";
	cin >> pos;
	while(!cin)
	{
		cin.clear();
		cin.ignore(MAX, '\n');
		cout << "Invalid input. Please try again: ";
		cin >> pos;
	}
	cin.ignore(MAX, '\n');
	return pos;
}

//Gets a position and likes from the user to change the likes of a song
void editLikes(SongList& aList)
{
	int likes;
	int pos;
	Song aSong;
	cout << "What song would you like to change the likes of?" << endl;
	pos = readInPosition();
	likes = readInLikes();
	aList.editLikes(likes, pos, aSong);
}

//Calls a function to search for songs by an artist
void search(SongList& aList)
{
	char name[MAX];
	readInName(name);
	aList.search(name);
}

//Finds the minimum likes wanted in the users music library
void remove(SongList& aList)
{
	int likes;
	cout << "Enter the minimum likes allowed in your library?" << endl;
	likes = readInLikes();
	aList.remove(likes);
}
