#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
#include <iostream>
#include <utility>

namespace s21 {

template <class T> struct QueueNode {
  QueueNode<T> *pNext;
  QueueNode<T> *pPrev;
  T key;
  QueueNode() : pNext(nullptr), pPrev(nullptr), T(0) {}
  QueueNode(T i, QueueNode<T> *p, QueueNode<T> *n)
      : pNext(n), pPrev(p), key(i) {}
};

template <class T> class queue {
private:
  QueueNode<T> *pFront;
  QueueNode<T> *pBack;
  size_t size_cont;

public:
  queue() : pFront(nullptr), pBack(nullptr), size_cont(0) {}

  queue(std::initializer_list<T> const &items)
      : pFront(nullptr), pBack(nullptr), size_cont(0) {
    for (auto i : items) {
      size_cont++;
      QueueNode<T> *n = new QueueNode<T>(i, pBack, nullptr);
      if (pBack != nullptr) {
        pBack->pNext = n;
      } else {
        pFront = n;
      }
      pBack = n;
    }
  }

  queue(const queue &q) {
    pFront = nullptr;
    pBack = nullptr;
    size_cont = 0;
    QueueNode<T> *n = q.pFront;
    while (n != nullptr) {
      size_cont++;
      n = new QueueNode<T>(n->key, pBack, nullptr);
      if (pBack != nullptr) {
        pBack->pNext = n;
      } else {
        pFront = n;
      }
      pBack = n;
      n = n->next;
    }
  }

  queue(queue &&q) noexcept {
    pFront = q.pFront;
    pBack = q.pBack;
    size_cont = q.size_cont;
    q.pFront = nullptr;
    q.pBack = nullptr;
    q.size_cont = 0;
  }

  ~queue() {
    while (pFront != nullptr) {
      this->pop();
    }
  }

  queue &operator=(queue &&q) noexcept {
    if (pFront != nullptr) {
      while (pFront != nullptr) {
        this->pop();
      }
    }
    pFront = q.pFront;
    pBack = q.pBack;
    size_cont = q.size_cont;
    q.pFront = nullptr;
    q.pBack = nullptr;
    q.size_cont = 0;
    return *this;
  }

  queue &operator=(const queue &q) {
    if (this == q)
      return *this;
    if (pFront != nullptr) {
      while (pFront != nullptr) {
        this->pop();
      }
    }
    pFront = nullptr;
    pBack = nullptr;
    QueueNode<T> *n = q.pFront;
    while (n != nullptr) {
      this->push(n->key);
      n = n->next;
    }
    return *this;
  }

  const T &front() { return pFront->key; }
  const T &back() { return pBack->key; }

  bool empty() const {
    if (size_cont == 0) {
      return true;
    }
    return false;
  }

  size_t size() const { return size_cont; }

  void push(const T &value) {
    size_cont++;
    QueueNode<T> *n = new QueueNode<T>(value, pBack, nullptr);
    if (pBack != nullptr) {
      pBack->pNext = n;
    } else {
      pFront = n;
    }
    pBack = n;
  }

  void pop() {
    if (pFront != nullptr) {
      size_cont--;
      QueueNode<T> *temp = pFront;
      pFront = pFront->pNext;
      delete temp;
      if (pFront == nullptr) {
        pBack = nullptr;
      }
    }
  }

  void swap(queue &rotate) {
    queue temp = rotate;
    rotate = *this;
    *this = temp;
  }

  template <class... Args> void emplace_back(Args &&...args) {
    T val(args...);
    this->push(val);
  }

  const T &get_start_element() { return this->front(); }
};

} // namespace s21

#endif