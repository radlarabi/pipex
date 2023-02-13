/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:58:02 by rlarabi           #+#    #+#             */
/*   Updated: 2023/02/12 21:28:18 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_command(char **path, char *cmd)
{
	int		i;
	char	*a;

	if (access(cmd, F_OK) != -1)
		return (cmd);
	i = 0;
	while (path[i])
	{
		a = ft_strjoin(path[i], cmd);
		if (access(a, F_OK) != -1)
		{
			free(a);
			return (ft_strjoin(path[i], cmd));
		}
		free(a);
		i++;
	}
	return (NULL);
}

char	**get_path(char **ev)
{
	int		i;
	char	**path;
	char	*a;

	if (!ev)
	{
		write(2, "Envirement do not exist\n", 24);
		exit(1);
	}
	i = 0;
	while (ev[i] && ft_strncmp(ev[i], "PATH", 4) != 0)
	{
		fprintf(stderr, "%s\n", ev[i]);
		i++;
	}
	i++;
	// exit(0);
	path = ft_split(ev[i + 5], ':');
	i = 0;
	while (path[i])
	{
		a = path[i];
		path[i] = ft_strjoin(a, "/");
		free(a);
		i++;
	}
	return (path);
}

void	print_error(char *a)
{
	perror(a);
	exit(1);
}
