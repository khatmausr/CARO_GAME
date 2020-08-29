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