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

int			deal_key(int key, t_window *w)
{
	if (key == 53)
		exit(1);
	else if (key == 126)
		w->mvy -= 0.3;
	else if (key == 125)
		w->mvy += 0.3;
	else if (key == 123)
		w->mvx -= 0.3;
	else if (key == 124)
		w->mvx += 0.3;
	else if (key == 78)
		w->zm *= 1.25;
	else if (key == 69)
		w->zm /= 1.25;
	mlx_clear_window(w->mlx_ptr, w->win_ptr);
	if (w->fractol == 1)
		julia(w, -1, -1, -1);
	else if (w->fractol == 2)
		mandelbrot(w, -1, -1, -1);
	else if (w->fractol == 3)
		tricorn(w, -1, -1, -1);
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
			w->zm /= 1.25;
		else if (key == 5)
			w->zm *= 1.25;
	}
	mlx_clear_window(w->mlx_ptr, w->win_ptr);
	if (w->fractol == 1)
		julia(w, -1, -1, -1);
	else if (w->fractol == 2)
		mandelbrot(w, -1, -1, -1);
	else if (w->fractol == 3)
		tricorn(w, -1, -1, -1);
	return (0);
}

t_window	*create_wind(char **av, t_window *w)
{
	w->zm = TRICORN ? 0.7 : 1;
	w->mvx = !ft_strcmp("mandelbrot", av[1]) || MANDELBROT ? -0.5 : 0;
	w->mvy = 0;
	w->clr = 6;
	w->endian = 0;
	w->size_line = 0;
	w->bpp = 0;
	w->image = mlx_new_image(w->mlx_ptr, WIDTH, HEIGHT);
	w->adr = (int *)mlx_get_data_addr(w->image, &w->endian,
		&w->size_line, &w->bpp);
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->image, 0, 0);
	w->pr = -0.7;
	w->pi = 0.27015;
	if (JULIA && (w->fractol = 1))
		julia(w, -1, -1, -1);
	if ((!ft_strcmp("mandelbrot", av[1]) || MANDELBROT) && (w->fractol = 2))
		mandelbrot(w, -1, -1, -1);
	if (TRICORN && (w->fractol = 3))
		tricorn(w, -1, -1, -1);
	return (w);
}

int			main(int ac, char **av)
{
	t_window	*w;

	if (ac != 2 || (ft_strcmp("Julia", av[1]) && ft_strcmp("julia", av[1])
		&& ft_strcmp("Mandelbrot", av[1]) && ft_strcmp("Tricorn", av[1])
		&& ft_strcmp("mandelbrot", av[1]) && ft_strcmp("tricorn", av[1])))
	{
		ft_printf(PINK "USAGE: " PURPLE "[./fractol {fractals}]\n" NC);
		ft_printf(PINK "fractals : " NC
			" (J/j)ulia | (M/m)andelbrot | (T/t)ricorn\n");
		return (0);
	}
	w = (t_window*)malloc(sizeof(t_window));
	w->mlx_ptr = mlx_init();
	w->win_ptr = mlx_new_window(w->mlx_ptr, WIDTH, HEIGHT, "fractol");
	w = create_wind(av, w);
	mlx_hook(w->win_ptr, 2, 0, deal_key, w);
	mlx_hook(w->win_ptr, 6, 0, zoom_jul, w);
	mlx_mouse_hook(w->win_ptr, zoom, w);
	mlx_hook(w->win_ptr, 17, 0, exit_x, w);
	mlx_loop(w->mlx_ptr);
	return (0);
}
