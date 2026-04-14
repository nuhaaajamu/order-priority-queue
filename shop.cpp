// CMSC 341 - Spring 2026 - Project 3
#include "shop.h"
Shop::Shop(){ // empty object
  m_shopID = 0;
  m_heap = nullptr;
  m_size = 0;
  m_priorFunc = nullptr;
  m_heapType = NOTYPE;
  m_structure = NOSTRUCT;
  m_regPrior = 0;
}

Shop::Shop(prifn_t priFn, HEAPTYPE heapType, STRUCTURE structure, int regPrior, int id){
  m_priorFunc = priFn;
  m_heapType = heapType;
  m_structure = structure;
  m_regPrior = regPrior;
  m_shopID = id;
  m_size = 0;
  m_heap = nullptr;
}

Shop::~Shop(){clear();}

void Shop::clearOperation(Order* node) {
  if (node == nullptr) {
    return;
  }

  // Use post-order traversal to de-allocate the nodes.
  clearOperation(node->m_left);
  clearOperation(node->m_right);
  delete node;
}

void Shop::clear() {
  // De-allocate the heap of order nodes.
  clearOperation(m_heap);

  // Re-initialize the rest of the member variables.
  m_shopID = 0;
  m_heap = nullptr;
  m_size = 0;
  m_priorFunc = nullptr;
  m_heapType = NOTYPE;
  m_structure = NOSTRUCT;
  m_regPrior = 0;
}

Order* Shop::copyOperation(Order* rhsNode) {
  // Base case
  if (rhsNode == nullptr) {
    return nullptr;
  }

  // Create new node and copy data from rhs node.
  Order* newNode = new Order(rhsNode->m_item, rhsNode->m_count, rhsNode->m_membership,
                             rhsNode->m_points, rhsNode->m_customerID, rhsNode->m_orderID);
  newNode->m_npl = rhsNode->m_npl;

  // Recursively copy the left and right children.
  newNode->m_left = copyOperation(rhsNode->m_left);
  newNode->m_right = copyOperation(rhsNode->m_right);

  return newNode;
}

Shop::Shop(const Shop& rhs) {

}

Shop& Shop::operator=(const Shop& rhs) {

}


Order* Shop::mergeOperation(Order* h1, Order* h2) {
  // Base Case
  if (h1 == nullptr) {
    return h2;
  }
  if (h2 == nullptr) {
    return h1;
  }

  Order* higherPrior = nullptr;
  Order* lowerPrior = nullptr;

  int h1Prior = m_priorFunc(*h1);   // Priority values for both heaps.
  int h2Prior = m_priorFunc(*h2);

  // Smaller value is higher priority.
  if (m_heapType == MINHEAP) {
    if (h1Prior <= h2Prior) {
      higherPrior = h1;
      lowerPrior = h2;
    } else {
      higherPrior = h2;
      lowerPrior = h1;
    }

  // Larger value is higher priority.
  } else {
    if (h1Prior >= h2Prior) {
      higherPrior = h1;
      lowerPrior = h2;
    } else {
      higherPrior = h2;
      lowerPrior = h1;
    }
  }

  // Recursive call on higher priority node's right child.
  higherPrior->m_right = mergeOperation(higherPrior->m_right, lowerPrior);

  // Swap the children of the higher priority node for a skew heap.
  if (m_structure == SKEW) {
    Order* currentRight = higherPrior->m_right;
    higherPrior->m_right = higherPrior->m_left;
    higherPrior->m_left = currentRight;
  }

  // Swap the children of the higher priority node for a leftist heap.
  if (m_structure == LEFTIST) {
    Order* currentRight = higherPrior->m_right;

    if (higherPrior->m_left == nullptr) {
      higherPrior->m_right = higherPrior->m_left;
      higherPrior->m_left = currentRight;

    } else if (higherPrior->m_right != nullptr && (higherPrior->m_left->m_npl < higherPrior->m_right->m_npl)) {
      higherPrior->m_right = higherPrior->m_left;
      higherPrior->m_left = currentRight;
    }

    // Re-calculate NPL value.
    if (higherPrior->m_right == nullptr) {
      higherPrior->m_npl = 0;
    } else {
      higherPrior->m_npl = higherPrior->m_right->m_npl + 1;
    }
  }

  // Return the root.
  return higherPrior;
}

void Shop::mergeWithQueue(Shop& rhs) {
  // Protect against self-merge.
  if (this == &rhs) {
    return;
  }

  // Queues must have the same heap types.
  if (m_heapType != rhs.m_heapType) {
    throw std::domain_error("Error: Different heap types");
  }

  // Queues must use the same priority function.
  if (m_priorFunc != rhs.m_priorFunc) {
    throw std::domain_error("Error: Different priority functions");
  }

  // Queues must use the same structure.
  if (m_structure != rhs.m_structure) {
    throw std::domain_error("Error: Different structures");
  }

  // Merge the heaps.
  m_heap = mergeOperation(m_heap, rhs.m_heap);

  // Update sizes.
  m_size += rhs.m_size;

  // Leave rhs empty.
  rhs.m_heap = nullptr;
  rhs.m_size = 0;
}

