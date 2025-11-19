/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi <malhendi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 03:29:19 by malhendi          #+#    #+#             */
/*   Updated: 2025/11/18 21:40:12 by malhendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	open_infile(t_pipex *px)
{
	px->fd_in = open(px->infile, O_RDONLY);
	if (px->fd_in < 0)
	{
		perror(px->infile);
		px->fd_in = -1;
	}
}

static void	open_outfile(t_pipex *px)
{
	px->fd_out = open(px->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->fd_out < 0)
	{
		perror(px->outfile);
		exit_handle(px, "Error: cannot open outfile", 1);
	}
}

static void	init_pipex(t_pipex *px, int argc, char **argv, char **envp)
{
	ft_bzero(px, sizeof(t_pipex));
	if (argc != 5)
		exit_handle(px, "Usage: ./pipex file1 cmd1 cmd2 file2", 1);
	px->infile = argv[1];
	px->outfile = argv[4];
	px->envp = envp;
	px->fd_in = -1;
	px->fd_out = -1;
	px->pipe_fd[0] = -1;
	px->pipe_fd[1] = -1;
	px->cmd1 = ft_split(argv[2], ' ');
	px->cmd2 = ft_split(argv[3], ' ');
	if (!px->cmd1 || !px->cmd2)
		exit_handle(px, "Error: malloc/ft_split failed", 1);
	init_paths(px);
}

int	main(int ac, char *av[], char **envp)
{
	t_pipex	px;

	init_pipex(&px, ac, av, envp);
	open_infile(&px);
	open_outfile(&px);
	pipex_run(&px);
	exit_handle(&px, "", 0);
}
