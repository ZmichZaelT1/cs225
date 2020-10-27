/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include<cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) {
      return true;
    } else if (first[curDim] == second[curDim]) {
      return first < second;
    }
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int pot_to_tar = 0;
    int curr_to_tar = 0;
    for (int i = 0; i < Dim; i++) {
      pot_to_tar += pow(potential[i] - target[i], 2);
      curr_to_tar += pow(currentBest[i] - target[i], 2);
    }
    if (pot_to_tar < curr_to_tar) {
      return true;
    } else if (pot_to_tar == curr_to_tar) {
      return potential < currentBest;
    }
    return false;
}

template <int Dim>
unsigned KDTree<Dim>::partition(vector<Point<Dim>>& list, int left, int right, int pivotIndex, int dim) {
  Point<Dim> pivotValue = list[pivotIndex];
  Point<Dim> temp = list[pivotIndex];
  list[pivotIndex] = list[right];
  list[right] = temp;
  int storeIndex = left;

  for(int i = left; i < right; i++) {
    if (smallerDimVal(list[i],pivotValue,dim)) {
      Point<Dim> tem = list[storeIndex];
      list[storeIndex] = list[i];
      list[i] = tem;
      storeIndex++;
    }
  }

  Point<Dim> tempp = list[right];
  list[right] = list[storeIndex];
  list[storeIndex] = tempp;
  return storeIndex;
}

template <int Dim>
Point<Dim>& KDTree<Dim>::select(vector<Point<Dim>>& list, int left, int right, unsigned k, int dim) {
  if(left == right) {
    return list[left];
  }
  unsigned pivotIndex = k;
  pivotIndex = partition(list, left, right, pivotIndex, dim);
  if (k == pivotIndex) {
    return list[k];
  } else if (k < pivotIndex) {
    return select(list, left, pivotIndex - 1, k, dim);
  } else {
    return select(list, pivotIndex + 1, right, k , dim);
  }
}

template <int Dim>  
void KDTree<Dim>::buildTree(vector<Point<Dim>>& points, int dim, int left, int right, KDTreeNode *& curRoot) {
  if(points.empty()) {
    return;
  }

  if(left <= right){
    unsigned middle = (left + right) / 2;
    curRoot = new KDTreeNode(select(points, left, right, middle, dim));
    size++;

    buildTree(points, (dim + 1) % Dim, left, middle - 1, curRoot->left);
    buildTree(points, (dim + 1) % Dim, middle + 1, right, curRoot->right);
  }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
	size = 0;
	if (newPoints.empty()) {
	  root = NULL;
	} else {
	  vector<Point<Dim>> copy = newPoints;
      buildTree(copy, 0, 0, copy.size() - 1, root);
	}

}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   copy(root, other);
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode * root, KDTreeNode * other) {
  root = new KDTreeNode(other->Point);
  copy(root->left, other->left);
  copy(root->right, other->right);
}


template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  _delete(root);
  _copy(root, rhs->root);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   _delete(root);
}

template <int Dim>
void KDTree<Dim>::_delete(KDTreeNode * root) {
  if (root == NULL) {
    return;
  }
  if (root->left != NULL) {
    _delete(root->left);
  }
  if (root->right != NULL) {
    _delete(root->right);
  }
  delete root;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return Point<Dim>();
}
