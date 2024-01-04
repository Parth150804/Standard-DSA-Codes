#include <iostream>
#include <vector>
#include <algorithm>

class BinaryHeap {
private:
  std::vector<int> heap;

public:
  void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
  }

  int getParentIndex(int i) {
    return (i - 1) / 2;           // 0 (root) should not be given as input and int will already give the floor of this value
  }
  
  int getLeftChildIndex(int i) {
    return 2 * i + 1;
  }
  
  int getRightChildIndex(int i) {
    return 2 * i + 2;
  }
  

  void insert(int val) {
    heap.push_back(val);   //satisfies the structural prop
    heapifyUp(heap.size() - 1);   // maintains order property
  }

// Both heapify functions take O(h) time

  // used in insertion
  void heapifyUp(int index) {      
    if (index == 0) return; // base condition for termination of a recursive invocation of the fnc
    
    int parentIndex = getParentIndex(index);
    
    if (heap[parentIndex] > heap[index]) {
      swap(heap[parentIndex], heap[index]);
      heapifyUp(parentIndex);
    }
  }
  
  // used in deletion
  void heapifyDown(int index) {   // When it is called, it assumes that binary trees rooted at left and right of 'index' are min_heaps
    int leftChild = getLeftChildIndex(index);
    int rightChild = getRightChildIndex(index);
    
    if (leftChild >= heap.size()) return; // No children
    
    int minIndex = index;
    
    if (heap[minIndex] > heap[leftChild]) {
      minIndex = leftChild;
    }
    
    if (rightChild < heap.size() && heap[minIndex] > heap[rightChild]) {
      minIndex = rightChild;
    }
    
    if (minIndex != index) {
      swap(heap[minIndex], heap[index]);
      heapifyDown(minIndex);
    }
  }

  void heapifyDown(int n, int index) {    // this one is useful when a part of the array (say n-sized) is min_heap (used in heapsort)
    int leftChild = getLeftChildIndex(index);
    int rightChild = getRightChildIndex(index);
    
    int minIndex = index;
    
    if (leftChild < n && heap[minIndex] > heap[leftChild]) {
      minIndex = leftChild;
    }
    
    if (rightChild < n && heap[minIndex] > heap[rightChild]) {
      minIndex = rightChild;
    }
    
    if (minIndex != index) {
      swap(heap[minIndex], heap[index]);
      heapifyDown(n, minIndex);
    }
  }

  int minElem(){
    return heap[0];
  }
  
  void deleteMin() {
    if (heap.empty()) {
      std::cout << "Heap is empty!" << std::endl;
      return;
    }
    
    heap[0] = heap.back();    // copy last element to the root element
    heap.pop_back();          // remove last element
    
    heapifyDown(0);
  }

  void buildHeap(const std::vector<int> &arr, int size) {

    for (int i = 0; i < size; i++)
      heap.push_back(arr[i]);
    
    int n = size;
    
    for (int i = n / 2 - 1; i >= 0; i--) {      // The last non-leaf node can be found at index n/2 - 1, 
      heapifyDown(i);    // as right and        //  where n is the number of elements in the array           
    }                    // left are already    //                    OR 
  }                      // min heaps           //           heap[n/2 + 1........n] are all leaves (satisfies heap property)


  void heapSort() {
    int n = heap.size();
    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
      // Move the root to the end
      std::swap(heap[0], heap[i]);
      
      // Heapify the reduced heap
      heapifyDown(i,0);
    }
  }

  
  void printHeap (){
    for (const auto &elem : heap) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
  }

  int findKthLargest(std::vector<int> &arr, int k){

    for(int i = k; i < arr.size(); i++){
      if (arr[k] > heap[0]){
        deleteMin();
        printHeap(); // debug func
        insert(arr[k]); 
      }
    }
    return heap[0];
  }
  
};

int main()
{
  BinaryHeap minHeap;
  std::vector<int> arr = {21, 13, 16, 31, 19, 24, 68, 65, 26, 32, 12};
  // minHeap.buildHeap(arr, 11);
  // minHeap.printHeap();
  // minHeap.heapSort();
  // minHeap.printHeap();
  minHeap.buildHeap(arr,4);
  minHeap.printHeap();
  std::cout<<"4th largest = " << minHeap.findKthLargest(arr, 4)<< std::endl;      

  return 0; 
}