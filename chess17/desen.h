// Chess17 v0.7 - Dan Nigai

void draw_lin(int l)
{
	for (int i = 1; i <= l; i++)
	{
		std::cout << "\n";
	}
}


void draw(tabla *tab)
{
	draw_lin(12);
	std::cout << "\nTura: " << tab->contor << "\nRandul jucatorului: ";
	if (tab->jucator == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //red
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	std::cout << tab->jucator;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	std::cout << ".\n\n";

	std::cout << "    a  b  c  d  e  f  g  h\n";
	for (int j = 1; j <= 8; j++)
	{
		std::cout << " ";
		std::cout << IO.Yout(j);
		std::cout << " ";
		for (int i = 1; i <= 8; i++)
		{
				if (i % 2 == j % 2)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

				std::cout << "[";

				if (tab->verif_mutare(tab, mutare(tab->select, pct(i, j))))	
				{

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (10-4*(tab->jucator)));  //2 sau 6
					if ( tab->pos[i][j]->jucator == 0)
						std::cout << "+";
					else
						std::cout << (tab->pos[i][j]->display);
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13 - tab->pos[i][j]->jucator);
					if ((i == tab->select.x) && (j == tab->select.y))
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5 - tab->pos[i][j]->jucator);
					std::cout << (tab->pos[i][j]->display);
				}
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

				if (i % 2 == j % 2)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); 
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

				std::cout << "]";

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		std::cout << "\n";
	}
}

