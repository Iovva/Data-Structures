#include <exception>
#include <iostream>
#include "LI.h"
#include "IteratorLI.h"
#include <exception>

Nod::Nod(TElem e, PNod urm) {
	this->e = e;
	this->urm = urm;
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)

TElem Nod::element() {
	return e;
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)

PNod Nod::urmator() {
	return urm;
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)

LI::LI() {
	len = 0;
	prim = nullptr;
	last = nullptr;
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)

int LI::dim() const {
	return len;
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)

bool LI::vida() const {
	if (dim() == 0)
		return true;
	return false;
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)

TElem LI::element(int i) const {
	if (i < 0 or i >= len)
		throw std::exception();
	PNod cur = prim;
	for (int j = 0; j < i; j++)
	{
		cur = cur->urm;
	}
	return cur->e;
} // CF- theta(1), CD- theta(n), CM- theta(n), TOTAL- O(n)

TElem LI::modifica(int i, TElem e) {
	if (i < 0 or i >= len)
		throw std::exception();
	PNod cur = prim;
	for (int j = 0; j < i; j++)
	{
		cur = cur->urm;
	}
	TElem copie = cur->e;
	cur->e = e;
	return copie;
} // CF- theta(1), CD- theta(n), CM- theta(n), TOTAL- O(n)

void LI::adaugaSfarsit(TElem e) {
	PNod nod = new Nod(e, nullptr);
	if (len == 0)
	{
		prim = nod;
		last = nod;
	}
	else
	{
		last->urm = nod;
		last = nod;
	}
	len++;
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)

void LI::adauga(int i, TElem e) {
	if (i < 0 or i > len)
		throw std::exception();
	if (len == 0 or i == len)
		adaugaSfarsit(e);
	else if (i == 0)
	{
		PNod nod = new Nod(e, nullptr);
		nod->urm = prim;
		prim = nod;
	}
	else
	{	
		PNod cur = prim;
		for (int j = 0; j < i - 1; j++)
		{
			cur = cur->urm;
		}
		PNod nod = new Nod(e, nullptr);
		nod->urm = cur->urm;
		cur->urm = nod;
	}
	len++;
} // CF- theta(1), CD- theta(n), CM- theta(n), TOTAL- O(n)

TElem LI::sterge(int i) {
	if (i < 0 or i >= len)
		throw std::exception();


	else if (i == 0)
	{
		PNod cur = prim;
		TElem copie = cur->e;
		cur = cur->urm;
		prim = cur;
		if (len == 1)
		{
			last = cur;
		}
		len--;
		return copie;
	}
	else if (i == len - 1)
	{
		PNod cur = prim;
		for (int j = 0; j < i - 1; j++)
		{
			cur = cur->urm;
		}
		PNod temp = cur;
		temp = temp->urm;
		last = cur->urm;
		len--;
		return temp->e;
	}
	else
	{
		PNod cur = prim;
		for (int j = 0; j < i - 1; j++)
		{
			cur = cur->urm;
		}
		PNod temp = cur;
		temp = temp->urm;
		cur->urm = temp->urm;
		len--;
		return temp->e;
	}
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)

int LI::cauta(TElem e) const{
	PNod cur = prim;
	for (int j = 0; j < len; j++)
	{
		if (cur->e == e)
			return j;
		cur = cur->urm;
	}
	return -1;
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)


IteratorLI LI::iterator() const {
	return  IteratorLI(*this);
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)

LI::~LI() {
	while (prim != nullptr) {
		PNod p = prim;
		prim = prim->urm;
		delete p;
	}
} // CF- theta(n), CD- theta(n), CM- theta(n), TOTAL- theta(n)

void LI::goleste() {
	while (prim != nullptr) {
		PNod p = prim;
		prim = prim->urm;
		delete p;
	}
	len = 0;
	prim = nullptr;
	last = nullptr;
} // CF- theta(n), CD- theta(n), CM- theta(n), TOTAL- theta(n)

/*
goleste ()
cattimp prim <> NULL atunci
	p = prim
	prim = prim.urm
	eliberam p
len <- 0
prim<- nullptr
last<- nullptr
*/