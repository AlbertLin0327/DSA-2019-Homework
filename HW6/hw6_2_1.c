#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "bst.h"
#include "rb.h"

char word_list[10005][1005];

int my_strcmp(const void* pa, const void* pb, void* param){
	char* a = (char*)pa;
	char* b = (char*)pb;

	return strcmp(a, b);
}

void postorder_avl(const struct avl_node* node){
  if(node == NULL)
    return;

  printf ("%s ", ((char *)node->avl_data));

  if(node->avl_link[0] != NULL || node->avl_link[1] != NULL){
      putchar('(');

      postorder_avl(node->avl_link[0]);
      putchar(',');
      putchar(' ');
      postorder_avl(node->avl_link[1]);
      putchar(')');
  }
}

void postorder_bst(const struct bst_node* node){
  if(node == NULL)
    return;

  printf ("%s ", ((char *)node->bst_data));
  if(node->bst_link[0] != NULL || node->bst_link[1] != NULL){
      putchar('(');

      postorder_bst(node->bst_link[0]);
      putchar(',');
      putchar(' ');
      postorder_bst(node->bst_link[1]);
      putchar(')');
  }
}

void postorder_rb(const struct rb_node* node){
  if(node == NULL)
    return;

  printf ("%s ", ((char *)node->rb_data));
  if(node->rb_link[0] != NULL || node->rb_link[1] != NULL){
      putchar('(');

      postorder_rb(node->rb_link[0]);
      putchar(',');
      putchar(' ');
      postorder_rb(node->rb_link[1]);
      putchar(')');
  }
}

int main(){
	struct bst_table* my_bst_tree = bst_create(my_strcmp, NULL, NULL);
	struct avl_table* my_avl_tree = avl_create(my_strcmp, NULL, NULL);
	struct rb_table* my_rb_tree = rb_create(my_strcmp, NULL, NULL);

	int n; scanf("%d", &n);

	for(int i = 0; i < n; i++){
		scanf("%s", word_list[i]);
		char* element = word_list[i];

		bst_probe(my_bst_tree, element);
		avl_probe(my_avl_tree, element);
		rb_probe(my_rb_tree, element);
	}

	postorder_bst(my_bst_tree->bst_root); puts("");
	postorder_avl(my_avl_tree->avl_root); puts("");
	postorder_rb(my_rb_tree->rb_root); puts("");

	return 0;
}