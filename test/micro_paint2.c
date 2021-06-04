#include <libc.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int ft_error(char *s, FILE *file)
{
	if (file)
		fclose(file);
	write(1, s, ft_strlen(s));
	return (1);
}

void print_tab(char **tab, float w, float h)
{
	int i = 0;
	int j = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			write(1, &tab[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void ft_free(char **tab, float w, float h)
{
	int i = 0;

	(void)w;
	while (i < h)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void algo(char **tab, float w, float h, float xc, float yc, float lx, float hy, char type, char c)
{
	float x = 0;
	float y = 0;

	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (x >= xc && x <= xc + lx && y >= yc && y <= yc + hy)
			{
				if (type == 'R')
					tab[(int)y][(int)x] = c;
				else if (type == 'r')
				{
					if (x - xc < 1 || y - yc < 1 ||
					(xc + lx) - x < 1 || (yc + hy) - y < 1)
						tab[(int)y][(int)x] = c;
				}
			}	
			x++;
		}
		y++;
	}
}

int main(int ac, char **av)
{
	int ret;
	int i = 0;
	FILE *file;
	char **tab;
	float w;
	float h;
	char type;
	char c;
	char empty;
	float xc;
	float yc;
	float lx;
	float hy;
	
	if (ac != 2)
		return(ft_error("Error: argument\n", NULL));
	file = fopen(av[1], "r");
	if (!file)
		return (ft_error("Error: Operation file corrupted\n", NULL));		
	// Reading start

	ret = fscanf(file, "%f %f %c\n", &w, &h, &empty);
	if (ret != 3 || w <= 0 || w >= 300 || h <= 0 || h >= 300)
	{
		// printf("Layer 1\n");
		return (ft_error("Error: Operation file corrupted\n", file));
	}	
	if (!(tab = (char**)malloc(h * sizeof(char*))))
		return (1);
	
	while (i < h)
	{
		if (!(tab[i] = (char*)malloc(w * sizeof(char))))
			return (1);
		memset(tab[i], empty, w);
		i++;
	}
	//print_tab(tab, w, h);
	i = 0;
	while  ((ret = fscanf(file, "%c %f %f %f %f %c\n", &type, &xc, &yc, &lx, &hy, &c)) == 6)
	{
		i++;
		if ((type != 'R' && type != 'r') || lx <= 0 || hy <= 0)
		{
			// printf("%c %f %f %f %f %c\n", type, xc, yc, lx, hy, c);
			// printf("Layer 2: iteration %d\n", i);
			ft_free(tab, w, h);
			return (ft_error("Error: Operation file corrupted\n", file));
		}
		algo(tab, w, h, xc, yc, lx, hy, type, c);
	}
	if (ret != -1)
	{
		// printf("Layer4\n");
		ft_free(tab, w, h);
		return (ft_error("Error: Operation file corrupted\n", file));
	}
	print_tab(tab, w, h);
	fclose(file);
	ft_free(tab, w, h);
	return (0);
}
