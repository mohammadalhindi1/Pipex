/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi@student.42amman.com <malhendi>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 03:29:19 by malhendi          #+#    #+#             */
/*   Updated: 2025/11/23 04:32:02 by malhendi@st      ###   ########.fr       */
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
	if (px->is_heredoc)
		px->fd_out = open(px->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		px->fd_out = open(px->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->fd_out < 0)
	{
		perror(px->outfile);
		exit_handle(px, "Error: cannot open outfile", 1);
	}
}

static void	parse_normal(t_pipex *px, int argc, char **argv)
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

static void	parse_heredoc(t_pipex *px, int argc, char **argv)
{
	int	i;

	px->cmd_count = argc - 4;
	px->cmds = malloc(sizeof(char **) * px->cmd_count);
	if (!px->cmds)
		exit_handle(px, "malloc error", 1);
	i = 0;
	while (i < px->cmd_count)
	{
		px->cmds[i] = ft_split(argv[3 + i], ' ');
		if (!px->cmds[i])
			exit_handle(px, "Error: malloc/ft_split failed", 1);
		i++;
	}
}

static void	init_pipex(t_pipex *px, int argc, char **argv, char **envp)
{
	ft_bzero(px, sizeof(t_pipex));
	if (argc < 5)
		exit_handle(px,"Usage: ./pipex file1 cmd1 cmd2 ... cmdN file2", 1);
	px->envp = envp;
	px->is_heredoc = 0;
	px->limiter = NULL;
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		if (argc < 6)
			exit_handle(px,"Usage: ./pipex here_doc LIMITER cmd cmd1 file", 1);
		px->is_heredoc = 1;
		px->limiter = argv[2];
		px->outfile = argv[argc - 1];
		parse_heredoc(px, argc, argv);
	}
	else
	{
		px->infile = argv[1];
		px->outfile = argv[argc - 1];
		parse_normal(px, argc, argv);
	}
	init_paths(px);
}

int	main(int ac, char *av[], char **envp)
{
	t_pipex	px;

	init_pipex(&px, ac, av, envp);
	if (px.is_heredoc)
		handle_heredoc(&px);
	else
		open_infile(&px);
	open_outfile(&px);
	pipex_run(&px);
	exit_handle(&px, NULL, 0);
}
