#pragma once

typedef int TCheie;
typedef int TValoare;

#define NULL_TVALOARE -1
#define NULL_TCHEIE -3001
#define NULL_TELEM make_pair(NULL_TCHEIE, NULL_TVALOARE)

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Iterator;

typedef bool(*Relatie)(TCheie, TCheie);
// n - lungimea dictionarului
// h - lungimea arborelui
class DO {
	friend class Iterator;
private:
	Relatie rel;
	TElem* elems;
	int* st;
	int* dr;
	int cap;
	int primLiber;
	int radacina;
	int len;
	// reschimba capacitatea arborelui
	// complexitate timp: Theta(n)
	// complexitate spatiu: Theta(n)
	void resize();
	// aloca o pozitie si o returneaza
	// complexitate timp: caz favorabil - theta(1), caz defavorabil - theta(n) - caz mediu(n)
	// complexitate generala: O(1)
	// complexitate spatiu: Theta(1)
	int aloca();
	// dealoca o pozitie data
	// complexitate timp: Theta(1)
	// complexitate spatiu: Theta(1)
	void dealoca(int i);
	// 
	// complexitate timp: Theta(n)
	// complexitate spatiu: Theta(n)
	int creeazaNod(TCheie c, TValoare v);
public:

	// constructorul implicit al dictionarului
	DO(Relatie r);


	// adauga o pereche (cheie, valoare) in dictionar
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	// complexitate timp: caz favorabil - theta(1), caz defavorabil - theta(n) - caz mediu - theta(h)
	// complexitate generala: O(n)
	// complexitate spatiu: Theta(1)
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	// complexitate timp: caz favorabil - theta(1), caz defavorabil - theta(n) - caz mediu - theta(h)
	// complexitate generala: O(h)
	// complexitate spatiu: Theta(1)
	TValoare cauta(TCheie c) const;


	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	// complexitate timp: caz favorabil - theta(1), caz defavorabil - theta(n) - caz mediu - theta(h)
	// complexitate generala: O(h)
	// complexitate spatiu: Theta(1)
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar
	// complexitate timp: caz favorabil - theta(1), caz defavorabil - theta(1) - caz mediu - theta(1)
	// complexitate spatiu: Theta(1)
	int dim() const;

	//verifica daca dictionarul e vid
	// complexitate timp: Theta(1)
	// complexitate spatiu: Theta(1)
	bool vid() const;

	// se returneaza iterator pe dictionar
	// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
	// complexitate timp: Theta(1)
	// complexitate spatiu: Theta(1)
	Iterator iterator() const;


	// destructorul dictionarului
	// complexitate timp: Theta(1)
	// complexitate spatiu: Theta(1)
	~DO();

};
