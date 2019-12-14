#include "mlx.h"
#include "../includes/lemin.h"


void	line(void *mlx_ptr, void *win_ptr,
		int x1, int y1, int x2, int y2, int c);
void	d_line(void *mlx_ptr, void *win_ptr,
		int x1, int y1, int x2, int y2);

void	display_graph(t_graph	*graph)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		height = 512;
	int		width = 512;
	int		size = 1;
	t_node	*node;
	t_link	*link;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, height, width, "window");
	int		i = 0;
	node = graph->node;
	while (node)
	{
		link = node->linkbox->link;
		while (link)
		{
			// if (!link->none)
			// {
				if (link->is_true == 1)
					d_line(mlx_ptr, win_ptr, node->x * size, node->y * size, link->node->x * size, link->node->y * size);
				else if (link->is_true == -1)
					d_line(mlx_ptr, win_ptr, link->node->x * size, link->node->y * size, node->x * size, node->y * size);
				else
					line(mlx_ptr, win_ptr, node->x * size, node->y * size, link->node->x * size, link->node->y * size, 0xffffff);
		//	}
			link = link->next;
		}
		i++;
		node = node->next;
	}
	 mlx_loop(mlx_ptr);
}
