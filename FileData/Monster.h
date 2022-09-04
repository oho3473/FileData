#pragma once
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<iostream>


class Monster
{
	std::string mName;
	int mLevel;
	int mHp;
	int mMp;

public:
	Monster() : mName{}, mLevel{}, mHp{}, mMp{}
	{}

	Monster(std::string name, int level, int hp, int mp) : mName{ name }, mLevel{ level }, mHp{ hp }, mMp{ mp }
	{}

	std::string Getname()
	{
		return mName;
	}

	std::ifstream& ReadBinary(std::ifstream& istream);
	std::ofstream& WriteBinary(std::ofstream& ostream);

	//friend std::istream& operator >>(std::ifstream& inputStream, Monster& monster);
	//friend std::ofstream& operator <<(std::ofstream& ostream, Monster& monster);

};

bool CreateFromFile(const char* filename, std::vector<Monster>& vector);
bool WriteToFile(const char* filename, std::vector<Monster>& vector);



std::istream& operator >>(std::ifstream& inputStream, Monster& monster);
std::ofstream& operator <<(std::ofstream& ostream, Monster& monster);

