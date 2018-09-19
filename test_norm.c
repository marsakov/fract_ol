void		julia(t_window *w, int x, int y, int i)
{
	w->pr = -0.7;
	w->pi = 0.27015;
	w->maxI = 128;
	while (++y < HEIGHT && (x = -1))
		while (++x < WIDTH && (y = -1))
		{
			w->newRe = 1.5 * (x - WIDTH / 2) / (0.5 * w->zoom * WIDTH) + w->mvX;
			w->newIm = (y - HEIGHT / 2) / (0.5 * w->zoom * HEIGHT) + w->mvY;
			i = -1;
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
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->image, 0, 0);
}