#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

class File
{
public:
	File();
	File(File &&); // Konstruktor przenoszący, niezbędny do: 'File file = File()'
	File(string path);
	~File();

	bool openFile(string path); // Otwieranie pliku i ładowanie zawartości do vectora
	static vector<string> s_openFile(string path); // s_ = static

	vector<string> getContent();

private:
	fstream file;
	vector<string> contentFile;
};

