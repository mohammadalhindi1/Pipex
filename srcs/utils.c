/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi <malhendi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 03:30:00 by malhendi          #+#    #+#             */
/*   Updated: 2025/11/19 03:30:00 by malhendi         ###   ########.fr       */
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