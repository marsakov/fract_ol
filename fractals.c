/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 18:13:16 by msakovyc          #+#    #+#             */
/*   Updated: 2018/09/21 18:13:21 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			clr(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int			exit_x(void)
{
	exit(1);
}

void		mandelbrot(t_window *w, int x, int y, int i)
{
	w->mvx = -0.5;
	w->maxi = 300;
	while (++y < HEIGHT && (x = -1))
		while (++x < WIDTH && (i = -1))
		{
			w->pr = 1.5 * (x - WIDTH / 2) / (0.5 * w->zm * WIDTH) + w->mvx;
			w->pi = (y - HEIGHT / 2) / (0.5 * w->zm * HEIGHT) + w->mvy;
			w->newre = 0;
			w->newim = 0;
			w->oldre = 0;
			w->oldim = 0;
			while (++i < w->maxi)
			{
				w->oldre = w->newre;
				w->oldim = w->newim;
				w->newre = w->oldre * w->oldre - w->oldim * w->oldim + w->pr;
				w->newim = 2 * w->oldre * w->oldim + w->pi;
				if ((w->newre * w->newre + w->newim * w->newim) > 4)
					break ;
			}
			if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
				w->adr[y * WIDTH + x] = (i < w->maxi) ? clr(R, G, G) : 0;
		}
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->image, 0, 0);
}

void		tricorn(t_window *w, int x, int y, int i)
{
	w->mvx = 0;
	w->maxi = 300;
	while (++y < HEIGHT && (x = -1))
		while (++x < WIDTH && (i = -1))
		{
			w->pr = 1.5 * (x - WIDTH / 2) / (0.5 * w->zm * WIDTH)
					+ w->mvx - 0.3;
			w->pi = (y - HEIGHT / 2) / (0.5 * w->zm * HEIGHT) + w->mvy;
			w->newre = 0;
			w->newim = 0;
			w->oldre = 0;
			w->oldim = 0;
			while (++i < w->maxi)
			{
				w->oldre = w->newre;
				w->oldim = w->newim;
				w->newre = w->oldre * w->oldre - w->oldim * w->oldim + w->pr;
				w->newim = -2 * w->oldre * w->oldim + w->pi;
				if ((w->newre * w->newre + w->newim * w->newim) > 4)
					break ;
			}
			if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
				w->adr[y * WIDTH + x] = (i < w->maxi) ? clr(R, G, G) : 0;
		}
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->image, 0, 0);
}

void		julia(t_window *w, int x, int y, int i)
{
	w->maxi = 128;
	while (++y < HEIGHT && (x = -1))
	{
		while (++x < WIDTH && (i = -1))
		{
			w->newre = 1.5 * (x - WIDTH / 2) / (0.5 * w->zm * WIDTH) + w->mvx;
			w->newim = (y - HEIGHT / 2) / (0.5 * w->zm * HEIGHT) + w->mvy;
			while (++i < w->maxi)
			{
				w->oldre = w->newre;
				w->oldim = w->newim;
				w->newre = w->oldre * w->oldre - w->oldim * w->oldim + w->pr;
				w->newim = 2 * w->oldre * w->oldim + w->pi;
				if ((w->newre * w->newre + w->newim * w->newim) > 4)
					break ;
			}
			if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
				w->adr[y * WIDTH + x] = (i < w->maxi) ? clr(R, G, G) : 0;
		}
	}
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->image, 0, 0);
}
