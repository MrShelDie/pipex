/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:08:44 by nick              #+#    #+#             */
/*   Updated: 2022/02/15 02:55:06 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft_tools.h"

static void	pipex_perror(const char *program, const char *file, char *err_str)
{
	ft_putstr_fd(program, 2);
	ft_putstr_fd(": ", 2);
	if (file != NULL)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(err_str, 2);
	ft_putchar_fd('\n', 2);
}

void	free_prime(t_prime *prime)
{
	if (prime)
	{
		if (prime->paths)
			ft_free_split((char **)prime->paths);
		if (prime->cmds)
		{
			while (--prime->cmds_size >= 0)
				ft_free_split((char **)prime->cmds[prime->cmds_size]);
			free(prime->cmds);
		}
	}
}

void	pipex_exit(
	t_prime *prime, const char *program, const char *file, char *err_str)
{
	if (err_str)
		pipex_perror(program, file, err_str);
	free_prime(prime);
	exit(EXIT_SUCCESS);
}
