#include "IteratorLI.h"
#include "LI.h"
#include <exception>

IteratorLI::IteratorLI(const LI& li): lista(li) {
    cur = li.prim;
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)

void IteratorLI::prim(){
    cur = lista.prim;
    i = 0;
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)

void IteratorLI::urmator(){
    if (valid() == false)
        throw std::exception();
    i++;
    cur = cur->urmator();
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)

bool IteratorLI::valid() const{
    if (lista.len == 0)
        return false;
    if (i > lista.len - 1)
        return false;
    return cur != nullptr;
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)

TElem IteratorLI::element() const{
    if (valid() == false)
        throw std::exception();
    return cur->element();
} // CF- theta(1), CD- theta(1), CM- theta(1),TOTAL- theta(1)
