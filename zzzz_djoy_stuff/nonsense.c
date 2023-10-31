// /**
//  * @param env environment stored in linked list
//  * @brief prints linked list containing env key or value
// */
// void	print_env_list(t_env *lst)
// {
// 	int	i;

// 	i = 0;
// 	while (lst != NULL)
// 	{
// 		printf("iterations [%d]\n", i);
// 		i++;
// 		lst = lst->next;
// 	}
// }

// /**
//  * @param env environment stored in linked list
//  * @brief prints linked list containing env full
// */
// void	print_list_full(t_env *env)
// {
// 	while (env != NULL)
// 	{
// 		printf("%s\n", env->full);
// 		env = env->next;
// 	}
// }

// /**
//  * @param env environment stored in linked list
//  * @brief prints linked list containing env key or value
// */
// void	print_parser_list(t_parser *lst)
// {
// 	int i;

// 	i = 0;
// 	while (lst != NULL)
// 	{
// 		printf("||\n");
// 		printf("index = [%d], cmd = [%s]\n", i, lst->cmd);
// 		printf("index = [%d], str = [%s]\n", i, lst->str);
// 		// printf("index = [%d], meta = [%s]\n", i, lst->redirect_list->meta);
// 		// printf("next node\n");
// 		if (lst->next == NULL)
// 			printf("NULL\n");
// 		lst = lst->next;
// 		i++;
// 	}
// }