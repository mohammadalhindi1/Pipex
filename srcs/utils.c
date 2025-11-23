/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi@student.42amman.com <malhendi>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 03:30:00 by malhendi          #+#    #+#             */
/*   Updated: 2025/11/23 04:26:43 by malhendi@st      ###   ########.fr       */
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

void	free_cmds(char ***cmds, int count)
{
	int	i;

	if (!cmds)
		return ;
	i = 0;
	while (i < count)
	{
		if (cmds[i])
			free_2d(cmds[i]);
		i++;
	}
	free(cmds);
}

static void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	cleanup_pipex(t_pipex *px)
{
	if (!px)
		return ;
	if (px->cmds)
	{
		free_cmds(px->cmds, px->cmd_count);
		px->cmds = NULL;
	}
	if (px->paths)
	{
		free_paths(px->paths);
		px->paths = NULL;
	}
	if (px->fd_in >= 0)
		close(px->fd_in);
	if (px->fd_out >= 0)
		close(px->fd_out);
	if (px->pipe_fd[0] >= 0)
		close(px->pipe_fd[0]);
	if (px->pipe_fd[1] >= 0)
		close(px->pipe_fd[1]);
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
