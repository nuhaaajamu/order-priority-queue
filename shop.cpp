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

Shop::~Shop()
{

}

void Shop::clear() {

}

Shop::Shop(const Shop& rhs)
{

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

  int h1Prior = m_priorFunc(*h1);
  int h2Prior = m_priorFunc(*h2);

  // Smaller value is higher priority.
  if (m_heapType == MINHEAP) {
    // Compare roots to determine node with the higher priority.
    if (h1Prior <= h2Prior) {
      higherPrior = h1;
      lowerPrior = h2;
    }else {
      higherPrior = h2;
      lowerPrior = h1;
    }
  }

  // Larger value is higher priority.
  if (m_heapType == MAXHEAP) {
    // Compare roots to determine node with the higher priority.
    if (h1Prior >= h2Prior) {
      higherPrior = h1;
      lowerPrior = h2;
    }else {
      higherPrior = h2;
      lowerPrior = h1;
    }
  }

  // Store right and left children of node with higher priority for easier reference.
  Order* right = higherPrior->m_right;
  Order* left = higherPrior->m_left;

  // Recursive call on higher priority node's right child.
  mergeOperation(right, lowerPrior);

  // Swap the children of the higher priority node for a skew heap. This is done every recursive call.
  if (m_structure == SKEW) {
    higherPrior->m_right = left;
    higherPrior->m_left = right;
  }

  // Swap the children of the higher priority node for a leftist heap.
  // This is only done if the right subtree is heavier than the left.
  if (m_structure == LEFTIST) {
    if (left->m_npl < right->m_npl) {
      higherPrior->m_right = left;
      higherPrior->m_left = right;
    }
  }

  // Return the root.
  return higherPrior;
}


void Shop::mergeWithQueue(Shop& rhs) {

}

// Must use merge.
bool Shop::insertOrder(const Order& order) {

}

int Shop::numOrders() const{return m_size;}
prifn_t Shop::getPriorityFn() const {return m_priorFunc;}

// Must use merge.
Order Shop::getNextOrder() {

}

// Must rebuild.
void Shop::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {

}

// Must rebuild.
void Shop::setStructure(STRUCTURE structure){

}

HEAPTYPE Shop::getHeapType() const {return m_heapType;}

STRUCTURE Shop::getStructure() const {return m_structure;}

// Use preorder traversal.
void Shop::printOrdersQueue() const {

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