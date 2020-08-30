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
		stat[i].setString(std::to_string(i + 1) + std::string(4, ' ') + highScoreList[i]._playerName + std::string(15 + (6-highScoreList[i]._playerName.length()) ,' ') + std::to_string(highScoreList[i]._score) + std::string(8,' ') + std::to_string(highScoreList[i]._ltm->tm_mday) + ":" + std::to_string(highScoreList[i]._ltm->tm_mon) + ":" + std::to_string(highScoreList[i]._ltm->tm_year) + " " + std::to_string(highScoreList[i]._ltm->tm_hour) + ":" + std::to_string(highScoreList[i]._ltm->tm_min)+ ":" + std::to_string(highScoreList[i]._ltm->tm_sec));
		stat[i].setFont(font_robotoMonoBold);
		stat[i].setFillColor(Color::White);
		stat[i].setCharacterSize(30);
		stat[i].setPosition(Vector2f(140.0f, 210.f + 50.f * i));
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

		// Configure background
		window.clear(Color::White); window.draw(menuBackground);

		// Configure content background
		RectangleShape contentBg(Vector2f(1000.0f, 530.0f));
		contentBg.setFillColor(sf::Color(0, 0, 0, 150));
		contentBg.setOrigin(contentBg.getLocalBounds().width / 2.0f, 0);
		contentBg.setPosition(WINDOW_WIDTH / 2.0f, 170.0f);
		window.draw(contentBg);


		// Configure column title
		Text title("ID" + std::string(3, ' ') + "Player name" + std::string(10, ' ') + "Diff" + std::string(5, ' ') + "Time played", font_robotoMonoBold, 30);
		//title.setOrigin(title.getLocalBounds().width / 2.0f, 0);
		title.setPosition(140.0f, 170.0f);
		window.draw(title);
		for (unsigned int i = 0; i < stat.size(); i++) window.draw(stat[i]);
		window.display();
	}
}

std::string typeGameConverter(unsigned int typeGame)
{
	std::string type;
	switch (typeGame)
	{
	case 1:
		type = "Easy";
		break;
	case 2:
		type = "Medium";
		break;
	case 3:
		type = "Hard";
		break;
	}
	return type;
}
