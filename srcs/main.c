/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:35:27 by rlarabi           #+#    #+#             */
/*   Updated: 2023/01/28 18:14:51 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd_line	*init_args(char **av)
{
	int			i;
	t_cmd_line	*cmd;

	cmd = malloc(sizeof(t_cmd_line));
	if (!cmd)
		return (NULL);
	cmd->infile = ft_strdup(av[1]);
	cmd->outfile = ft_strdup(av[4]);
	i = 2;
	while (i <= 3)
	{
		if (i == 2)
			cmd->cmd1 = ft_split(av[i], ' ');
		if (i == 3)
			cmd->cmd2 = ft_split(av[i], ' ');
		i++;
	}
	return (cmd);
}

void	main_free(char **path, t_cmd_line *cmd)
{
	free_2d_table(path);
	free_2d_table(cmd->cmd1);
	free_2d_table(cmd->cmd2);
	free(cmd->infile);
	free(cmd->outfile);
	free(cmd);
}

void	pipex(t_cmd_line *cmd, char **path, int in, int out)
{
	int	fd[2];
	int	id;
	int	id2;

	pipe(fd);
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		dup2(in, 0);
		if (execve(get_command(path, cmd->cmd1[0]), cmd->cmd1, NULL) == -1)
			exit(1);
	}
	id2 = fork();
	if (id2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		dup2(out, 1);
		if (execve(get_command(path, cmd->cmd2[0]), cmd->cmd2, NULL) == -1)
			exit(1);
	}
}

int	main(int ac, char **av, char **ev)
{
	t_cmd_line	*cmd;
	int			in;
	int			out;
	char		**path;

	if (ac != 5)
		return (0);
	cmd = init_args(av);
	in = open(cmd->infile, O_RDWR);
	out = open(cmd->outfile, O_RDWR | O_CREAT);
	check_files(av, in, out);
	path = get_path(ev);
	check_path(path, cmd);
	pipex(cmd, path, in, out);
	main_free(path, cmd);
	return (0);
}
