#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

void DO::resize()
{
	int new_cap = 2 * cap;
	TElem* new_elems = new TElem[new_cap];
	int* new_st = new int[new_cap];
	int* new_dr = new int[new_cap];

	for (int i = 0; i < cap; i++)
	{
		new_elems[i] = elems[i];
		new_st[i] = st[i];
		new_dr[i] = dr[i];
	}
	for (int i = cap; i < new_cap; i++)
	{
		new_elems[i] = NULL_TELEM;
		new_st[i] = i + 1;
		new_dr[i] = -1;
	}
	new_st[new_cap - 1] = -1;
	delete[] st;
	delete[] dr;
	delete[] elems;

	st = new_st;
	dr = new_dr;
	elems = new_elems;
	primLiber = cap;
	cap = new_cap;
}

DO::DO(Relatie r) : rel{ r } {
	cap = 10;
	len = 0;
	st = new int[cap];
	dr = new int[cap];
	elems = new TElem[cap];

	for (int i = 0; i < cap; i++)
	{
		elems[i] = NULL_TELEM;
		st[i] = i + 1; // in st pastreaza atat indiciele nodurilor din stanga, cat si o serie de noduri libere, in casutele neocupate
					   // de indiciele nodurilor
		dr[i] = -1;
	} 
	st[cap - 1] = -1;  // nu urmeazaza nici un nod liber dupa ultimul (pentru un pseudo-vector de urm)
	radacina = -1;
}

int DO::aloca()
{
	int i = primLiber;
	if (primLiber != -1)
		primLiber = st[primLiber];
	return i;
}

void DO::dealoca(int i)
{
	st[i] = primLiber;
	primLiber = i;
}

