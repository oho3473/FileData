#include "Monster.h"

bool CreateFromFile(const char* filename, std::vector<Monster>& vector)
{
	std::ifstream ist;

	ist.exceptions(std::ifstream::badbit);

	try
	{
		ist.open(filename);

		std::string buffer;
		std::vector<std::string> argVector;

		std::getline(ist, buffer);
		while (!ist.eof())
		{
			/*std::getline(ist, buffer);
			
			if (std::count(buffer.begin(), buffer.end(), ',') == 3)
			{
				std::stringstream ss(buffer);
				for (int i= 0; i<4;++i)
				{
					std::string token;
					std::getline(ss, token, ',');
					argVector.push_back(token);
				}

				vector.push_back(Monster{
					argVector[0],
					std::stoi(argVector[1]),
					std::stoi(argVector[2]),
					std::stoi(argVector[3]) });

				argVector.clear();
			}
			else
			{
				if (buffer.length() != 0)
				{
					std::cerr << "몬스터 데이터 양식이 잘못되었습니다\n";
				}
			}*/

			if (ist.peek() == EOF)
			{
				break;
			}

			Monster monster;
			ist >> monster;
			vector.push_back(monster);
		}

		ist.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "파일 연산 도중 예외가 발생했습니다\n" << e.what() << std::endl;
		ist.close();
		return false;
	}
	return true;
}

bool WriteToFile(const char* filename, std::vector<Monster>& vector)
{
	std::ofstream ost;
	ost.exceptions(std::ofstream::badbit);
	try
	{
		ost.open(filename);
		ost << "---MONSTER DATA---\n";

		for (auto monster : vector)
		{
			ost << monster;
		}
		ost.close();
	}
	catch(std::ofstream::failure e)
	{
		std::cerr << "파일 연산 도중 예외가 발생했습니다\n" << e.what() << std::endl;
		ost.close();
		return false;
	}

	return true;
}

std::istream& operator >>(std::ifstream& inputStream, Monster& monster)
{
	/*std::string buffer;
	try
	{
		std::getline(inputStream, buffer, ',');
		monster.mName = buffer;
		std::getline(inputStream, buffer, ',');
		monster.mLevel = std::stoi(buffer);
		std::getline(inputStream, buffer, ',');
		monster.mHp = std::stoi(buffer);
		std::getline(inputStream, buffer);
		monster.mMp = std::stoi(buffer);
	}
	catch(std::exception e)
	{
		std::cerr << "데이터 형식이 잘못 되었습니다\n";
	}
	return inputStream;*/

	return monster.ReadBinary(inputStream);
}

std::ofstream& operator <<(std::ofstream& ostream, Monster& monster)
{
 	/*try
	{
		ostream << monster.mName << ","
			<< monster.mLevel << ","
			<< monster.mHp << ","
			<< monster.mMp << std::endl;
	}
	catch (std::exception e)
	{
		std::cerr << "스트림에 쓸 때 오류가 발생했습니다\n";
	}
	return ostream;*/

	return monster.WriteBinary(ostream);
}

std::ifstream& Monster::ReadBinary(std::ifstream& istream)
{
	int strLen{};
	istream.read(reinterpret_cast<char*>(&strLen), sizeof(int));
	mName.resize(strLen);
	istream.read(&mName[0], strLen);
	istream.read(reinterpret_cast<char*>(&mLevel), sizeof(int));
	istream.read(reinterpret_cast<char*>(&mHp), sizeof(int));
	istream.read(reinterpret_cast<char*>(&mMp), sizeof(int));

	return istream;
}

std::ofstream& Monster::WriteBinary(std::ofstream& ostream)
{
	int strLen = static_cast<int>(mName.size());
	ostream.write(reinterpret_cast<char*>(&strLen), sizeof(int));
	ostream.write(mName.c_str(), strLen);
	ostream.write(reinterpret_cast<char*>(&mLevel),sizeof(int));
	ostream.write(reinterpret_cast<char*>(&mHp),sizeof(int));
	ostream.write(reinterpret_cast<char*>(&mMp),sizeof(int));

	return ostream;
}
