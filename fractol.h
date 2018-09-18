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
	int					maxIterations;
	double				newRe;
	double				newIm;
	double				oldRe;
	double				oldIm;
	double				pr;
	double				pi;
	double				moveX;
	double				moveY;
	double				zoom;
	unsigned int		color;
}						t_window;

#endif