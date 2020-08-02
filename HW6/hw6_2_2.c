#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "bst.h"
#include "rb.h"

int my_intcmp(const void* pa, const void* pb, void* param){
	int* a = (int*)pa;
	int* b = (int*)pb;

	return *a > *b ? 1 : *a < *b ? -1 : 0;
}

int bst_find_height(const struct bst_node* node){
  if(node == NULL)
    return 0;

  int left = bst_find_height(node->bst_link[0]);
  int right = bst_find_height(node->bst_link[1]);

  return (node->bst_link[0] == NULL && node->bst_link[1] == NULL ? 0 : 1) + (left > right ? left : right);
}

int avl_find_height(const struct avl_node* node){
  if(node == NULL)
    return 0;

  int left = avl_find_height(node->avl_link[0]);
  int right = avl_find_height(node->avl_link[1]);

  return (node->avl_link[0] == NULL && node->avl_link[1] == NULL ? 0 : 1) + (left > right ? left : right);
}

int rb_find_height(const struct rb_node* node){
  if(node == NULL)
    return 0;

  int left = rb_find_height(node->rb_link[0]);
  int right = rb_find_height(node->rb_link[1]);

  return (node->rb_link[0] == NULL && node->rb_link[1] == NULL ? 0 : 1) + (left > right ? left : right);
}

int main(){
  int height[3][3];

	struct bst_table* my_bst_tree = bst_create(my_intcmp, NULL, NULL);
	struct avl_table* my_avl_tree = avl_create(my_intcmp, NULL, NULL);
	struct rb_table* my_rb_tree = rb_create(my_intcmp, NULL, NULL);

	for(int i = 1; i <= 2048; i++){
		int* element = (int *)malloc(sizeof(int));
    *element = i;

		bst_probe(my_bst_tree, element);
		avl_probe(my_avl_tree, element);
		rb_probe(my_rb_tree, element);
	}

  height[0][0] = bst_find_height(my_bst_tree->bst_root);
  height[0][1] = avl_find_height(my_avl_tree->avl_root);
  height[0][2] = rb_find_height(my_rb_tree->rb_root);

  for(int i = 1; i <= 1024; i++){
    int* element = (int *)malloc(sizeof(int));
    *element = i;

    bst_delete(my_bst_tree, element);
    avl_delete(my_avl_tree, element);
    rb_delete(my_rb_tree, element);
  }

  height[1][0] = bst_find_height(my_bst_tree->bst_root);
  height[1][1] = avl_find_height(my_avl_tree->avl_root);
  height[1][2] = rb_find_height(my_rb_tree->rb_root);

  for(int i = 2049; i <= 4096; i++){
    int* element = (int *)malloc(sizeof(int));
    *element = i;

    bst_probe(my_bst_tree, element);
    avl_probe(my_avl_tree, element);
    rb_probe(my_rb_tree, element);
  }

  height[2][0] = bst_find_height(my_bst_tree->bst_root);
  height[2][1] = avl_find_height(my_avl_tree->avl_root);
  height[2][2] = rb_find_height(my_rb_tree->rb_root);

  printf("bst %d %d %d\n", height[0][0], height[1][0], height[2][0]);
  printf("avl %d %d %d\n", height[0][1], height[1][1], height[2][1]);
  printf("rb %d %d %d\n", height[0][2], height[1][2], height[2][2]);

  return 0;

}