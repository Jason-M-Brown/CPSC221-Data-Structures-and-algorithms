/**
 * @file        queue.cpp
 * @description Implementation of the Queue class.
 *
 *              SUBMIT THIS FILE WITH YOUR MODIFICATIONS
 */

/**
 * Adds the parameter object to the back of the Queue.
 *
 * NOTE: This fuction should have O(1) behavior amortized over n operations!
 *
 * @param item - object to be added to the Queue.
 */
template <class T>
void Queue<T>::Enqueue(T const& item) {   
	stack_1.Add(item);
	
}

/**
 * Removes the object at the front of the Queue, and returns it to
 * the caller. You may assume that this function is only called
 * when the Queue is non-empty.
 *
 * NOTE: This function should have O(1) behavior over n operations!
 *
 * @return the item that used to be at the front of the Queue.
 */
template <class T>
T Queue<T>::Dequeue() {
	if(stack_2.IsEmpty()) {
        while(!stack_1.IsEmpty()) {
            stack_2.Add(stack_1.Remove());
        }
    } 
    return stack_2.Remove();
	//T item = stack_2.Remove();
	//return item; 
}

/**
 * Adds an element to the ordering structure.
 *
 * See OrderingStructure::Add()
 */
template <class T>
void Queue<T>::Add(const T& item) {
    Enqueue(item);
	// Hint: this function should call a Queue	
}

/*
*  Removes an element from the ordering structure.
*
*  See OrderingStructure::Remove()
*/
template <class T>
T Queue<T>::Remove() {
	// function to remove an element from the Queue and return it. You will
	return Dequeue();
}

/*
*  Finds the object at the front of the Queue, and returns it to
*  the caller. Unlike Dequeue(), this operation does (conceptually!) not alter the
*  Queue; however, you may need to alter the internal representation of the Queue.
*  You may assume that this function is only called when the
*  Queue is non-empty.
*
*  NOTE: This function should have O(1) behavior amortized over n operations!
*
*  @return the item at the front of the queue.
*/
template <class T>
T Queue<T>::Peek() {
	if(stack_2.IsEmpty()) {
        while(!stack_1.IsEmpty()) {
            stack_2.Add(stack_1.Remove());
        }
    }
	return stack_2.Peek();
}

/*
*  Determines if the Queue is empty.
*
*  @return true if the stack is empty,
*          false otherwise.
* 
*  NOTE: This function must always run in O(1) time!
*/
template <class T>
bool Queue<T>::IsEmpty() const {
	if(stack_1.IsEmpty() && stack_2.IsEmpty()) {
        return true;
    }
	return false; 
}
