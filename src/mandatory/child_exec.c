/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 09:44:52 by nick              #+#    #+#             */
/*   Updated: 2022/02/16 15:50:03 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft_tools.h"

void	check_cmd(char *cmd_full_path, const char *cmd, t_prime *prime)
{
	if (!cmd_full_path)
		pipex_exit(prime, prime->argv[0], cmd, "command not found");
	if (access(cmd_full_path, X_OK) == -1)
	{
		free(cmd_full_path);
		pipex_exit(prime, prime->argv[0], cmd, strerror(EACCES));
	}
}

void	replace_stdio(t_prime *prime, int readfd, int writefd)
{
	if (dup2(readfd, STDIN_FILENO) == -1 || dup2(writefd, STDOUT_FILENO) == -1)
	{
		prime->err_str = strerror(errno);
		close(readfd);
		close(writefd);
		pipex_exit(prime, prime->argv[0], NULL, prime->err_str);
	}
}

static char	*get_correct_path(const char *slash_cmd, char *const *paths)
{
	char	*last_correct_path;
	char	*new_path;

	last_correct_path = NULL;
	while (*paths)
	{
		new_path = ft_strjoin(*paths, slash_cmd);
		if (new_path && access(new_path, F_OK) == 0)
		{
			if (last_correct_path)
				free(last_correct_path);
			last_correct_path = new_path;
			if (access(new_path, X_OK) == 0)
				return (new_path);
		}
		else if (new_path)
			free(new_path);
		paths++;
	}
	return (last_correct_path);
}

char	*find_cmd_path(const char *cmd, char *const *paths)
{
	char	*cmd_full_path;
	char	*slash_cmd;

	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	slash_cmd = ft_strjoin("/", cmd);
	if (!slash_cmd)
		return (NULL);
	cmd_full_path = get_correct_path(slash_cmd, paths);
	free(slash_cmd);
	return (cmd_full_path);
}
