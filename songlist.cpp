#include "songlist.h"
#include <fstream>

//Constructor
SongList::SongList()
{
	init();
}

//constructor that calls loadFromFile()
SongList::SongList(const char * fileName)
{
	init();
	loadFromFile(fileName);
}

//Sets size to 0 and head and tail to null
void SongList::init()
{
	head = tail = nullptr;
	size = 0;
}

//Destructor
SongList::~SongList()
{
	Node * curr = head;
	while(head)
	{
		head = curr->next;
		delete curr;
		curr = head;
	}
	head = tail = nullptr;
}

//This adds a new song to the list
void SongList::add(int likes, const Song& aSong)
{
	Node * prev = nullptr;
	Node * curr = head;
	int tempLikes = 0;
	Node * newNode = new Node;
	newNode->song = aSong;
	newNode->next = nullptr;
	if (!head)
	{
		head = newNode;
		tail = newNode;
	} 
	else
	{
		curr = head;
		tempLikes = curr->song.getLikes();
		while (curr && likes < tempLikes)
		{
			prev = curr;
			curr = curr->next;
			if (curr)
			{
				tempLikes = curr->song.getLikes();
			}
		}
		if (!curr)
		{
			tail->next = newNode;
			tail = newNode;
		}
		else if (prev)
		{
			newNode->next = curr;
			prev->next = newNode;
		}
		else
		{
			newNode->next = curr;
			head = newNode;
		}
	}
	size++;
	cout << endl;
}

//This function calls a print function
void SongList::print(ostream& out) const
{
	print(head, 0, out);
}

//Recursive function that prints the contents of the list
void SongList::print(Node * currHead, int currPos, ostream& out) const
{
	if (currHead)
	{
		out << currPos << " " << currHead->song << endl;
		print(currHead->next, ++currPos, out);
	}
}

//Loads the contents of the file into the list
void SongList::loadFromFile(const char * fileName)
{
	ifstream in;
	in.open(fileName);
	if(!in)
	{
		cerr << "Fail to open " << fileName << ", closing program!" << endl;
		exit(1);
	}
	
	char name[MAX];
	char title[MAX];
	float length;
	int likes;
	Song aSong;

	in.getline(name, MAX, ';');
	while(!in.eof())
	{
		in.getline(title, MAX, ';');

		in >> length;
		in.ignore(MAX, ';');

		in >> likes;
		in.ignore(MAX, '\n');
		
		aSong.setName(name);
		aSong.setTitle(title);
		aSong.setLength(length);
		aSong.setLikes(likes);

		this->add(likes, aSong);

		in.getline(name, MAX, ';');
	}
	in.close();
}

//Edits the likes of a song
void SongList::editLikes(int likes, int pos, Song& aSong)
{
	int count = 0;
	Node* curr = head;
	Node* prev;
	while(count < pos)
	{
		prev = curr;
		curr = curr->next;
		count++;
	}
	aSong.setName(curr->song.getName());
	aSong.setTitle(curr->song.getTitle());
	aSong.setLength(curr->song.getLength());
	aSong.setLikes(likes);
	if (!prev)
	{
		head = curr->next;
	}
	else if (curr == tail)
	{
		prev->next = curr->next;
		tail = prev;
	}
	else
	{
		prev->next = curr->next;
	}
	delete curr;
	size--;
	add(likes, aSong);
}

//Searches for songs made by a given artist
void SongList::search(char* name)
{
	bool found = false;
	char tempName[MAX];
	char tempTitle[MAX];
	float tempLength;
	int tempLikes;
	int count = 0;
	for (Node* curr = head; curr; curr = curr->next)
	{
		strcpy(tempName, curr->song.getName());
		if (strstr(tempName, name) != NULL)
		{
			found = true;
			strcpy(tempTitle, curr->song.getTitle());
			tempLength = curr->song.getLength();
			tempLikes = curr->song.getLikes();
			cout << count << " " << name << "\t" << tempTitle << "\t" << tempLength << "\t" << tempLikes << endl;
		}
		count++;
	}
	cout << endl;
	if (!found)
	{
		cout << "No music by this artist" << endl;
	}
}

//This removes a song with less than the given likes
void SongList::remove(int likes)
{

	Node* curr = head;
	Node* prev = nullptr;

	while(curr)
	{
		if(curr->song.getLikes() < likes)
		{
			if(!prev)
			{
				head = curr->next;
				delete curr;
				curr = head;
			}
			else if(curr == tail)
			{
				prev->next = nullptr;
				tail = prev;
				delete curr;
				curr = nullptr;
			}
			else
			{
				prev->next = curr->next;
				delete curr;
				curr = prev->next;
			}
			size--;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	cout << endl;
}

//This file reads the contents of the list into a file
void SongList::saveToFile(const char * fileName) const
{
	ofstream out;
	out.open(fileName);
	Node * curr;
	char tempName[MAX];
	char tempTitle[MAX];
	float tempLength;
	int tempLikes;
	for(curr = head; curr; curr = curr->next)
	{
		strcpy(tempName, curr->song.getName());
		strcpy(tempTitle, curr->song.getTitle());
		tempLength = curr->song.getLength();
		tempLikes = curr->song.getLikes();
		out << tempName << ";" << tempTitle << ";" << tempLength << ";" << tempLikes << endl;
	}
	out.close();
}
