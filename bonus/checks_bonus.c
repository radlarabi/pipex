/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:56:22 by rlarabi           #+#    #+#             */
/*   Updated: 2023/02/06 20:24:32 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_command(char **path, char *cmd)
{
	int		i;
	char	*a;

	if (access(cmd, F_OK) != -1)
		return (1);
	i = 0;
	while (path[i])
	{
		a = ft_strjoin(path[i], cmd);
		if (access(a, F_OK) != -1)
		{
			free(a);
			return (1);
		}
		free(a);
		i++;
	}
	return (0);
}

void	check_files(char **av, int in, int out)
{
	if (in == -1)
		print_error(av[1]);
	if (out == -1)
		print_error(av[4]);
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
