/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi <malhendi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 03:50:00 by malhendi          #+#    #+#             */
/*   Updated: 2025/11/19 21:16:58 by malhendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_in_out(t_pipex *px, int idx, int prev_fd)
{
	if (idx == 0)
	{
		if (px->fd_in < 0)
			exit_handle(px, NULL, 1);
		if (dup2(px->fd_in, STDIN_FILENO) == -1)
			exit_handle(px, "dup2 error", 1);
	}
	else if (dup2(prev_fd, STDIN_FILENO) == -1)
		exit_handle(px, "dup2 error", 1);
	if (idx == px->cmd_count - 1)
	{
		if (dup2(px->fd_out, STDOUT_FILENO) == -1)
			exit_handle(px, "dup2 error", 1);
	}
	else if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
		exit_handle(px, "dup2 error", 1);
}

static void	close_fds_child(t_pipex *px, int prev_fd)
{
	if (prev_fd >= 0 && prev_fd != px->fd_in)
		close(prev_fd);
	if (px->fd_in >= 0)
		close(px->fd_in);
	if (px->fd_out >= 0)
		close(px->fd_out);
	if (px->pipe_fd[0] >= 0)
		close(px->pipe_fd[0]);
	if (px->pipe_fd[1] >= 0)
		close(px->pipe_fd[1]);
}

void	exec_child(t_pipex *px, int idx, int prev_fd)
{
	char	*path;

	set_in_out(px, idx, prev_fd);
	close_fds_child(px, prev_fd);
	path = get_cmd_path(px, px->cmds[idx]);
	if (!path)
		exit_handle(px, "command not found", 127);
	execve(path, px->cmds[idx], px->envp);
	perror("execve");
	free(path);
	exit_handle(px, NULL, 1);
}
