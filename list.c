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
    Node * current;
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
  List * nueva = (List *)malloc(sizeof(List));
  nueva->current = NULL;
  nueva->tail = NULL;
  nueva->head = NULL;

  return nueva;
}

void * firstList(List * list) {
  
  if ((list->head != NULL) && (list->head->data != NULL)) {
    list->current = list->head;
    return (List *)list->head->data; 
    /** 
    return list->head->data; Me salia el error return discards ‘const’ qualifier from pointer target type, pero encontre esto ... https://stackoverflow.com/questions/24830335/c-compiler-warning-return-discards-qualifiers-from-pointer-target-type **/
  }
  return NULL;
}

void * nextList(List * list) {
  if ((list->current) && (list->current->next) && (list->current->next->data != NULL))
  {
    list->current = list->current->next;
    return (List *)list->current->data;
  }
    
  return NULL;
}

void * lastList(List * list) {

    if ((list->tail) && (list->tail->data))
  {
    list->current = list->tail;
    list->current->next = NULL; //Es necesario?
    return (List *)list->current->data;
  }
    
    return NULL;
}

void * prevList(List * list) {
  if (list->current && list->current->prev && list->current->prev->data )
  {
    list->current = list->current->prev;
    return (List *)list->current->data;   
  }
    return NULL;
}

void pushFront(List * list, const void * data) {
  Node * temp = createNode(data);
  if (list->head == NULL || list->head->next == NULL)
  {
    list->head = temp;
    list->tail = temp;
    list->head->next = NULL;
    return;
  }
  if ((list->head != NULL) && list->head->next != NULL)
  {
    list->head->prev = temp;
    temp->next = list->head;
    list->head = temp;
    return;    
  }
}

void pushBack(List * list, const void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
  Node * temp = createNode(data);

  if (list->head == NULL)
  {
    list->head = temp;
    temp->prev =NULL;
    temp->next =NULL;

    return;
  }
  if (list->current != NULL && list->current->prev != NULL && list->current->next == NULL) //Push en la cola
  {
    list->current->next = temp;
    temp->prev = list->tail;
    list->tail = temp;
 
    return;
    
  }
  if (list->current != NULL && list->current->next != NULL && list->current->prev != NULL) //en medio
  { 
    temp->prev = list->current;
    temp->next = list->current->next;
    list->current->next = temp;

    return;
  }
  if (list->current != NULL && list->current->prev == NULL ) //push en cabeza
  {
    if (list->head->next == NULL)
    {
      temp->prev = list->head;
      list->head->next = temp;
      return;
    }
    temp->prev = list->head;
    temp->next = list->head->next;
    list->head->next = temp;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {

  void *dato;
  dato = calloc(1, sizeof(void *)); /**reservando memoria para dato "void" y asi                                            guardar contenido de list->current->data **/
  if (list->head == NULL || list->current == NULL)
  { 
    return 0;
  }

  Node * temp = list->current;
  dato = (List *)temp->data;

  if (list->current == list->head) // caso current en head 
  {
    list->head = temp->next;
    list->head->prev = NULL;
    list->current = temp->next;
    free(temp);
    return dato;
  }
  
  if (list->current == list->tail)
  {
    list->tail = temp->prev;
    list->tail->prev = temp->prev->prev;
    list->current = temp->prev;

    list->current->next = NULL;
    list->tail->next = NULL;
  }

  return dato;

}



void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}