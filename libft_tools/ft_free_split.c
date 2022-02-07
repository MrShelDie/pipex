/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:13:29 by nick              #+#    #+#             */
/*   Updated: 2022/02/07 02:29:36 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tools.h"

void	ft_free_split(char **str_tab)
{
	int	i;

	if (!str_tab)
		return ;
	i = -1;
	while (str_tab[++i])
		free(str_tab[i]);
	free(str_tab[i]);
	free(str_tab);
}
