#include "mlx.h"
#include "../includes/lemin.h"


void	line(void *mlx_ptr, void *win_ptr,
		int x1, int y1, int x2, int y2, int c);
void	d_line(void *mlx_ptr, void *win_ptr,
		int x1, int y1, int x2, int y2);

void	display_graph(t_main *main)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		size = main->coeff;
	t_node	*node;
	t_link	*link;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, main->wsize, main->wsize, "window");
	int		i = 0;
	node = main->graph->node;
	while (node)
	{
		if (node->linkbox->count)
		{
		link = node->linkbox->link;
		while (link)
		{
				if (link->is_true == 1)
					d_line(mlx_ptr, win_ptr, node->x * size, node->y * size, link->node->x * size, link->node->y * size);
				else if (link->is_true == -1)
					d_line(mlx_ptr, win_ptr, link->node->x * size, link->node->y * size, node->x * size, node->y * size);
				else if (link->is_true == 0)
					line(mlx_ptr, win_ptr, node->x * size, node->y * size, link->node->x * size, link->node->y * size, 0xffffff);
			link = link->next;
			}
		}
		i++;
		node = node->next;
	}
	 mlx_loop(mlx_ptr);
}
