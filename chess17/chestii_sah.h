// Chess17 v0.7 - Dan Nigai

class pct
{
public:
	int x;
	int y;
	pct()
	{
		x = 0;
		y = 0;
	}
	pct(int a, int b)
	{
		x = a;
		y = b;
	}
};

class mutare
{
public:
	pct p0, p1;
	int dX()
	{
		return p1.x - p0.x;
	}
	int dY()
	{
		return p1.y - p0.y;
	}
	int dXa()		//dist*dir.x
	{
		return abs(p1.x - p0.x);
	}
	int dYa()
	{
		return abs(p1.y - p0.y);
	}
	pct vector()	//vector
	{
		pct v;
		v.x = p1.x - p0.x;
		v.y = p1.y - p0.y;
		return v;
	}
	pct dir()	//versor
	{
		pct v;
		if (vector().x != 0)
		{
			v.x = vector().x / abs(vector().x);
		}
		else
		{
			v.x = 0;
		}
		if (vector().y != 0)
		{
			v.y = vector().y / abs(vector().y);
		}
		else
		{
			v.y = 0;
		}
		return v;
	}
	//versor

	int dist()			//lungime
	{
		return max(abs(vector().x), abs(vector().y));
	}

	int distM()
	{
		return abs(vector().x) + abs(vector().y);
	}

	int supr()
	{
		return abs(vector().x) * abs(vector().y);
	}
	int diag()
	{
		return (abs(vector().x) == abs(vector().y));
	}
	mutare(){}
	mutare(pct a, pct b)
	{
		p0 = a; 
		p1 = b;
	}
};

class tabla;

class piesa
{
public:
	char display;	//ascii
	int jucator;	//0 sau 1 sau 2		(0 = spatiu liber)
	int moved;		//a fost mutat?
	pct spawn_point;//unde s-a initializat, pt a verif daca a fost mutata vreodata
	int cost;		//pt. AI
	int index;		//pt. reguli si altele
	piesa(){}
	piesa(pct p0)
	{
			if ((p0.x == 1) || (p0.x == 8))		//tura
			{
				if ((p0.y == 1) || (p0.y == 8))
				{
					display = 'R';
					index = 7;
					cost = 525;
					//+compatibilitate reguli?
				}
			}
			if ((p0.x == 2) || (p0.x == 7))		//cal
			{
				if ((p0.y == 1) || (p0.y == 8))
				{
					display = 'H';
					index = 2;
					cost = 350;
				}
			}
			if ((p0.x == 3) || (p0.x == 6))		//nebun
			{
				if ((p0.y == 1) || (p0.y == 8))
				{
					display = 'B';
					index = 5;
					cost = 350;
				}
			}
			if (p0.x == 4)		//regina
			{
				if ((p0.y == 1) || (p0.y == 8))
				{
					display = 'Q';
					index = 35;
					cost = 1000;
				}
			}
			if (p0.x == 5)	//rege
			{
				if ((p0.y == 1) || (p0.y == 8))
				{
					display = 'K';
					index = 3;
					cost = 1000000;
				}
			}
			if ((p0.x >= 1) && (p0.x <= 8))		//pion
			{
				if ((p0.y == 2) || (p0.y == 7))
				{
					display = 'P';
					index = 11;
					cost = 100;
				}
			}
			if ((p0.x >= 1) && (p0.x <= 8))		//gol
			{
				if ((p0.y >= 3) && (p0.y <= 6))
				{
					jucator = 0;
					display = ' ';
					index = 0;
					cost = 0;
				}
			}
			if (p0.y <= 2)	jucator = 2;
			if (p0.y >= 7)	jucator = 1;
			cost = 300;
			moved = 0;
			spawn_point = p0;
	}

	int cal(mutare mut)
	{
		return ((index % 2 == 0) && (mut.supr() == 2) && (mut.distM() == 3));
	}

	int diag(mutare mut)
	{
		return ((index % 5 == 0) && (mut.dXa() == mut.dYa()));
	}
	int drept(mutare mut)
	{
		return ((index % 7 == 0) && (mut.supr() == 0));
	}
	int unu(mutare mut)
	{
		return ((index % 3 == 0) && ((mut.supr() == 1) || (mut.distM() == 1)));	// +rocada mai tarziu
	}
	int pion(mutare mut, int j)			// j==0 liber, j==1 oponent
	{
		if (index % 11 != 0)
		{
			return 0;
		}
		int directie = ((jucator * 2) - 3);
		if (mut.vector().y*directie < 1)
		{
			return 0;
		}
		if (j == 1 && (mut.dYa() != 1 || mut.dXa() != 1))
		{
			return 0;
		}
		if (j == 0 && mut.dXa() != 0)
		{
			return 0;
		}
		if (j == 0 && (moved == 0 && mut.dYa() > 2) || (moved == 1 && mut.dYa() > 1))
		{
			return 0;
		}
		return 1;
	}

};



