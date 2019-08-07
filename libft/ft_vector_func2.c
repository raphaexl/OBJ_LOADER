/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_func2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 11:46:43 by ebatchas          #+#    #+#             */
/*   Updated: 2019/08/07 14:36:55 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_vector_resize(t_vector *v, int capacity)
{
	void	**items;

	items = ft_realloc(v->items, sizeof(void *) * v->capacity,
			sizeof(void *) * capacity);
	if (items)
	{
		v->items = items;
		v->capacity = capacity;
	}
}

void			ft_vector_push_back(t_vector *v, void *value)
{
	void	*new;

	if (!v)
		return ;
	if (v->capacity == v->length)
		ft_vector_resize(v, v->capacity * 2);
	new = malloc(v->type_size);
	v->items[v->length++] = ft_memcpy(new, value, v->type_size);
}

void			ft_vector_remove(t_vector *v, int index)
{
	size_t		i;
	size_t		size;

	if (!v)
		return ;
	if (index < 0 || index >= v->length)
		return ;
	i = index;
	free(v->items[i]);
	size = v->length;
	while (i < size - 1)
	{
		v->items[i] = v->items[i + 1];
		free(v->items[i + 1]);
		i++;
	}
	v->length--;
	if (v->size > 0 && v->length == size / 4)
		ft_vector_resize(v, size / 2);
}

void			ft_vector_delete(t_vector *v, void *value)
{
	size_t		i;
	size_t		size;

	if (!v || !value)
		return ;
	i = 0;
	size = v->length;
	while (i < size)
	{
		if (v->items[i] == value)
		{
			free(v->items[i]);
			break ;
		}
		i++;
	}
	while (i < size - 1)
	{
		v->items[i] = v->items[i + 1];
		free(v->items[i + 1]);
		i++;
	}
	v->length--;
	if (v->size > 0 && v->length == size / 4)
		ft_vector_resize(v, size / 2);
}
