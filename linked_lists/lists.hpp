#pragma once
#include <array>
#include <memory>
#include <optional>
#include <string>
#include <vector>

class SinglyList {
public:
    struct Node { int value; Node* next = nullptr; };
    SinglyList() = default;
    SinglyList(const SinglyList&) = delete;
    SinglyList& operator=(const SinglyList&) = delete;
    ~SinglyList();
    void push_front(int value);
    void push_back(int value);
    void push_back_by_scan(int value);
    bool insert_after(int target, int value);
    bool erase_first(int value);
    void insert_sorted(int value);
    const Node* find(int value) const;
    const Node* find_before(int value) const;
    std::optional<int> maximum() const;
    bool sorted() const;
    std::vector<int> values() const;
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    void insert_after_node(Node* previous, int value);
};

class DoublyList {
public:
    DoublyList();
    DoublyList(const DoublyList&) = delete;
    DoublyList& operator=(const DoublyList&) = delete;
    ~DoublyList();
    void push_front(int value);
    void push_back(int value);
    void insert_sorted(int value);
    bool erase_first(int value);
    std::vector<int> values(bool reverse = false) const;
private:
    struct Node { int value; Node* prev; Node* next; };
    Node head{}, tail{};
    static void insert_cell(Node* previous, int value);
    static void erase_cell(Node* cell);
};

enum class Order { Distance, Mass, Diameter };
struct Planet {
    std::string name;
    double distance_to_sun, mass, diameter;
    std::array<Planet*, 3> next{};
};
class PlanetList {
public:
    void add_planet_to_list(std::string name, double distance, double mass, double diameter);
    std::vector<std::string> names(Order order) const;
private:
    std::vector<std::unique_ptr<Planet>> storage;
    std::array<Planet*, 3> heads{};
};

// Returns the cycle entry, or nullptr for an acyclic chain.
SinglyList::Node* cycle_entry(SinglyList::Node* head);
bool break_cycle(SinglyList::Node* head);
