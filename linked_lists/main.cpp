#include "lists.hpp"
#include <iostream>
#include <string>

template<class T>
void print(const std::string& label, const std::vector<T>& values) {
    std::cout << label;
    for (const auto& value : values) std::cout << ' ' << value;
    std::cout << '\n';
}

int main(int argc, char** argv) {
    if (argc > 1) {
        const std::string mode = argv[1];
        if (mode != "distance" && mode != "mass" && mode != "diameter") {
            std::cerr << "Usage: list_demo [distance|mass|diameter]\n";
            return 2;
        }
        PlanetList planets;
        planets.add_planet_to_list("Earth", 149.6, 5.97, 12742);
        planets.add_planet_to_list("Mercury", 57.9, 0.33, 4879);
        planets.add_planet_to_list("Mars", 227.9, 0.642, 6779);
        planets.add_planet_to_list("Venus", 108.2, 4.87, 12104);
        const auto order = mode == "distance" ? Order::Distance : mode == "mass" ? Order::Mass : Order::Diameter;
        print("Planets by " + mode + ":", planets.names(order));
        return 0;
    }
    SinglyList singly;
    singly.push_back_by_scan(7);
    singly.push_front(-3);
    singly.push_back(2);
    singly.insert_after(7, 4);
    print("Singly linked:", singly.values());
    std::cout << "Maximum: " << *singly.maximum() << '\n';
    std::cout << "Predecessor of 4: " << singly.find_before(4)->value << '\n';
    std::cout << "Sorted: " << std::boolalpha << singly.sorted() << '\n';
    singly.erase_first(2);
    print("After deleting tail:", singly.values());
    DoublyList doubly;
    doubly.push_front(4);
    doubly.push_back(9);
    doubly.insert_sorted(6);
    print("Doubly linked:", doubly.values());
    print("Reverse traversal:", doubly.values(true));
    doubly.erase_first(6);
    print("After deleting 6:", doubly.values());
    SinglyList::Node first{1}, second{2}, third{3};
    first.next = &second;
    second.next = &third;
    third.next = &second;
    std::cout << "Cycle entry: " << cycle_entry(&first)->value << '\n';
    break_cycle(&first);
    std::cout << "Cycle after unlinking: " << (cycle_entry(&first) != nullptr) << '\n';
}
