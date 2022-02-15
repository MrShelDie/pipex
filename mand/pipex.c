/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:04:34 by nick              #+#    #+#             */
/*   Updated: 2022/02/15 19:56:53 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft_tools.h"

static char	**get_paths(char *const *envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_split(envp[i] + 5, ':'));
	}
	return (NULL);
}

static void	init_prime(char *const *argv, char *const *envp, t_prime *prime)
{
	prime->argv = argv;
	prime->envp = envp;
	prime->paths = get_paths(envp);
}

static void	fill_prime(int argc, char *const *argv, t_prime *prime)
{
	int		first_cmd_idx;
	int		i;

	first_cmd_idx = 2;
	i = -1;
	while (++i + first_cmd_idx < argc - 1)
	{
		prime->cmds[i] = ft_split(argv[i + first_cmd_idx], ' ');
		if (!prime->cmds[i])
			pipex_exit(prime, prime->argv[0], NULL, strerror(ENOMEM));
	}
}

static int	pipex(t_prime *prime)
{
	pid_t	pid;
	int		status;
	int		pipefd[2];

	first_child(pipefd, prime);
	pid = last_child(pipefd[READ_END], prime);
	waitpid(pid, &status, 0);
	wait(NULL);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_prime	prime;
	int		status;

	if (argc != 5)
		pipex_exit(NULL, argv[0], NULL,
			"The number of arguments is not equal to 4");
	init_prime(argv, envp, &prime);
	fill_prime(argc, argv, &prime);
	status = pipex(&prime);
	status >>= 8;
	free_prime(&prime);
	exit(status);
}
