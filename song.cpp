#include "song.h"

//Song constructor
Song::Song()
{
	name = nullptr;
	title = nullptr;
	length = 0.0;
	likes = 0;
}

//Song constructor
Song::Song(const char * name, const char * title, float length, int likes)
{
	init(name, title, length, likes);
}

//Copy constructor for a Song
Song::Song(const Song& aSong)
{
	init(aSong.name, aSong.title, aSong.length, aSong.likes);
}

//Song destructor
Song::~Song()
{
	if(this->name)
		delete [] this->name;
	if (this->title)
		delete [] this->title;
}

//This function assigns given variables to private variables
void Song::init(const char * name, const char * title, float length, int likes)
{
	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);
	this->title = new char[strlen(title)+1];
	strcpy(this->title, title);
	this->length = length;
	this->likes = likes;
}

//Gets name
const char * Song::getName() const
{
	return name;
}

//Gets title
const char * Song::getTitle() const
{
	return title;
}

//Gets length
float Song::getLength() const
{
	return length;
}

//Gets likes
int Song::getLikes() const
{
	return likes;
}

//Allocates enough memory to fit the given name
void Song::setName(const char * name)
{
	if(this->name)
	{
		delete [] this->name;
	}
	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);
}

//Allocates enought memory to fit the given title
void Song::setTitle(const char * title)
{
	if(this->title)
	{
		delete [] this->title;
	}
	this->title = new char[strlen(title)+1];
	strcpy(this->title, title);
}

//Sets the length
void Song::setLength(float length)
{
	this->length = length;
}

//Sets the likes
void Song::setLikes(int likes)
{
	this->likes = likes;
}

//Prints the contents of the song data type
void Song::print(ostream& out) const
{
	out << name << "\t" << title << "\t" << length << "\t" << likes << endl;
}

//Overloading the out statement
ostream& operator<< (ostream& out, const Song& aSong)
{
	aSong.print(out);
	return out;
}

//Overloading the assignment operator
const Song& Song::operator= (const Song& aSong)
{
	if(this == &aSong)
		return *this;

	if (this->name)
	{
		delete [] this->name;
	}
	if (this->title)
	{
		delete [] this->title;
	}
	this->name = new char[strlen(aSong.name)+1];
	strcpy(this->name, aSong.name);
	this->title = new char[strlen(aSong.title)+1];
	strcpy(this->title, aSong.title);
	this->length = aSong.length;
	this->likes = aSong.likes;
	return *this;
}
