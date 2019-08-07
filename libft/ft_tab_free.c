/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 14:43:56 by ebatchas          #+#    #+#             */
/*   Updated: 2019/08/07 14:58:41 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tab_free(char **tab)
{
	int		i;
	int		size;

	size = 0;
	while (tab[size++])
		;
	i = -1;
	while (++i < size)
		free(tab[i]);
	free(tab);
	tab = NULL;
}
