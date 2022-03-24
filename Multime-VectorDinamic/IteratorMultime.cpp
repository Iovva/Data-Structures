#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>


IteratorMultime::IteratorMultime(const Multime& m): mult(m) {
	prim();
} //CF- theta(1),CD- theta(1),CM- theta(1),TOTAL- theta(1)

TElem IteratorMultime::element() const {
	if (valid() == false)
		throw std::exception();
	return mult.m[it];
} //CF- theta(1),CD- theta(1),CM- theta(1),TOTAL- theta(1)

bool IteratorMultime::valid() const {
	if (it >= mult.dim())
		return false;
	return true;
} //CF- theta(1),CD- theta(1),CM- theta(1),TOTAL- theta(1)

void IteratorMultime::urmator() {
	if (valid() == false)
		throw std::exception();
	it++;
} //CF- theta(1),CD- theta(1),CM- theta(1),TOTAL- theta(1)

void IteratorMultime::prim() {
	it = 0;
} //CF- theta(1),CD- theta(1),CM- theta(1),TOTAL- theta(1)

