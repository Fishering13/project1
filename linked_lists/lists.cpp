#include "lists.hpp"
#include <algorithm>
#include <limits>
#include <utility>

SinglyList::~SinglyList() {
    while (head) {
        Node* old = head;
        head = head->next;
        delete old;
    }
}
void SinglyList::insert_after_node(Node* previous, int value) {
    Node*& link = previous ? previous->next : head;
    link = new Node{value, link};
    if (!link->next) tail = link;
}
void SinglyList::push_front(int value) { insert_after_node(nullptr, value); }
void SinglyList::push_back(int value) { insert_after_node(tail, value); }
void SinglyList::push_back_by_scan(int value) {
    Node* last = head;
    while (last && last->next) last = last->next;
    insert_after_node(last, value);
}
bool SinglyList::insert_after(int target, int value) {
    Node* node = head;
    while (node && node->value != target) node = node->next;
    if (!node) return false;
    insert_after_node(node, value);
    return true;
}
bool SinglyList::erase_first(int value) {
    Node* previous = nullptr;
    Node* current = head;
    while (current && current->value != value) {
        previous = current;
        current = current->next;
    }
    if (!current) return false;
    (previous ? previous->next : head) = current->next;
    if (tail == current) tail = previous;
    delete current;
    return true;
}
void SinglyList::insert_sorted(int value) {
    Node* previous = nullptr;
    for (Node* node = head; node && node->value < value; node = node->next)
        previous = node;
    insert_after_node(previous, value);
}
const SinglyList::Node* SinglyList::find(int value) const {
    for (const Node* node = head; node; node = node->next)
        if (node->value == value) return node;
    return nullptr;
}
const SinglyList::Node* SinglyList::find_before(int value) const {
    if (!head || head->value == value) return nullptr;
    for (const Node* node = head; node->next; node = node->next)
        if (node->next->value == value) return node;
    return nullptr;
}
std::optional<int> SinglyList::maximum() const {
    if (!head) return std::nullopt;
    int result = head->value;
    for (const Node* node = head->next; node; node = node->next)
        result = std::max(result, node->value);
    return result;
}
bool SinglyList::sorted() const {
    for (const Node* node = head; node && node->next; node = node->next)
        if (node->value > node->next->value) return false;
    return true;
}
std::vector<int> SinglyList::values() const {
    std::vector<int> result;
    for (const Node* node = head; node; node = node->next) result.push_back(node->value);
    return result;
}

DoublyList::DoublyList() {
    head = {std::numeric_limits<int>::min(), nullptr, &tail};
    tail = {std::numeric_limits<int>::max(), &head, nullptr};
}
DoublyList::~DoublyList() { while (head.next != &tail) erase_cell(head.next); }
void DoublyList::insert_cell(Node* previous, int value) {
    Node* cell = new Node{value, previous, previous->next};
    previous->next->prev = cell;
    previous->next = cell;
}
void DoublyList::erase_cell(Node* cell) {
    cell->prev->next = cell->next;
    cell->next->prev = cell->prev;
    delete cell;
}
void DoublyList::push_front(int value) { insert_cell(&head, value); }
void DoublyList::push_back(int value) { insert_cell(tail.prev, value); }
void DoublyList::insert_sorted(int value) {
    Node* previous = &head;
    while (previous->next != &tail && previous->next->value < value)
        previous = previous->next;
    insert_cell(previous, value);
}
bool DoublyList::erase_first(int value) {
    for (Node* cell = head.next; cell != &tail; cell = cell->next) {
        if (cell->value == value) {
            erase_cell(cell);
            return true;
        }
    }
    return false;
}
std::vector<int> DoublyList::values(bool reverse) const {
    std::vector<int> result;
    if (reverse) {
        for (const Node* cell = tail.prev; cell != &head; cell = cell->prev) result.push_back(cell->value);
    } else {
        for (const Node* cell = head.next; cell != &tail; cell = cell->next) result.push_back(cell->value);
    }
    return result;
}

namespace {
constexpr std::array<double Planet::*, 3> keys{
    &Planet::distance_to_sun, &Planet::mass, &Planet::diameter
};
}
void PlanetList::add_planet_to_list(std::string name, double distance, double mass, double diameter) {
    storage.push_back(std::make_unique<Planet>(Planet{std::move(name), distance, mass, diameter}));
    Planet* planet = storage.back().get();
    for (std::size_t index = 0; index < keys.size(); ++index) {
        const auto key = keys[index];
        Planet** link = &heads[index];
        while (*link && (*link)->*key <= planet->*key) link = &(*link)->next[index];
        planet->next[index] = *link;
        *link = planet;
    }
}
std::vector<std::string> PlanetList::names(Order order) const {
    std::vector<std::string> result;
    const auto index = static_cast<std::size_t>(order);
    for (const Planet* node = heads[index]; node; node = node->next[index]) result.push_back(node->name);
    return result;
}
SinglyList::Node* cycle_entry(SinglyList::Node* head) {
    auto* slow = head;
    auto* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            fast = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }
    return nullptr;
}
bool break_cycle(SinglyList::Node* head) {
    auto* entry = cycle_entry(head);
    if (!entry) return false;
    auto* last = entry;
    while (last->next != entry) last = last->next;
    last->next = nullptr;
    return true;
}
