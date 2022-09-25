#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (!new) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap *) malloc(sizeof(TreeMap));
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
  
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if(!tree || !tree->root) return;

  TreeNode * aux = tree->root;
  TreeNode * parent = NULL;
  TreeNode * node = createTreeNode(key, value);

  parent = aux;
  if(tree->lower_than(aux->pair->key, key)) {
    aux = aux->right;
  } else if(tree->lower_than(key, aux->pair->key)) {
    aux = aux->left;
  } else {
    return;
  }
  
  if(!parent) {
    tree->root = node;
    tree->current = node;
  } else if(tree->lower_than(parent->pair->key, node->pair->key)) {
    node->parent = parent;
    parent->right = node;
    tree->current = node;
  } else {
    node->parent = parent;
    parent->left = node;
    tree->current = node;
  }
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  if(!tree || !tree->root) return NULL;

  TreeNode * aux = tree->root;
  tree->current = aux;
  
  if(tree->lower_than(aux->pair->key, key) == 1) {
    aux = aux->right;
  } else if(tree->lower_than(key, aux->pair->key) == 1) {
    aux = aux->left;
  } else {
    return NULL;
  }

  if (aux == NULL) return NULL;
  tree->current = aux;
    
  return aux->pair;
}

Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
