/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:23:51 by nick              #+#    #+#             */
/*   Updated: 2022/02/06 23:04:55 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TOOLS_H
# define LIBFT_TOOLS_H

# include <unistd.h>
# include <stdlib.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(const char *s, int fd);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

#endif
