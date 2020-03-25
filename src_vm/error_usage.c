/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:25:50 by student           #+#    #+#             */
/*   Updated: 2020/03/25 12:27:17 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_usage(void)
{
	ft_printf("Usage: ./corewar [(-dump|-d) <num> -vis] [-n <num>] ");
	ft_printf("<champion.cor> <...>\n");
	ft_printf("-dump <num> : Dump memory ");
	ft_printf("(32 octets per line) after <num> cycles and exit\n");
	ft_printf("-d    <num> : Dump memory ");
	ft_printf("(64 octets per line) after <num> cycles and exit\n");
	ft_printf("-vis        : Run visualizer\n");
	ft_printf("-n    <num> : Set <num> of the next player\n");
	exit(0);
}

void	check_error(char *name, char *text)
{
	if (errno)
	{
		ft_printf("%s: %s\n", name, strerror(errno));
		exit(1);
	}
	else if (name && text)
	{
		ft_printf("%s: %s\n", name, text);
		exit(1);
	}
}

void	free_and_usage(char *tmp)
{
	free(tmp);
	print_usage();
}
