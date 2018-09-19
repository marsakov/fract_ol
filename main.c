/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 15:08:23 by msakovyc          #+#    #+#             */
/*   Updated: 2018/09/16 15:09:04 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				clr(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

unsigned int	chs_clr(int n, int i)
{
	if (!n)
		return (clr(250 - (i % 256),\
			255 - ((i * 30) % 256), 252 - ((i * 51) % 256)));
	else if (n == 1)
		return (clr(255 - (i * 232 % 256),\
			255 - ((i * 510) % 256), 255 - ((i * 232) % 256)));
	else if (n == 2)
		return (clr(((i * 100) % 256),\
			(5 - (i * 20) % 200), ((i * 175) % 200)));
	else if (n == 3)
		return (clr(255 - (i * 30 % 256),\
			255 - ((i * 5) % 256), 255 - ((i * 2) % 256)));
	else if (n == 4)
		return (clr((i % 256),\
			((i * 30) % 256), ((i * 5) % 256)));
	else if (n == 5)
		return (clr(255 - (i * 252 % 256),\
			255 - ((i * 500) % 256), 255 - ((i * 500) % 256)));
	else if (n == 6)
		return (clr(255 - (i * 0),\
			255 - ((i * 80) % 256), 200 - ((i * 450) % 256)));
	return (0);
}

void		mandelbrot(t_window *w, int x, int y, int i)
{
	w->mvX = -0.5;
	w->maxI = 300;
	while (++y < HEIGHT && (x = -1))
		while (++x < WIDTH && (i = -1))
		{
			w->pr = 1.5 * (x - WIDTH / 2) / (0.5 * w->zm * WIDTH) + w->mvX;
			w->pi = (y - HEIGHT / 2) / (0.5 * w->zm * HEIGHT) + w->mvY;
			w->newRe = 0;
			w->newIm = 0;
			w->oldRe = 0;
			w->oldIm = 0;
			while (++i < w->maxI)
			{
				w->oldRe = w->newRe;
				w->oldIm = w->newIm;
				w->newRe = w->oldRe * w->oldRe - w->oldIm * w->oldIm + w->pr;
				w->newIm = 2 * w->oldRe * w->oldIm + w->pi;
				if ((w->newRe * w->newRe + w->newIm * w->newIm) > 4)
					break ;
			}
			if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
				w->adr[y * WIDTH + x] = (i < w->maxI) ? chs_clr(w->clr % 7, i) : 0;
		}
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->image, 0, 0);
}

void		julia(t_window *w, int x, int y, int i)
{
	w->maxI = 128;
	while (++y < HEIGHT && (x = -1))
	{
		while (++x < WIDTH && (i = -1))
		{
			w->newRe = 1.5 * (x - WIDTH / 2) / (0.5 * w->zm * WIDTH) + w->mvX;
			w->newIm = (y - HEIGHT / 2) / (0.5 * w->zm * HEIGHT) + w->mvY;
			while (++i < w->maxI)
			{
				w->oldRe = w->newRe;
				w->oldIm = w->newIm;
				w->newRe = w->oldRe * w->oldRe - w->oldIm * w->oldIm + w->pr;
				w->newIm = 2 * w->oldRe * w->oldIm + w->pi;
				if ((w->newRe * w->newRe + w->newIm * w->newIm) > 4)
					break;
			}
			if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
				w->adr[y * WIDTH + x] = (i < w->maxI) ? chs_clr(w->clr % 7, i) : 0;
		}
	}
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->image, 0, 0);
}

int			deal_key(int key, t_window *w)
{
	key++;
	mlx_clear_window(w->mlx_ptr, w->win_ptr);
	if (w->fractol == 1)
		julia(w, -1, -1, -1);
	else if (w->fractol == 2)
		mandelbrot(w, -1, -1, -1);
	return (0);
}

int			zoom_jul(int x, int y, t_window *w)
{
	if (w->fractol == 1)
	{
		w->pr = (x - 300) / 128.0;
		w->pi = (y - 300) / 128.0;
		mlx_clear_window(w->mlx_ptr, w->win_ptr);
		julia(w, -1, -1, -1);
	}
	return (0);
}

int			zoom(int key, int x, int y, t_window *w)
{
	if (x >= 0 && y >= 0 && x <= WIDTH && y <= HEIGHT)
	{
		if (key == 4)
			w->zm /= 0.1;
		else if (key == 5)
			w->zm *= 0.1;
	}
	mlx_clear_window(w->mlx_ptr, w->win_ptr);
	if (w->fractol == 1)
		julia(w, -1, -1, -1);
	else if (w->fractol == 2)
		mandelbrot(w, -1, -1, -1);
	return (0);
}

t_window	*create_wind(char **av)
{
	t_window	*w;

	w = (t_window*)malloc(sizeof(t_window));
	w->mlx_ptr = mlx_init();
	w->win_ptr = mlx_new_window(w->mlx_ptr, WIDTH, HEIGHT, "fractol");
	w->zm = 1;
	w->mvX = 0;
	w->mvY = 0;
	w->clr = 0;
	w->endian = 0;
	w->size_line = 0;
	w->bpp = 0;
	w->image = mlx_new_image(w->mlx_ptr, WIDTH, HEIGHT);
	w->adr = (int *)mlx_get_data_addr(w->image, &w->endian, &w->size_line, &w->bpp);
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->image, 0, 0);
	w->pr = -0.7;
	w->pi = 0.27015;
	if ((!ft_strcmp("Julia", av[1]) || !ft_strcmp("julia", av[1])) && (w->fractol = 1))
		julia(w, -1, -1, -1);
	if ((!ft_strcmp("Mandelbrot", av[1]) || !ft_strcmp("mandelbrot", av[1])) && (w->fractol = 2))
		mandelbrot(w, -1, -1, -1);
	// if (!ft_strcmp("Island", av[1]) || !ft_strcmp("island", av[1]))
		// w->fractol = 2;
	mlx_hook(w->win_ptr, 2, 0, deal_key, w);
	mlx_hook(w->win_ptr, 6, 0, zoom_jul, w);
	mlx_mouse_hook(w->win_ptr, zoom, w);
	mlx_loop(w->mlx_ptr);
	return (w);
}


int			main(int ac, char **av)
{
	t_window	*w;

	if (ac != 2 || (ft_strcmp("Julia", av[1]) && ft_strcmp("julia", av[1])
		&& ft_strcmp("Mandelbrot", av[1]) && ft_strcmp("Island", av[1])
		&& ft_strcmp("mandelbrot", av[1]) && ft_strcmp("island", av[1])))
	{
		ft_printf(PINK "USAGE: " PURPLE "[./fractol {fractals}]\n" NC);
		ft_printf(PINK "fractals : " NC " (J/j)ulia | (M/m)andelbrot | (I/i)sland\n");
		return (0);
	}
	w = create_wind(av);
	return (0);
}
