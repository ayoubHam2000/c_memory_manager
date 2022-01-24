/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 19:17:14 by aben-ham          #+#    #+#             */
/*   Updated: 2022/01/24 19:17:14 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_addresses
{
	void	**adds;
	size_t	size;
}	t_addresses;

void	mem_clean(void);
void	ft_free(void *ptr);
void	*ft_malloc(size_t size);
void	*ft_mem_error(void);

#endif
