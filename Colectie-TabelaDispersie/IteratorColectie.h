#pragma once
#include "Colectie.h"

class Colectie;
typedef int TElem;

class IteratorColectie
{
	friend class Colectie;
private:
	//constructorul primeste o referinta catre Container
    //iteratorul va referi primul element din container
	IteratorColectie(const Colectie& c);
	//best case: theta(1), worst case: theta(1), caz mediu: theta(1), complexitatea generala: theta(1)

    //contine o referinta catre containerul pe care il itereaza
	const Colectie& col;
	/* aici e reprezentarea pecifica a iteratorului*/

	int curent;

	void deplasare();
	//best case: theta(1), worst case: theta(n), caz mediu: theta(1), complexitatea generala: O(n)

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();
		//best case: theta(1), worst case: theta(1), caz mediu: theta(1), complexitatea generala: theta(1)

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();
		//best case: theta(1), worst case: theta(1), caz mediu: theta(1), complexitatea generala: theta(1)

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;
		//best case: theta(1), worst case: theta(1), caz mediu: theta(1), complexitatea generala: theta(1)

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element() const;
		//best case: theta(1), worst case: theta(1), caz mediu: theta(1), complexitatea generala: theta(1)
};

