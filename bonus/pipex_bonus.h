/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:59:07 by rlarabi           #+#    #+#             */
/*   Updated: 2023/02/08 00:14:19 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_cmd_line
{
	char	*infile;
	char	*outfile;
	int		num_cmds;
	int		num_pipes;
	int		here_doc;
	char	**cmds;
}			t_cmd_line;

char		*get_command(char **path, char *cmd);
char		**get_path(char **ev);
void		check_path(char **path, t_cmd_line *cmd);
int			check_command(char **path, char *cmd);
void		check_files(char **av, int in, int out);
int			strlen_2d(char **a);
void		free_2d_table(char **t);
void		print_error(char *a);
void	cmd_not_found(char *cmd);
#endif
