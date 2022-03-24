#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	curent = 0;
	deplasare();
} 

void IteratorColectie::deplasare() {
	while ((curent < col.m) && (col.e[curent] == NULL_TELEM || col.e[curent] == STERS))
		curent++;
} 

void IteratorColectie::prim() {
	curent = 0;
	deplasare();
} 

void IteratorColectie::urmator() {
	curent++;
	deplasare();
} 


bool IteratorColectie::valid() const {
	if (col.e[curent] == NULL_TELEM || col.e[curent] == STERS)
		return false;
	return (curent < col.m);
} 

TElem IteratorColectie::element() const {
	return col.e[curent];
} 
