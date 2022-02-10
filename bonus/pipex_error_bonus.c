/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:08:44 by nick              #+#    #+#             */
/*   Updated: 2022/02/10 09:45:32 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft_tools.h"

static void	pipex_perror(t_error error, char *program, char *file)
{
	ft_putstr_fd(program, 2);
	ft_putstr_fd(": ", 2);
	if (file != NULL)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error == ARGS)
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
