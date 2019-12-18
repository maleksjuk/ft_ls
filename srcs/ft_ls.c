/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:12:31 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/18 16:43:08 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		final_ls(t_options *options)
{
	int	i;

	i = 0;
	while (options->dir_array[i])
	{
//		free(options->dir_array[i]);
		i++;
	}
//	free(options->dir_array);
	free(options->cur_dir);
	free(options);
	return (0);
}

int		reading(t_info *list, char *file)
{
	DIR				*dir;
	struct dirent	*dir_read;
	int				i;

	dir = NULL;
	dir_read = NULL;
	i = 0;
	if ((dir = opendir(file)) == NULL)	// begin read this folder
	{
		perror("opendir\n");
		exit(1);
	}
	dir_read = readdir(dir);
	i = 0;
	while (dir_read != NULL)
	{
		list[i].name = ft_strdup(dir_read->d_name);
		i++;
		dir_read = readdir(dir);
	}
	if (closedir(dir) == -1)
		perror("closedir\n");
	return (i);
}

int		printing(t_info *list, t_options *options, struct stat about)
{
	int	i;

	while (options->tab_len % 8 != 0)
		options->tab_len++;
	i = 0;
	while (i < (int)about.st_nlink)
	{
		if (list[i].name[0] != '.' || (list[i].name[0] == '.' && options->all))
		{
			if (options->list)
				ft_printf("%s\n", list[i].name);
			else
				ft_printf("%-*s", options->tab_len, list[i].name);
		}
		i++;
	}
	ft_printf(options->list ? "" : "\n");
	return (0);
}

int		processing(t_options *options, char *file)
{
	t_info			*list;
	struct stat		about;
	int				i;

	list = NULL;
	if (stat(file, &about))
	{
		perror("stat\n");
		exit(1);
	}
	if ((list = set_info_list(list, about.st_nlink)) == NULL)
	{
		perror("list error\n");
		exit(1);
	}
	if ((i = reading(list, file)) == 0)
		return (1);
	sort_info_list(list, i, options);
	printing(list, options, about);
	if (options->recursive)
		recursive(options, file);
	return (0);
}

int		ft_ls(t_options *options, int num)
{
	int		i;
	char	*tmp;

	i = 0;
	if (num > 0)
	{
		sort_ascii(options->dir_array, num);
		while (i < num)
		{
			if (num > 1)
				ft_printf("%s%s:\n", i > 0 ? "\n" : "", options->dir_array[i]);
			tmp = options->cur_dir;
			options->cur_dir = ft_strdup(options->dir_array[i]);
			free(tmp);
			processing(options, options->dir_array[i++]);
		}
	}
	else
		processing(options, "./");
	return (final_ls(options));
}
