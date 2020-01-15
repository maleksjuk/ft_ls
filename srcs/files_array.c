/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 19:38:03 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/15 15:56:41 by obanshee         ###   ########.fr       */
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
		update_path(options, NULL);
		set_path(options, options->files_array[count]);
		lstat(options->files_array[count], &about_link);
		if (S_ISLNK(about_link.st_mode))
			list[count].flag_link = 1;
		if (reading_one_file(list, options->files_array[count], options, count))
			return (-1);
		count++;
	}
	return (count);
}
