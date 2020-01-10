/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:58:34 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/10 18:53:14 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	usage(t_options *options)
{
	ft_printf("ft_ls: illegal option -- %c\n", options->illegal);
	ft_printf("usage: ./ft_ls [-Ralrt] [file ...]\n");
	return (1);
}

int	error_message(char *str, int exit_flag)
{
	ft_printf("./ft_ls: ");
	perror(str);
	if (exit_flag)
		exit(1);
	else
		return (1);
}

int	check_file(char *name)
{
	struct stat	about;
	struct stat	about_link;

	if (stat(name, &about))
	{
		error_message(name, 0);
		return (2);
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
	int			ret;

	i = 1;
	options = (t_options *)malloc(sizeof(t_options));
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
			ret = check_file(av[i]);
			if (ret == 1)
			{
				if (!(options->files_array[options->len_for_array[0]++] = ft_strdup(av[i])))
					error_message("error malloc()", 1);
			}
			else if (ret == 0)
			{
				if (!(options->dir_array[options->len_for_array[1]++] = ft_strdup(av[i])))
					error_message("error malloc()", 1);
			}
			i++;
		}
	}
	sort_ascii(options->files_array, options->len_for_array[0]);
	sort_ascii(options->dir_array, options->len_for_array[1]);
	ft_ls(options);
	return (0);
}
