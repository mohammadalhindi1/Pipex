/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi <malhendi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 03:55:00 by malhendi          #+#    #+#             */
/*   Updated: 2025/11/18 21:40:42 by malhendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_run(t_pipex *px)
{
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(px->pipe_fd) == -1)
		exit_handle(px, "pipe error", 1);
	pid1 = fork();
	if (pid1 == -1)
		exit_handle(px, "fork error", 1);
	if (pid1 == 0)
		first_child(px);
	pid2 = fork();
	if (pid2 == -1)
		exit_handle(px, "fork error", 1);
	if (pid2 == 0)
		second_child(px);
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	if (px->fd_in >= 0)
		close(px->fd_in);
	if (px->fd_out >= 0)
		close(px->fd_out);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
