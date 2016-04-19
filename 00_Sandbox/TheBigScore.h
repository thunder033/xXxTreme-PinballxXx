#ifndef THE_BIG_SCORE
#define THE_BIG_SCORE

#include "AppClass.h"
#include <iostream>
#include <fstream>

class TheBigScore
{
	static TheBigScore* instance;
	uint score;
	uint multiplier;
	uint highScore;
	TheBigScore();
	TheBigScore(TheBigScore const& other) {};
	TheBigScore& operator=(TheBigScore const& other) {};
	~TheBigScore();
public:
	void operator+=(const int& rhs);
	void operator-=(const int& rhs);
	std::ostream& operator<<(std::ostream& out);
	static TheBigScore* GetInstance();
	static void ReleaseInstance();
	uint HighScore();
	void SaveScore();
	void ReadScore();
};

#endif

