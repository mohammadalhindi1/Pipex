/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi <malhendi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 03:29:19 by malhendi          #+#    #+#             */
/*   Updated: 2025/11/16 04:30:02 by malhendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_2d(char **strings)
{
	char	**temp;

	temp = strings;
	while (*strings)
		free(*strings++);
	free(temp);
}

void	exit_handle(t_pipex *px, char *msg, int flag)
{
	if (px->cmd1)
		free_2d(px->cmd1);
	if (px->cmd2)
		free_2d(px->cmd2);
	ft_printf(msg);
	exit(flag);
}

static void	init_pipex(t_pipex *px, int argc, char **argv, char **envp)
{
	ft_bzero(px, sizeof(t_pipex));
	if (argc != 5)
		exit_handle(px, "Error: ./pipex file1 cmd1 cmd2 file2\n", 1);
	px->infile = argv[1];
	px->outfile = argv[4];
	px->envp = envp;
	px->paths = NULL;
	px->cmd1 = ft_split(argv[2], ' ');
	px->cmd2 = ft_split(argv[3], ' ');
	if (!px->cmd1 || !px->cmd2)
		exit_handle(px, "Error: malloc/ft_split failed\n", 1);
}

int	main(int ac, char *av[], char **envp)
{
	t_pipex	px;

	init_pipex(&px, ac, av, envp);
	exit_handle(&px, "", 0);
}
