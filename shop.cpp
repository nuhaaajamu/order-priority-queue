// CMSC 341 - Spring 2026 - Project 3
#include "shop.h"
Shop::Shop(){ // empty object

}
Shop::Shop(prifn_t priFn, HEAPTYPE heapType,
          STRUCTURE structure, int regPrior,
          int id)
{

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
void Shop::mergeWithQueue(Shop& rhs) {

}

bool Shop::insertOrder(const Order& order) {

}

int Shop::numOrders() const
{

}
prifn_t Shop::getPriorityFn() const {

}
Order Shop::getNextOrder() {

}
void Shop::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {

}
void Shop::setStructure(STRUCTURE structure){

}
HEAPTYPE Shop::getHeapType() const {

}
STRUCTURE Shop::getStructure() const {

}
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