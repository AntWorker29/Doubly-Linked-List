#include <iostream>
#include <conio.h>
using namespace std;
#define MEM_INSUFFICIENT -1
///// LISTE DUBLU INLANTUITE
// Definire NOD
typedef struct Nod_ {
	int info;
	struct Nod_* suc;//succesor, urmator, legatura
	struct Nod_* pred;//predecesor
}Nod;
//Definire Lista (va contine Front si End) Inceputul si Sfarsitul Listei
typedef struct LDI {
	Nod* front;
	Nod* end;
}LDI;

///////////////////////////////////
Nod* init(const int info) {

	Nod* nodNou = new Nod;
	nodNou->info = info;
	nodNou->suc = NULL;
	nodNou->pred = NULL;
	return nodNou;
}
/*
void Dezalocare(Nod* p) { ////dezalocare din memorie, se va folosi pt stergerea nodurilor
	p = NULL;
	delete[]p;
}
*/
int cautare(LDI* lista, const int elem)
{
	Nod* temp = lista->front;
	bool gasit = false;
	while (temp != NULL)
	{
		if (temp->info == elem)
			gasit = true;
		temp = temp->suc;
	}
	if (gasit == false)
	{
		cout << " Elementul nu a fost gasit!";
		return -1;
	}
	else
	{
		cout << "Valoarea " << elem << " a fost gasita";
		return 0;
	}
}
/////////////////////////////////////////////////////////////////
// De la  stanga la dreapta (inceput -> Sfrasit)
void parcurgereDirecta(LDI* lista) {
	if (lista->front == NULL) {
		cout << "Lista este NULA";
		return;
	}
	Nod* temp = lista->front;
	while (temp != NULL)
	{
		cout << temp->info << " ";
		temp = temp->suc;
	}
}
/////////////////////////////////////////////////////////////////
// De la  dreapta la stanga (sfarsit -> inceput)
void parcurgereInversa(LDI* lista) {
	if (lista->front == NULL) {
		cout << "Lista este NULA";
		return;
	}
	Nod* temp = lista->end;
	while (temp != NULL)
	{
		cout << temp->info << " ";
		temp = temp->pred;
	}
}
/////////////////////////////////////////////////////////////////
LDI* inserareInceput(LDI* lista, const int info)
{
	Nod* nodNou = init(info);
	if (lista->front == NULL)	{
		lista->front = lista->end = nodNou;
	}
	else {
		lista->front->pred = nodNou;
		nodNou->suc = lista->front;
		lista->front = nodNou;
	}
	return lista;
}
/////////////////////////////////////////////////////////////////
LDI* inserareSfarsit(LDI* lista,const int info)
{
	if (lista->front == NULL)
		lista=inserareInceput(lista, info);
	else
	{
		Nod* temp = init(info);
		lista->end->suc = temp;
		temp->pred = lista->end;
		lista->end = temp;
	}
	return lista;
}
/////////////////////////////////////////////////////////////////
LDI* inserareDupa(LDI* lista, const int info_cautata, const int elem_de_inserat)
{
	bool gasit = false;
	if (lista->front == NULL)
		return lista;
	Nod* temp = lista->front;
	while (temp != NULL)
	{
		if (temp->info == info_cautata)
		{
			Nod* nodNou = init(elem_de_inserat);
			nodNou->suc = temp->suc;
			temp->suc->pred = nodNou;
			nodNou->pred = temp;
			temp->suc = nodNou;
			gasit = true;
			break;
		}
		temp = temp->suc;
	}
	if (gasit == false)
		cout << "Elementul nu exista in lista, asa ca nu s-a facut inserarea";

	return lista;
}
/////////////////////////////////////////////////////////////////
LDI* inserareInainte(LDI* lista, const int info_cautata, const int elem_de_inserat)
{
	bool gasit = false;
	if (lista->front == NULL)
		return lista;
	Nod* temp = lista->front;
	//Nod* prim = lista->front;
	if (lista->front->info == info_cautata)
	{
		Nod* prim = init(elem_de_inserat);
		prim->suc = lista->front;
		lista->front->pred = prim;
		prim->pred = NULL;
		lista->front = prim;
		gasit = true;
	}
	while (temp->suc != NULL)
	{
		if (temp->suc->info == info_cautata)
		{

			Nod* nodNou = init(elem_de_inserat);
			nodNou->suc = temp->suc;
			temp->suc->pred = nodNou;
			temp->suc = nodNou;
			nodNou->pred = temp;
			gasit = true;
			break;
		}
		temp = temp->suc;
	}
	if (gasit == false)
		cout << "Elementul nu exista in lista, asa ca nu s-a facut inserarea";
	return lista;
}
/////////////////////////////////////////////////////////////////
LDI* stergereInceput(LDI* lista)
{
	if (lista->front == NULL)
		return NULL;
	Nod* temp = lista->front;
	lista->front = lista->front->suc;
	lista->front->pred = NULL;
	delete[] temp;
	return lista;
}
/////////////////////////////////////////////////////////////////
LDI* stergereSfarsit(LDI* lista)
{
	if (lista->front == NULL)
		return NULL;
	Nod* temp = lista->end->pred; //temp= penultimul element din lista
	temp->suc = NULL;
	lista->end->pred = NULL;
	lista->end = temp;
	return lista;
}
/////////////////////////////////////////////////////////////////
LDI* stergereMijloc(LDI* lista, const int elem_de_sters)
{
	if (lista->front == NULL)
		return NULL;
	Nod* temp = lista->front;
	while (temp->suc != NULL)
	{
		if (temp->suc->info == elem_de_sters)
		{
			Nod* tempptsters = temp->suc;
			temp->suc->suc->pred = temp;
			temp->suc = temp->suc->suc;
			tempptsters->suc = NULL;
			tempptsters->pred = NULL;
			delete[] tempptsters;
		}
		temp = temp->suc;
	}
	return lista;
}
/////////////////////////////////////////////////////////////////
LDI* distrugere(LDI* lista) {
	if (NULL == lista->front)
		return NULL;
	while (NULL != lista->front)
	{
		Nod* temp = lista->front;
		lista->front->pred = NULL;
		lista->front = lista->front->suc;
		delete[] temp;
	}
}
/////////////////////////////////////////////////////////////////
LDI* actualizare(LDI* lista, const int elem_de_actualizat, const int elem_inlocuitor)
{
	Nod* temp = lista->front;
	while (temp != NULL)
	{
		if (temp->info == elem_de_actualizat)
			temp->info = elem_inlocuitor;
		temp = temp->suc;
	}
	return lista;
}
/////////////////////////////////////////////////////////////////
LDI* sortare(LDI* lista) {
	if (lista->front == NULL)
		return lista;
	Nod* temp = lista->front;
	Nod* temp1 = lista->front->suc;
	while (temp->suc != NULL)
	{
		temp1 = temp->suc;
		while (temp1 != NULL)
		{
			if (temp->info > temp1->info)
			{
				int aux = temp->info;
				temp->info = temp->suc->info;
				temp->suc->info = aux;
			}
			temp1 = temp1->suc;
		}
		temp = temp->suc;
	}
	return lista;
}
/////////////////////////////////////////////////////////////////
int Minim(LDI* lista, int minim)
{
	Nod* temp = lista->front;
	if (lista->front == NULL)
		return -100;
	minim = lista->front->info;
	while (temp != NULL)
	{
		if (temp->info < minim)
			minim = temp->info;
		temp = temp->suc;
	}
	return minim;
}
int Maxim(LDI* lista, int maxim)
{
	Nod* temp = lista->front;
	if (lista->front == NULL)
		return -100;
	maxim = lista->front->info;
	while (temp != NULL)
	{
		if (temp->info > maxim)
			maxim = temp->info;
		temp = temp->suc;
	}
	return maxim;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	//Initializare LDI (structura va contine primul si ultimul NOD)
	LDI* lista = new LDI;
	lista->front = NULL;
	lista->end = NULL;
	char meniu, subMeniu;

	do {
		system("cls");
		cout << "Lista Dublu Inlantuita: " << endl;
		cout << "(p) Parcurgere Directa \n";
		cout << "(o) Parcurgere Inversa \n";
		cout << "(c) Cautare \n";
		cout << "(s) Inserare \n";
		cout << "(t) Stergere \n";
		cout << "(l) Sortare lista \n";
		cout << "(k) Parcurgere Indexata \n";
		cout << "(d) Distrugere \n";
		cout << "(g) Actualizare \n";
		cout << "(r) Minim \n";
		cout << "(f) Maxim \n";
		cout << "(x) Iesire \n";
		meniu = _getch();

		switch (meniu) {
		case 'd':
		{
			//Distrugere / eliberare
			distrugere(lista);
			cout << "Lista este NULA";
			_getch();
			break;
		}
		case 'l':
		{
			//// SORTARE
			cout << "Lista initiala este: " << endl;
			parcurgereDirecta(lista);
			lista=sortare(lista);
			cout << endl << "Lista finala este: " << endl;
			parcurgereDirecta(lista);
			_getch();
			break;
		}
		case 'r':
		{
			//Cautare MINIM
			parcurgereDirecta(lista);
			cout << endl << "Minimul listei este: ";
			cout << Minim(lista, -1);
			_getch();
			break;
		}
		case 'f':
		{
			//Cautare MAXIM
			parcurgereDirecta(lista);
			cout << endl << "Maximul listei este: ";
			cout << Maxim(lista, -1);
			_getch();
			break;
		}
		case 'k':
		{
			//Parcurgere Indexata
			parcurgereDirecta(lista);
			cout << endl;
			for (int i = 0; i < 7; i++);
			_getch();
			break;
		}
		case 'g':
		{
			//Actualizare
			int elem_de_actualizat, elem_inlocuitor;
			cout << "Elementul de actualizat este: "; cin >> elem_de_actualizat;
			cout << "El va fi inlocuit cu valoarea: "; cin >> elem_inlocuitor;
			lista = actualizare(lista, elem_de_actualizat, elem_inlocuitor);
			parcurgereDirecta(lista);
			_getch();
			break;
		}
		case 'p':
		{
			//Parcurgere Directa
			cout << "Lista este: " << endl;
			parcurgereDirecta(lista);
			_getch();
			break;
		}
		case 'o':
		{
			//Parcurgere Inversa
			cout << "Lista este: " << endl;
			parcurgereInversa(lista);
			_getch();
			break;
		}
		case 'c':
		{
			//Cautare
			int cautat;
			cout << "Inserati elementul pe care il cautati: ";
			cin >> cautat;
			cautare(lista, cautat);
			_getch();
			break;
		}
		case 's':
		{
			// Meniu pentru Inserare
			do {
				system("cls");
				cout << "(a) Inserare Inceput \n";
				cout << "(b) Inserare Inainte \n";
				cout << "(c) Inserare Dupa \n";
				cout << "(d) Inserare Sfarsit \n";
				cout << "(x) Iesire \n";
				subMeniu = _getch();
				switch (subMeniu)
				{
				case 'a':
				{	//inserare inceput
					int valoarea;
					cout << "Introduceti valoarea inserata" << endl;
					cin >> valoarea;
					lista = inserareInceput(lista,valoarea);
					parcurgereDirecta(lista);
					_getch();
					break;
				}
				case 'b':
				{	//inserare inainte
					int valcautata, valdeinserat;
					cout << "Valoarea pe care o veti insera: "; cin >> valdeinserat;
					cout << endl << "Valoarea inaintea careia vreti sa inserati: "; cin >> valcautata;
					lista = inserareInainte(lista, valcautata, valdeinserat);
					cout << endl;
					parcurgereDirecta(lista);
					_getch();
					break;
				}

				case 'c':
				{	///Inserare dupa
					int valcautata, valdeinserat;
					cout << "Valoarea pe care o veti insera: "; cin >> valdeinserat;
					cout << endl << "Valoarea dupa care vreti sa inserati: "; cin >> valcautata;
					lista=inserareDupa(lista, valcautata, valdeinserat);
					parcurgereDirecta(lista);
					_getch();
					break;
				}

				case 'd':
				{	//// Inserare Sfarsit
					int valoarea;
					cout << "Inserati la sfarsit elementul: ";
					cin >> valoarea;
					lista = inserareSfarsit(lista, valoarea);
					parcurgereDirecta(lista);
					_getch();
					break;
				}

				}
			} while (subMeniu != 'x');

			break;
		}
		case 't':
		{
			// Meniu pentru Stergere
			do {
				system("cls");
				cout << "(a) Stergere Inceput \n";
				cout << "(b) Stergere Mijloc \n";
				cout << "(c) Stergere Sfarsit \n";
				cout << "(x) Iesire \n";
				subMeniu = _getch();
				switch (subMeniu)
				{
				case 'a':
				{	//stergere inceput
					lista = stergereInceput(lista);
					parcurgereDirecta(lista);
					_getch();
					break;
				}
				case 'b':
				{	// stergere element din mijloc
					int elem_de_sters;
					cout << "Ce element DIN MIJLOCUL LISTEI vreti sa stergeti?"; cin >> elem_de_sters;
					/// DACA ELEM VA FI PE LA MARGINI, NU SE VA STERGE NIMIC, SAU CHIAR INTRA IN EROARE daca e ultimul
					lista = stergereMijloc(lista, elem_de_sters);
					parcurgereDirecta(lista);
					_getch();
					break;
				}
				case 'c':
				{	///stergere sfarsit
					lista = stergereSfarsit(lista);
					parcurgereDirecta(lista);
					_getch();
					break;
				}
				}
			} while (subMeniu != 'x');
			break;
		}
		}

	} while (meniu != 'x');

	distrugere(lista);
	return 0;
}
