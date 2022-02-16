/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:08:44 by nick              #+#    #+#             */
/*   Updated: 2022/02/15 17:13:00 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
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
		ft_free_split((char **)prime->cmds[0]);
		ft_free_split((char **)prime->cmds[1]);
	}
}

void	pipex_exit(
	t_prime *prime, const char *program, const char *file, char *err_str)
{
	if (err_str)
		pipex_perror(program, file, err_str);
	free_prime(prime);
	if (err_str)
	{
		if (!ft_strncmp(err_str, strerror(EACCES), ft_strlen(err_str)))
			exit(126);
		if (!ft_strncmp(err_str, "command not found", ft_strlen(err_str)))
			exit(127);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
