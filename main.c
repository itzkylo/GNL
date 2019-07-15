/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjohnsto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 09:36:14 by kjohnsto          #+#    #+#             */
/*   Updated: 2019/07/15 09:54:15 by kjohnsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"
#include "fcntl.h"

int	main(int argc, char **argv)
{
	int		ret;
	int		line;
	char	*buff;
	int		fd;

	line = 0;
	fd = open(argv[1], O_RDONLY);
	while ((ret = get_next_line(fd, &buff)) > 0)
	{
		ft_putnbr(ret);
		ft_putstr(" | ");
		ft_putnbr(line++);
		ft_putstr(" | ");
		ft_putendl(buff);
		ft_strdel(&buff);
	}
	if (ret == 0)
	{
		ft_putnbr(ret);
		ft_strdel(&buff);
		ft_putstr(" | EOF");
	}
	sleep(20);
	return (0);
}
