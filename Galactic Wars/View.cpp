#include "View.h"

void project::View::show()
{
	// Metoda ta jest wirtualna, wi�c b�dzie dziedziczona, a jej cia�o
	// i tak zostanie przys�oni�te

	// Metoda ta nie jest czysto wirtualna tylko dlatego, �e klasa 'Game' 
	// nie b�dzie z niej korzysta�, a jednocze�nie dziedziczy z klasy 'View', 
	// w przeciwnym wypadku trzebaby stworzy� definicj� tej metody w klasie 'Game'
}
