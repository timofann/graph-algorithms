#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <iostream>
#include <utility>

namespace s21 {

template <class T> struct S_Node {
  S_Node<T> *sNext;
  S_Node<T> *sPrev;
  T key;
  S_Node() {
    sNext = nullptr;
    sPrev = nullptr;
  }
  S_Node(T i, S_Node<T> *p, S_Node<T> *n) {
    key = i;
    sNext = n;
    sPrev = p;
  }
};

template <class T> class stack {
private:
  S_Node<T> *sFront;
  S_Node<T> *sBack;
  size_t size_cont;

public:
  stack() : sFront(nullptr), sBack(nullptr), size_cont(0) {}
  stack(std::initializer_list<T> const &items)
      : sFront(nullptr), sBack(nullptr), size_cont(0) {
    for (auto i : items) {
      this->push(i);
    }
  }

  stack(const stack &q) : sFront(nullptr), sBack(nullptr), size_cont(0) {
    S_Node<T> *n = q.front_;
    while (n != nullptr) {
      this->push(n->key);
      n = n->sNext;
    }
  }

  stack(stack &&q) noexcept
      : sFront(q.front_), sBack(q.back_), size_cont(q.size_cont) {
    q.front_ = q.back_ = nullptr;
    q.size_cont = 0;
  }

  ~stack() {
    while (sFront != nullptr) {
      this->pop();
    }
  }

  stack &operator=(stack &&q) noexcept {
    if (sFront != nullptr) {
      this->~stack();
    }
    sFront = q.sFront;
    sBack = q.sBack;
    size_cont = q.size_cont;
    q.sFront = q.sBack = nullptr;
    q.size_cont = 0;
    return *this;
  }

  stack &operator=(const stack &q) {
    if (this->sFront == q.sFront)
      return *this;
    if (sFront != nullptr) {
      this->~stack();
    }
    S_Node<T> *n = q.sFront;
    while (n != nullptr) {
      this->push(n->key);
      n = n->sNext;
    }
    return *this;
  }

  const T &top() const { return sBack->key; }

  bool empty() const {
    if (size_cont == 0) {
      return true;
    }
    return false;
  }

  size_t size() const { return size_cont; }

  void push(const T &value) {
    size_cont++;
    S_Node<T> *n = new S_Node<T>(value, sBack, nullptr);
    if (sBack != nullptr) {
      sBack->sNext = n;
    } else {
      sFront = n;
    }
    sBack = n;
  }

  void pop() {
    if (sFront != nullptr) {
      size_cont--;
      S_Node<T> *temp = sBack;
      sBack = sBack->sPrev;
      delete temp;
      if (sBack == nullptr) {
        sFront = nullptr;
      }
    }
  }

  void swap(stack &rotate) {
    stack temp = rotate;
    rotate = *this;
    *this = temp;
  }

  template <class... Args> void emplace_front(Args &&...args) {
    T val(args...);
    this->push(val);
  }

  const T &get_start_element() const { return this->top(); }
};

} // namespace s21

#endif