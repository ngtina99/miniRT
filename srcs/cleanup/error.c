/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:30:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/19 16:30:04 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	error_message(int fd, int err_sign)
{
	if (err_sign == ARG_ERR)
	{
		printf(RED "Error: Please put a valid .rt file path as an argument\n" \
			RESET);
		exit (1);
	}
	if (err_sign == MALLOC_ERR)
	{
		printf(RED"Error: Memory allocation failed for scene\n"RESET);
		close(fd);
		exit (1);
	}
	if (err_sign == PARSE_ERR)
	{
		close(fd);
		exit (1);
	}
}