class tabla
{
public:
	piesa *pos[9][9];
	int contor;
	int jucator;
	int cost;
	pct select;
	//tabla *tabs[100]
	//^pointeri spre table virtuale dupa mutari virtuale => arbore?

	int verif_select(tabla *tab, pct p0, int j)	//(j e 0(piesa mea) sau 1(piesa oponent/spatiu liber))
	{
		return	 ( 
				 ((j == 0) && (jucator == pos[p0.x][p0.y]->jucator))				//piesa mea cand j == 0
				 ||
				 ((j == 1) && (pos[p0.x][p0.y]->jucator == ((jucator % 2) + 1)))	//piesa oponent cand j == 1
				 ||
				 ((j == 2) && (pos[p0.x][p0.y]->jucator == 0)) 			         	//spatiu liber cand j == 2
				 ||
				 ((j == 3) && ((pos[p0.x][p0.y]->jucator == 0) || (pos[p0.x][p0.y]->jucator == ((jucator % 2) + 1)) ) ) //liber/oponent
				 );	

	}

	int	verif_mutare(tabla *tab, mutare mut)
	{

		if (verif_select(tab, mut.p0, 0) && verif_select(tab, mut.p1, 0))
			return 0;
		if (verif_select(tab, mut.p0, 0) && verif_select(tab, mut.p1, 3))
		{
			if ((tab->pos[mut.p0.x][mut.p0.y]->cal(mut)) && verif_select(tab, mut.p1, 3))
			{
				return 1;
			}
			if ((tab->pos[mut.p0.x][mut.p0.y]->diag(mut)) && verif_select(tab, mut.p1, 3))
			{
				if (tab->raytrace(mut, tab))
				{
					return 1;
				}
			}
			if ((tab->pos[mut.p0.x][mut.p0.y]->drept(mut)) && verif_select(tab, mut.p1, 3))
			{
				if (tab->raytrace(mut, tab))
				{
					return 1;
				}
			}
			if ((tab->pos[mut.p0.x][mut.p0.y]->pion(mut, verif_select(tab, mut.p1, 1))) && verif_select(tab, mut.p1, 3))
			{
				return 1;
			}
			
			if ((tab->pos[mut.p0.x][mut.p0.y]->unu(mut)) && verif_select(tab, mut.p1, 3))
			{
				return 1;
			}
			return 0;
		}
		return 0;
	}

	int raytrace(mutare mut, tabla *tab)
	{

		for (int i = 1; i < mut.dist(); i++)
		{
			if ((tab->verif_select(tab, pct((mut.p0.x + (mut.dir().x*i)), (mut.p0.y + (mut.dir().y*i))), 2)) == 0)
			{
				return 0;
			}
		}
		return 1;
	}

	void aplic_mutare(tabla *tab, mutare mut)
	{
		piesa* x;
		x = tab->pos[mut.p1.x][mut.p1.y];
		tab->pos[mut.p1.x][mut.p1.y] = tab->pos[mut.p0.x][mut.p0.y];
		tab->pos[mut.p0.x][mut.p0.y] = new piesa(pct(7, 6));	//adica egal cu un spatiu liber sau ceva
		tab->pos[mut.p1.x][mut.p1.y]->moved = 1;	//piesa a fost mutata, nu stiu daca ajuta la ceva
		tab->contor++;
		tab->jucator = (2 - (tab->contor % 2));
		tab->select = pct(0, 0);
	}



	tabla(){}
	//+constructor sub-tabla virtuala (tabla_radacina + mutare)
	//+deconstructor tabla virtuala
	//functie parcurgere toate table virtuale, aplicand deconstructorul la fiecare
	//functie cautare cost minmin (sau maxim?) 
	tabla(int a)
	{
		if (a == 0)
		{
			for (int i = 1; i <= 8; i++)
			{
				for (int j = 1; j <= 8; j++)
				{
					pos[i][j] = new piesa(pct(i, j));
				}
			}
			contor = 1;
			jucator = 1;
		}
		cost = 0;
		select = pct(0, 0);

	}
};