int DO::creeazaNod(TCheie c, TValoare v)
{
	int i = aloca();
	if (i == -1) {
		resize();
		i = aloca();
	}

	elems[i] = pair<TCheie, TValoare>(c, v);
	dr[i] = -1;
	st[i] = -1;
	return i;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	int i = creeazaNod(c, v);

	if (radacina == -1)		// caz 1 - nu am nimic, il fac radacina
		radacina = i;	
	else
	{
		int prev;
		int curent = radacina;

		while (curent != -1)
		{
			prev = curent;
			if (c == elems[curent].first)	// caz 2 - exista si il modific
			{
				TValoare val = elems[curent].second;
				elems[curent].second = v;
				dealoca(i);
				return val;
			}
			else if (rel(c, elems[curent].first))
				curent = st[curent];
			else                          // parcurg la stanga sau la dreapta, in functie de relatie
				curent = dr[curent];
		}

										  // caz 3 - nu exista, si il adaug
										  // pastrez prev pentru a nu pierde referinta dupa ca sa adaug ( in functie de relatie )
		if (rel(c, elems[prev].first))
		{
			st[prev] = i;
		}
		else
		{
			dr[prev] = i;
		}
	}
	len++;
	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
	int curent = radacina;

	if (radacina == -1)					// caz 1 - daca nu ex radacina, cauta nu gaseste
		return NULL_TVALOARE;

	while (curent != -1)				
	{
		if (c == elems[curent].first)
			return elems[curent].second;			// caz 2 - e gasit dupa parcurgrea in functie de relatie
		else if (rel(c, elems[curent].first))	
			curent = st[curent];
		else
			curent = dr[curent];
	}

	return NULL_TVALOARE;				// caz 3 - nu exista
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	if (radacina == -1)
		return NULL_TVALOARE;			// caz 1 - nu exista radacina, nu am ce sa sterg
	int curent = radacina;		// elementul ce trebuie sters
	int prev = curent;			// elementul precedent celui ce trebuie sters
	if (elems[curent].first == c)		// cazurile in care radacina e ce trebuie stearsa
	{
		TValoare val = elems[curent].second;
		int del_radacina = radacina;
		if (st[curent] == -1 && dr[curent] == -1)
			radacina = -1;				// caz 2 - nu are urmasi
		else if (st[curent] == -1)
			radacina = dr[curent];
		else if (dr[curent] == -1)		// caz(urile) 3 - are doar un urmas (stanga/dreapta),
										// si ii pun urmasul direct ca radacina
			radacina = st[curent];
		else
		{								// cazurile in care radaccina are doi urmasi
										// cautam cea mai din dreapta frunza pe ramura din stanga si inlocuim valoarea nodului
										// radacina cu ea, eliminand nodul initial al frunzei gasite

			int curent2 = st[radacina];				// elementul cu care va fi inlocuita radacina
			int st_radacina = st[radacina];	 
			if (dr[curent2] == -1) {
				if (st[curent2] != -1) {			// caz 4
					st[radacina] = st[curent2];		// daca primul nod pe ramura de stanga nu are nici un urmas pe dreata ( este astfel, cel mai din dreapta pe ramura) si
				}									// are un urmas pe stanga
				else {								// caz 5	
					st[radacina] = -1;				// daca primul nod pe ramura de stanga nu are nici un urmas pe dreata nici pe stanga ( e frunza nodul din dreapta celui
				}									// ce trebuie sters

				elems[radacina] = elems[curent2];	// inlocuiesc nodul "sters" cu valoarea celui mai din dreapta nod pe ramura din stanga
				del_radacina = radacina;				// marchez elementul initial pentru dealocare
			}
			else {									// daca primul nod pe stanga radacinii are urmas pe dreapta
				while (dr[curent2] != -1)
				{							
					st_radacina = curent2;
					curent2 = dr[curent2];
				}						
				if (st[curent2] != -1)				  // caz 6
					dr[st_radacina] = st[radacina];	  // daca cel mai din dreapta nod nu e frunza, legam ce urmeaza pe stanga, de dreapta nodului precedent pe care l-am luat pentru
													  // inlocuirea nodului sters
													  // (poate avea doar urmas pe stanga, pentru ca daca avea pe dreapta, mergea pe ala in continuare)
				else								  // caz 7 
					dr[st_radacina] = -1;             // daca cel mai din dreapta nod e frunza, scot referinta la frunza initiala cu care se inlocuieste nodul ce trebuie sters	
				
				elems[radacina] = elems[curent2];	  // inlocuiesc nodul "sters" cu valoarea celui mai din dreapta nod pe ramura din stanga
				del_radacina = radacina;				  // marchez radacina pentru dealocare
			}
		}
		dealoca(del_radacina);
		len--;
		return val;
	}

	while (curent != -1)			// cazurile in care nu e radacina ceea ce trebuie sters
	{
		if (c == elems[curent].first)
		{
			TValoare val = elems[curent].second;					
			int del_elem = curent;
			if (st[curent] == -1 && dr[curent] == -1)				// caz 8 - nodul nu are urmasi ( e frunza )
			{
				if (elems[st[prev]].first == elems[curent].first)
					st[prev] = -1;
				else
					dr[prev] = -1;
			}
			else if (st[curent] == -1)								// caz(urile) 9 - nodul are un singur urmas
			{
				if (elems[st[prev]].first == elems[curent].first)
					st[prev] = dr[curent];
				else
					dr[prev] = dr[curent];
			}
			else if (dr[curent] == -1)
			{
				if (elems[st[prev]].first == elems[curent].first)
					st[prev] = st[curent];
				else
					dr[prev] = st[curent];
			}
			else													// cazurile in care nodul are doi urmasi
			{														// cautam cea mai din dreapta frunza pe ramura din stanga si inlocuim valoarea nodului
																	// radacina cu ea, eliminand nodul initial al frunzei gasite
				
				int curent2 = st[curent];							// elementul cu care va fi inlocuit cel ce trebuie sters					
				int prev2 = curent;									// elementul precedent elementui cu care va fi inlocuit
				if (dr[curent2] == -1) {						
					if (st[curent2] != -1) {						// caz 10 
						st[curent] = st[curent2];					// daca primul nod pe ramura de stanga nu are nici un urmas pe dreata ( este astfel, cel mai din dreapta pe ramura) si
					}												// are un urmas pe stanga
					else {											// caz 11
						st[curent] = -1;							// daca primul nod pe ramura de stanga nu are nici un urmas pe dreata nici pe stanga ( e frunza nodul din dreapta celui
					}												// ce trebuie sters

					elems[curent] = elems[curent2];					// inlocuiesc nodul "sters" cu valoarea celui mai din dreapta nod pe ramura din stanga
					del_elem = curent;								// marchez elementul initial pentru dealocare
				}
				else {												// daca primul nod pe stanga nodului ce trebuie sters are urmas pe dreapta
					while (dr[curent2] != -1)
					{
						prev2 = curent2;
						curent2 = dr[curent2];
					}												// caz 12
					if (st[curent2] != -1)							// daca cel mai din dreapta nod nu e frunza, legam ce urmeaza pe stanga, de dreapta nodului precedent pe care l-am luat pentru
																	// inlocuirea nodului sters
																	// (poate avea doar urmas pe stanga, pentru ca daca avea pe dreapta, mergea pe ala in continuare)
						dr[prev2] = st[curent2];
					else											// caz 13 
						dr[prev2] = -1;								// daca cel mai din dreapta nod e frunza, scot referinta la frunza initiala cu care se inlocuieste nodul ce trebuie sters	
																		
																		 
					elems[curent] = elems[curent2];						// inlocuiesc nodul "sters" cu valoarea celui mai din dreapta nod pe ramura din stanga
					del_elem = curent2;									// marchez elementul initial pentru dealocare
				}
				
			}
			dealoca(del_elem);
			len--;
			return val;
		}
		prev = curent;
		if (rel(c, elems[curent].first))
			curent = st[curent];
		else
			curent = dr[curent];
	}
	return NULL_TVALOARE;											// caz 14 - nu se gaseste ):
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	return len;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
	if (len == 0)
		return true;
	return false;
}

Iterator DO::iterator() const {
	return  Iterator(*this);
}

DO::~DO() {
	delete st;
	delete dr;
	delete elems;
}
