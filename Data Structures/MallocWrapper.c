#include <stdlib.h>

#include <string.h>

#include <stdio.h>

#include <Windows.h>

typedef struct ctrl_str
{
	void *addr;

	size_t size;

	char file[50];

	int line;

	struct ctrl_str *n, *p;
}*Control;
Control head;
Control lastCtrl = NULL;
int allocedMem = 0;
int freedMem = 0;
#define TABLE_SIZE 2000000
typedef struct
{
	Control table[TABLE_SIZE];
	Control tail[TABLE_SIZE];
}T;
typedef struct st
{
	Control *toRet;
	int *flag;
	void *toSearch;
	int begining;
}*ThreadData;

T table;

int wasInit = 0;

void wrp_init()
{
	int i;
	for (i = 0; i < TABLE_SIZE; i++)
	{
		table.table[i] = NULL;
	}
	wasInit = 1;
}
void* wrp_malloc(size_t sz, const char* file, int line) {
	void* ptr = malloc(sz);
	if (!wasInit)
		wrp_init();
	if (ptr) {
		allocedMem += sz;
		Control c;
		Control tmp = malloc(sizeof *tmp);
		tmp->addr = ptr;
		tmp->size = sz;
		strncpy(tmp->file, file, 50);
		tmp->line = line;
		tmp->n = NULL;
		int i = ((int)(ptr) % TABLE_SIZE);
		if (table.table[i])
		{
			c = table.tail[i];
			c->n = tmp;
			c->n->p = c;
			table.tail[i] = tmp;
		}
		else
		{
			tmp->p = NULL;
			table.table[i] = tmp;
			table.tail[i] = tmp;
		}
		/*
		if (lastCtrl)
		{
			Control tmp2;
			lastCtrl->n = tmp;
			tmp2 = lastCtrl;
			lastCtrl = tmp;
			lastCtrl->p = tmp2;
		}
		else
		{
			head = tmp;
			lastCtrl = tmp;
			lastCtrl->p = NULL;
		}*/
	}
	else {
		printf("ERROR: could not malloc OOM\n");
	}
	return ptr;
}


void search_record(void* asd)
{
	Control	c;
	ThreadData data = asd;
	printf("beginning search\n");
	if (data->begining)
	{
		c = head;
		while (data && !data->flag)
		{
			if (data->toSearch == c->addr)
			{
				data->toRet = &c;
				*data->flag = 1;
				printf("found\n");
				return;
			}
			else
			{
				if (!c->n)
				{
					return;
				}
				else
				{
					c = c->n;
				}
			}
		}
	}
	else
	{
		c = lastCtrl;
		while (data && !*data->flag)
		{
			if (data->toSearch == c->addr)
			{
				data->toRet = &c;
				*data->flag = 1;
			}
			else
			{
				if (!c->p)
				{
					return;
				}
				else
				{
					c = c->p;
				}
			}
		}
	}

}


void wrp_free(void* ptr, const char* file, int line)
{
	if (!ptr)
		return;
	HANDLE t1, t2;
	ThreadData data = malloc(sizeof *data);
	Control c;
	data->flag = malloc(sizeof *data->flag); *data->flag = 0; data->toRet = NULL; data->toSearch = ptr;
	data->begining = 1;
	/*
					   t1 = CreateThread(NULL, 0, search_record, data, 0, NULL);
					   data->begining = 0;
					   t2 = CreateThread(NULL, 0, search_record, data, 0, NULL);

					   WaitForSingleObject(t1, 0);
					   WaitForSingleObject(t2, 0);

	c = head;
	while (c && c->addr != ptr)
	{
		c = c->n;
	}
	if (c)
	{
		freedMem -= c->size;
		Control tmp;
		if (c->p && c->n)
		{
			tmp = c->p;
			tmp->n = c->n;
			c->n->p = tmp;
			//c->p->n = c->n;
		}
		if (!c->p)
		{
			head = c->n;
			if (head)
				head->p = NULL;
		}
		if (!c->n)
		{
			lastCtrl = c->p;
			if (lastCtrl)
				lastCtrl->n = NULL;
		}
		free(c);
	}*/

	int i = ((int)(ptr) % TABLE_SIZE);
	c = table.table[i];
	while (c && c->addr != ptr)
	{
		c = c->n;
	}
	if (c)
	{
		freedMem += c->size;
		Control tmp;
		if (c->p && c->n)
		{
			tmp = c->p;
			tmp->n = c->n;
			c->n->p = tmp;
			//c->p->n = c->n;
		}
		if (!c->p)
		{
			table.table[i] = c->n;
			if (c->n)
				c->n->p = NULL;
		}
		if (!c->n)
		{
			if (c->p)
				c->p->n = NULL;
			else table.table[i] = NULL;
		}
		free(c);
	}
	free(ptr);

}

void wrp_mem_report()
{
	Control c;
	printf("\nAlloced %d MBytes and Free'd %d \n", allocedMem / (1024 * 1), freedMem / (1024 * 1));
	if (allocedMem == freedMem)
		printf("\n No Leaks Detected \n");
	else 
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			c = table.table[i];
			while (c)
			{
				printf("LEAK AT: %s Line %d of %d bytes \n", c->file, c->line, c->size);
				c = c->n;
			}
		}
	
}

void wrp_mem_report_file(char* file)
{
	Control c = head;
	printf("\nAlloced %d Bytes and Free'd %d \n", allocedMem, freedMem);
	if (!c)
		printf("\n No Leaks Detected \n");
	else while (c)
	{
		if (!strcmp(file,c->file))
			printf("LEAK AT: %s Line %d of %d bytes \n", c->file, c->line, c->size);
		c = c->n;
	}
}