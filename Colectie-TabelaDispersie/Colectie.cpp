#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>
#include <vector>
using namespace std;

double Colectie::LF() const {
	return static_cast<float>(len) / static_cast<float>(m);
}

long long Colectie::d1(TElem e) const {
	return abs(e) % m;
} 

long long Colectie::d2(TElem e) const {
	return 1 + abs(e) % (m - 1);
} 

long long Colectie::d(TElem e, int i) const {
	return (d1(e) + i * d2(e)) % m;
} 

void Colectie::redimensionare() {
	TElem* eAux = new TElem[m];
	for (int i = 0; i < m; i++) {
		eAux[i] = e[i];
	}
	delete[] e;
	TElem* eNou = new TElem[2 * m - 1];
	for (int i = 0; i < 2 * m - 1; i++) {
		eNou[i] = NULL_TELEM;
	}
	e = eNou;
	int c = m;
	m = 2 * m - 1;
	len = 0;
	for (int i = 0; i < c; i++) {
		adauga(eAux[i]);
	}
	delete[] eAux;
} 

Colectie::Colectie() {
	e = new TElem[13];
	m = 13;
	len = 0;
	for (int i = 0; i < m; i++) {
		e[i] = NULL_TELEM;
	}
} 

void Colectie::adauga(TElem elem) {
	if (elem == NULL_TELEM or elem == STERS)
		return;
	long long i = 0;
	bool gasit = false;
	do {
		long long j = d(elem, i);
		if (e[j] == NULL_TELEM or e[j] == STERS) {
			e[j] = elem;
			gasit = true;
			len++;
		}
		else i++;
	} while (i < m && !gasit);
	if (i == m) {
		redimensionare();
		adauga(elem);
	}
	if (LF() > 0.75) {
		redimensionare();
	}
} 

bool Colectie::sterge(TElem elem) {
	long long i = 0, j;
	bool gasit = false;
	do {
		j = d(elem, i);
		if (e[j] == elem)
		{	
			e[j] = STERS;
			gasit = true;
			len--;
		}
		else i++;
	} while (e[j] != NULL_TELEM and i != m and gasit == false);
	return gasit;
} 

bool Colectie::cauta(TElem elem) const {
	long long i = 0, j;
	bool gasit = false;
	do {
		j = d(elem, i);
		if (e[j] == elem)
			gasit = true;
		else i++;
	} while (e[j] != NULL_TELEM and i != m and gasit == false);
	return gasit;
} 

int Colectie::nrAparitii(TElem elem) const {
	int nr = 0;
	long long i = 0, j;
	do {
		j = d(elem, i);
		if (e[j] == elem)
			nr++;
		i++;
	} while (e[j] != NULL_TELEM and i != m);
	return nr;
} 

int Colectie::dim() const {
	return len;
} 

bool Colectie::vida() const {
	return len == 0;
} 

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
} 

Colectie::~Colectie() {
	delete[] e;
} 
void Colectie::intersectie(const Colectie& b) {
	IteratorColectie ic = iterator();
	while (ic.valid()) { 
		TElem e = ic.element();
		if (nrAparitii(e) > b.nrAparitii(e))
		{
			for (int j = nrAparitii(e) - b.nrAparitii(e); j > 0; j--)
				sterge(e);
		}
		ic.urmator(); 
	}
}
	

