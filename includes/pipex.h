/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi <malhendi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 23:13:25 by malhendi          #+#    #+#             */
/*   Updated: 2025/11/16 03:47:01 by malhendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	**cmd1;
	char	**cmd2;
	char	**paths;
	char	**envp;

	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
}	t_pipex;

/* function prototypes */
void	free_2d(char **strings);
void	exit_handle(t_pipex *px, char *msg, int flag);
void	init_paths(t_pipex *px);
char	*get_cmd_path(t_pipex *px, char **cmd);
void	first_child(t_pipex *px);
void	second_child(t_pipex *px);
void	pipex_run(t_pipex *px);

#endif
