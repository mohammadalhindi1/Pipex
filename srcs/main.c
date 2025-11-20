/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi <malhendi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 03:29:19 by malhendi          #+#    #+#             */
/*   Updated: 2025/11/19 21:17:11 by malhendi         ###   ########.fr       */
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

static void	init_cmds(t_pipex *px, int argc, char **argv)
{
	int	i;

	px->cmd_count = argc - 3;
	px->cmds = malloc(sizeof(char **) * px->cmd_count);
	if (!px->cmds)
		exit_handle(px, "malloc error", 1);
	i = 0;
	while (i < px->cmd_count)
	{
		px->cmds[i] = ft_split(argv[2 + i], ' ');
		if (!px->cmds[i])
			exit_handle(px, "Error: malloc/ft_split failed", 1);
		i++;
	}
}

static void	init_pipex(t_pipex *px, int argc, char **argv, char **envp)
{
	ft_bzero(px, sizeof(t_pipex));
	if (argc < 5)
		exit_handle(px, "Usage: ./pipex file1 cmd1 cmd2 ... cmdN file2", 1);
	px->infile = argv[1];
	px->outfile = argv[argc - 1];
	px->envp = envp;
	px->fd_in = -1;
	px->fd_out = -1;
	px->pipe_fd[0] = -1;
	px->pipe_fd[1] = -1;
	init_cmds(px, argc, argv);
	init_paths(px);
}

int	main(int ac, char *av[], char **envp)
{
	t_pipex	px;

	init_pipex(&px, ac, av, envp);
	open_infile(&px);
	open_outfile(&px);
	pipex_run(&px);
	exit_handle(&px, NULL, 0);
}
