#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "avl.h"
#include "bst.h"
#include "rb.h"

#define MAX(x, y) ((x) > (y) ? (x) : (y));
#define MIN(x, y) ((x) < (y) ? (x) : (y));

int my_intcmp(const void* pa, const void* pb, void* param){
	int* a = (int*)pa;
	int* b = (int*)pb;

	return *a > *b ? 1 : *a < *b ? -1 : 0;
}

bool appeared(int* elements, int size, int num){
  for(int i = 0; i < size; i++)
    if(elements[i] == num)
      return 1;

  return 0;
}

int bst_height(const struct bst_node* node){
  if(node == NULL)
    return 0;

  int left = bst_height(node->bst_link[0]);
  int right = bst_height(node->bst_link[1]);

  return (node->bst_link[0] == NULL && node->bst_link[1] == NULL ? 0 : 1) + (left > right ? left : right);
}

int avl_height(const struct avl_node* node){
  if(node == NULL)
    return 0;

  int left = avl_height(node->avl_link[0]);
  int right = avl_height(node->avl_link[1]);

  return (node->avl_link[0] == NULL && node->avl_link[1] == NULL ? 0 : 1) + (left > right ? left : right);
}

int rb_height(const struct rb_node* node){
  if(node == NULL)
    return 0;

  int left = rb_height(node->rb_link[0]);
  int right = rb_height(node->rb_link[1]);

  return (node->rb_link[0] == NULL && node->rb_link[1] == NULL ? 0 : 1) + (left > right ? left : right);
}

int my_round(double x){
  if(x - (double)((int)x) < 0.5)
    return (int)x;
  return (int)x + 1;
}

int height[3][3][3];

void solve(){
  int elements[5000];

  struct bst_table* my_bst_tree = bst_create(my_intcmp, NULL, NULL);
  struct avl_table* my_avl_tree = avl_create(my_intcmp, NULL, NULL);
  struct rb_table* my_rb_tree = rb_create(my_intcmp, NULL, NULL);

  int cnt = 0;
  while(cnt < 2048){
    int num = rand(); 
    while(appeared(elements, cnt, num)){
      num = rand();
    }

    int* element = (int *)malloc(sizeof(int));
    elements[cnt++] = *element = num;

    bst_probe(my_bst_tree, element);
    avl_probe(my_avl_tree, element);
    rb_probe(my_rb_tree, element);
  }

  int Hbst = bst_height(my_bst_tree->bst_root);
  int Havl = avl_height(my_avl_tree->avl_root);
  int Hrb = rb_height(my_rb_tree->rb_root);

  height[0][0][0] = MAX((height[0][0][0]), (Hbst));
  height[0][0][1] = MIN((height[0][0][1]), (Hbst));
  height[0][0][2] += Hbst;

  height[0][1][0] = MAX((height[0][1][0]), (Havl));
  height[0][1][1] = MIN((height[0][1][1]), (Havl));
  height[0][1][2] += Havl;

  height[0][2][0] = MAX((height[0][2][0]), (Hrb));
  height[0][2][1] = MIN((height[0][2][1]), (Hrb));
  height[0][2][2] += Hrb;

  for(int i = 0; i < 1024; i++){
    int* element = (int *)malloc(sizeof(int));
    *element = elements[i];
    elements[i] = -1;

    bst_delete(my_bst_tree, element);
    avl_delete(my_avl_tree, element);
    rb_delete(my_rb_tree, element);
  }

  Hbst = bst_height(my_bst_tree->bst_root);
  Havl = avl_height(my_avl_tree->avl_root);
  Hrb = rb_height(my_rb_tree->rb_root);

  height[1][0][0] = MAX((height[1][0][0]), (Hbst));
  height[1][0][1] = MIN((height[1][0][1]), (Hbst));
  height[1][0][2] += Hbst;

  height[1][1][0] = MAX((height[1][1][0]), (Havl));
  height[1][1][1] = MIN((height[1][1][1]), (Havl));
  height[1][1][2] += Havl;

  height[1][2][0] = MAX((height[1][2][0]), (Hrb));
  height[1][2][1] = MIN((height[1][2][1]), (Hrb));
  height[1][2][2] += Hrb;

  cnt = 1024;                                                   
  for(int i = 0; i < 1024; i++)
    elements[i] = elements[i + 1024];
  
  while(cnt < 3072){
    int num = rand(); 
    while(appeared(elements, cnt, num)){
      num = rand();
    }

    int* element = (int *)malloc(sizeof(int));
    elements[cnt] = *element = num;
    cnt++;

    bst_probe(my_bst_tree, element);
    avl_probe(my_avl_tree, element);
    rb_probe(my_rb_tree, element);
  }

  Hbst = bst_height(my_bst_tree->bst_root);
  Havl = avl_height(my_avl_tree->avl_root);
  Hrb = rb_height(my_rb_tree->rb_root);

  height[2][0][0] = MAX((height[2][0][0]), (Hbst));
  height[2][0][1] = MIN((height[2][0][1]), (Hbst));
  height[2][0][2] += Hbst;

  height[2][1][0] = MAX((height[2][1][0]), (Havl));
  height[2][1][1] = MIN((height[2][1][1]), (Havl));
  height[2][1][2] += Havl;

  height[2][2][0] = MAX((height[2][2][0]), (Hrb));
  height[2][2][1] = MIN((height[2][2][1]), (Hrb));
  height[2][2][2] += Hrb;

  bst_destroy(my_bst_tree, NULL);
  avl_destroy(my_avl_tree, NULL);
  rb_destroy(my_rb_tree, NULL);

}

int main(){
  srand(time(NULL));

  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      for(int k = 0; k < 3; k++)
        height[i][j][k] = 0;

  height[0][0][1] = height[0][1][1] = height[0][2][1] = height[1][0][1] = height[1][1][1] = height[1][2][1] =\
  height[2][0][1] = height[2][1][1] = height[2][2][1] = INT_MAX;

  for(int i = 0; i < 10000; i++)
	 solve();
  

  printf("after first insertion\n");
  printf("bst %d %d %d\n", height[0][0][0], height[0][0][1], my_round(height[0][0][2] / 10000.0));
  printf("avl %d %d %d\n", height[0][1][0], height[0][1][1], my_round(height[0][1][2] / 10000.0));
  printf("rb %d %d %d\n", height[0][2][0], height[0][2][1], my_round(height[0][2][2] / 10000.0));

  printf("after removal\n");
  printf("bst %d %d %d\n", height[1][0][0], height[1][0][1], my_round(height[1][0][2] / 10000.0));
  printf("avl %d %d %d\n", height[1][1][0], height[1][1][1], my_round(height[1][1][2] / 10000.0));
  printf("rb %d %d %d\n", height[1][2][0], height[1][2][1], my_round(height[1][2][2] / 10000.0));

  printf("after 2nd insertion\n");
  printf("bst %d %d %d\n", height[2][0][0], height[2][0][1], my_round(height[2][0][2] / 10000.0));
  printf("avl %d %d %d\n", height[2][1][0], height[2][1][1], my_round(height[2][1][2] / 10000.0));
  printf("rb %d %d %d\n", height[2][2][0], height[2][2][1], my_round(height[2][2][2] / 10000.0));

  return 0;

}