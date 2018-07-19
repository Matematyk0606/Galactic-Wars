#include "View.h"

void project::View::show()
{
	// Metoda ta jest wirtualna, wiêc bêdzie dziedziczona, a jej cia³o
	// i tak zostanie przys³oniête

	// Metoda ta nie jest czysto wirtualna tylko dlatego, ¿e klasa 'Game' 
	// nie bêdzie z niej korzystaæ, a jednoczeœnie dziedziczy z klasy 'View', 
	// w przeciwnym wypadku trzebaby stworzyæ definicjê tej metody w klasie 'Game'
}
