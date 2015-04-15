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

typedef struct st
{
	Control *toRet;
	int *flag;
	void *toSearch;
	int begining;
}*ThreadData;

void* wrp_malloc(size_t sz, const char* file, int line) {
	void* ptr = malloc(sz);
	if (ptr) {
		Control tmp = malloc(sizeof *tmp);
		tmp->addr = ptr;
		tmp->size = sz;
		strncpy(tmp->file, file, 50);
		tmp->line = line;
		tmp->n = NULL;
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
		}
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
	HANDLE t1, t2;
	ThreadData data = malloc(sizeof *data);
	Control c;
	data->flag = malloc(sizeof *data->flag); *data->flag = 0; data->toRet = NULL; data->toSearch = ptr;
	data->begining = 1;/*
	t1 = CreateThread(NULL, 0, search_record, data, 0, NULL);
	data->begining = 0;
	t2 = CreateThread(NULL, 0, search_record, data, 0, NULL);

	WaitForSingleObject(t1, 0);
	WaitForSingleObject(t2, 0);*/

	search_record(data);
	c = data->toRet;
	if (c)
	{
		if (c->p && c->n)
		{
			c->p->n = c->n;
			free(c);
		}
		if (!c->p)
		{
			head = c->n;
			free(c);
		}
		if (!c->n)
		{
			lastCtrl = c->p;
			free(c);
		}
	}

	free(ptr);

}

void wrp_mem_report()
{
	Control c = head;

	while (c)
	{
		printf("LEAK AT: %s Line %d of %d bytes \n", c->file, c->line, c->size);
		c = c->n;
	}
}