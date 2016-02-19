// Chess17 v0.7 - Dan Nigai

int nr_prim(int p)		// 1>
{
	if (p <= 1)
		return 0;
	for (int i = 2; i < p; i++)
	{
		if (p % i != 0)
			return 0;
	}
	return 1;
}