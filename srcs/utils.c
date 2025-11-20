/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi <malhendi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 03:30:00 by malhendi          #+#    #+#             */
/*   Updated: 2025/11/19 21:14:10 by malhendi         ###   ########.fr       */
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

static void	free_cmds(t_pipex *px)
{
	int	i;

	if (!px->cmds)
		return ;
	i = 0;
	while (i < px->cmd_count)
	{
		if (px->cmds[i])
			free_2d(px->cmds[i]);
		i++;
	}
	free(px->cmds);
	px->cmds = NULL;
}

static void	cleanup_pipex(t_pipex *px)
{
	if (!px)
		return ;
	if (px->cmds)
		free_cmds(px);
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
