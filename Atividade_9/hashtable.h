#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashlist.h"

typedef struct hashtable {
    int size;
    list **table;
} hashtable;

int hash_index(hashtable *table, unsigned char *key)
{ 
    unsigned h = 0;
    for (int i = 0; key[i] != '\0'; i++) 
      h = (h * 256 + key[i]) % table->size;
    return h;
}

char *hash_lookup(hashtable *hashtab, unsigned char *key)
{ 
    int index;
    index = hash_index(hashtab, key);
    list *templist = hashtab->table[index];
    if (isListEmpty(templist))
        return "not found";
    else {
        node *tempnode = searchNodeByKey(templist, key);
        return tempnode->value;
    }
}

void hash_insert(hashtable *hashtab, unsigned char *key, char *value)
{ 
    int index = hash_index(hashtab, key);
    list *temp = hashtab->table[index];
    insertNode(temp, newNode(key, value));
}

int hash_update(hashtable *hashtab, unsigned char *key, char *value)
{
    int index = hash_index(hashtab, key);
    list *temp = hashtab->table[index];
    return updateNode(temp, key, value);
}

hashtable *hash_init(int size)
{ 
    list **hasharray;
    hasharray = malloc(sizeof (list) * size);
    hashtable *hashtab;
    hashtab = malloc(sizeof (hashtable));

    int i;
    for (i = 0; i < size; i++) {
        hasharray[i] = newList();
    }

    hashtab->table = hasharray;
    hashtab->size = size;
    return hashtab;
}

void hash_destroy(hashtable *oldtable)
{ // destroy!!
    int i;
    for (i = 0; i < oldtable->size; i++) {
        destroyList(oldtable->table[i]);
    }
    free(oldtable);
}

void hash_print(hashtable *toprint)
{
    int i;
    list *templist;
    printf("keys:\tvalues:\n");
    for (i = 0; i < toprint->size; i++) {
        templist = toprint->table[i];
        if (! (isListEmpty(templist))){            
            printlist(templist);
        }
            
    }
}

void hash_remove(hashtable *hashtab, unsigned char *key)
{ 
    int index = hash_index(hashtab, key);
    list *templist = hashtab->table[index];
    if (! (isListEmpty(templist))) {
        node *delnode = searchNodeByKey(templist, key);
        removeNode(templist, delnode);
    }
}