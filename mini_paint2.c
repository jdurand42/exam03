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

void algo(char **tab, float w, float h, float xc, float yc, float r, char type, char c)
{
	float i = 0;
	float j = 0;
	float d;

	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			d = sqrtf((xc - j) * (xc - j) + (yc - i) * (yc - i));
		 	if (type == 'C' && d <= r)
				tab[(int)i][(int)j] = c;
			else if (type == 'c' && d <= r && r - d <= 1)
				tab[(int)i][(int)j] = c; 
			j++;
				
		}
		i++;
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
	float r;
	char type;
	char c;
	char empty;
	float xc;
	float yc;
	
	if (ac != 2)
		return(ft_error("Error: argument\n", NULL));
	file = fopen(av[1], "r");
	if (!file)
		return (ft_error("Error: Operation file corrupted\n", NULL));		
	// Reading start

	ret = fscanf(file, "%f %f %c\n", &w, &h, &empty);
	if (ret != 3 || w < 0 || w >= 300 || h < 0 || h >= 300)
		return (ft_error("Error: Operation file corrupted\n", file));
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
	while  ((ret = fscanf(file, "%c %f %f %f %c\n", &type, &xc, &yc, &r, &c)) == 5)
	{
		if ((type != 'C' && type != 'c') || r <= 0)
		{
			ft_free(tab, w, h);
			return (ft_error("Error: Operation file corrupted\n", file));
		}
		algo(tab, w, h, xc, yc, r, type, c);
	}
	if (ret != -1)
	{
		ft_free(tab, w, h);
		return (ft_error("Error: Operation file corrupted\n", file));
	}	
	print_tab(tab, w, h);
	fclose(file); 
	ft_free(tab, w, h);
	return (0);
}
