/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi <malhendi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 03:55:00 by malhendi          #+#    #+#             */
/*   Updated: 2025/11/19 21:16:27 by malhendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_if_open(int *fd)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

static void	parent_after_fork(t_pipex *px, int i, int *prev_fd)
{
	if (*prev_fd >= 0 && *prev_fd != px->fd_in)
		close_if_open(prev_fd);
	if (i < px->cmd_count - 1)
	{
		close_if_open(&px->pipe_fd[1]);
		*prev_fd = px->pipe_fd[0];
	}
	else
	{
		close_if_open(&px->pipe_fd[0]);
		close_if_open(&px->fd_in);
		close_if_open(&px->fd_out);
	}
}

void	pipex_run(t_pipex *px)
{
	int		i;
	int		prev_fd;
	pid_t	pid;

	prev_fd = px->fd_in;
	i = 0;
	while (i < px->cmd_count)
	{
		if (i < px->cmd_count - 1 && pipe(px->pipe_fd) == -1)
			exit_handle(px, "pipe error", 1);
		pid = fork();
		if (pid == -1)
			exit_handle(px, "fork error", 1);
		if (pid == 0)
			exec_child(px, i, prev_fd);
		parent_after_fork(px, i, &prev_fd);
		i++;
	}
	while (wait(NULL) > 0)
		;
}