bool Shop::insertOrder(const Order& order) {
  // Ensure that the priority value is valid.
  int priority = m_priorFunc(order);
  if (priority <= 0) {
    return false;
  }

  // Create node to insert.
  Order* newNode = new Order(order.getItem(),order.getCount(),order.getMemebership(),order.getPoints(),order.getCustomerID(),order.getOrderID());

  // Add the order to the queue.
  m_heap = mergeOperation(m_heap, newNode);
  m_size++;
  return true;
}

int Shop::numOrders() const{return m_size;}

prifn_t Shop::getPriorityFn() const {return m_priorFunc;}

Order Shop::getNextOrder() {
  // Ensure that the queue is not empty.
  if (m_heap == nullptr) {
    throw std::out_of_range("Error: Queue is empty");
  }

  // Store the root (highest priority order).
  Order nextOrder = *m_heap;

  // Store the left and right subtrees that will be needed to rebuild the heap.
  Order* h1 = m_heap->m_left;
  Order* h2 = m_heap->m_right;

  // Now delete the root.
  delete m_heap;

  // We must re-build the heap since the root was deleted.
  m_heap = mergeOperation(h1, h2);

  // Update the size.
  m_size--;

  // Get the highest priority order from the queue.
  return nextOrder;
}

void Shop::rebuildOperation(Order* node) {
  // Base case
  if (node == nullptr) {
    return;
  }

  // Store children of node before detachment.
  Order* left = node->m_left;
  Order* right = node->m_right;

  // Now, detach node from children so that it becomes a single node.
  node->m_right = nullptr;
  node->m_left = nullptr;
  node->m_npl = 0;

  // Merge the detached node into the new heap using the updated priority and structure.
  m_heap = mergeOperation(m_heap, node);

  // Recursively rebuild.
  rebuildOperation(left);
  rebuildOperation(right);
}

void Shop::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {
  // Save original heap and update priority/heap structure before rebuilding.
  Order* originalHeap = m_heap;
  m_heap = nullptr;
  m_priorFunc = priFn;
  m_heapType = heapType;

  // Call on helper function to rebuild the heap.
  rebuildOperation(originalHeap);
}

void Shop::setStructure(STRUCTURE structure){
  // Save original heap and update structure before rebuilding.
  Order* originalHeap = m_heap;
  m_heap = nullptr;
  m_structure = structure;

  // Call on helper function to rebuild the heap.
  rebuildOperation(originalHeap);
}

HEAPTYPE Shop::getHeapType() const {return m_heapType;}

STRUCTURE Shop::getStructure() const {return m_structure;}

void Shop::print(Order* node) const{
  // Base Case
  if (node == nullptr) {
    return;
  }

  // Calculate priority value and print data.
  int priorityVal = m_priorFunc(*node);
  cout << "[" << priorityVal << "] " << *node << endl;

  // Recursively print the data in pre-order traversal.
  print(node->m_left);
  print(node->m_right);
}

void Shop::printOrdersQueue() const {
  cout << "Contents of the queue:" << endl;

  // Print data of queue using pre-order traversal.
  print(m_heap);
}

void Shop::dump() const {
  if (m_size == 0) {
    cout << "Empty heap.\n" ;
  } else {
    cout << "Shop " << m_regPrior << ": => ";
    dump(m_heap);
  }
  cout << endl;
}
void Shop::dump(Order *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->m_left);
    if (m_structure == SKEW)
        cout << m_priorFunc(*pos) << ":" << pos->m_orderID;
    else
        cout << m_priorFunc(*pos) << ":" << pos->m_orderID << ":" << pos->m_npl;
    dump(pos->m_right);
    cout << ")";
  }
}

ostream& operator<<(ostream& sout, const Order& order) {
  sout << "Order ID: " << order.getOrderID()
        << ", item: " << order.getItem()
        << ", count: " << order.getCount();
  return sout;
}

//////////////////////////////////////////////////////////////
Region::Region(int size){

}
Region::~Region(){

}
bool Region::addShop(Shop & aShop){

}

bool Region::getShop(Shop & aShop){

}

bool Region::getNthShop(Shop & aShop, int n){

}

bool Region::setPriorityFn(prifn_t priFn, HEAPTYPE heapType, int n){

}

bool Region::setStructure(STRUCTURE structure, int n){

}
bool Region::getOrder(Order & order){

}
void Region::dump(){
    dump(ROOTINDEX);
    cout << endl;
}
void Region::dump(int index){
  if (index <= m_size){
    cout << "(";
    dump(index*2);
    cout << m_heap[index].m_regPrior;
    dump(index*2 + 1);
    cout << ")";
  }
}