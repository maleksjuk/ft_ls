/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 15:22:26 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/17 05:41:58 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	reading_one_file(t_info *list, char name[1024], t_options *options, int i)
{
	list[i].name = ft_strdup(name);
	list[i].full_params = options->list;
	if (get_list_params(options->cur_dir, list, i))
		return (0);
	if (list[i].name[0] != '.' || options->all || options->list_files)
		options->count++;
	return (0);
}

int	reading(t_info *list, char *file, t_options *options)
{
	DIR				*dir;
	struct dirent	*dir_read;
	int				i;

	dir = opendir(file);
	if (!dir)
		if (error_message(file, 0) == 2)
			return (0);
	i = 0;
	dir_read = readdir(dir);
	while (dir_read != NULL)
	{
		if (!list[i].flag_link)
			add_path(options->cur_dir, dir_read->d_name);
		reading_one_file(list, dir_read->d_name, options, i);
		update_path(options, file);
		i++;
		dir_read = readdir(dir);
	}
	if (closedir(dir) == -1)
		error_message("close", 0);
	return (i);
}
