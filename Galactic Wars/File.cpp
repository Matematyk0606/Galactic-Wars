#include "File.h"


File::File()
{
}

File::File(File &&)
{
}

File::File(string path)
{
	openFile(path);
}

File::~File()
{
}


bool File::openFile(string path)
{
	if(!contentFile.empty()) contentFile.clear(); // Czyszczenie vectora
	
	file.open(path, ios::in); // Otwarcie pliku

	if (file.is_open()) // Otwarty?
	{
		string line; // Jedna linijka z pliku

		while (file.good()) // Wszystko OK?
		{
			getline(file, line); // Pobieranie linijki
			contentFile.push_back(line); // Umieszczenie w vectorze
		}
	}
	else
	{
		cout << "Blad! Nie mozna otworzyc pliku!" << endl;
	}

	file.close(); // Zamykanie pliku
	file.clear(); // Czyszczenie pliku

	if (contentFile.size() > 0) return true;
	else return false;
}

vector<string> File::s_openFile(string path)
{
	fstream file;
	vector<string> contentFile;

	file.open(path, ios::in); // Otwarcie pliku

	if (file.is_open()) // Otwarty?
	{
		string line; // Jedna linijka z pliku

		while (file.good()) // Wszystko OK?
		{
			getline(file, line); // Pobieranie linijki
			contentFile.push_back(line); // Umieszczenie w vectorze
			cout << line << endl;
		}

	}
	else
	{
		cout << "Blad! Nie mozna otworzyc pliku!" << endl;
	}

	file.close(); // Zamykanie pliku
	file.clear(); // Czyszczenie pliku

	return contentFile;
}

vector<string> File::getContent()
{
	return contentFile;
}

