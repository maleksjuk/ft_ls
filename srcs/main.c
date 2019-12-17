/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:58:34 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/17 17:17:15 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		usage(t_options *options)
{
	ft_printf("ft_ls: illegal option -- %c\n", options->illegal);
	ft_printf("usage: ./ft_ls [-Ralrt] [file ...]\n");
	return (1);
}

int		main(int ac, char **av)
{
	t_options	*options;
	int			curr_arg;
	int			i;

	curr_arg = 1;
	i = 1;
	options = (t_options *)malloc(sizeof(t_options) * 1);
	init_options(options, ac);
	if (ac > 1)
	{
		if (av[1][0] == '-')
		{
			curr_arg = input_options(options, av[1]);
			if (curr_arg == 0)
				return (usage(options));
		}
		i = curr_arg;
		while (curr_arg < ac)
		{
			if ((options->dir_array[curr_arg - i] = (char *)malloc(sizeof(char) *
				(ft_strlen(av[curr_arg]) + 1))) == NULL)
			{
				perror("malloc error\n");
				exit(1);
			}
			ft_strcpy(options->dir_array[curr_arg - i], av[curr_arg]);
			curr_arg++;
		}
	}
	ft_ls(options, curr_arg - i);
	return (0);
}
