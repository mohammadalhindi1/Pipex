/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi <malhendi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 03:50:00 by malhendi          #+#    #+#             */
/*   Updated: 2025/11/18 21:40:29 by malhendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex *px)
{
	char	*path;

	if (px->fd_in < 0)
		exit(1);
	if (dup2(px->fd_in, STDIN_FILENO) == -1)
		exit_handle(px, "dup2 error", 1);
	if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
		exit_handle(px, "dup2 error", 1);
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	close(px->fd_in);
	path = get_cmd_path(px, px->cmd1);
	if (!path)
	{
		ft_putendl_fd("command not found", 2);
		exit(127);
	}
	execve(path, px->cmd1, px->envp);
	perror("execve");
	exit(1);
}

void	second_child(t_pipex *px)
{
	char	*path;

	if (dup2(px->pipe_fd[0], STDIN_FILENO) == -1)
		exit_handle(px, "dup2 error", 1);
	if (dup2(px->fd_out, STDOUT_FILENO) == -1)
		exit_handle(px, "dup2 error", 1);
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	if (px->fd_in >= 0)
		close(px->fd_in);
	close(px->fd_out);
	path = get_cmd_path(px, px->cmd2);
	if (!path)
	{
		ft_putendl_fd("command not found", 2);
		exit(127);
	}
	execve(path, px->cmd2, px->envp);
	perror("execve");
	exit(1);
}
