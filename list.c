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
    return (void *)list->head->data; 
    /** 
    return list->head->data; Me salia el error return discards ‘const’ qualifier from pointer target type, pero encontre esto ... https://stackoverflow.com/questions/24830335/c-compiler-warning-return-discards-qualifiers-from-pointer-target-type **/
  }
  return NULL;
}

void * nextList(List * list) {
  if ((list->current) && (list->current->next) && (list->current->next->data != NULL))
  {
    list->current = list->current->next;
    return (void *)list->current->data;
  }
    
  return NULL;
}

void * lastList(List * list) {

    if ((list->tail) && (list->tail->data))
  {
    list->current = list->tail;
    list->current->next = NULL; //Es necesario?
    return (void *)list->current->data;
  }
    
    return NULL;
}

void * prevList(List * list) {
  if (list->current && list->current->prev && list->current->prev->data )
  {
    list->current = list->current->prev;
    return (void *)list->current->data;   
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

 Node * temp = list->current;

 void * dato;
 dato = calloc(1, sizeof(void *));
 dato = (List *)list->current->data;

/** if(list->current->prev != NULL)
 {
   list->current->prev->next = temp->next;
 } else list->head = temp->next;
 if (temp->next != NULL)
 {
   temp->next->prev = temp->prev;
 }
 **/
 if (list->current == NULL) return NULL;

  if (list->current == list->head)
  {
    list->current->next->prev = NULL;
    list->head = list->current->next;
    list->current = list->current->next;

  } else if (list->current == list->tail)
  {
    list->current->prev->next = NULL;
    list->tail = list->current->prev;
    list->current = NULL; 
    /** En este caso no se podria apuntar al nodo siguiente como lo piden las instruccions ya que es la cola de la lista**/
  } else {
    if (temp->next != NULL) temp->next->prev = temp->prev;
    if (temp->prev != NULL) temp->prev->next = temp->next;
    list->current = list->current->next;
  }
  free(temp);
 return dato;
}



void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}