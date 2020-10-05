/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  ListNode * curr = head_;
  if(curr==NULL)
  {
    return;
  }
  ListNode * temp = curr;
  while(curr != NULL)
  {
    temp=temp->next;
    delete curr;
    curr = temp;
  }
  // head_ = NULL;
  // tail_ = NULL;
  // length_ = 0;
  /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  // @todo Graded in MP3.1
  ListNode* temp = new ListNode(ndata);
  if(length_ == 0){
    head_ = temp;
    tail_ = temp;
  }
  else{
    temp->next = head_;
    head_->prev = temp;
    head_ = head_->prev;
  }
  length_++;
}


/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  ListNode* temp = new ListNode(ndata);
  if(length_ == 0){
    head_ = temp;
    tail_ = temp;
  }
  else{
    tail_->next = temp;
    temp->prev = tail_;
    tail_ = tail_->next;
  }
  length_++;
  //@todo Graded in MP3.1
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if (start == NULL || splitPoint >= length_) {
    return NULL;
  } else if (splitPoint < 1) {
    return start;
  }

  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
    if (curr->prev != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
    }
    return curr;
  }

  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  ListNode * curr = head_;
  int i = 1;

  while (curr != NULL) {
    if (i % 3 == 0) {
      ListNode * third = curr;
      ListNode * second = third->prev;
      ListNode * first = second->prev;
      curr = curr->next;
      ListNode * front = first->prev;
      third->next = first;
      second->prev = front;

      if (front != NULL) {
        front->next = second;
      }
      if (curr != NULL) {
        curr->prev = first;
      }

      first->next = curr;
      first->prev = third;
      if (i == 3) {
        head_ = second;
      }
      if (i / 3 == length_ / 3) {
        tail_ = first;
      }
    } else {
      curr = curr->next;
    }
    i++;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  if (startPoint == NULL || endPoint == NULL) {
    return;
  }

  ListNode * curr = startPoint;
  ListNode * prev = startPoint->prev;
  ListNode * next = curr->next;
  int count = 0;

  while (curr != endPoint) {
    if (count == 0) {
        curr->next = endPoint->next;
        curr->prev = next;
        curr = next;
    }
    next = curr->next;
    curr->next = curr->prev;
    curr->prev = prev;
    curr = next;
    count ++;
  }

  endPoint->next = endPoint->prev;
  endPoint->prev = prev;

  if (head_ != startPoint) {
    prev->next = curr;
  } else {
    head_ = endPoint;
  }

  if (tail_ != endPoint) {
    startPoint->next->prev = startPoint;
  } else {
    tail_ = startPoint;
  }
  /// @todo Graded in MP3.2
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  if(n <= 1 || head_ == NULL){
    return;
  }

  ListNode * start = head_;
  ListNode * end = start;

  while (start != NULL) {
    int count = 0;

    while (count < n - 1) {
      if (end != tail_) {
        end = end->next;
      }
      count++;
    }

    reverse(start, end);
    start = start->next;
    end = start;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  // if (first == NULL && second == NULL) {
  //   return NULL;
  // } else if (first == NULL) {
  //   return second;
  // } else if (second == NULL) {
  //   return first;
  // }
  
  // ListNode * head;
	// if (first->data < second->data) {
	// 	head = first;
	// }
	// else {
	// 	head = second;
	// }

  //   ListNode * curr = head;
  //   ListNode * temp;
  //   ListNode * temps = second;
  //   ListNode * tempf = first;

	// while (first != NULL && second != NULL) {
  //   if (first->data < second->data) {

  //     while (tempf->next != NULL) {
  //       if (first->next->data < second->data) {
  //         first = first->next;
  //       }
  //       tempf = tempf->next;
  //     }

  //     temp = first->next;
  //     first->next = second;
  //     second->prev = first;
  //     first = temp;
  //     tempf = first;
	//   } else {
  //     while (temps->next != NULL) {
  //       if(second->next->data < first->data){
  //         second = second->next;
  //       }
  //       temps = temps->next;
  //     }

  //     temp = second->next;
  //     second->next = first;
  //     first->prev = second;
  //     second = temp;
  //     temps = second;
	//   }
  // }
  // return head;
  if (first == NULL && second == NULL) {
    return NULL;
  } else if (first == NULL) {
    return second;
  } else if (second == NULL) {
    return first;
  }

  ListNode * head;
	if (first->data < second->data) {
		head = first;
		first = first->next;
	}
	else {
		head = second;
		second = second->next;
	}


	ListNode * curr = head;
	while (first != NULL && second != NULL) {
		if (second->data < first->data) {
			curr->next = second;
			second->prev = curr;
			second = second->next;
	  	curr = curr->next;
		}
		else {
			curr->next = first;
			first->prev = curr;
			first = first->next;
  		curr = curr->next;
		}
	}

	if (first == NULL && second != NULL) {
		curr->next = second;
		second->prev = curr;
	} else if (second == NULL && first != NULL) {
		curr->next = first;
		first->prev = curr;
	}

	return head;
  /// @todo Graded in MP3.2
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  	if (start->next == NULL) {
      return start;
    }

  	ListNode * second = split(start, chainLength / 2);
  	return merge(mergesort(start, chainLength / 2), mergesort(second, (chainLength % 2) + (chainLength / 2)));
}
