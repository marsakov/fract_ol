/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 15:18:09 by msakovyc          #+#    #+#             */
/*   Updated: 2018/09/16 15:18:18 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/includes/libft.h"
# include "mlx.h"
# include "math.h"

# define HEIGHT 600
# define WIDTH 800
# define R 255 - (i * 252 % 256)
# define G 255 - ((i * 500) % 256)
# define JULIA (!ft_strcmp("Julia", av[1]) || !ft_strcmp("julia", av[1]))
# define MANDELBROT !ft_strcmp("Mandelbrot", av[1])
# define TRICORN (!ft_strcmp("Tricorn", av[1]) || !ft_strcmp("tricorn", av[1]))

typedef struct			s_window
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*image;
	int					endian;
	int					size_line;
	int					bpp;
	int					maxi;
	double				newre;
	double				newim;
	double				oldre;
	double				oldim;
	double				pr;
	double				pi;
	double				mvx;
	double				mvy;
	double				zm;
	int					clr;
	int					*adr;
	int					fractol;
}						t_window;

int			clr(int r, int g, int b);
void		mandelbrot(t_window *w, int x, int y, int i);
void		tricorn(t_window *w, int x, int y, int i);
void		julia(t_window *w, int x, int y, int i);
int			deal_key(int key, t_window *w);
int			zoom_jul(int x, int y, t_window *w);
int			zoom(int key, int x, int y, t_window *w);
int			exit_x(void);
t_window	*create_wind(char **av, t_window *w);

#endif