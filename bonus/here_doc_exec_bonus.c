/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_exec_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 09:49:35 by nick              #+#    #+#             */
/*   Updated: 2022/02/10 09:51:55 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft_tools.h"

static void	write_var(
	const char *line, const char *const *envp, int writefd, size_t *i)
{
	size_t	start;
	size_t	len;
	char	*envp_value;

	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n'
		&& line[*i] != '\v' && line[*i] != '\f' && line[*i] != '\r'
	)
		(*i)++;
	len = *i - start;
	while (*envp)
	{
		if (!ft_strncmp(*envp, line, len))
		{
			envp_value = *envp;
			while (*envp_value && *envp_value != '=')
				envp_value++;
			envp_value++;
			write(writefd, envp_value, ft_strlen(envp_value));
		}
		envp++;
	}
}

static void	write_here_doc_line(
	const char *line, const char *const *envp, int writefd)
{
	size_t	i;
	size_t	start;

	if (!line[0])
		return ;
	start = 0;
	i = 1;
	while (line[i])
	{
		while (line[i] && (line[i] != '$' || line[i - 1] == '\\'))
			i++;
		write(writefd, line + start, i);
		write_var(line, envp, writefd, &i);
		start = i;
	}
}

void	here_doc_exec(const t_prime *prime, int writefd)
{
	char	*line;

	line = get_next_line(0);
	while (line
		&& ft_strncmp(line, prime->argv[2], ft_strlen(prime->argv[2]) + 1))
	{
		write_here_doc_line(line, prime->envp, writefd);
		free(line);
		line = get_next_line(0);
	}
	if (line)
		free(line);
	close(writefd);
	pipex_exit(prime, NONE, prime->argv[0], NULL);
}
