#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// structs
typedef struct node {
    struct node *previous;
    struct node *next;
    char *key;
    char *value;
} node;

typedef struct list {
    node *head;
    node *tail;
} list;

// functions
list *newList()
{
    list *newlist;
    newlist = malloc(sizeof (list));
    node *sentinel;
    sentinel = malloc(sizeof (node));

    sentinel->key = '\0';
    sentinel->value = '\0';
    sentinel->next = sentinel;
    sentinel->previous = sentinel;

    newlist->head = sentinel;
    newlist->tail = sentinel;
    
    return newlist;
}

void destroyList(list *oldlist)
{
    node *sentinel = oldlist->tail;
    node *iternode = oldlist->head;
    node *next;
    while (iternode != sentinel) {
        next = iternode->next;
        free(iternode);
        iternode = next;
    }
    free(sentinel);
    free(oldlist);
}

node *newNode(char *key, char *value)
{ // make a new node
    node *newnode;
    newnode = malloc(sizeof (node));
    newnode->key = key;
    newnode->value = value;
    return newnode;
}

void insertNode(list *insertlist, node *toinsert)
{ // inserts a new item at the beginning
    toinsert->next = insertlist->head;
    insertlist->head->previous = toinsert;
    toinsert->previous = insertlist->tail;
    insertlist->head = toinsert;
}

int updateNode(list *tosearch, char *key, char *value)
{
    node *iternode = tosearch->head;
    while (iternode != tosearch->tail) {
        if (strcmp(iternode->key, key) == 0) {
            iternode->value = value;
            return 1;
        } else {
            iternode = iternode->next;
        }
    }
    return 0;
}

void removeNode(list *curlist, node *toremove)
{ // remove a given node (use listsearch to find it)
    
    if (curlist->head == toremove) {
        curlist->head = toremove->next;
        curlist->head->previous = toremove->previous;
        free(toremove);
    } 
    else {
        toremove->next->previous = toremove->previous;
        toremove->previous->next = toremove->next;
        free(toremove);
    }
}

node *searchNode(list *tosearch, char *key, char *value)
{
    node *iternode = tosearch->head;
    while (iternode != tosearch->tail) {
        if ((strcmp(iternode->key, key) == 0) && (strcmp(iternode->value, value) == 0)) {
            return iternode;
        } else {
            iternode = iternode->next;
        }
    }
    return tosearch->tail;
}

node *searchNodeByKey(list *tosearch, char *key)
{
    node *iternode = tosearch->head;
    while (iternode != tosearch->tail) {
        if (strcmp(iternode->key, key) == 0) {
            return iternode;
        } else {
            iternode = iternode->next;
        }
    }
    return tosearch->tail;
}

int isListEmpty(list *tocheck)
{
    if (tocheck->head == tocheck->tail)
        return 1;
    else
        return 0;
}

// debugging tools
void printlist(list *toprint)
{
    node *iternode = toprint->head;
    if (iternode == toprint->tail)
        printf("empty list!\n");
    while (iternode != toprint->tail)
    {
	    printf("%s\t", iternode->key);
	    printf("%s\n", iternode->value);
	    iternode = iternode->next;
    }
}