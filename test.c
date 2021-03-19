#include "includes/ft_minishell.h"

unsigned int hash(char *name)
{
	int len;
	int i;
	unsigned int hash_value;

	len = strlen(name);
	hash_value = 0;
	i = 0;
	while (i < len)
	{
		hash_value += name[i];
		hash_value = (hash_value * name[i]) % TABLE_SIZE;
		i++;
	}
	return (hash_value);

}

t_env	*hash_table_lookup(t_env **hash_table, char *name)
{
	int index;
	int i;
	int try;

	index = hash(name);
	while (i < TABLE_SIZE)
	{
		try = (index + i) % TABLE_SIZE; 
		if (hash_table[try] == NULL)
			return (NULL);
		if (hash_table[try] == DELETED)
			continue;
		if (strcmp(hash_table[try]->name, name) == 0)
			return (hash_table[try]);
	}
	return NULL;
}

int	hash_table_insert(t_env **hash_table, t_env *var)
{
	int index;
	int try;
	int i;

	if (var == NULL)
		return (0);
	index = hash(var->name);
	i = 0;
	while (i < TABLE_SIZE)
	{
		try = (i + index) % TABLE_SIZE;
		if (hash_table[try] == NULL || hash_table[try] == DELETED)
		{
			hash_table[try] = var;
			return (1);
		}
	}
	return (0);
}

void	print_table(t_env **hash_table)
{
	int i;

	i = 0;
	printf("Start\n");
	while (i < TABLE_SIZE)
	{
		if (hash_table[i] == NULL || hash_table[i] == DELETED)
			printf("\t%i\t---\n", i);
		else
			printf("\t%i\t%s\n", i, hash_table[i]->name);
		i++;
	}
	printf("Finish\n");
}

void	init_hash_table(t_env **hash_table)
{
	int i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		hash_table[i] = NULL;
		i++;
	}
}
t_env	*hash_table_delete(t_env **hash_table, char *name)
{
	int index;
	int i;
	int try;
	t_env *tmp;

	index = hash(name);
	while (i < TABLE_SIZE)
	{
		try = (index + i) % TABLE_SIZE; 
		if (hash_table[try] == NULL)
			return (NULL);
		if (hash_table[try] == DELETED)
			continue;
		if (strcmp(hash_table[try]->name, name) == 0)
		{
			tmp = hash_table[try];
			hash_table[try] = NULL;
			return (tmp);
		}
	}
	return NULL;
}

int	main(int ac, char **av, char **env)
{
	int i = 0;
	t_env *hash_table[TABLE_SIZE];
	
	init_hash_table(hash_table);
	t_env kek = {.name = "KEK", .value = "123"};
	hash_table_insert(hash_table, &kek);
	//print_table(hash_table);
	
	//t_env *tmp = hash_table_lookup(hash_table, "KEK");
	//if (tmp == NULL)
		//printf("Not foundi\n");
	//else
		//printf("Found %s\n", tmp->value);
//
	//t_env *tmp = hash_table_delete(hash_table, "KEK");
	print_table(hash_table);

	//while (env[i])
	//{
		//printf("%s => %d\n", env[i], hash(env[i]));
		//i++;
	//}
}
