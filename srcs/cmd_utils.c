/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi <malhendi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:40:31 by malhendi          #+#    #+#             */
/*   Updated: 2025/11/18 21:40:32 by malhendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*join_path_cmd(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

char	*get_cmd_path(t_pipex *px, char **cmd)
{
	int		i;
	char	*full;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], X_OK) == 0)
			return (ft_strdup(cmd[0]));
		return (NULL);
	}
	i = 0;
	while (px->paths && px->paths[i])
	{
		full = join_path_cmd(px->paths[i], cmd[0]);
		if (!full)
			exit_handle(px, "Error: malloc failed\n", 1);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}
