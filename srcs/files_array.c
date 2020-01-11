/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 19:38:03 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/11 20:03:28 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	processing_files(t_options *options, t_info *list)
{
	struct stat	about;
	struct stat	about_link;
	int			count;

	count = 0;
	while (count < options->len_for_array[0])
	{
		if (options->files_array[count][0] == '/' ||
			ft_strnequ(options->files_array[count], "./\0", 2) ||
			ft_strnequ(options->files_array[count], "../\0", 3))
			update_path(options, "\0");
		else
			update_path(options, "./\0");
		if (stat(options->files_array[count], &about))	// EACCES
			error_message(options->files_array[count], 1);
		lstat(options->files_array[count], &about_link);	// EACCES
		if (S_ISLNK(about_link.st_mode))
		{
			list[count].flag_link = 1;
			set_path(options, options->files_array[count]);
			if (reading_one_file(list, options->files_array[count], options, count))
				return (-1);
		}
		else
		{
			list[count].flag_link = 0;
			set_path(options, options->files_array[count]);
			if (reading_one_file(list, options->files_array[count], options, count))
				return (-1);
		}
		count++;
		options->flag_list = 1;
	}
	return (count);
}
