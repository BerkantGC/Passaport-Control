#include <string.h>
#include <stdio.h>
#include <time.h>
#include "linkedqueue.h"

/* DEFINE THE MQUEUE HERE */
typedef struct MQUEUE_s
{
	LINKED_QUEUE *queues;
	char **queue_names;
	int queue_count;
}MQUEUE_t[1], *MQUEUE;

/* IMPLEMENT THE FUNCTIONS HERE */

MQUEUE mqueue_init()
{
	MQUEUE mqueue;
	mqueue = (MQUEUE)malloc(sizeof(MQUEUE_t));
	 
	mqueue->queues = (LINKED_QUEUE*)malloc(sizeof(LINKED_QUEUE));
	
	if(mqueue->queues != NULL)
	{
	    mqueue->queues[0] = linked_queue_init();
	}
	
	mqueue->queue_count = 0;
	mqueue->queue_names = malloc(sizeof(*mqueue->queue_names));
	return mqueue;
}

void mqueue_add_queue_with_name(MQUEUE mqueue, char *queue_name)
{	
    mqueue->queue_count++;
	int count =  mqueue->queue_count;
	int size = strlen(queue_name);
	
	LINKED_QUEUE newq;
	newq = linked_queue_init();
	
	mqueue->queues = (LINKED_QUEUE*)realloc(mqueue->queues, sizeof(*mqueue->queues)*count);
	mqueue->queues[count-1] = malloc(sizeof(LINKED_QUEUE));
	mqueue->queues[count-1] = newq;
	
	mqueue->queue_names = (char**)realloc(mqueue->queue_names, (count)*sizeof(*mqueue->queue_names));
	mqueue->queue_names[count-1] = malloc(sizeof(char)*size);
	mqueue->queue_names[count-1] = queue_name;
}

void mqueue_print(MQUEUE mqueue)
{
	int count = mqueue->queue_count;
	LINKED_QUEUE_NODE tmp;
	
	for (int i = 0; i < count; i++)
    {
        printf("QUEUE NAME: %s\nQUEUE: ", mqueue->queue_names[i]);
        tmp = mqueue->queues[i]->head;
        while(tmp!=NULL)
        {
        	printf("%d ", *((int*)tmp->data));
        	tmp = tmp->next;
		}
        printf("\n");
    }
    
}

void mqueue_enqueue_with_name(MQUEUE mqueue, char *queue_name, void *data)
{
    int count = mqueue->queue_count;
    
	for(int i = 0; i < count; i++)
	{
		if(strcmp(mqueue->queue_names[i],queue_name) == 0)
		{
			linked_queue_enqueue(mqueue->queues[i], data);
		}
	}
}

void *mqueue_dequeue_with_name(MQUEUE mqueue, char *queue_name)
{
	int *data;
	
	for(int i = 0; i < mqueue->queue_count; i++)
	{
		if(strcmp(mqueue->queue_names[i],queue_name) == 0)
		{
			data = (int*)linked_queue_dequeue(mqueue->queues[i]);
		}
	}

	return data;
}

void mqueue_free(MQUEUE mqueue)
{
	LINKED_QUEUE_NODE tmp;
	
	for(int i = 0; i < mqueue->queue_count; i++)
	{
	    
 		while(mqueue->queues[i]->head != NULL)
 		{
 			tmp = mqueue->queues[i]->head;
 			mqueue->queues[i]->head = mqueue->queues[i]->head->next;
 			free(tmp);
		}
		free(mqueue->queue_names[i]); 
	}
	
	free(mqueue);
}

int main() {
    srand(time(NULL));
    MQUEUE mqueue = mqueue_init();
    mqueue_add_queue_with_name(mqueue, "EU Passport Control");
    //mqueue->queue_count++;
    mqueue_add_queue_with_name(mqueue, "Non-EU Passport Control");
    //mqueue->queue_count++;
    
    int rnd;
	int *data;
    char *names[] = {"EU Passport Control", "Non-EU Passport Control"};

    for(int i = 0; i < 30; i++) {
        rnd = rand() % 100;
        data = (int *)malloc(sizeof(int));
        *data = rand() % 100;
        if(rnd < 20) {
            mqueue_enqueue_with_name(mqueue, "EU Passport Control", data);
            printf("Citizen %d\t enters to \tEU Passport Control\n", *data);
        } else if(rnd < 60) {
            mqueue_enqueue_with_name(mqueue, "Non-EU Passport Control", data);
            printf("Citizen %d\t enters to \tNon-EU Passport Control\n", *data);
        }
        rnd = rand() % 100;
        if(rnd < 30) {
            data = mqueue_dequeue_with_name(mqueue, "EU Passport Control");
            if(data != NULL) {
                printf("Citizen %d\t exits \t\tEU Passport Control\n", *data);
            }
        } else if(rnd < 50) {
            data = mqueue_dequeue_with_name(mqueue, "Non-EU Passport Control");
            if(data != NULL) {
                printf("Citizen %d\t exits \t\tNon-EU Passport Control\n", *data);
            }
        }
    }
    printf("\n---------------------------\n");
    printf("\nCurrent queue lines:\n\n");
    
    mqueue_print(mqueue);
    //mqueue_free(mqueue);

    return 0;
}
