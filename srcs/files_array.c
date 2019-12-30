/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 19:38:03 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/30 19:38:30 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	processing_files(t_options *options)
{
	t_info		*list;
	struct stat	about;
	struct stat	about_link;
	int			count;
	char		*file;
	int			i;

	list = NULL;
	if ((list = set_info_list(list, options->len_for_array[0])) == NULL)
			error_message("processing_files list error");
	i = 0;
	while (i < options->len_for_array[0])
	{
		file = options->files_array[i];
		if (stat(file, &about))
			error_message("processing_files stat");
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
		else
		{
			free(options->cur_dir);
			options->cur_dir = ft_strdup("./\0");
			list[i].name = options->files_array[i];
			if (reading_no_dir(list, file, options, i))
				return (0);
			count = 1;
			options->flag_list = 1;
		}
		set_null_tab_len(options);
		sort_info_list(list, count, options);
		update_value_tab_len(options, list, count);
		printing(list, options, count);
		i++;
	}
	return (0);
}