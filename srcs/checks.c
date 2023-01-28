/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:56:22 by rlarabi           #+#    #+#             */
/*   Updated: 2023/01/28 18:15:01 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_path(char **path, t_cmd_line *cmd)
{
	if (!check_command(path, cmd->cmd1[0]))
	{
		perror(cmd->cmd1[0]);
		exit(1);
	}
	if (!check_command(path, cmd->cmd2[0]))
	{
		perror(cmd->cmd2[0]);
		exit(1);
	}
}

int	check_command(char **path, char *cmd)
{
	int	i;

	if (access(cmd, F_OK) != -1)
		return (1);
	i = 0;
	while (path[i])
	{
		if (access(ft_strjoin(path[i], cmd), F_OK) != -1)
			return (1);
		i++;
	}
	return (0);
}

void	check_files(char **av, int in, int out)
{
	if (in == -1)
	{
		perror(av[1]);
		exit(1);
	}
	if (out == -1)
	{
		perror(av[4]);
		exit(1);
	}
}

int	strlen_2d(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

void	free_2d_table(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		free(t[i]);
		i++;
	}
	free(t);
}
