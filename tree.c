#include "./tree.h"
#include <stdio.h>
#include <string.h>

Tree root = {.n = {
                 .tag = (TagRoot | TagNode),
                 .north = (Node *)((Tree *)&root),
                 .west = 0,
                 .east = 0,
                 .path = "/",
             }};

void zero(int8 *str, int16 size) {
    int8 *p;
    int16 n;

    for (n = 0, p = str; n < size; p++, n++)
        *p=0;

    return;
}

Node *create_node(Node *parent, int8 *path) {
    assert(parent);

    Node *n;
    int16 size = sizeof(struct s_node) ;

   n = (Node *)malloc((int)(size));
   zero((int8 *)n, size);

   parent -> west = n;
   n -> tag = TagNode;
   n -> north = parent;
   strncpy((char*)n->path, (char *)path, 255);

   return n;
}

Leaf *find_last_linear(Node *parent) {
    assert(parent);

    errno  = NoError;
    if (!parent -> east)
        reterr(NoError);

    Leaf *l;
    for (l = parent -> east, l -> east; l = l -> east);
    assert(l);
    return l;
}

Leaf *create_leaf(Node *parent, int8 *key, int8 value, int16 count) {
    assert(parent);

    Leaf *l  = find_last(parent);
    int16 size = sizeof(struct s_leaf);
    Leaf *new = (Leaf*)malloc(size);

    assert(new);

    if (!l) {
        parent -> east = new;
    }
    else {
        l -> east = new;
    }
    Node *n;
    zero((int8 *)new, size);
    new -> tag = TagLeaf;
    new -> west = (!l) ?
        (Node *)parent : (Leaf * )l;

    strncpy((char*)new->key, (char*)key, 127 );

    new -> value = (int8*)malloc(count);
    zero(new -> value, count);
    assert(new -> value);
    strncpy((char *)new -> value, (char*)value, count);

    new -> size = count;

    return l;

}

int main() {
  Node *n, *n2;

  n = create_node((Node*)&root, (int8*)"/Users");
  assert(n);
  n2 = create_node(n, (int8*)"/Users/login");
  assert(n2);

  printf("%p %p \n", n, n2);

  free(n);
  free(n2);
  return 0;
}
