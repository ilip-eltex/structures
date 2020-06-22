#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

unsigned int count = 0;

struct record {
	unsigned int id;
	unsigned int age;
	char name[64];
	char surname[64];
};

struct list {
	struct record data;
	struct list *previous;
};

void add (struct list **previous)
{
	struct list *l = malloc (sizeof(struct list));
        if (l == NULL)
	{
		printf ("Error while init list var\n");
		exit (1);
	}
	l->data.id = ++count;
	l->data.age = 0;
        strcpy (l->data.name, "NONE\0");
        strcpy (l->data.surname, "NONE\0");
	l->previous = *previous;
	(*previous) = l;

}

void print_record (struct record r)
{
	printf ("\n\tPerson #%d\n\tName: %s\n\tSurname: %s\n\tAge: %d\n", r.id, r.name, r.surname, r.age);
}

int main ()
{
	struct list *head = NULL;
       	char choice='\0';
	struct list *tmp = NULL;
	
	while (1)
	{
		printf ("\e[2J\e[HWelcome to directory (%d records)!\nPlease choose action:\n(1) Add record\n(2) Show records\n(3) Exit\n\n>> ", count);
		choice = getchar();
		if (choice == '3')
			break;
		switch (choice) 
		{
		case '1':
			add (&head);
			printf ("Enter: <age> <name> <surname>\n");
			scanf ("%d %s %s", &head->data.age, head->data.name, head->data.surname);
			printf ("\nAdded:\n");
			print_record (head->data);
			getchar();
			getchar();
			break;
		
		case '2':
			tmp = head;
			while (tmp != NULL)
			{
				print_record (tmp->data);
				tmp = tmp->previous;
			}
			getchar ();
			getchar ();
			break;
		}

	}
	

	while (tmp != NULL && head != NULL)
	{
		tmp = head->previous;
		free(head);
		head = tmp;
	}


	return 0;
}
