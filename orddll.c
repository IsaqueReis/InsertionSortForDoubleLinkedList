#include <stdio.h>
#include <stdlib.h>

#include "orddll.h"

struct s_ord_dll 
{
    void *fst; //ponteiro para o primeiro elemento
    void *lst; //ponteiro para o último elemento

    int n;     //numero de elementos da lista
};
typedef struct s_ord_dll* ODLL;

struct s_node
{
    void *data; //armazena informação do nó

    struct s_node *next, *prev; //ponteiros para os elementos próximo e anterior
};
typedef struct s_node* NODE;


ordDLL dListCreate()
{
    ODLL l = (ODLL) calloc(1, sizeof(ODLL));
    l->fst = l->lst = NULL;
    l->n = 0;

    return l;
}

void dListDestroy(ordDLL list)
{
    ODLL l = (ODLL) list;
    NODE current = NULL;
    NODE tmp = NULL;

    if(l == NULL)
        return;
    
    current = l->fst;
    while(current != NULL)
    {
        tmp = current->next;
        free(current);
        current = tmp;
    }

    free(l);
    return;
}

item listFindE(ordDLL list, void *e, int (*cmp) (const void *a, const void *b))
{
    ODLL l = (ODLL) list;
    NODE current = NULL;
    
    current = l->fst;
    if(cmp(current->data, e) == 0)
        return current->data;
    
    while(current != NULL)
    {
        if(cmp(current->data, e) == 0)
            return current->data;
        current = current->next;
    }

    if(current == NULL)
        return NULL;
    
    return NULL;
}

item dListGetI(ordDLL list, int p)
{
    ODLL l = (ODLL) list;
    NODE current = l->fst;

    if((l == NULL) || (p > l->n))
        return NULL;
    
    for(int i = 1; i < p; i++)
        current = current->next;
    
    return current->data;
}

void listInsert(ordDLL list, void *elem, int (*cmp) (const void *a, const void *b))
{
    ODLL l = (ODLL) list;
    NODE current = NULL;
    NODE new_node = (NODE) calloc(1, sizeof(NODE));
    if(!new_node)
    {
        fprintf(stderr, "allocation error!\n");
        exit(1);
    }

    new_node->data = elem;
    current = l->fst;

    //se a lista estiver vazia
    if((current == NULL))
    {
        l->fst = l->lst = new_node;
    } else if(cmp(current->data, new_node->data) > 0) //se o elemento tem que ser inserido no começo da lista
    {
        new_node->next = l->fst;
        new_node->next->prev = new_node;
        l->fst = new_node;

        if(l->lst == NULL)
            l->lst = new_node;
    } else {

        //achar o elemento para inserir logo após
        while(current->next != NULL && 
        (cmp(current->next->data, new_node->data) < 0))
            current = current->next;
        
        //criando as ligações
        new_node->next = current->next;

        //se nao foir inserido no final
        if(current->next != NULL)
            new_node->next->prev = new_node;
        
        current->next = new_node;
        new_node->prev = current;    
    }//else

    l->n++;
    return;
}

int length(ordDLL list)
{
    ODLL l = (ODLL) list;
    return l->n;
}

item listRemove(ordDLL list, void *elem, int (*cmp) (const void *a, const void*b))
{
    ODLL l = (ODLL) list;
    NODE current = NULL;

    current = l->fst;
    if((l == NULL) || (elem == NULL))
        return NULL;

    //se o elemento for logo o primeiro da lista
    if(cmp(current->data, elem) == 0)
    {
        l->fst = current->next;
        l->n--;
        return current->data;
    }
    
    //caso contrario ele esta em algum lugar entre a cabeça e a cauda
    while((current != NULL) && (cmp(current->data, elem) != 0))
        current = current->next;
    
    if(current == NULL)
        return NULL;
    
    //se ele estiver na ultima posição
    if(current->next == NULL)
    {
        current->prev->next = NULL;
        l->n--;
        return current->data;
    }

    //senão
    current->prev->next = current->next;
    current->next->prev = current->prev;
    l->n--;
    return current->data;
}
