#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

//o posibila relatie
bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)

Multime::Multime() {
	m = new TElem[2];
	len = 0;
	cap = 2;
} // CF- theta(1), CD- theta(1), CM- theta(1), TOTAL- theta(1)

void Multime::verifica_capacitate() {
	if (len < cap)
		return;

	TElem* mNou = new int[2 * cap];
	for (int i = 0; i < dim(); i++)
		mNou[i] = m[i];
	cap = 2 * cap;
	delete[] m;
	m = mNou;

} //  CF- theta(1), CD- theta(n), CM- theta(n), TOTAL- O(n)

bool Multime::adauga(TElem elem) {
	if (cauta(elem) == true)
		return false;
	verifica_capacitate();
	if (vida() == true)
		m[0] = elem;
	else if (elem > m[dim() - 1])
		m[dim()] = elem;
	else
	{
		for (int i = 0; i < dim(); i++)
		{
			if (rel(elem, m[i]) == true)
			{
				for (int j = dim() - 1; j >= i; j--)
					m[j + 1] = m[j];
				m[i] = elem;
				break;
			}
		}
	}
	len++;
	return true;
} // CF- theta(1), CD- theta(n), CM- theta(n), TOTAL- O(n)


bool Multime::sterge(TElem elem) {
	if (cauta(elem) == false)
		return false;
	for (int i = 0; i < len; i++)
	{
		if (m[i] == elem)
		{
			for (int j = i; j < len - 1; j++)
				m[j] = m[j + 1];
		break;
		}
	}
	len--;
	return true;
} // CF- theta(1), CD- theta(n), CM- theta(n), TOTAL- O(n)


bool Multime::cauta(TElem elem) const {
	
	for (int i = 0; i < len; i++)
	{
		if (m[i] == elem)
		{
			return true;
		}
	}
	return false;
} // CF- theta(1), CD- theta(n), CM- theta(n), TOTAL- O(n)


int Multime::dim() const {
	return len;
} // CF- theta(1), CD- theta(1), CM- theta(1), TOTAL- theta(1)



bool Multime::vida() const {
	if (dim() == 0)
		return true;
	return false;
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)

IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)


Multime::~Multime() {
	delete[] m;
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)






