#include <stdio.h>

struct Node {
    int coeff;
    int power;
    Node *next;

    Node(int c, int p) : coeff(c), power(p), next(nullptr) {};
};

struct Polynomial {
    struct Node *head;

    Polynomial() : head(nullptr) {};
};

void PrintPolynomial(const Polynomial &poly) {
    for (Node *start = poly.head; start != nullptr; start = start->next)
        if (start->coeff)
            printf("%+dx^%d", start->coeff, start->power);
    printf("\n");
}

Polynomial InsertNode(const Polynomial &p, Node *node) {
    Polynomial poly = p;
    Node **start = &poly.head;
    if (*start == nullptr || (*start)->power <= node->power) {
        if (*start != nullptr && (*start)->power == node->power) {
            (*start)->coeff += node->coeff;
            delete node;
        } else {
            node->next = *start;
            *start = node;
        }
        return poly;
    }
    Node *current_node = *start;
    for (; current_node->next != nullptr && current_node->next->power > node->power; current_node = current_node->next);
    if (current_node->next != nullptr && current_node->next->power == node->power) {
        current_node->next->coeff += node->coeff;
        delete node;
    } else {    
        node->next = current_node->next;
        current_node->next = node;
    }
    return poly;
}

Polynomial copy(const Polynomial &poly) {
    Polynomial p;
    for (Node *start = poly.head; start != nullptr; start = start->next)
        p = InsertNode(p, new Node(start->coeff, start->power));
    return p;
}

Polynomial Add(const Polynomial &lhs, const Polynomial &rhs) {
    Polynomial p = copy(lhs);
    for (Node *start = rhs.head; start != nullptr; start = start->next)
        p = InsertNode(p, new Node(start->coeff, start->power));
    return p;
}

Polynomial Minus(const Polynomial &lhs, const Polynomial &rhs) {
    Polynomial p = copy(lhs);
    for (Node *start = rhs.head; start != nullptr; start = start->next)
        p = InsertNode(p, new Node(-start->coeff, start->power));
    return p;
}

Polynomial Multiply(const Polynomial &lhs, const Polynomial &rhs) {
    Polynomial p;
    for (Node *start_rhs = rhs.head; start_rhs != nullptr; start_rhs = start_rhs->next)
        for (Node *start_lhs = lhs.head; start_lhs != nullptr; start_lhs = start_lhs->next)
            p = InsertNode(p, new Node(start_lhs->coeff * start_rhs->coeff, start_lhs->power + start_rhs->power));
    return p;
}

Polynomial Power(const Polynomial &base, int exp) {
    Polynomial p = copy(base);
    for (int i = 1; i < exp; i++)
        p = Multiply(p, base);
    return p;
}

Polynomial InitPolynomial(const char *str) {
    Polynomial p;
    while (*str) {
        int coeff, power;
        sscanf(str, "%dx^%d", &coeff, &power);
        for (str++; *str != '\0' && (*str != '+' && *str != '-'); str++);
        p = InsertNode(p, new Node(coeff, power));
    }
    return p;
}

// ATTENTION: DO NOT MODIFY THE CODE BELOW

#include "test.hpp"

int main() {
    test();
    return 0;
}
