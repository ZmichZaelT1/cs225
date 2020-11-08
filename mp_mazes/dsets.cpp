/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements (int num){
    for (int i =0; i < num; i++) {
        tree.push_back(-1);
    }
}

int DisjointSets::find (int elem) {
    if (tree[elem] < 0) {
        return elem;
    } else {
        return find(tree[elem]);
    }
}

void DisjointSets::setunion (int a, int b) {
    a = find(a);
    b = find(b);

    int newSize = tree[a] + tree[b];
    if (tree[a] < tree[b]) {
        tree[b] = a;
        tree[a] = newSize;
    } else {
        tree[a] = b;
        tree[b] = newSize;
    }
}

int DisjointSets::size (int elem) {
    int temp = find(elem);
    return -1 * tree[temp];
}