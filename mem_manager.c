/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 19:17:08 by aben-ham          #+#    #+#             */
/*   Updated: 2022/01/24 19:17:08 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

static t_addresses	*ft_get_addresses(void)
{
	const int			initial_size = 100;
	static t_addresses	addresses;
	size_t				i;

	if (addresses.adds == NULL)
	{
		addresses.adds = malloc(8 * initial_size);
		if (!(addresses.adds))
			return (NULL);
		addresses.size = initial_size;
		i = -1;
		while (++i < addresses.size)
			addresses.adds[i] = NULL;
	}
	return (&addresses);
}

static void	**extend_adds(void)
{
	t_addresses	*addresses;
	void		**new_adds;
	size_t		i;

	addresses = ft_get_addresses();
	if (!addresses)
		return (NULL);
	new_adds = malloc(8 * addresses->size * 2);
	if (!new_adds)
		return (NULL);
	i = -1;
	while (++i < addresses->size)
		new_adds[i] = addresses->adds[i];
	i--;
	while (++i < addresses->size * 2)
		new_adds[i] = NULL;
	addresses->adds = new_adds;
	addresses->size = addresses->size * 2;
	return (new_adds);
}

void	mem_clean(void)
{
	t_addresses	*addresses;
	size_t		i;

	addresses = ft_get_addresses();
	if (!addresses)
		return ;
	i = -1;
	while (++i < addresses->size)
	{
		if (addresses->adds[i] != NULL)
		{
			free(addresses->adds[i]);
			addresses->adds[i] = NULL;
		}	
	}
	free(addresses->adds);
	addresses->adds = NULL;
}

void	ft_free(void *ptr)
{
	t_addresses	*addresses;
	size_t		i;

	addresses = ft_get_addresses();
	if (!ptr || !addresses)
		return ;
	i = -1;
	while (++i < addresses->size)
	{
		if (addresses->adds[i] == ptr)
		{
			free(ptr);
			addresses->adds[i] = NULL;
			return ;
		}
	}
	ft_mem_error();
}

void	*ft_malloc(size_t size)
{
	t_addresses	*addresses;
	size_t		i;

	if (!size)
		return (NULL);
	addresses = ft_get_addresses();
	i = -1;
	while (++i < addresses->size)
	{
		if (addresses->adds[i] == NULL)
		{
			addresses->adds[i] = malloc(size);
			if (!(addresses->adds[i]))
				return (ft_mem_error());
			return (addresses->adds[i]);
		}
	}
	if (!extend_adds())
		return (ft_mem_error());
	return (ft_malloc(size));
}
