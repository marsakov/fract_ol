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

int				color(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

unsigned int	choose_col(int n, int i)
{
	if (!n)
		return (color(250 - (i % 256),\
			255 - ((i * 30) % 256), 252 - ((i * 51) % 256)));
	else if (n == 1)
		return (color(255 - (i * 232 % 256),\
			255 - ((i * 510) % 256), 255 - ((i * 232) % 256)));
	else if (n == 2)
		return (color(((i * 100) % 256),\
			(5 - (i * 20) % 200), ((i * 175) % 200)));
	else if (n == 3)
		return (color(255 - (i * 30 % 256),\
			255 - ((i * 5) % 256), 255 - ((i * 2) % 256)));
	else if (n == 4)
		return (color((i % 256),\
			((i * 30) % 256), ((i * 5) % 256)));
	else if (n == 5)
		return (color(255 - (i * 252 % 256),\
			255 - ((i * 500) % 256), 255 - ((i * 500) % 256)));
	else if (n == 6)
		return (color(255 - (i * 0),\
			255 - ((i * 80) % 256), 200 - ((i * 450) % 256)));
		return (0);
}

void		mandelbrot(t_window *wnd)
{
	wnd->zoom = 1;
	wnd->moveX = -0.5;
	wnd->moveY = 0;
	wnd->maxIterations = 300;
	wnd->color = 0;
	for(int y = 0; y < HEIGHT; y++)
		for(int x = 0; x < WIDTH; x++)
		{
			wnd->pr = 1.5 * (x - WIDTH / 2) / (0.5 * wnd->zoom * WIDTH) + wnd->moveX;
			wnd->pi = (y - HEIGHT / 2) / (0.5 * wnd->zoom * HEIGHT) + wnd->moveY;
			wnd->newRe = wnd->newIm = wnd->oldRe = wnd->oldIm = 0;
			int i;
			for(i = 0; i < wnd->maxIterations; i++)
			{
				wnd->oldRe = wnd->newRe;
				wnd->oldIm = wnd->newIm;
				wnd->newRe = wnd->oldRe * wnd->oldRe - wnd->oldIm * wnd->oldIm + wnd->pr;
				wnd->newIm = 2 * wnd->oldRe * wnd->oldIm + wnd->pi;
				if((wnd->newRe * wnd->newRe + wnd->newIm * wnd->newIm) > 4) break;
			}
			if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
			{
				if (i < wnd->maxIterations)
					wnd->color = choose_col(wnd->color % 7, i);
				else
					wnd->color = 0;
			}
			// wnd->color = choose_col(wnd->color % 7, i);
			mlx_pixel_put(wnd->mlx_ptr, wnd->win_ptr, x, y, wnd->color);
		}
}

void		julia(t_window *wnd)
{
	wnd->color = 0;
	wnd->pr = -0.7;
	wnd->pi = 0.27015;
	wnd->maxIterations = 128;
	wnd->color = 0;
	for(int y = 0; y < HEIGHT; y++)
	{
		for(int x = 0; x < WIDTH; x++)
		{
			wnd->newRe = 1.5 * (x - WIDTH / 2) / (0.5 * wnd->zoom * WIDTH) + wnd->moveX;
			wnd->newIm = (y - HEIGHT / 2) / (0.5 * wnd->zoom * HEIGHT) + wnd->moveY;
			int i;
			for(i = 0; i < wnd->maxIterations; i++)
			{
				wnd->oldRe = wnd->newRe;
				wnd->oldIm = wnd->newIm;
				wnd->newRe = wnd->oldRe * wnd->oldRe - wnd->oldIm * wnd->oldIm + wnd->pr;
				wnd->newIm = 2 * wnd->oldRe * wnd->oldIm + wnd->pi;
				if ((wnd->newRe * wnd->newRe + wnd->newIm * wnd->newIm) > 4)
					break;
			}
			if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
			{
				if (i < wnd->maxIterations)
					wnd->color = choose_col(wnd->color % 7, i);
				else
					wnd->color = 0;
			}
			mlx_pixel_put(wnd->mlx_ptr, wnd->win_ptr, x, y, wnd->color);
		}
	}
}

int			deal_key(int key, t_window *wnd)
{
	key++;
	mlx_clear_window(wnd->mlx_ptr, wnd->win_ptr);
	// julia(wnd);
	return (0);
}

t_window	*create_wind(char **av)
{
	t_window	*wnd;

	wnd = (t_window*)malloc(sizeof(t_window));
	wnd->mlx_ptr = mlx_init();
	wnd->win_ptr = mlx_new_window(wnd->mlx_ptr, WIDTH, HEIGHT, "fractol");
	wnd->zoom = 1;
	wnd->moveX = 0;
	wnd->moveY = 0;
	if (!ft_strcmp("Julia", av[1]) || !ft_strcmp("julia", av[1]))
		julia(wnd);
	if (!ft_strcmp("Mandelbrot", av[1]) || !ft_strcmp("mandelbrot", av[1]))
		mandelbrot(wnd);
	// if (!ft_strcmp("Island", av[1]) || !ft_strcmp("island", av[1]))
		// set(wnd, -0.7, 0.27015, 128);
	mlx_hook(wnd->win_ptr, 2, 5, deal_key, wnd);
	mlx_loop(wnd->mlx_ptr);
	return (wnd);
}


int			main(int ac, char **av)
{
	t_window	*wnd;

	if (ac != 2 || (ft_strcmp("Julia", av[1]) && ft_strcmp("julia", av[1])
		&& ft_strcmp("Mandelbrot", av[1]) && ft_strcmp("Island", av[1])
		&& ft_strcmp("mandelbrot", av[1]) && ft_strcmp("island", av[1])))
	{
		ft_printf(PINK "USAGE: " PURPLE "[./fractol {fractals}]\n" NC);
		ft_printf(PINK "fractals : " NC " (J/j)ulia | (M/m)andelbrot | (I/i)sland\n");
		return (0);
	}
	wnd = create_wind(av);
	return (0);
}
