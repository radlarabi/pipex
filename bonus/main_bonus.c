/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:35:27 by rlarabi           #+#    #+#             */
/*   Updated: 2023/02/08 00:19:12 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	cmd_not_found(char *cmd)
{
	ft_putstr("command not found: ");
	ft_putstr(cmd);
	ft_putstr("\n");
	exit(1);
}

t_cmd_line	*init_args(int ac, char **av)
{
	t_cmd_line	*cmd;
	int			i;

	i = 0;
	cmd = malloc(sizeof(t_cmd_line));
	if (!cmd)
		return (NULL);
	cmd->num_cmds = ac - 3;
	cmd->num_pipes = ac - 4;
	cmd->cmds = malloc(sizeof(char *) * (cmd->num_cmds + 1));
	while (i < cmd->num_cmds)
	{
		cmd->cmds[i] = ft_strdup(av[2 + i]);
		i++;
	}
	cmd->cmds[i] = NULL;
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
	{
		
	}
	cmd->infile = ft_strdup(av[1]);
	cmd->outfile = ft_strdup(av[ac - 1]);
	return (cmd);
}

void close_pipes(int a, int b, int pipefd[a][b])
{
	int j;

	j = 0;
	while (j < a)
	{
		close(pipefd[j][0]);
		close(pipefd[j][1]);
		j++;
	}
}

void	pipex(t_cmd_line *cmd, char **path)
{
	int pipefd[cmd->num_pipes][2];
	int pids[cmd->num_cmds];
	int i;
	int in;
	int out;
	char **command;

	i = 0;
	while (i <= cmd->num_pipes)
	{
		pipe(pipefd[i]);
		i++;
	}
	i = 0;
	while (i < cmd->num_cmds)
	{
		pids[i] = fork();
		command = ft_split(cmd->cmds[i], ' ');
		if (pids[i] == 0)
		{
			if (!check_command(path, command[0]))
				cmd_not_found(command[0]);
			if (i == 0)
			{
				in = open(cmd->infile, O_RDONLY);
				if (in == -1)
					print_error(cmd->infile);
				dup2(in, 0);
				close(in);
			}
			else
				dup2(pipefd[i - 1][0], 0);
			if (i == cmd->num_pipes)
			{
				out = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
				if (out == -1)
					print_error(cmd->outfile);
				dup2(out, 1);
				close(out);
			}
			else
				dup2(pipefd[i][1], 1);
			close_pipes(cmd->num_pipes, 2, pipefd);
			execve(get_command(path, command[0]), command, NULL);
			perror("execve");
			exit(1);
		}
		free_2d_table(command);
		i++;
	}
	close_pipes(cmd->num_pipes, 2, pipefd);
	i = 0;
	while (i < cmd->num_pipes)
	{
		waitpid(pids[i], 0, 0);
		i++;
	}
}

void main_free(t_cmd_line *cmd, char **path)
{
	free_2d_table(path);
	free_2d_table(cmd->cmds);
	free(cmd->infile);
	free(cmd->outfile);
}
int	main(int ac, char **av, char **ev)
{
	t_cmd_line	*cmd;
	char		**path;

	if (ac < 5)
	{
		write(2, "Error Args\n", 11);
		write(2, "how it works : ", 15);
		write(2, "./pipex infile \"cmd1\" \"cmd2\" ... \"cmdn\" outfile\n", 48);
		exit(1);
	}
	cmd = init_args(ac, av);
	path = get_path(ev);
	pipex(cmd, path);
	main_free(cmd, path);
	return (0);
}
