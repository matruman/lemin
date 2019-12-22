#include "lemin.h"

void			die(void)
{
	ft_putstr("ERROR\n");
	exit(1);
}

int				main(void)
{
	t_main	*main;
	char	*line;
	int		ch;

	line = NULL;
	ch = 0;
	if (!(main = (t_main*)lm_init(get_next_line(ch, &line), line)))
		die();
	ft_memdel((void**)&line);
	while (get_next_line(ch, &line) > 0)
	{
			if (!reader(main, &line, ch))
                break ;
		ft_memdel((void**)&line);
	}
    ft_memdel((void**)&line);
	display_graph(main);
	return (0);
}