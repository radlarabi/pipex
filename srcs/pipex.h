/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:59:07 by rlarabi           #+#    #+#             */
/*   Updated: 2023/02/13 18:45:20 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_cmd_line
{
	char	*infile;
	char	*outfile;
	char	**cmd1;
	char	**cmd2;
	char	**av;
	char	**ev;
	int		c1;
	int		c2;
}			t_cmd_line;

char		*get_command(char **path, char *cmd);
char		**get_path(char **ev);
int			check_command(char **path, char *cmd);
void		free_2d_table(char **t);
int			fork_1(t_cmd_line *cmd, char **path, int in, int *fd);
int			fork_2(t_cmd_line *cmd, char **path, int out, int *fd);
void		print_error(char *a);
void		cmd_not_found(char **av, int i);
#endif
