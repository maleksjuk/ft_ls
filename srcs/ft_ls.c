/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:12:31 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/17 19:59:07 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		recursive(t_options *options, char *file)
{
	DIR				*dir;
	struct dirent	*dir_read;

	dir = NULL;
	dir_read = NULL;
	if ((dir = opendir(file)) == NULL)
	{
		perror("opendir\n");
		return (1);
	}
	dir_read = readdir(dir);
	while (dir_read != NULL)
	{
		if (dir_read->d_name[0] != '.' ||
			(dir_read->d_name[0] == '.' && options->all))
			if (dir_read->d_type == 4)
			{
				set_path(options, dir_read->d_name);
				ft_printf("\n%s:\n", options->cur_dir);
				processing(options, options->cur_dir);
				options->cur_dir[ft_strlen(options->cur_dir) -
					ft_strlen(dir_read->d_name) - 1] = '\0';
			}
		dir_read = readdir(dir);
	}
	if (closedir(dir) == -1)
		perror("closedir\n");
	return (0);
}

int		processing(t_options *options, char *file)
{
	DIR				*dir;
	struct dirent	*dir_read;

	dir = NULL;
	dir_read = NULL;
	if ((dir = opendir(file)) == NULL)
	{
		perror("opendir\n");
		exit(1);
	}
	dir_read = readdir(dir);
	while (dir_read != NULL)
	{
		if (dir_read->d_name[0] != '.' ||
			(dir_read->d_name[0] == '.' && options->all))
			ft_printf("%s%s", dir_read->d_name, options->list ? "\n" : "\t");
		dir_read = readdir(dir);
	}
	if (closedir(dir) == -1)
		perror("closedir\n");
	ft_printf(options->list ? "" : "\n");
	if (options->recursive)
		recursive(options, file);
	return (0);
}

int		ft_ls(t_options *options, int num)
{
	int	i;

	i = 0;
	if (num > 0)
	{
		sort_ascii(options->dir_array, num);
		while (i < num)
		{
			if (num > 1)
				ft_printf("%s%s:\n", i > 0 ? "\n" : "", options->dir_array[i]);
			processing(options, options->dir_array[i++]);
		}
	}
	else
		processing(options, "./");
	return (0);
}
