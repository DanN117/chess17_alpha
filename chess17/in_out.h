// Chess17 v0.7 - Dan Nigai

void draw (tabla *tab);

class IO
{
public:
	char Yout(int Yi)	//fct traducere 1-8 -> 8-1 (y out)
	{
		return (9 - Yi) + 48;
	}
	char Xin(char Xc)
	{
		if ((Xc >= 97) && (Xc <= 104))
			return Xc - 96;
		else
			return 0;
	}
	char Yin(char Yc)
	{
		if ((Yc >= 49) && (Yc <= 56))
			return 9 - (Yc - 48);
		else
			return 0;
	}
	pct read_pos(tabla *tab, int j)
	{
		pct pos;
		pos.x = 0;
		pos.y = 0;

		pos.x = 0;
		pos.y = 0;
		char cin;
		std::cout << "\nSelectare coloana ";
		if (j == 1)
			std::cout << "destinatie ";
		std::cout << "(a, b, c, d, e, f, g, h): ";	// X
		while (pos.x == 0)
		{
			std::cin >> cin;
			pos.x = Xin(cin);
		}
		std::cout << "\nSelectare linie ";
		if (j == 1)
			std::cout << "destinatie ";
		std::cout << "(8, 7, 6, 5, 4, 3, 2, 1): ";	// Y
		while (pos.y == 0)
		{
			std::cin >> cin;
			pos.y = Yin(cin);
			draw(tab);
		}
		return pos;
	}
} IO;
