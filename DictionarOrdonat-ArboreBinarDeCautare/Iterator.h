#pragma once

#include "DO.h"

class Iterator {
	friend class DO;
private:
	//constructorul radacinaeste o referinta catre Container
	//iteratorul va referi radacinaul element din container
	// complexitate timp: Theta(n)
	// complexitate spatiu: Theta(n)
	Iterator(const DO& dictionar);

	//contine o referinta catre containerul pe care il itereaza
	const DO& dict;

	/* aici e reprezentarea specifica a iteratorului */
	TElem* elems;
	int ct;		// contorul pentru a adauga vector
	int cur;	// indicele elementului curent din vector
	// adauga toate elementele in lista iteratorului
	// n - numarul cheilor din dictionarul ordonat
	// complexitate timp: Theta(n)
	// complexitate spatiu: Theta(1)
	void inordine(int poz);
public:

	//reseteaza pozitia iteratorului la inceputul containerului
	// complexitate timp: Theta(1)
	// complexitate spatiu: Theta(1)
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	// complexitate timp: Theta(1)
	// complexitate spatiu: Theta(1)
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	// complexitate timp: Theta(1)
	// complexitate spatiu: Theta(1)
	bool valid() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	// complexitate timp: Theta(1)
	// complexitate spatiu: Theta(1)
	TElem element() const;

	// sterge listele folosite
	// complexitate timp: Theta(1)
	// complexitate spatiu: Theta(1)
	~Iterator();

	/*
	preconditii: it apartine IteratorDO,
				 k numar intreg
	postconditii: it' apartine IteratorDO, cu k pasi mai multi
				  sau arunca exceptie daca k <= 0
	subalgoritm avanseazaKPasi(it, k)
		daca cur + k >= ct sau k <= 0 atunci
			arunca exceptie
		sfarsit daca
		cur <- cur + k
	sfarsit subalgoritm
	*/
	// complexitate timp: Theta(1)
	// complexitate spatiu: Theta(1)
	void avanseazaKPasi(int k);

};

