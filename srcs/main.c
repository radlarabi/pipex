/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:35:27 by rlarabi           #+#    #+#             */
/*   Updated: 2023/02/04 19:42:07 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_not_found(char **av, int i)
{
	ft_putstr("command not found: ");
	ft_putstr(av[i]);
	ft_putstr("\n");
	exit(1);
}

t_cmd_line	*init_args(char **av)
{
	t_cmd_line	*cmd;

	cmd = malloc(sizeof(t_cmd_line));
	if (!cmd)
		return (NULL);
	cmd->infile = ft_strdup(av[1]);
	cmd->outfile = ft_strdup(av[4]);
	if (av[2][0] == ' ')
		cmd->c1 = 1;
	else
		cmd->c1 = 0;
	if (av[3][0] == ' ')
		cmd->c2 = 1;
	else
		cmd->c2 = 0;
	cmd->av = av;
	cmd->cmd1 = ft_split(av[2], ' ');
	cmd->cmd2 = ft_split(av[3], ' ');
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

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	id = fork_1(cmd, path, in, fd);
	id2 = fork_2(cmd, path, out, fd);
	close(fd[1]);
	close(fd[0]);
	waitpid(id, 0, 0);
	waitpid(id2, 0, 0);
}

int	main(int ac, char **av, char **ev)
{
	t_cmd_line	*cmd;
	int			in;
	int			out = 0;
	char		**path;

	if (ac != 5)
	{
		ft_putstr("Error Args\nhow it works : \
			./pipex infile cmd1 cmd2 outfile\n");
		exit(1);
	}
	cmd = init_args(av);
	in = open(cmd->infile, O_RDONLY);
	// out = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	path = get_path(ev);
	pipex(cmd, path, in, out);
	main_free(path, cmd);
	return (0);
}
