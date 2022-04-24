#include "treemap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode TreeNode;

struct TreeNode {
	Pair *pair;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
};

struct TreeMap {
	TreeNode *root;
	TreeNode *current;
	int (*lower_than)(void *key1, void *key2);
};

int is_equal(TreeMap *tree, void *key1, void *key2) {
	if (tree->lower_than(key1, key2) == 0 && tree->lower_than(key2, key1) == 0)
		return 1;
	else
		return 0;
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

TreeMap *createTreeMap(int (*lower_than)(void *key1, void *key2)) {
	TreeMap *New = (TreeMap *)malloc(sizeof(TreeMap));
	New->lower_than = lower_than;
	return New;
}

void insertTreeMap(TreeMap *tree, void *key, void *value) {
  TreeNode *new = createTreeNode(key,value);
  TreeNode *aux = tree->current;
  
  if(tree->root == NULL){
    tree->root = new;
    return;
  }

  aux = tree->root;
  tree->current = aux;

  while(aux != NULL){
    if(is_equal(tree,key,aux->pair->key) == 1) return;
    
    if(tree->lower_than(key, aux->pair->key) == 1){
      if(aux->left == NULL){
        aux->left = new;
        new->parent = aux;
        aux = aux->left;
        tree->current = aux;
        return;
      }
      aux = aux->left;
    }
    else{
      if(aux->right == NULL){
        aux->right = new;
        new->parent = aux;
        aux = aux->right;
        tree->current = aux;
        return;
      }
      aux = aux->right;
    }
  }
}

TreeNode *minimum(TreeNode *x) {
  while(x -> left != NULL)
    x = x -> left;
	return x;
}

void removeNode(TreeMap *tree, TreeNode *node) {

  if(node->right == NULL && node->left == NULL){
    if(node == tree->root){
      tree->root = NULL;
      tree->current = NULL;
    }
    else{
      
        
    }
  }
}

void eraseTreeMap(TreeMap *tree, void *key) {
	if (tree == NULL || tree->root == NULL)
		return;

	if (searchTreeMap(tree, key) == NULL)
		return;
	TreeNode *node = tree->current;
	removeNode(tree, node);
}

Pair *searchTreeMap(TreeMap *tree, void *key) {
  TreeNode *aux = tree->root;
  while(aux != NULL){
    if(is_equal(tree, aux->pair->key, key)){
      tree->current = aux;
      return aux -> pair;
    }
    if(tree->lower_than(aux->pair->key, key))
      aux = aux -> right;
    else
      aux = aux -> left;
  }
	return NULL;
}

Pair *upperBound(TreeMap *tree, void *key) {
	return NULL;
}

Pair *firstTreeMap(TreeMap *tree) {
  tree->current = minimum(tree->root);
  if(tree->current == NULL) return NULL;
	return tree->current->pair;
}

Pair *nextTreeMap(TreeMap *tree) {
  TreeNode *nextNode;
  //si tiene hijo derecho
  if(tree->current->right != NULL){
    //clave mínima
    nextNode = minimum(tree->current->right);
    tree->current = nextNode;
    if(nextNode == NULL) return NULL;
    return nextNode->pair;
  }
  else{
    //si el current es la raíz
    if(tree->current->parent == NULL){
      tree->current = NULL;
      return NULL;
    }
    //current está en el subárbol izquierdo
    else if(tree->current->parent->left == tree->current){
      tree->current = tree->current->parent;
      if(tree->current == NULL) return NULL;
      return tree->current->pair;
    }
    else{
      //encontrar el 1° ancestro mayor al current
      while(tree->current->parent != NULL && tree->lower_than(tree->current->pair->key, tree->current->parent->pair->key) != 1){
        tree->current = tree->current->parent;
      }
      tree->current = tree->current;
      if(tree->current == NULL) return NULL;
      return tree->current->pair;
    }
  }
	return NULL;
}
