/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi@student.42amman.com <malhendi>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 23:13:25 by malhendi          #+#    #+#             */
/*   Updated: 2025/11/23 02:56:28 by malhendi@st      ###   ########.fr       */
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

	int		is_heredoc;
	char	*limiter;

	char	***cmds;
	int		cmd_count;

	char	**paths;
	char	**envp;

	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
}	t_pipex;

void	free_2d(char **strings);
void	free_cmds(char ***cmds, int count);
void	cleanup_pipex(t_pipex *px);
void	exit_handle(t_pipex *px, char *msg, int flag);

void	init_paths(t_pipex *px);
char	*get_cmd_path(t_pipex *px, char **cmd);

void	exec_child(t_pipex *px, int idx, int prev_fd);
void	pipex_run(t_pipex *px);

void	handle_heredoc(t_pipex *px);

#endif
