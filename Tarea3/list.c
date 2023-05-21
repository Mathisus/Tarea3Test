#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * actual;
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
     List * new = (List *)malloc(sizeof(List));
     assert(new != NULL);
     new->head = new->tail = new->actual = NULL;
     return new;
}

void * firstList(List * list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->actual = list->head;
    return (void *)list->actual->data;
}

void * nextList(List * list) {
    if (list == NULL || list->head == NULL || list->actual == NULL || list->actual->next == NULL) return NULL;
    list->actual = list->actual->next;
    return (void *)list->actual->data;
}

void * lastList(List * list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->actual = list->tail;
    return (void *)list->actual->data;
}

void * prevList(List * list) {
    if (list == NULL || list->head == NULL || list->actual == NULL || list->actual->prev == NULL) return NULL;
    list->actual = list->actual->prev;
    return (void *)list->actual->data;
}

void pushFront(List * list, const void * data) {
    assert(list != NULL);
    
    Node * new = createNode(data);
    
    if (list->head == NULL) {
        list->tail = new;
    } else {
        new->next = list->head;
        list->head->prev = new;
    }
    
    list->head = new;
}

void pushBack(List * list, const void * data) {
    list->actual = list->tail;
    if(list->actual==NULL) pushFront(list,data);
    else pushactual(list,data);
}

void pushactual(List * list, const void * data) {
    assert(list != NULL && list->actual !=NULL);
    Node * new = createNode(data);

    if(list->actual->next)
        new->next = list->actual->next;
    new->prev = list->actual;

    if(list->actual->next)
        list->actual->next->prev = new;
    list->actual->next = new;

    if(list->actual==list->tail)
        list->tail=new;

}

void * popFront(List * list) {
    list->actual = list->head;
    return popactual(list);
}

void * popBack(List * list) {
    list->actual = list->tail;
    return popactual(list);
}

void * popactual(List * list) {
    assert(list != NULL || list->head != NULL);
    
    if (list->actual == NULL) return NULL;
    
    Node * aux = list->actual;
    
    if (aux->next != NULL) 
        aux->next->prev = aux->prev;
    
    
    if (aux->prev != NULL) 
        aux->prev->next = aux->next;
    
    
    void * data = (void *)aux->data;
    
    if(list->actual == list->tail)
        list->tail = list->actual->prev;

    if(list->actual == list->head)
        list->head = list->actual->next;
        
    list->actual = aux->prev;



    
    free(aux);
    
    return data;
}

void cleanList(List * list) {
    assert(list != NULL);
    
    while (list->head != NULL) {
        popFront(list);
    }
}