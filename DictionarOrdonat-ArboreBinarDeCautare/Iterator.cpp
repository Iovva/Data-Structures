#include "Iterator.h"
#include "DO.h"
#include <exception>
#include <iostream>

using namespace std;

Iterator::Iterator(const DO& d) : dict(d) {
	int dim = d.dim();
	elems = new TElem[dim];
	ct = 0;				// contor pentru a adauga in vector
	cur = 0;			// elementul curent din vector

	if (dict.vid())
		return;

	inordine(dict.radacina);
	prim();
}

void Iterator::inordine(int poz)
{
	if (poz != -1)
	{
		inordine(dict.st[poz]);
		elems[ct] = dict.elems[poz];		// parcurgem : pe stanga -> elementul -> pe dreapta
		ct++;
		inordine(dict.dr[poz]);
	}
}

void Iterator::prim() {
	cur = 0;
}

void Iterator::urmator() {
	if (!valid())
		throw exception();
	cur++;
}

bool Iterator::valid() const {
	if (cur == ct)
		return false;
	return true;
}

TElem Iterator::element() const {
	if (!valid())
		throw exception();
	return elems[cur];
}

Iterator::~Iterator()
{
	delete[] elems;
}

void Iterator::avanseazaKPasi(int k) {
	if (cur + k >= ct || k <= 0)
		throw exception();
	cur = cur + k;
}
