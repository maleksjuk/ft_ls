/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:12:31 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/31 21:30:59 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	final_ls(t_options *options)
{
	int	i;

	i = 0;
	while (options->dir_array[i])
	{
//		free(options->dir_array[i]);
		i++;
	}
//	free(options->dir_array);
	free(options->cur_dir);
	free(options);
	return (0);
}

/*int	reading_no_dir(t_info *list, char name[1024], t_options *options, int i)
{
	char	*tmp;

	tmp = list[i].name;
	list[i].name = ft_strdup(name);
	// free(tmp);
	if (list[i].flag_link)
		options->cur_dir = ft_strdup("\0");
	set_path(options, NULL, name);
	if (get_list_params(options->cur_dir, list, i))
		return (0);
	options->cur_dir[ft_strlen(options->cur_dir) - ft_strlen(name) - 1] = '\0';
	if (list[i].name[0] != '.' || options->all)
		options->count++;
	return (0);
}

int	reading(t_info *list, char *file, t_options *options)
{
	DIR				*dir;
	struct dirent	*dir_read;
	int				i;

	dir = NULL;
	dir_read = NULL;
	i = 0;
	if ((dir = opendir(file)) == NULL)
	{
		perror("opendir_reading");
		exit(1);
	}
	dir_read = readdir(dir);
	i = 0;
	while (dir_read != NULL)
	{
		reading_no_dir(list, dir_read->d_name, options, i);
		i++;
		dir_read = readdir(dir);
	}
	if (closedir(dir) == -1)
		perror("closedir_reading");
	return (i);
}

int	printing(t_info *list, t_options *options, int len)
{
	int	i;

	while (options->tab_len[6] % 8 != 0)
		options->tab_len[6]++;
	i = 0;
	if (options->list && !options->flag_list && options->count)
		ft_printf("total %lld\n", options->all ? list[0].total : list[0].total_no_all);
	while (i < len)
	{
		if (list[i].name[0] == '\0')
			break ;
		if (list[i].name[0] != '.' || (list[i].name[0] == '.' && options->all))
		{
			if (options->list)
				print_list(list, i, options);
			else
				ft_printf("%-*s", options->tab_len[6], list[i].name);
		}
		i++;
	}
	ft_printf(options->list ? "" : "\n");
	return (0);
}

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
}*/

int	ft_ls(t_options *options)
{
	int			i;
	char		*tmp;

	if (options->len_for_array[0])		// обработка файлов
	{
		processing_files(options);
	}
	if (options->len_for_array[1])		// обработка директорий
	{
		i = 0;
		while (i < options->len_for_array[1])
		{
			tmp = options->cur_dir;
			options->cur_dir = ft_strdup(options->dir_array[i]);
			free(tmp);
			if (options->len_for_array[1] > 1)
				ft_printf("%s%s:\n", i > 0 ? "\n" : "", options->dir_array[i]);
			processing_dir(options, options->dir_array[i]);
			i++;
		}
	}
	if (!options->len_for_array[0] && !options->len_for_array[0])	// обработка без списка файлов и директорий
		processing_without(options, "./");
	return (final_ls(options));
}
