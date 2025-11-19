/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi <malhendi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:39:57 by malhendi          #+#    #+#             */
/*   Updated: 2025/11/18 21:39:58 by malhendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path_line(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	init_paths(t_pipex *px)
{
	char	*path_line;

	path_line = get_path_line(px->envp);
	if (!path_line)
		exit_handle(px, "Error: PATH not found in env\n", 1);
	px->paths = ft_split(path_line, ':');
	if (!px->paths)
		exit_handle(px, "Error: malloc/ft_split failed\n", 1);
}
