/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:58:34 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/17 13:19:23 by obanshee         ###   ########.fr       */
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
	char	*path;

	ft_printf("ft_ls: ");
	path = ft_strrchr(str, '/') ? ft_strrchr(str, '/') + 1 : str;
	perror(path);
	if (errno == EACCES)
		return (2);
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
	if (S_ISLNK(about_link.st_mode))
		return (1);
	if (S_ISDIR(about.st_mode))
		return (0);
	return (1);
}

int	sort_args(int ac, char **av, t_options *options, int i)
{
	int	ret;

	while (i < ac)
	{
		ret = check_file(av[i]);
		if (ret == 1 || ret == 3)
		{
			if (!(options->files_array[options->len_for_array[0]++] =
				ft_strdup(av[i])))
				error_message("error malloc()", FULL_EXIT);
		}
		if (ret == 0 || ret == 3)
		{
			if (!(options->dir_array[options->len_for_array[1]++] =
				ft_strdup(av[i])))
				error_message("error malloc()", FULL_EXIT);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_options	*options;
	int			i;

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
		sort_args(ac, av, options, i);
	}
	options->files_array[options->len_for_array[0]] = NULL;
	options->dir_array[options->len_for_array[1]] = NULL;
	sort_ascii(options->files_array, options->len_for_array[0]);
	sort_ascii(options->dir_array, options->len_for_array[1]);
	ft_ls(options);
	return (0);
}
