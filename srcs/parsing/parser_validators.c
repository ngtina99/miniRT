/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:25:33 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/20 10:41:53 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	is_valid_end(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ' || c == '\0');
}

bool	is_valid_separator(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

bool	validator_rgb_end(char *line)
{
	int		value;
	int		count;

	count = 0;
	while (*line)
	{
		while (is_valid_separator(*line))
			line++;
		if (*line == '\0')
			break;
		if (!ft_isdigit(*line))
			return (false);
		value = ft_atoi(line);
		if (value < 0 || value > 255)
			return (false);
		count++;
		while (ft_isdigit(*line))
			line++;
		if (*line == ',')
		{
			line++;
			if (count == 3)
				return (false);
		}
		else if (!is_valid_end(*line))
			return (false);
	}
	return (count == 3);
}

bool	validator_ratio_inline(char **line)
{
	float	ratio;
	int		point_count;
	char	*start;

	while (is_valid_separator(**line))
		(*line)++;
	start = *line;
	if (!ft_isdigit(**line))
		return (false);
	point_count = 0;
	while (ft_isdigit(**line) || **line == '.')
	{
		if (**line == '.')
		{
			point_count++;
			if (point_count > 1)
				return (false);
		}
		(*line)++;
	}
	if (*line == start)
		return (false);
	ratio = parse_float(&start);
	if (ratio < 0.0 || ratio > 1.0)
		return (false);
	return (true);
}

bool	validator_ambient(char *line)
{
	while (is_valid_separator(*line))
		line++;
	if (*line != 'A')
		return (false);
	line++;
	while (is_valid_separator(*line))
	{
		line++;
	}
	if (!validator_ratio_inline(&line))
		return (false);
	while (is_valid_separator(*line))
		line++;
	return (validator_rgb_end(line));
}



