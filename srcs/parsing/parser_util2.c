/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:25:14 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/16 23:32:44 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	parse_sign(char **line)
{
	int	sign;

	sign = 1;
	if (**line == '-')
	{
		sign = -1;
		(*line)++;
	}
	else if (**line == '+')
		(*line)++;
	return (sign);
}

void	parse_number(char **line, float *result, float *fraction,
		bool *is_fractional)
{
	while (ft_isdigit(**line) || **line == '.')
	{
		if (**line == '.')
		{
			*is_fractional = true;
			(*line)++;
			continue ;
		}
		if (!(*is_fractional))
			*result = *result * 10.0 + (**line - '0');
		else
		{
			*fraction *= 0.1;
			*result += (**line - '0') * (*fraction);
		}
		(*line)++;
	}
}

float	parse_float(char **line)
{
	float	result;
	float	fraction;
	int		sign;
	bool	is_fractional;

	result = 0.0;
	fraction = 1.0;
	is_fractional = false;
	skip_whitespace(line);
	sign = parse_sign(line);
	parse_number(line, &result, &fraction, &is_fractional);
	skip_invalid_chars(line);
	skip_whitespace(line);
	return (result * sign);
}

int	parse_vector(char **line, t_vec3d *vector)
{
	vector->x = parse_float(line);
	if (**line == ',')
		(*line)++;
	vector->y = parse_float(line);
	if (**line == ',')
		(*line)++;
	vector->z = parse_float(line);
	return (EXIT_SUCCESS);
}

int	parse_rgb(char **line, t__color_rgb *color)
{
	color->red = ft_atoi(*line);
	while (**line != ',' && **line != '\0')
		(*line)++;
	if (**line == ',')
		(*line)++;
	color->green = ft_atoi(*line);
	while (**line != ',' && **line != '\0')
		(*line)++;
	if (**line == ',')
		(*line)++;
	color->blue = ft_atoi(*line);
	while (**line != ' ' && **line != '\0')
		(*line)++;
	return (EXIT_SUCCESS);
}
