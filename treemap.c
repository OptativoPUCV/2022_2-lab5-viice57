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
    if(tree->lower_than(key1,key2) == 0 &&  
        tree->lower_than(key2,key1) == 0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *) malloc(sizeof(TreeNode));
    if (!new) return NULL;
    new->pair = (Pair *) malloc(sizeof(Pair));
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
}

TreeNode * minimum(TreeNode * x) {
  while(x->left) x = x->left;
  return x;
}

void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
  if(!tree || !tree->root) return;

  if(!searchTreeMap(tree, key)) return;
  TreeNode* node = tree->current;
  removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) {
  if(!tree || !tree->root) return NULL;
  
  tree->current = tree->root;
  while(tree->current) {
      if (is_equal(tree, tree->current->pair->key, key)) return tree->current->pair;
    
      if(tree->lower_than(tree->current->pair->key, key)) tree->current = tree->current->right;
      else tree->current = tree->current->left;
  }
  
  return NULL;
}

Pair * upperBound(TreeMap * tree, void* key) {
  TreeNode *ub_node;
  Pair *flag;

  if(!searchTreeMap(tree, key)) {
    firstTreeMap(tree);
    
    while((flag = nextTreeMap(tree))) {
      if(tree->lower_than(tree->current->pair->key, key) == 0) break;
    }

    if(!flag) return NULL;
  } 
  ub_node = tree->current;
    
  if(!ub_node) return NULL;
  return ub_node->pair;
}

Pair * firstTreeMap(TreeMap * tree) {
  if(!tree) return NULL;

  TreeNode * firstNode = minimum(tree->root);
  return firstNode->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  if (!tree) return NULL;
  
  TreeNode *aux = tree->current;
    
  if(aux->right) {
    tree->current = minimum(aux->right);
  } else {
    TreeNode *parentNode = aux->parent;
    
    while(parentNode) {
      if(tree->lower_than(parentNode->pair->key, aux->pair->key)) parentNode = parentNode->parent;
      else break;
    }
    
    if(!parentNode) return NULL;
    tree->current = parentNode;
  }
  
  return tree->current->pair;
}
