#include "lists.hpp"
#include <climits>
#include <iostream>
#include <stdexcept>
#include <string>

void check(bool value, const char* message) {
    if (!value) throw std::runtime_error(message);
}
void singly_test() {
    SinglyList list;
    check(list.sorted() && !list.maximum() && !list.erase_first(0), "empty list");
    list.push_back(-5);
    check(list.erase_first(-5), "erase sole node");
    list.push_back(-2);
    list.push_front(-4);
    list.push_back_by_scan(-1);
    check(list.insert_after(-2, 0) && !list.insert_after(20, 9), "insert after");
    check(!list.sorted() && list.maximum() == 0, "maximum and order");
    check(list.find_before(0)->value == -2 && !list.find_before(-4) && list.find(-1), "search");
    check(list.erase_first(-1) && list.erase_first(0), "erase tail twice");
    list.insert_sorted(-3);
    list.push_back(-1);
    check(list.sorted() && list.values() == std::vector<int>{-4,-3,-2,-1}, "tail and sorted insert");
}
void doubly_test() {
    DoublyList list;
    list.push_front(0);
    list.push_back(INT_MAX);
    list.insert_sorted(INT_MIN);
    list.insert_sorted(0);
    check(list.values() == std::vector<int>{INT_MIN,0,0,INT_MAX}, "sentinel limits");
    check(list.erase_first(0) && list.erase_first(INT_MAX) && !list.erase_first(9), "remove node");
    check(list.values(true) == std::vector<int>{0,INT_MIN}, "reverse links");
    list.erase_first(0);
    list.erase_first(INT_MIN);
    list.push_back(12);
    check(list.values(true) == std::vector<int>{12}, "reuse after clearing");
}
void planet_test() {
    PlanetList list;
    list.add_planet_to_list("A", 1, 3, 2);
    list.add_planet_to_list("B", 2, 1, 3);
    list.add_planet_to_list("C", 3, 2, 1);
    check(list.names(Order::Distance) == std::vector<std::string>{"A","B","C"}, "distance");
    check(list.names(Order::Mass) == std::vector<std::string>{"B","C","A"}, "mass");
    check(list.names(Order::Diameter) == std::vector<std::string>{"C","A","B"}, "diameter");
}
void cycle_test() {
    using Node = SinglyList::Node;
    check(!cycle_entry(nullptr), "empty chain");
    Node a{1}, b{2}, c{3};
    a.next = &b; b.next = &c;
    check(!cycle_entry(&a) && !break_cycle(&a), "acyclic chain");
    c.next = &b;
    check(cycle_entry(&a) == &b && break_cycle(&a) && !c.next, "cycle after prefix");
    c.next = &a;
    check(cycle_entry(&a) == &a && break_cycle(&a), "cycle at head");
    a.next = &a;
    check(cycle_entry(&a) == &a && break_cycle(&a) && !a.next, "self loop");
}
int main(int argc, char** argv) {
    if (argc != 2) return 2;
    const std::string name = argv[1];
    try {
        if (name == "singly") singly_test();
        else if (name == "doubly") doubly_test();
        else if (name == "planets") planet_test();
        else if (name == "cycle") cycle_test();
        else return 2;
        std::cout << name << ": passed\n";
    } catch (const std::exception& error) {
        std::cerr << name << ": " << error.what() << '\n';
        return 1;
    }
}
