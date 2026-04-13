// CMSC 341 - Spring 2026 - Project 3
#include "shop.h"

// Have not pushed this yet. Will push when we create tests that are specific to project.
int priorityFn1(const Order &order) {
    //this function works with a MAXHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [0-5003]
    //the highest priority would be 3+5000 = 5003
    //the lowest priority would be 0+0 = 0 => 1
    //the larger value means the higher priority
    int priority = static_cast<int>(order.getCount()) + order.getPoints();
    if (priority == 0 ) priority = 1;
    return priority;
}

int priorityFn2(const Order &order) {
    //this function works with a MINHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [0-10]
    //the highest priority would be 0+0 = 0 => 1
    //the lowest priority would be 5+5 =10
    //the smaller value means the higher priority
    int priority = static_cast<int>(order.getItem()) + static_cast<int>(order.getMemebership());
    if (priority == 0 ) priority = 1;
    return priority;
}

class Tester {
public:

    void testingBase() {
        // Basic test for when h2 is null. h1 will not have children.
        Shop obj1;
        Order * h1 = new Order;
        obj1.m_heap = h1;
        Order * h2 = nullptr;
        cout << "This is h1 address: " << h1 << endl;
        cout << "Should print h1: " << endl;
        cout << obj1.mergeOperation(obj1.m_heap, h2) << endl;

        // Basic test for when h1 is null. h2 will not have children.
        Shop obj2;
        Order * h3 = nullptr;
        obj2.m_heap = h3;
        Order * h4 = new Order;

        cout << "This is h4 address " << h4 << endl;
        cout << "Should print h4: " << endl;
        cout << obj2.mergeOperation(obj2.m_heap, h4);
    }

    void testSkew() {
        // HEAP #1
        // Node (4)
        Order * node4 = new Order;
        node4->m_item = SOFTDRINK;
        node4->m_membership = TIER3;

        // Node (2)
        Order * node2 = new Order;
        node2->m_item = LATTE;
        node2->m_membership = TIER2;

        // Node (1)
        Order * node1 = new Order;
        node1->m_membership = TIER1;
        node1->m_right = node2;
        node1->m_left = node4;

        // HEAP #2
        // Node (3)
        Order * node3 = new Order;
        node3->m_membership = TIER3;
        node3->m_item = LATTE;


        // Create shop object to store root of h1 which is NODE (1).
        Shop obj1;
        obj1.m_priorFunc = priorityFn2;
        obj1.m_heapType = MINHEAP;
        obj1.m_structure = SKEW;
        obj1.m_heap = node1;

        // Merge the two heaps.
        obj1.m_heap = obj1.mergeOperation(obj1.m_heap, node3);


        // Traverse to ensure that it was done correctly.

        // Checking root (right/left child)
        if (obj1.m_heap != nullptr) {
            cout << "Root (should be 1): " <<  obj1.m_priorFunc(*obj1.m_heap) << endl;
        }else {
            cout << "Root (should be 1): nullptr" << endl;
        }


        if (obj1.m_heap->m_left != nullptr) {
            cout << "Left child of root (should be 2): " << obj1.m_priorFunc(*obj1.m_heap->m_left) << endl;
        }else {
            cout << "Left child of root (should be 2): nullptr" << endl;
        }

        if (obj1.m_heap->m_right != nullptr) {
            cout << "Right child of root (should be 4): " << obj1.m_priorFunc(*obj1.m_heap->m_right) << endl;
        }else {
            cout << "Right child of root (should be 4): nullptr" << endl;
        }


        // Checking left child of root (left child and right child)
        if (obj1.m_heap->m_left->m_left != nullptr) {
            cout << "Left child of left child (should be 3): " << obj1.m_priorFunc(*obj1.m_heap->m_left->m_left) << endl;
        }else {
            cout << "Left child of left child (should be 3): nullptr" << endl;
        }

        if (obj1.m_heap->m_left->m_right != nullptr) {
            cout << "Right child of left child (should be null): " << obj1.m_priorFunc(*obj1.m_heap->m_left->m_right) << endl;
        }else {
            cout << "Right child of left child (should be null): nullptr" << endl;
        }


        // Checking right child of root (left child and right child)
        if (obj1.m_heap->m_right->m_left != nullptr) {
            cout << "Left child of right child (should be null): " << obj1.m_priorFunc(*obj1.m_heap->m_right->m_left) << endl;
        }else {
            cout << "Left child of right child (should be null): nullptr" << endl;
        }

        if (obj1.m_heap->m_right->m_right != nullptr) {
            cout << "Right child of right child (should be null): " << obj1.m_priorFunc(*obj1.m_heap->m_right->m_right) << endl;
        }else {
            cout << "Right child of right child (should be null): nullptr" << endl;
        }




    }
};







int main() {
    // Testing min-heap SKEW
    Tester test1;
    test1.testSkew();





}

