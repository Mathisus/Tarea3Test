#include "treemap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_equal(TreeMap *tree, void *key1, void *key2) {
  if (tree->lower_than(key1, key2) == 0 && tree->lower_than(key2, key1) == 0)
    return 1;
  else
    return 0;
}

TreeNode *minimum(TreeNode *x) {

  if (x->left == NULL) {
    return x;
  }
  return minimum(x->left);
}

TreeNode *createTreeNode(void *key, void *value) {
  TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode));
  if (new == NULL)
    return NULL;
  new->pair = (Pair *)malloc(sizeof(Pair));
  new->pair->key = key;
  new->pair->value = value;
  new->parent = new->left = new->right = NULL;
  return new;
}



TreeMap *createTreeMap(int (*lower_than)(void *key1, void *key2), int (*compare)(void*, void*), void (*destroyKey)(void*), void (*destroyValue)(void*)) {

  TreeMap *newTree = (TreeMap *)malloc(sizeof(TreeMap));
  newTree->root = NULL;
  newTree->actual = NULL;
  newTree->compare = compare;
  newTree->destroyKey = destroyKey;
  newTree->destroyValue = destroyValue;

  newTree->lower_than = lower_than;

  return newTree;
}

void destroyTreeMap(TreeMap* map)
{
    eraseTreeMap(map);
    free(map);
}

void eraseTreeMap(TreeMap* map)
{
    eraseTreeMapNode(map->root, map->destroyKey, map->destroyValue);
    map->root = NULL;
    map->size = 0;
}

void insertTreeMap(TreeMap *tree, void *key, void *value) {
  if (tree == NULL)
    return;

  // Crear un nuevo nodo con la clave y el valor proporcionados
  TreeNode *newNode = createTreeNode(key, value);
  if (newNode == NULL)
    return;

  if (tree->root == NULL) {
    // Si el árbol está vacío, el nuevo nodo se convierte en la raíz
    tree->root = newNode;
    tree->actual = newNode;
  } else {
    TreeNode *actualNode = tree->root;
    TreeNode *parent = NULL;

    // Recorrer el árbol para encontrar la ubicación adecuada para insertar el nuevo nodo
    while (actualNode != NULL) {
      parent = actualNode;

      // Si la clave ya existe, el nuevo nodo se convierte en el hijo izquierdo del nodo repetido
      if (is_equal(tree, key, actualNode->pair->key)) {
        newNode->parent = parent;
        parent->left = newNode;
        return;
      } else if (tree->lower_than(key, actualNode->pair->key)) {
        // Si la clave es menor que la clave actual, moverse hacia la izquierda
        actualNode = actualNode->left;
      } else {
        // Si la clave es mayor que la clave actual, moverse hacia la derecha
        actualNode = actualNode->right;
      }
    }

    // Asignar el padre al nuevo nodo y colocarlo como hijo izquierdo o derecho del padre según corresponda
    newNode->parent = parent;
    if (tree->lower_than(key, parent->pair->key))
      parent->left = newNode;
    else
      parent->right = newNode;
  }
}

void RemoveNode(TreeMap *tree, TreeNode *node) {
  if (tree == NULL || node == NULL)
    return;

  // Caso 1: El nodo no tiene hijos
  if (node->left == NULL && node->right == NULL) {
    if (node->parent == NULL) {
      // El nodo es la raíz del árbol
      tree->root = NULL;
    } else {
      // El nodo es un hijo izquierdo o derecho de su padre
      TreeNode *parent = node->parent;
      if (parent->left == node)
        parent->left = NULL;
      else
        parent->right = NULL;
    }
    free(node->pair);
    free(node);
  }
  // Caso 2: El nodo tiene un hijo izquierdo pero no un hijo derecho
  else if (node->left != NULL && node->right == NULL) {
    TreeNode *child = node->left;
    TreeNode *parent = node->parent;
    child->parent = parent;

    if (parent == NULL) {
      // El nodo es la raíz del árbol
      tree->root = child;
    } else {
      // El nodo es un hijo izquierdo o derecho de su padre
      if (parent->left == node)
        parent->left = child;
      else
        parent->right = child;
    }
    free(node->pair);
    free(node);
  }
  // Caso 3: El nodo tiene un hijo derecho pero no un hijo izquierdo
  else if (node->left == NULL && node->right != NULL) {
    TreeNode *child = node->right;
    TreeNode *parent = node->parent;
    child->parent = parent;

    if (parent == NULL) {
      // El nodo es la raíz del árbol
      tree->root = child;
    } else {
      // El nodo es un hijo izquierdo o derecho de su padre
      if (parent->left == node)
        parent->left = child;
      else
        parent->right = child;
    }
    free(node->pair);
    free(node);
  }
  // Caso 4: El nodo tiene tanto un hijo izquierdo como un hijo derecho
  else {
    TreeNode *successor = minimum(node->right);
    node->pair->key = successor->pair->key;
    node->pair->value = successor->pair->value;
    RemoveNode(tree, successor);
  }
}

void eraseTreeMap(TreeMap *tree) {
  if (tree == NULL || tree->root == NULL)
    return;

  TreeNode *node = tree->actual;
  if (node == NULL)
    return;

  RemoveNode(tree, node);
}

void* firstTreeMap(TreeMap *tree) {
  if (tree == NULL || tree->root == NULL)
    return NULL;

  // Encontrar el nodo más pequeño (el nodo izquierdo más profundo)
  TreeNode *actualNode = minimum(tree->root);

  tree->actual = actualNode;  // Establecer el nodo actual en el nodo más pequeño
  return actualNode->pair->value;
}

void* nextTreeMap(TreeMap *tree) {
  if (tree == NULL || tree->actual == NULL)
    return NULL;

  TreeNode *actualNode = tree->actual;

  // Si el nodo tiene un hijo derecho, el siguiente valor es el nodo más pequeño en el subárbol derecho
  if (actualNode->right != NULL) {
    actualNode = minimum(actualNode->right);
    tree->actual = actualNode;  // Actualizar el nodo actual
    return actualNode->pair->value;
  }

  // Si el nodo no tiene un hijo derecho, se busca el primer ancestro mayor
  TreeNode *parent = actualNode->parent;
  while (parent != NULL && actualNode == parent->right) {
    actualNode = parent;
    parent = parent->parent;
  }

  tree->actual = parent;  // Actualizar el nodo actual
  if (parent != NULL)
    return parent->pair->value;
  else
    return NULL;

  
}

void eraseTreeMapNode(TreeNode* node, void (*destroyKey)(void*), void (*destroyValue)(void*))
{
    if (node == NULL)
        return;

    eraseTreeMapNode(node->left, destroyKey, destroyValue);
    eraseTreeMapNode(node->right, destroyKey, destroyValue);

    if (destroyKey != NULL)
        destroyKey(node->key);
    if (destroyValue != NULL)
        destroyValue(node->value);

    destroyNode(node);
}