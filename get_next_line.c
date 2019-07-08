/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjohnsto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 09:30:46 by kjohnsto          #+#    #+#             */
/*   Updated: 2019/07/08 13:11:41 by kjohnsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	verifyline(char **stack, char **line)
{
	char	*tmp_stack;
	char	*strch_stack;
	int		i;

	i = 0;
	strch_stack = *stack;
	while (strch_stack[i] != '\n')
		if (!strch_stack[i++])
			return (0);
	tmp_stack = &strch_stack[i];
	*tmp_stack = '\0';
	*line = ft_strdup(*stack);
	*stack = ft_strdup(tmp_stack + 1);
	return (1);
}

static int	readline(int fd, char *heap, char **stack, char **line)
{
	int		ret;
	char	*tmp_stack;

	while ((ret = read(fd, heap, BUFF_SIZE)) > 0)
	{
		heap[ret] = '\0';
		if (*stack)
		{
			tmp_stack = *stack;
			*stack = ft_strjoin(tmp_stack, heap);
			free(tmp_stack);
			tmp_stack = NULL;
		}
		else
			*stack = ft_strdup(heap);
		if (verifyline(stack, line))
			break;
	}
	return (RET_VALUE(ret));
}

int		get_next_line(const int fd, char **line)
{
	static char	*stack[MAX_FD];
	char		*heap;
	int			ret;
	int			i;

	if (!line || (fd < 0 || fd >= MAX_FD) || (read(fd,stack[fd], 0) <0) ||
			!(heap = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	i = 0;
	while (i < BUFF_SIZE)
		heap[i++] = '\0';
	ret = readline(fd, heap, &stack[fd], line);
	free (heap);
	if (ret != 0 || stack[fd] == NULL || stack[fd][0] == '\0')
	{
		if (!ret && *line)
			*line = NULL;
		return (ret);
	}
	*line = stack[fd];
	stack[fd] = NULL;
	return (1);
}
