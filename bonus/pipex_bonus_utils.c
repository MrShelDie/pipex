/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:08:44 by nick              #+#    #+#             */
/*   Updated: 2022/02/09 01:38:37 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft_tools.h"
#include "get_next_line.h"

static void	write_var(const char *line, char **envp, int writefd, size_t *i)
{
	size_t	var_start;
	size_t	var_len;

	(*i)++;
	var_start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n'
		&& line[*i] != '\v' && line[*i] != '\f' && line[*i] != '\r'
	)
		(*i)++;
	var_len = *i - var_start;
	while (*envp)
	{
		if (!ft_strncmp(*envp, line, var_len))
			break ;
		envp++;
	}
	if (*envp)
		write(writefd, line + var_start, var_len);
}

void	write_here_doc_line(const char *line, char **envp, int writefd)
{
	size_t	i;

	if (!line[0])
		return ;
	i = 1;
	while (line[i])
	{
		while (line[i] != '$' || line[i - 1] == '\\')
			i++;
		write(writefd, line, i);
		write_var(line, envp, writefd, &i);
	}
}

static void	pipex_perror(t_error error, char *program, char *file)
{
	ft_putstr_fd(program, 2);
	ft_putstr_fd(": ", 2);
	if (file != NULL)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error == FEW_ARGS)
		ft_putstr_fd("too few argumets\n", 2);
}

void	pipex_exit(t_prime *prime, t_error error, char *program, char *file)
{
	if (error != NONE)
		pipex_perror(error, program, file);
	if (prime)
	{
		if (prime->envp_paths)
			ft_free_split(prime->envp_paths);
		if (prime->cmds)
		{
			while (--prime->cmds_size >= 0)
				ft_free_split(prime->cmds[prime->cmds_size]);
		}
	}
	exit(EXIT_SUCCESS);
}
