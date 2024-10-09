/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:20:15 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/01/27 17:00:09 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printcheck(char s, va_list args)
{
	int	count;
	int	decimal;
	int	hexadecimal;

	decimal = 10;
	hexadecimal = 16;
	count = 0;
	if (s == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (s == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (s == 'p')
		count += ft_putcharptr((unsigned long)va_arg(args, void *));
	else if (s == 'd' || s == 'i')
		count += ft_putnbr((long)va_arg(args, int), decimal, s);
	else if (s == 'u')
		count += ft_putnbr(va_arg(args, unsigned int), decimal, s);
	else if (s == 'x')
		count += ft_putnbr(va_arg(args, unsigned int), hexadecimal, s);
	else if (s == 'X')
		count += ft_putnbr(va_arg(args, unsigned int), hexadecimal, s);
	else
		count += ft_putchar(s);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format += 1;
			count += ft_printcheck(*(format), args);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (count);
}
// int	main()
// {
// // 	char	*pointer = "it is something";
// // 	int count = ft_printf("it is: %s\n %d\n %i\n %x\n %X\n %p\n %p\n
// // %u\n %%\n", "something", 42, 42, 42, 42, NULL, pointer, 123);
// // 	ft_printf("%d\n", count);
// // 	int countreal = printf("it is: %s\n %d\n %i\n %x\n %X\n %p\n %p\n 
// //%u\n %%\n", "something", 42, 42, 42, 42, NULL, pointer, 123);
// // 	printf("%d\n", countreal);

// // 	// int	count = ft_printf("it is s %s\n", "something");
// 	// ft_printf("value: %d\n", count);
// 	// int	countreal = printf("it is s %s\n", "something");
// 	// printf("value: %d\n", countreal);

// 	int	count2 = ft_printf("it is d %d\n", -42);
// 	ft_printf("value: %d\n", count2);
// 	int	count2real = printf("it is d %d\n", -42);
// 	printf("value: %d\n", count2real);

// 	// int	countb2 = ft_printf("it is i %i\n", 42);
// 	// ft_printf("value: %d\n", countb2);
// 	// int	countrealb2 = printf("it is i %i\n", 42);
// 	// printf("value: %d\n", countrealb2);

// 	// int	count3 = ft_printf("it is x %x\n", 42);
// 	// ft_printf("value: %d\n", count3);
// 	// int	count3real = printf("it is x %x\n", 42);
// 	// printf("value: %d\n", count3real);

// 	// int	count4 = ft_printf("it is X %X\n", 42);
// 	// ft_printf("value: %d\n", count4);
// 	// int	count4real = printf("it is X %X\n", 42);
// 	// printf("value: %d\n", count4real);

// 	// char *ptr = "something";

// 	// int 	count5 = ft_printf("it is p %p\n", NULL);
// 	// ft_printf("value: %d\n", count5);
// 	// int	count5real = printf("it is p %p\n", NULL);
// 	// printf("value: %d\n", count5real);

// 	// int	count6 = ft_printf("it is p %p\n", ptr);
// 	// ft_printf("value: %d\n", count6);
// 	// int	count6real = printf("it is p %p\n", ptr);
// 	// printf("value: %d\n", count6real);

// 	// int	count8 = ft_printf("it is percentage %u\n", 123);
// 	// ft_printf("value: %d\n", count8);
// 	// int	count8real = printf("it is percentage %u\n", 123);
// 	// printf("value: %d\n", count8real);

// 	// int	count7 = ft_printf("it is percentage %%\n");
// 	// ft_printf("value: %d\n", count7);
// 	// int	count7real = printf("it is percentage %%\n");
// 	// printf("value: %d\n", count7real);
// }
