/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:12:31 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/17 21:06:33 by obanshee         ###   ########.fr       */
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
//	free(options->cur_dir);
	return (0);
}

t_info	*set_info_list(t_info *list, int len)
{
	list = (t_info *)malloc(sizeof(t_info) * (len + 1));
	if (list == NULL)
		return (NULL);
	return (list);
}

int		processing(t_options *options, char *file)
{
	DIR				*dir;
	struct dirent	*dir_read;
	t_info			*list;
	struct stat		about;
	int				i;

	list = NULL;
	dir = NULL;
	dir_read = NULL;
	if (stat("./", &about))
	{
		perror("stat\n");
		exit(1);
	}
	list = set_info_list(list, about.st_nlink);
	if (list == NULL)
	{
		perror("list error\n");
		exit(1);
	}
	if ((dir = opendir(file)) == NULL)
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
	sort_info_list(list, i);
	i = 0;
	while (i < (int)about.st_nlink)
	{
		ft_printf("(%2i): %s\n", i, list[i].name);
		i++;
	}
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
	return (final_ls(options));
}
