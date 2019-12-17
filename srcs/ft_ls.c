/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:12:31 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/17 18:15:49 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	sort_ascii(char **array, int num)
{
	char	*point;
	int		i;
	int		j;

	j = 0;
	while (j < num)
	{
		i = 0;
		while (i < num - 1)
		{
			if (ft_strcmp(array[i], array[i + 1]) > 0)
			{
				point = array[i];
				array[i] = array[i + 1];
				array[i + 1] = point;
			}
			i++;
		}
		j++;
	}
}

int		processing(t_options *options, char *file)
{
	DIR				*dir;
	struct dirent	*dir_read;

	if (options->flag)
		options->flag = 1;
	dir = NULL;
	if ((dir = opendir(file)) == NULL)
	{
		perror("opendir\n");
		exit(1);
	}
	dir_read = NULL;
	dir_read = readdir(dir);
	while (dir_read != NULL)
	{
		if (dir_read->d_name[0] != '.' ||
			(dir_read->d_name[0] == '.' && options->all))
			ft_printf("%s\t", dir_read->d_name);
		dir_read = readdir(dir);
	}
	if (closedir(dir) == -1)
		perror("closedir\n");
	ft_printf("\n");
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
