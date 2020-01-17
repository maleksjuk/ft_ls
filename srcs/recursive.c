/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:19:23 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/17 11:54:14 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		rec_get_list_param(char *file, t_info *list, int i)
{
	struct stat	about_file;

	if (stat(file, &about_file))
		return (error_message(file, (errno == EACCES) ? 0 : FULL_EXIT));
	list[i].time_active_digit = about_file.st_atimespec.tv_sec;
	list[i].time_modif_digit = about_file.st_mtimespec.tv_sec;
	list[i].time_create_digit = about_file.st_ctimespec.tv_sec;
	list[i].user = ft_strdup("-R\0");
	list[i].group = ft_strdup("-R\0");
	list[i].time_active = ft_strdup("-R\0");
	list[i].time_create = ft_strdup("-R\0");
	list[i].time_modif = ft_strdup("-R\0");
	return (0);
}

void	rec_array_set_val(char *file, int *current, t_info *list,
		char *name)
{
	char	*path;

	path = ft_strnew(MAX_PATH);
	list[*current].name = ft_strdup(name);
	update_path(path, file);
	set_path(path, name);
	rec_get_list_param(path, list, *current);
	(*current)++;
}

int		rec_reading_directory(t_options *options, char *file, int *len,
		t_info *list)
{
	DIR				*dir;
	struct dirent	*dir_read;

	if (!(dir = opendir(file)))
		return (1);
	dir_read = readdir(dir);
	while (dir_read != NULL)
	{
		if (dir_read->d_name[0] != '.' || (!ft_strequ(dir_read->d_name, ".") &&
			options->all && !ft_strequ(dir_read->d_name, "..")))
			if (dir_read->d_type == 4)
			{
				if (list)
					rec_array_set_val(file, len, list, dir_read->d_name);
				else
					(*len)++;
			}
		dir_read = readdir(dir);
	}
	if (closedir(dir) == -1)
		return (1);
	return (0);
}

t_info	*rec_create_array(t_options *options, char *file)
{
	int		len;
	int		current;
	t_info	*list_rev;

	len = 0;
	if (rec_reading_directory(options, file, &len, NULL))
		error_message(file, 0);
	current = 0;
	list_rev = set_info_list(len);
	if (rec_reading_directory(options, file, &current, list_rev))
		error_message(file, 0);
	sort_info_list(list_rev, len, options);
	list_rev[0].size = len;
	return (list_rev);
}

void	rec_print_current_directory(t_options *options)
{
	int	len;

	if (options->flag_current_process == 1 &&
		!ft_strequ(options->dir_array[options->bug_ls_for_recursion], "/\0"))
	{
		ft_printf("\n%s", options->dir_array[options->bug_ls_for_recursion]);
		len = ft_strlen(options->dir_array[options->bug_ls_for_recursion]);
		if (options->dir_array[options->bug_ls_for_recursion][len - 1] == '/')
			ft_printf("/");
		ft_printf("%s:\n", options->cur_dir + len);
	}
	else
		ft_printf("\n%s:\n", options->cur_dir);
}
