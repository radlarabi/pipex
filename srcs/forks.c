/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:26:59 by rlarabi           #+#    #+#             */
/*   Updated: 2023/02/04 19:41:38 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fork_1(t_cmd_line *cmd, char **path, int in, int *fd)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		if (in == -1)
			print_error(cmd->infile);
		if (cmd->c1 == 1 || !check_command(path, cmd->cmd1[0]))
			cmd_not_found(cmd->av, 2);
		dup2(fd[1], 1);
		dup2(in, 0);
		close(fd[0]);
		close(fd[1]);
		close(in);
		if (execve(get_command(path, cmd->cmd1[0]), cmd->cmd1, NULL) == -1)
			exit(1);
	}
	else if (id == -1)
	{
		perror("fork");
		exit(1);
	}
	return (id);
}

int	fork_2(t_cmd_line *cmd, char **path, int out, int *fd)
{
	int	id2;

	id2 = fork();
	if (id2 == 0)
	{
		out = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (out == -1)
			print_error(cmd->outfile);
		if (cmd->c2 == 1 || !check_command(path, cmd->cmd2[0]))
			cmd_not_found(cmd->av, 3);
		dup2(fd[0], 0);
		dup2(out, 1);
		close(fd[0]);
		close(fd[1]);
		close(out);
		if (execve(get_command(path, cmd->cmd2[0]), cmd->cmd2, NULL) == -1)
			exit(1);
	}
	else if (id2 == -1)
	{
		perror("fork");
		exit(1);
	}
	return (id2);
}
