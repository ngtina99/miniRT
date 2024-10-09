/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:26:59 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/26 12:17:13 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*new_start;
	t_list	*curr_new;
	void	*c;

	if (!lst || !f || !del)
		return (NULL);
	current = lst;
	new_start = NULL;
	while (current)
	{
		c = f(current -> content);
		curr_new = ft_lstnew(c);
		if (!curr_new)
		{
			ft_lstclear(&new_start, del);
			del(c);
			return (NULL);
		}
		ft_lstadd_back(&new_start, curr_new);
		current = current -> next;
	}
	return (new_start);
}
