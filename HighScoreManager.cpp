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

	// Configure content background
	RectangleShape contentBg(Vector2f(800.0f, 600.0f));
	contentBg.setFillColor(sf::Color(0, 0, 0, 200));
	contentBg.setPosition(200.0f, 50.0f);

	// Configure column title
	std::vector<Text> title;
	for (int i = 0; i < 4; ++i)
	{
		Text t("", font_bebasNeueBold, 30);
		t.setFillColor(Color::White);
		title.push_back(t);
	}
	title[0].setString("ID"); title[0].setPosition(220.0f, 72.0f);
	title[1].setString("Player name"); title[1].setPosition(275.0f, 72.0f);
	title[2].setString("Diff"); title[2].setPosition(540.0f, 72.0f);
	title[3].setString("Date played"); title[3].setPosition(790.0f, 72.0f);
	//Text title("ID" + std::string(3, ' ') + "Player name" + std::string(10, ' ') + "Diff" + std::string(5, ' ') + "Time played", font_robotoMonoBold, 30);
	
	// Declaire for some object
	std::vector <std::vector<Text>> stat(highScoreList.size());
	for (unsigned int i = 0; i < stat.size(); i++)
	{
		for (int j = 0; j < 4; ++j)
		{
			Text t("", font_bebasNeueBold, 26);
			t.setFillColor(Color::White);
			stat[i].push_back(t);
		}
		stat[i][0].setString(std::to_string(i+1)); stat[i][0].setPosition(220.0f, 110.0f + i * 30);
		stat[i][1].setString(highScoreList[i]._playerName); stat[i][1].setPosition(275.0f, 110.0f + i * 30);
		stat[i][2].setString(std::to_string(highScoreList[i]._score)); stat[i][2].setPosition(540.0f, 110.0f + i * 30);
		stat[i][3].setString(std::to_string(highScoreList[i]._ltm->tm_mday) 
			+ ":" + std::to_string(highScoreList[i]._ltm->tm_mon) 
			+ ":" + std::to_string(highScoreList[i]._ltm->tm_year) 
			+ " " + std::to_string(highScoreList[i]._ltm->tm_hour) 
			+ ":" + std::to_string(highScoreList[i]._ltm->tm_min) 
			+ ":" + std::to_string(highScoreList[i]._ltm->tm_sec));
		stat[i][3].setPosition(790.0f, 110.0f + i * 30);
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
		window.clear(); window.draw(menuBackground);
		
		window.draw(contentBg);

		for (int i = 0; i < 4; ++i) window.draw(title[i]);

		for (unsigned int i = 0; i < stat.size(); i++) 
			for(unsigned int j = 0;j<4;++j)
				window.draw(stat[i][j]);
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
