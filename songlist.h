#pragma once
#include "song.h"

class SongList
{
public:
	//Constructor and destructor
	SongList();
	SongList(const char * fileName);
	~SongList();

	//List commands
	void add(int likes, const Song& aSong);
	void search(char * name);
	void editLikes(int likes, int pos, Song& aSong);
	void remove(int likes);
	void print(ostream& out) const;
	void loadFromFile(const char * fileName);
	void saveToFile(const char * fileName) const;

private:
	//Node that contains data and a pointer to the next node
	struct Node
	{
		Song song;
		Node * next;
	};

	//Head and tail pointer with list size
	Node * head, * tail;
	int size;

	//Private functions that print and assign variables
	void init();
	void print(Node * currHead, int currPos, ostream& out) const;
};
