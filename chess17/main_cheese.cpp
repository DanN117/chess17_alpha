// Chess17 v0.7 - Dan Nigai

#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<string> 
#include<math.h> 
#include<conio.h>
#include<stdio.h>
#include<Windows.h>
#include "extra.h"
#include "chestii_sah.h"
#include "in_out.h"
#include "desen.h"


// aici se primeste un pointer catre un int (adica o adresa de memorie unde se afla un int)
void inc(int *x)
{
	(*x)++;
}

// aici se primeste un int 'prin referinta', adica nu se copiaza valoarea (deci nu prin valoare), ci efectiv obiectul/variabila
void incbyref(int &x)
{
	x++;
}

class TablaPlusScor
{
	tabla tabla;
	mutare mutare;

	TablaPlusScor *prev;
	TablaPlusScor **next;

	// next = new *next[nr_moves];
	//for (...) next[i] = new TablaPlusScor();
};

void main()
{ 
	int x = 0;
	inc(&x);
	incbyref(x);

	tabla *tab0 = new tabla (0);
	mutare mtc;
	while (tab0->contor < 37)
	{
		/*
		if (tab0->contor % 2 == 0)
		{
			//AI
		}
		else
		{*/
			do
			{
				draw(tab0);
				mtc.p0 = IO.read_pos(tab0, 0);
			} while (tab0->verif_select(tab0, mtc.p0, 0) == 0);

			tab0->select = mtc.p0;

			do
			{
				draw(tab0);
				mtc.p1 = IO.read_pos(tab0, 1);
			} while (tab0->verif_mutare(tab0, mtc) == 0);
		//}

		if (tab0->verif_mutare(tab0, mtc))	
			tab0->aplic_mutare(tab0, mtc);
		draw_lin(12);
	}
	std::cout << "\n\n  ERROR!  \n";
	getchar();
}