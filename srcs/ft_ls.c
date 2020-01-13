/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:12:31 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/13 21:11:06 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	final_ls(t_options *options)
{
	int	i;

	i = 0;
	while (i < options->len_for_array[0])
	{
		free(options->dir_array[i]);
		i++;
	}
	i = 0;
	while (i < options->len_for_array[1])
	{
		free(options->files_array[i]);
		i++;
	}
	free(options->dir_array);
	free(options->files_array);
	free(options);
	return (0);
}

// int	free_list(t_info *list, int count)
// {
// 	int	i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		// free(list[i].name);
// 		free(list[i].user);
// 		free(list[i].group);
// 		// free(list[i].time_active);
// 		free(list[i].time_create);
// 		free(list[i].time_modif);
// 		if (list[i].mode[0] == 'l')
// 			free(list[i].path_link);
// 		i++;
// 	}
// 	free(list);
// 	return (0);
// }

int	processing(t_options *options, char *file)
{
	t_info		*list;
	struct stat	about;
	int			count;

	if (!file)			//  обработка файлов
	{
		if ((list = set_info_list(options->len_for_array[0])) == NULL)
			error_message("error malloc()", FULL_EXIT);
		count = processing_files(options, list);
	}
	else				//	обработка директорий
	{
		if (stat(file, &about))	// EACCES
		{
			error_message(file, 0);
			if (errno == EACCES)
				return (0);
		}
		if ((list = set_info_list(about.st_nlink)) == NULL)
			error_message("error malloc()", FULL_EXIT);
		count = processing_dir(options, list, file);
	}
	if (count < 0)
		return (0);
		// error_message("count", 1);
	sort_info_list(list, count, options);
	update_value_tab_len(options, list, count);
	list[0].total = total_counter(list, count, options->all);
	printing(list, options, count);
	// free_list(list, count);
	if (file && options->recursive)
		recursive(options, file);
	return (0);
}

int	ft_ls(t_options *options)
{
	int	i;

	if (options->len_for_array[0])		// обработка файлов
	{
		update_path(options, "\0");
		processing(options, NULL);
	}
	if (options->len_for_array[1])		// обработка директорий
	{
		i = options->reverse ? options->len_for_array[1] : 0;
		while ((!options->reverse && i < options->len_for_array[1]) ||
			(options->reverse && i > 0))
		{
			i -= options->reverse ? 1 : 0;
			update_path(options, options->dir_array[i]);
			if (options->len_for_array[1] > 1 || options->len_for_array[0])
				ft_printf("%s%s:\n",  (i > 0 || options->len_for_array[0]) ?
					"\n" : "", options->dir_array[i]);
			processing(options, options->dir_array[i]);
			i += options->reverse ? 0 : 1;
		}
	}
	if (!options->len_for_array[0] && !options->len_for_array[1])	// обработка без списка файлов и директорий
	{
		update_path(options, "./\0");
		processing(options, "./\0");
	}
	return (final_ls(options));
}
