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

typedef struct			s_window
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*image;
	int					endian;
	int					size_line;
	int					bpp;
	int					maxI;
	double				newRe;
	double				newIm;
	double				oldRe;
	double				oldIm;
	double				pr;
	double				pi;
	double				mvX;
	double				mvY;
	double				zm;
	int					clr;
	int					*adr;
	int					fractol;
}						t_window;

#endif