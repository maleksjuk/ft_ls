/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 15:22:26 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/10 18:22:17 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	reading_one_file(t_info *list, char name[1024], t_options *options, int i)
{
	list[i].name = ft_strdup(name);
	if (get_list_params(options->cur_dir, list, i))
		return (0);
	if (list[i].name[0] != '.' || options->all)
		options->count++;
	return (0);
}

int	reading(t_info *list, char *file, t_options *options)
{
	DIR				*dir;
	struct dirent	*dir_read;
	int				i;
	char			*path;

	path = ft_strdup(file);
	dir = NULL;
	dir_read = NULL;
	i = 0;
	if ((dir = opendir(file)) == NULL)
		error_message("opendir_reading", 1);
	dir_read = readdir(dir);
	i = 0;
	while (dir_read != NULL)
	{
		if (!list[i].flag_link)
			set_path(options, dir_read->d_name);	// SET_PATH
		reading_one_file(list, dir_read->d_name, options, i);
		update_path(options, path);					// UPDATE_PATH
		i++;
		dir_read = readdir(dir);
	}
	if (closedir(dir) == -1)
		perror("closedir_reading");
	free(path);
	return (i);
}
