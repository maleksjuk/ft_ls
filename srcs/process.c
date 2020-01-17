/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 07:44:35 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/17 10:42:39 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	processing_files(t_options *options, t_info *list)
{
	struct stat	about_link;
	int			count;

	count = 0;
	options->list_files = 1;
	while (count < options->len_for_array[0])
	{
		update_path(options->cur_dir, NULL);
		set_path(options->cur_dir, options->files_array[count]);
		lstat(options->files_array[count], &about_link);
		if (S_ISLNK(about_link.st_mode))
			list[count].flag_link = 1;
		if (reading_one_file(list, options->files_array[count], options, count))
			return (-1);
		count++;
	}
	return (count);
}

int	processing_dir(t_options *options, t_info *list, char *file)
{
	int	count;

	options->list_files = 0;
	count = reading(list, file, options);
	if (!count)
		return (-1);
	return (count);
}

int	processing_helper(t_options *options, char *file)
{
	t_info		*list;
	struct stat	about;
	int			count;

	if (!file)
	{
		if ((list = set_info_list(options->len_for_array[0])) == NULL)
			error_message("error malloc()", FULL_EXIT);
		count = processing_files(options, list);
	}
	else
	{
		if (stat(file, &about))
			return (error_message(file, 0));
		if (S_ISDIR(about.st_mode) && !(about.st_mode & S_IXUSR))
			return (0);
		if ((list = set_info_list(about.st_nlink)) == NULL)
			error_message("error malloc()", FULL_EXIT);
		count = processing_dir(options, list, file);
	}
	sort_info_list(list, count, options);
	update_value_tab_len(options, list, count);
	printing(list, options, count);
	free_list(list, count);
	return (0);
}

int	processing(t_options *options, char *file)
{
	processing_helper(options, file);
	if (file && options->recursive)
		recursive(options, file);
	return (0);
}
