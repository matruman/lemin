#include "mlx.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int		color_w(float val, int c)
{
	int		color;
	int		r;
	int		g;
	int		b;

	if (val > 1)
		return (c);
	val = powf(val, 0.7);
	r = (c & 0xff0000) >> 16;
	g = (c & 0x00ff00) >> 8;
	b = c & 0x0000ff;
	color = ((int)(val * r) << 16) + ((int)(val * g) << 8) + (int)(val * b);
	return (color);
}

int		color_d(float val, float pos)
{
	float	red;
	float	blue;
	int		color;

	if (val > 1)
		return (0xffffff);
	val = powf(val, 0.7);
	red = val * 256.0 * pos;
	blue = val * 256.0 * (1 - pos);
	color = 256 * 256 * (int)red + (int)blue;
	return (color);
}

void	gv_line(void *mlx_ptr, void *win_ptr,
		int x1, int y1, int x2, int y2, int color)
{
	int dy;
	int dx;

	if (y2 == y1 && x2 == x1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, color);
		return ;
	}
	if (x1 == x2)
	{
		dy = (y2 - y1)/abs(y2 - y1);
		while (y1 != y2)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, color);
			y1 += dy;
		}
	}
	else
	{
		dx = (x2 - x1)/abs(x2 - x1);
		while (x1 != x2)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, color);
			x1 += dx;
		}
	}
}

void	dgv_line(void *mlx_ptr, void *win_ptr,
		int x1, int y1, int x2, int y2)
{
	int 	dy;
	int 	dx;
	int		lx;
	int		ly;
	float	pos;
	int		c;

	if (y2 == y1 && x2 == x1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 0xffffff);
		return ;
	}
	if (x1 == x2)
	{
		dy = (y2 - y1)/abs(y2 - y1);
		ly = (float)(y2 - y1);
		while (y1 != y2)
		{
			pos = (ly - (float)(y2 - y1)) / ly;
			c = color_d(1, pos);
			mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, c);
			y1 += dy;
		}
	}
	else
	{
		dx = (x2 - x1)/abs(x2 - x1);
		lx = (float)(x2 - x1);
		while (x1 != x2)
		{
			pos = (lx - (float)(x2 - x1)) / lx;
			c = color_d(1, pos);
			mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, c);
			x1 += dx;
		}
	}
}

void	line(void *mlx_ptr, void *win_ptr,
		int x1, int y1, int x2, int y2, int color)
{	
	int sign;
	int sign2;
	int	c;

	if (y2 == y1 || x2 == x1)
	{
		gv_line(mlx_ptr, win_ptr, x1, y1, x2, y2, color);
		return ;
	}
	if (abs(y2 - y1) > abs(x2 - x1))
	{
		sign = (y2 - y1)/(abs(y2 - y1));
		sign2 = (x2 - x1)/(abs(x2 - x1));
		float dx = sign * (float)(x2 - x1)/(float)(y2 - y1);
		float sx = 0;
		while (sign * y1 <= sign * y2)
		{
			c = color_w(1 - fabsf((int)sx - sx), color);
			mlx_pixel_put(mlx_ptr, win_ptr, x1 + (int)sx, y1, c);
			c = color_w(1 - fabsf((int)sx - sx + 1 * sign2), color);
			mlx_pixel_put(mlx_ptr, win_ptr, x1 + (int)sx + 1 * sign2, y1, c);
			y1 += sign;
			sx += dx;
		}
	}
	else
	{
		sign = (x2 - x1)/(abs(x2 - x1));
		sign2 = (y2 - y1)/(abs(y2 - y1));
		float dy = sign * (float)(y2 - y1)/(float)(x2 - x1);
		float sy = 0;
		while(sign * x1 <= sign * x2)
		{
			c = color_w(1 - fabsf((int)sy - sy), color);
			mlx_pixel_put(mlx_ptr, win_ptr, x1, y1 + (int)sy, c);
			c = color_w(1 - fabsf((int)sy - sy + 1 * sign2), color);
			mlx_pixel_put(mlx_ptr, win_ptr, x1, y1 + (int)sy + 1 * sign2, c);
			x1 += sign;
			sy += dy;
		}
	}
}

void	d_line(void *mlx_ptr, void *win_ptr,
		int x1, int y1, int x2, int y2)
{	
	int 	sign;
	int 	sign2;
	float	pos;
	float	lx;
	float	ly;
	int		c;

	lx = (float)(x2 - x1);
	ly = (float)(y2 - y1);
	if (y2 == y1 || x2 == x1)
	{
		dgv_line(mlx_ptr, win_ptr, x1, y1, x2, y2);
		return ;
	}
	if (abs(y2 - y1) > abs(x2 - x1))
	{
		sign = (y2 - y1)/(abs(y2 - y1));
		sign2 = (x2 - x1)/(abs(x2 - x1));
		float dx = sign * lx / ly;
		float sx = 0;
		while (sign * y1 <= sign * y2)
		{
			pos = sx / lx;
			c = color_d(1 - fabsf((int)sx - sx), pos);
			mlx_pixel_put(mlx_ptr, win_ptr, x1 + (int)sx, y1, c);
			c = color_d(1 - fabsf((int)sx - sx + 1 * sign2), pos);
			mlx_pixel_put(mlx_ptr, win_ptr, x1 + (int)sx + 1 * sign2, y1, c);
			y1 += sign;
			sx += dx;
		}
	}
	else
	{
		sign = (x2 - x1)/(abs(x2 - x1));
		sign2 = (y2 - y1)/(abs(y2 - y1));
		float dy = sign * ly / lx;
		float sy = 0;
		while(sign * x1 <= sign * x2)
		{
			pos = sy / ly;
			c = color_d(1 - fabsf((int)sy - sy), pos);
			mlx_pixel_put(mlx_ptr, win_ptr, x1, y1 + (int)sy, c);
			c = color_d(1 - fabsf((int)sy - sy + 1 * sign2), pos);
			mlx_pixel_put(mlx_ptr, win_ptr, x1, y1 + (int)sy + 1 * sign2, c);
			x1 += sign;
			sy += dy;
		}
	}
}
