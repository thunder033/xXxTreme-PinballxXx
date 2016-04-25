#include "TheBigScore.h"

TheBigScore* TheBigScore::instance = nullptr;

TheBigScore* TheBigScore::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new TheBigScore();
		instance->score = 0;
		instance->multiplier = 1;
		instance->highScore = 0;
	}
	return instance;
}

void TheBigScore::ReleaseInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void TheBigScore::operator+=(const int& rhs)
{
	score += rhs * multiplier;
}

void TheBigScore::operator-=(const int& rhs)
{
	score -= rhs * multiplier;
}

uint TheBigScore::HighScore()
{
	return highScore;
}

void TheBigScore::SaveScore()
{
	ReadScore();
	if (score > highScore)
	{
		std::ofstream saveFile;
		saveFile.open("samsaidtonameitsavedotdat.dat", std::ios::out | std::ios::trunc);
		if (saveFile.is_open())
		{
			saveFile << score;
			saveFile.close();
		}
		else
		{
			std::cout << "File failed to load";
		}
	}
}

void TheBigScore::ReadScore()
{
	std::ifstream saveFile;
	saveFile.open("samsaidtonameitsavedotdat.dat", std::ios::in);
	if (saveFile.is_open())
	{
		saveFile >> highScore;
		saveFile.close();
	}
}

std::ostream& TheBigScore::operator<<(std::ostream& out)
{
	return out << score;
}

TheBigScore::TheBigScore()
{
}


TheBigScore::~TheBigScore()
{
}
