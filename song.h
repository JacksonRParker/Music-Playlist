#pragma once
#include "util.h"

class Song
{
public:
	//Constructors and destructor
	Song();
	Song(const char * name, const char * title, float length, int likes);
	Song(const Song& aSong);
	~Song();

	//Get functions
	const char * getName() const;
	const char * getTitle() const;
	float getLength() const;
	int getLikes() const;

	//Set functions
	void setName(const char * name);
	void setTitle(const char * title);
	void setLength(float length);
	void setLikes(int likes);

	//Print function and overloading function
	void print(ostream& out) const;
	const Song& operator= (const Song& aSong);

private:
	//Private variables
	char * name;
	char * title;
	float length;
	int likes;

	//Assigns variables
	void init(const char * name, const char * title, float length, int likes);
};
//cout overloading function
ostream& operator<< (ostream& out, const Song& aSong);
