/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_R.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:19:23 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/02 16:40:08 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
int	processing(t_options *options, char *file)
{
	t_info		*list;
	struct stat	about;
	struct stat	about_link;
	int			count;

	list = NULL;
	if (stat(file, &about))
		error_message("processing stat");
	if ((list = set_info_list(list, about.st_nlink)) == NULL)
		error_message("processing list error");
	lstat(file, &about_link);
	if (S_ISLNK(about_link.st_mode))
	{
		list[0].flag_link = 1;
		free(options->cur_dir);
		options->cur_dir = ft_strdup(file);
		if (reading_no_dir(list, file, options, 0))
			return (0);
		count = 1;
		options->flag_list = 1;
	}
	else if (!S_ISDIR(about.st_mode))
	{
		free(options->cur_dir);
		options->cur_dir = ft_strdup("./\0");
		if (reading_no_dir(list, file, options, 0))
			return (0);
		count = 1;
		options->flag_list = 1;
	}
	else if ((count = reading(list, options->cur_dir, options)) == 0)
		return (1);
	set_null_tab_len(options);
	sort_info_list(list, count, options);
	update_value_tab_len(options, list, count);
	printing(list, options, count);
	if (options->recursive)
		recursive(options, options->cur_dir);
	return (0);
}
*/

int		recursive(t_options *options, char *file)
{
	DIR				*dir;
	struct dirent	*dir_read;

	dir = NULL;
	dir_read = NULL;
	if ((dir = opendir(file)) == NULL)
	{
		perror(file);
		return (1);
	}
	dir_read = readdir(dir);
	while (dir_read != NULL)
	{
		if (dir_read->d_name[0] != '.' || (options->all &&
			(dir_read->d_name[0] == '.' && dir_read->d_name[1] != '.' &&
			dir_read->d_name[1] != '\0')))
			if (dir_read->d_type == 4)
			{
				set_path(options, NULL, dir_read->d_name);
				ft_printf("\n%s:\n", options->cur_dir);
			//	processing(options, options->cur_dir);
				options->cur_dir[ft_strlen(options->cur_dir) -
					ft_strlen(dir_read->d_name) - 1] = '\0';
			}
		dir_read = readdir(dir);
	}
	if (closedir(dir) == -1)
		perror("closedir -R");
	return (0);
}
