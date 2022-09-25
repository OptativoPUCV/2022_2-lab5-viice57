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
/*  if(!tree->root) {
    tree->root = createTreeNode(key, value);
  } else {
    tree->current = tree->root;
    TreeNode * aux = tree->current;
    
    while(aux) {
      if(is_equal(tree, aux->pair->key, key)) return;
      
      if(tree->lower_than(key, aux->pair->key)) {
        if(!aux->left) {
          aux->left = createTreeNode(key, value);
          aux->left->parent = tree->current;
          aux = aux->left;
          return;
        } 
      } else {
        if(!aux->right) {
          aux->right = createTreeNode(key, value);
          aux->right->parent = aux;
          aux = aux->right;
          return;
        }
      }
    }
  }*/
}

TreeNode * minimum(TreeNode * x) {
  while(x->left) x = x->left;
  return x;
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
  /*if(!tree || !tree->root) return NULL;

  TreeNode * aux = tree->root;
  tree->current = aux;
  
  if(tree->lower_than(aux->pair->key, key)) {
    tree->current = aux->right;
  } else if(tree->lower_than(key, aux->pair->key)) { //si lo buscado es menor a nodo raiz
    tree->current = aux->left;
  } else {
    return NULL;
  }
    
  return aux->pair;*/    tree->current = tree->root;

    while (tree->current != NULL) {
        if (is_equal(tree, tree->current->pair->key, key)) return tree->current->pair;
        if (tree->lower_than(tree->current->pair->key, key)){
            tree->current = tree->current->right;
        }
        else {
            tree->current = tree->current->left;
        }
    }
    
    return NULL;
}

Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  if(!tree) return NULL;

  TreeNode * firstNode = minimum(tree->root);
  return firstNode->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  return NULL;
}
