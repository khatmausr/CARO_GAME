#include "common.h"
#include "SaveLoadManager.h"

std::istream& operator >> (std::istream& in, tm*& ltm)
{
	in >> ltm->tm_hour >> ltm->tm_isdst >> ltm->tm_mday >> ltm->tm_min;
	in >> ltm->tm_mon >> ltm->tm_sec >> ltm->tm_wday >> ltm->tm_yday >> ltm->tm_year;
	return in;
}

std::ostream& operator << (std::ostream& out, tm*& ltm)
{
	out << ltm->tm_hour << " " << ltm->tm_isdst << " " << ltm->tm_mday << " " << ltm->tm_min << " ";
	out << ltm->tm_mon << " " << ltm->tm_sec << " " << ltm->tm_wday << " " << ltm->tm_yday << " " << ltm->tm_year;
	return out;
}

std::istream& operator >> (std::istream& in, saveGameInfo& temp)
{
	std::getline(in, temp._filename);
	in >> temp._typeGame; in.ignore();
	std::getline(in, temp._s1);
	std::getline(in, temp._s2);
	in >> temp._ltm; in.ignore();
	return in;
}

std::ostream& operator << (std::ostream& out, saveGameInfo& temp)
{
	out << temp._filename << std::endl;
	out << temp._typeGame << std::endl;
	out << temp._s1 << std::endl;
	out << temp._s2 << std::endl;
	out << temp._ltm << std::endl;
	return out;
}

void SaveLoadManager::updateSaveList()
{
	saveList.clear();

	std::ifstream fin("savegame/SaveGameManager.DAT");
	
	int n; fin >> n; fin.ignore();
	for (int i = 0; i < n; i++)
	{
		saveGameInfo temp; temp._ltm = new tm;
		fin >> temp;
		saveList.push_back(temp);
	}

	fin.close();
}

void SaveLoadManager::updateFileManager()
{
	std::ofstream fout("saveGame/SaveGameManager.DAT");

	fout << saveList.size() << std::endl;
	for (unsigned int i = 0; i < saveList.size(); i++)
		fout << saveList[i];

	fout.close();
}

bool SaveLoadManager::checkFile(std::string filename, int typeGame)
{
	updateSaveList();

	for (unsigned int i = 0; i < saveList.size(); i++)
		if ((filename == saveList[i]._filename) && (bool(typeGame) == bool(saveList[i]._typeGame)))
			return true;

	return false;
}

void SaveLoadManager::pushSaveGame(saveGameInfo& temp)
{
	updateSaveList();
	
	bool isExist = false;
	for (unsigned int i = 0; i < saveList.size(); i++)
		if (saveList[i]._filename == temp._filename)
		{
			saveList[i] = temp;
			isExist = true;
		}

	if (!isExist)
	{
		if (saveList.size() < MAX_SAVEGAME)
			saveList.push_back(temp);
		else
		{
			remove(saveList[0]._filename.c_str());
			for (unsigned int i = 0; i < saveList.size() - 1; i++)
				saveList[i] = saveList[i + 1];
			saveList[saveList.size() - 1] = temp;
		}
	}

	updateFileManager();
}

int SaveLoadManager::loadForGame(std::string& filename)
{
	updateSaveList();

	// Configure content background
	RectangleShape contentBg(Vector2f(800.0f, 600.0f));
	contentBg.setFillColor(sf::Color(0, 0, 0, 200));
	contentBg.setPosition(200.0f, 50.0f);

	// Declaire for some object
	RectangleShape chooseBox(Vector2f(800.f, 50.f));
	chooseBox.setFillColor(Color(0, 0, 0, 128));

	std::vector <Text> option(saveList.size());
	for (unsigned int i = 0; i < option.size(); i++)
	{
		option[i].setFont(font_arial);
		option[i].setFillColor(Color::White);
		option[i].setCharacterSize(30);
		option[i].setPosition(Vector2f(0.f, 5.f + 50.f * i));
		option[i].setString(saveList[i]._filename + " " + std::to_string(saveList[i]._typeGame) + " " + saveList[i]._s1 + " " + saveList[i]._s2);
	}

	// Choose a file to load
	unsigned int choice = 0;
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
				switch (e.key.code)
				{
				case Keyboard::Escape:
				{
					isDone = true;
					break;
				}
				case Keyboard::Up:
				{
					if (choice > 0) choice--;
					break;
				}
				case Keyboard::Down:
				{
					if (choice < option.size() - 1) choice++;
					break;
				}
				case Keyboard::Enter:
				{
					// Announce It's Done
					Text txt_status;
					txt_status.setFont(font_arial);
					txt_status.setCharacterSize(50);
					txt_status.setStyle(Text::Italic);
					txt_status.setString("Done!");

					for (int i = 0; i <= 25; i++)
					{
						txt_status.setFillColor(Color(0, 255, 0, i * 10));
						txt_status.setPosition(Vector2f(1000.f, 200.f + 2.f * i));

						window.clear(Color::White); window.draw(menuBackground);
						chooseBox.setPosition(Vector2f(0.f, 50.f * choice)); window.draw(chooseBox);
						for (unsigned int i = 0; i < option.size(); i++) window.draw(option[i]);
						window.draw(txt_status);
						window.display();
					}

					sleep(milliseconds(1000));

					// Return the answer
					isDone = true;
					filename = saveList[choice]._filename;
					return saveList[choice]._typeGame;
					break;
				}
				}
		}

		// Display
		window.clear(Color::White); window.draw(menuBackground);
		chooseBox.setPosition(Vector2f(0.f, 50.f * choice)); window.draw(chooseBox);
		for (unsigned int i = 0; i < option.size(); i++) window.draw(option[i]);
		window.display();
	}

	filename = "";
	return -1; //Exit with No file choosen
}