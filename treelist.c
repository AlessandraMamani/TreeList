#include "treelist.h"
#include <stdlib.h>

Node *newNode(int data) {
  Node *p = malloc(sizeof *p);
  if(p == NULL) return NULL;
  p->data = data;
  p->small = NULL;
  p->large = NULL;
  return p;
}

/* EJERCICIO 1. Inserte usando una referencia local al puntero
   que enlazara el nuevo nodo. Devuelva 1 si tuvo exito; 0
   si malloc falla. Los repetidos van al subarbol izquierdo. */
int treeInsert(Node **root, int data) {
  if (*root == NULL) {
    *root = newNode(data);
    if (!*root) return 0;
    return 1;
  }
  if (data <= (*root)->data)
    return treeInsert(&((*root)->small), data);
  else
    return treeInsert(&((*root)->large), data);
}

/* EJERCICIO 2. Despues de join(a,b), b sigue a a, y a
   precede a b. Se asume a != NULL y b != NULL. */
void join(Node *a, Node *b) {
  a->large = b;
  b->small = a;
}

/* EJERCICIO 3. Concatene dos listas DOBLEMENTE CIRCULARES.
   Devuelva el primer nodo de a, o de b si a esta vacia.
   Debe ejecutarse en O(1) y no reservar nodos. */
Node *append(Node *a, Node *b) {
  if (!a) return b;
  if (!b) return a;
  
  Node* aLast = a->small;
  Node* bLast = b->small;

  join(aLast, b);
  join(bLast, a);
  
  return a;
}

/* EJERCICIO 4. Convierta el ABB en lista circular ordenada,
   reusando exactamente los mismos nodos, en tiempo O(n). a-left b-right
   Devuelva el nodo de menor valor o NULL si no hay nodos. */
Node *treeToList(Node *root) {
  if (!root) return NULL;
  
  Node* aList = treeToList(root->small);
  Node* bList = treeToList(root->large);
  
  root->small = root;
  root->large = root;
  
  Node* heap = append(aList, root);
  heap = append(heap, bList);

  return heap;
}

/* Son utilidades de infraestructura: no modificarlas. */
void freeTree(Node *root) {
  if(root == NULL) return;
  freeTree(root->small);
  freeTree(root->large);
  free(root);
}

void freeList(Node *head) {
  if(head == NULL) return;
  Node *p = head->large;
  while(p != head) {
    Node *next = p->large;
    free(p);
    p = next;
  }
  free(head);
}
