#pragma once

#define NULL_TELEM -2147483646 

#define STERS -2147483645 

typedef int TElem;

class IteratorColectie;

class Colectie
{
	friend class IteratorColectie;

private:

	TElem* e;

	long long m;

	int len;

	double LF() const;
	//best case: theta(1), worst case: theta(1), caz mediu: theta(1), complexitatea generala: theta(1)

	long long d1(TElem e) const;
	//best case: theta(1), worst case: theta(1), caz mediu: theta(1), complexitatea generala: theta(1)

	long long d2(TElem e) const;
	//best case: theta(1), worst case: theta(1), caz mediu: theta(1), complexitatea generala: theta(1)

	long long d(TElem e, int i) const;
	//best case: theta(1), worst case: theta(1), caz mediu: theta(1), complexitatea generala: theta(1)

	void redimensionare();
	//best case: theta(n), worst case: theta(n), caz mediu: theta(n), complexitatea generala: theta(n)

public:
		//constructorul implicit
		Colectie();
		//best case: theta(n), worst case: theta(n), caz mediu: theta(n), complexitatea generala: theta(n)

		//adauga un element in colectie
		void adauga(TElem e);
		//best case: theta(1), worst case: theta(n), caz mediu: theta(1), complexitatea generala: O(n)

		//sterge o aparitie a unui element din colectie
		//returneaza adevarat daca s-a putut sterge
		bool sterge(TElem e);
		//best case: theta(1), worst case: theta(n), caz mediu: theta(1), complexitatea generala: O(n)

		//verifica daca un element se afla in colectie
		bool cauta(TElem elem) const;
		//best case: theta(1), worst case: theta(n), caz mediu: theta(1), complexitatea generala: O(n)

		//returneaza numar de aparitii ale unui element in colectie
		int nrAparitii(TElem elem) const;
		//best case: theta(1), worst case: theta(n), caz mediu: theta(1), complexitatea generala: O(n)

		//intoarce numarul de elemente din colectie;
		int dim() const;
		//best case: theta(1), worst case: theta(1), caz mediu: theta(1), complexitatea generala: theta(1)

		//verifica daca colectia e vida;
		bool vida() const;
		//best case: theta(1), worst case: theta(1), caz mediu: theta(1), complexitatea generala: theta(1)

		//returneaza un iterator pe colectie
		IteratorColectie iterator() const;
		//best case: theta(1), worst case: theta(1), caz mediu: theta(1), complexitatea generala: theta(1)

		// destructorul colectiei
		~Colectie();
		//best case: theta(1), worst case: theta(1), caz mediu: theta(1), complexitatea generala: theta(1)

		void intersectie(const Colectie& b);
		// m - nr. elemente din b
		//best case: theta(n), worst case: theta(n + m), caz mediu: theta(n + m), complexitatea generala: O(n + m)
		/*
		preconditii: a, b apartin Colectie
		postcondtii: a' = a intersectat cu b
		subalgoritm intersectie(a, b)
			ic <- iterator(a)
			cat timp valid(ic) <> NIL
				e <- element(ic) 
				daca nrAparitii(a, e) > nrAparitii(b, e) atunci
					pentru j <- nrAparitii(a, e) - nrAparitii(b, e), 0, - 1 executa
						sterge(a, e)
					sfarsit pentru
				sfarsit daca
				urmator(ic)
			sfarsit cat timp
		sfarsit subalgoritm
		*/
};