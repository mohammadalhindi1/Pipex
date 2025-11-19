/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi@student.42amman.com <malhendi>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 03:30:00 by malhendi          #+#    #+#             */
/*   Updated: 2025/11/19 07:59:12 by malhendi@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_2d(char **strings)
{
	int	i;

	if (!strings)
		return ;
	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

static void	cleanup_pipex(t_pipex *px)
{
	if (!px)
		return ;
	if (px->cmd1)
	{
		free_2d(px->cmd1);
		px->cmd1 = NULL;
	}
	if (px->cmd2)
	{
		free_2d(px->cmd2);
		px->cmd2 = NULL;
	}
	if (px->paths)
	{
		free_2d(px->paths);
		px->paths = NULL;
	}
}

void	exit_handle(t_pipex *px, char *msg, int flag)
{
	cleanup_pipex(px);
	if (msg && *msg)
	{
		if (flag)
			ft_putendl_fd(msg, 2);
		else
			ft_putendl_fd(msg, 1);
	}
	exit(flag);
}
