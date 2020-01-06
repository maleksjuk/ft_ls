/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:58:34 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/06 16:56:48 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	usage(t_options *options)
{
	ft_printf("ft_ls: illegal option -- %c\n", options->illegal);
	ft_printf("usage: ./ft_ls [-Ralrt] [file ...]\n");
	return (1);
}

int	error_message(char *str)
{
	perror(str);
	exit(1);
}

int	check_file(char *name)
{
	struct stat	about;
	struct stat	about_link;

	if (stat(name, &about))
	{
		perror("stat");
		exit(1);
	}
	lstat(name, &about_link);
	if (S_ISDIR(about.st_mode))
	{
		if (S_ISLNK(about_link.st_mode))
			return (1);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_options	*options;
	int			i;

	i = 1;
	options = (t_options *)malloc(sizeof(t_options) * 1);
	init_options(options, ac);
	if (ac > 1)
	{
		while (av[i] && av[i][0] == '-')
		{
			if (input_options(options, av[i]) == 0)
				return (usage(options));
			i++;
		}
		while (i < ac)
		{
			if (check_file(av[i]))
			{
				if (!(options->files_array[options->len_for_array[0]++] = ft_strdup(av[i])))
					error_message("error malloc files_array[]");
			}
			else
			{
				if (!(options->dir_array[options->len_for_array[1]++] = ft_strdup(av[i])))
					error_message("error malloc dir_array[]");
			}
			i++;
		}
	}
	sort_ascii(options->files_array, options->len_for_array[0]);
	sort_ascii(options->dir_array, options->len_for_array[1]);
	ft_ls(options);
	return (0);
}
