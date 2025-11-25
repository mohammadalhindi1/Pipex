/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhendi <malhendi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:57:38 by malhendi@st       #+#    #+#             */
/*   Updated: 2025/11/25 00:29:15 by malhendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_limiter(char *line, char *limiter)
{
	size_t	len;

	if (!line || !limiter)
		return (0);
	len = ft_strlen(limiter);
	if (ft_strncmp(line, limiter, len) != 0)
		return (0);
	if (line[len] == '\n' && line[len + 1] == '\0')
		return (1);
	return (0);
}

static int	read_line(char *buf, int size)
{
	int		i;
	char	c;
	ssize_t	r;

	i = 0;
	while (i + 1 < size)
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r <= 0)
			break ;
		buf[i++] = c;
		if (c == '\n')
			break ;
	}
	buf[i] = '\0';
	if (i == 0 && r <= 0)
		return (0);
	return (1);
}

void	handle_heredoc(t_pipex *px)
{
	int		hd[2];
	char	buf[1024];

	if (pipe(hd) == -1)
		exit_handle(px, "pipe error", 1);
	while (read_line(buf, sizeof(buf)))
	{
		if (is_limiter(buf, px->limiter))
			break ;
		write(hd[1], buf, ft_strlen(buf));
	}
	close(hd[1]);
	px->fd_in = hd[0];
}
