#include "Caption.h"


Caption::Caption()
{
	this->setCharacterSize(20);
}

Caption::Caption(Font & font, string text, float x, float y, int size)
{
		this->setFont(font);

		if (text != "") this->setString(text);
		if (size != 20) this->setCharacterSize(size);
		if (x != 0) this->setPosition(x, this->getPosition().y);
		if (y != 0) this->setPosition(this->getPosition().x, y);
}

Caption::~Caption()
{
}

void loadFont(Font & font, string path)
{
	font.loadFromFile(path);
}

string intToString(int number)
{
	ostringstream ss; // Obiekt do konwersji "int to string"
	ss << number;

	string text = ss.str(); // £πczenie cz≥onÛw napisu
	return text;
}

int stringToInt(string text)
{
	int number = atoi(text.c_str());
	return number;
}

string convertToPolishChars(string text)
{
	string convertedText = "";
	for (int i = 0; i < text.length(); i++)
	{
		switch (text[i])
		{
			/*case 'π': convertedText += "\245"; break;
			case 'Ê': convertedText += "\206"; break;
			case 'Í': convertedText += "\251"; break;
			case '≥': convertedText += "\210"; break;
			case 'Ò': convertedText += "\344"; break;
			case 'Û': convertedText += "\242"; break;
			case 'ú': convertedText += "\230"; break;
			case 'ü': convertedText += "\253"; break;
			case 'ø': convertedText += "\256"; break; // Øadna z tych linii nie dzia≥a w prawid≥owy sposÛb
			case '•': convertedText += "\143"; break; // Uøy≥em rÛønych zestawÛw liczb majπcych odpowiadaÊ znakom w tablicy ASCII
			case '∆': convertedText += "\149"; break; // Ale øaden nie zamienia poprawnie pojawiajπcych siÍ krzaczkÛw (np. ten poniøej)
			case ' ': convertedText += "\144"; break;
			case '£': convertedText += "\157"; break;
			case '—': convertedText += "\165"; break;
			case '”': convertedText += "\163"; break;
			case 'å': convertedText += "\152"; break;
			case 'è': convertedText += "\160"; break;
			case 'Ø': convertedText += "\161"; break;
			case '∞': convertedText += "\248"; break;

			default: convertedText += text[i]; break;*/

			/*206 - Ê
			210 - ≥
			230 - ú
			242 - Û
			245 - π
			251 - Í
			253 - ü
			276 - ø
			344 - Ò*/

			case 'π': convertedText += static_cast<char>(165); break;
			case 'Ê': convertedText += static_cast<char>(134); break;
			case 'Í': convertedText += static_cast<char>(169); break;
			case '≥': convertedText += static_cast<char>(136); break;
			case 'Ò': convertedText += static_cast<char>(228); break;
			case 'Û': convertedText += static_cast<char>(162); break;
			case 'ú': convertedText += static_cast<char>(152); break;
			case 'ü': convertedText += static_cast<char>(171); break;
			case 'ø': convertedText += static_cast<char>(190); break;

			case '•': convertedText += static_cast<char>(164); break;
			case '∆': convertedText += static_cast<char>(143); break;
			case ' ': convertedText += static_cast<char>(168); break;
			case '£': convertedText += static_cast<char>(157); break;
			case '—': convertedText += static_cast<char>(227); break;
			case '”': convertedText += static_cast<char>(224); break;
			case 'å': convertedText += static_cast<char>(151); break;
			case 'è': convertedText += static_cast<char>(141); break;
			case 'Ø': convertedText += static_cast<char>(189); break;
			case '∞': convertedText += static_cast<char>(248); break;

			default: convertedText += text[i]; break;
		}
	}

	return convertedText;
}

void setColorConsoleFont(unsigned int color)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, color);
}

bool isNumeric(string number)
{
	bool isNumeric = false;
	for (int i = 0; i < number.length(); i++)
	{
		if (number[i] == '1' || number[i] == '2' || number[i] == '3' || number[i] == '4' ||
			number[i] == '5' || number[i] == '6' || number[i] == '7' || number[i] == '8' ||
			number[i] == '9' || number[i] == '0')
		{
			isNumeric = true;
			continue;
		}
		else
		{
			isNumeric = false;
			break;
		}

	}

	if(isNumeric == true) return true;
	else return false;
}

bool isNumeric(char number)
{
	if (number == '1' || number == '2' || number == '3' || number == '4' || number == '5' || 
		number == '6' || number == '7' || number == '8' || number == '9' || number == '0')
		return true;
	else 
		return false;
}

