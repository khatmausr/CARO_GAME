#include "common.h"
#include "HighScoreManager.h"

extern std::istream& operator >> (std::istream& in, tm*& ltm);
extern std::ostream& operator << (std::ostream& out, tm*& ltm);

std::istream& operator >> (std::istream& in, HighScoreInfo& temp)
{
	std::getline(in, temp._playerName);
	in >> temp._typeGame >> temp._score >> temp._scoreX >> temp._scoreO;
	in >> temp._ltm; in.ignore();
	return in;
}

std::ostream& operator << (std::ostream& out, HighScoreInfo& temp)
{
	out << temp._playerName << std::endl;
	out << temp._typeGame << " " << temp._score << " " << temp._scoreX << " " << temp._scoreO << std::endl;
	out << temp._ltm << std::endl;
	return out;
}

void HighScoreManager::updateHighScoreList()
{
	highScoreList.clear();

	std::ifstream fin("savegame/HighScore.DAT");

	int n; fin >> n; fin.ignore();
	for (int i = 0; i < n; i++)
	{
		HighScoreInfo temp; temp._ltm = new tm;
		fin >> temp;
		highScoreList.push_back(temp);
	}

	fin.close();

	sortHighScoreList();
}

void HighScoreManager::sortHighScoreList()
{
	int n = (int)highScoreList.size();

	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
		{
			if (highScoreList[i]._score < highScoreList[j]._score)
			{
				HighScoreInfo temp = highScoreList[i];
				highScoreList[i] = highScoreList[j];
				highScoreList[j] = temp;
			}
		}
}

void HighScoreManager::updateFileManager()
{
	std::ofstream fout("saveGame/HighScore.DAT");

	fout << highScoreList.size() << std::endl;
	for (unsigned int i = 0; i < highScoreList.size(); i++)
		fout << highScoreList[i];

	fout.close();
}

void HighScoreManager::pushHighScore(HighScoreInfo& temp)
{
	updateHighScoreList();

	bool isExist = false;
	for (unsigned int i = 0; i < highScoreList.size(); i++)
		if (highScoreList[i]._playerName == temp._playerName)
		{
			if (highScoreList[i]._score < temp._score)
				highScoreList[i] = temp;
			isExist = true;
		}

	if (!isExist)
	{
		if (highScoreList.size() < MAX_RECORD)
			highScoreList.push_back(temp);
		else
		{
			for (unsigned int i = 0; i < highScoreList.size() - 1; i++)
				highScoreList[i] = highScoreList[i + 1];
			highScoreList[highScoreList.size() - 1] = temp;
		}
	}

	updateFileManager();
}

void HighScoreManager::showHighScore()
{
	updateHighScoreList();

	// Declaire for some object
	std::vector <Text> stat(highScoreList.size());
	for (unsigned int i = 0; i < stat.size(); i++)
	{
		stat[i].setFont(font_arial);
		stat[i].setFillColor(Color::White);
		stat[i].setCharacterSize(30);
		stat[i].setPosition(Vector2f(0.f, 5.f + 50.f * i));
		stat[i].setString(highScoreList[i]._playerName + " " + std::to_string(highScoreList[i]._score) + " (" + std::to_string(highScoreList[i]._scoreX) + "-" + std::to_string(highScoreList[i]._scoreO) + ")");
	}

	// Show High Scores
	bool isDone = false;
	while (!isDone)
	{
		// Event
		Event e;

		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				isDone = true;
				window.close();
			}

			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Escape)
					isDone = true;
		}

		// Display
		window.clear(Color::White); window.draw(menuBackground);
		for (unsigned int i = 0; i < stat.size(); i++) window.draw(stat[i]);
		window.display();
	}
}