#ifndef MYQUEUE_H_INCLUDED
#define MYQUEUE_H_INCLUDED

#include "MyArithmetic.h"

template<typename value_type>
struct MyQueue {
    value_type* base;
    size_t head, tail;
    size_t cap;

    MyQueue() {
    	base = new value_type[2];
        cap = 2;
        clear();
    }
    ~MyQueue() {
        //delete base;
    }

    void clear() {
        head = tail = 0;
    }
    //before insertion
    bool empty() {
        return head == tail;
    }
    value_type& front() {
        return base[head];
    }
	const value_type& front() const {
		return base[head];
	}
	value_type& back() {
		return tail ? base[tail-1] : base[cap-1];
	}
	const value_type& back() const {
		return tail ? base[tail-1] : base[cap-1];
	}
    void pop() {
        AddMod(++head, cap);
    }
    //After insertion, head == tail
    void Expand_full() {
        size_t old_cap = cap;
        cap += cap >> 1;
        auto tmp = base;
        base = new value_type[cap];
        int i = 0;
        do {
			//swap(base[i++], tmp[head]);
			base[i++] = tmp[head];
			AddMod(++head, old_cap);
        } while (head != tail);
        head = 0;
        tail = i;
        delete tmp;
    }
    //After insertion
    void HandleFull() {
        if (head == tail) {
            Expand_full();
        }
    }
    void push(const value_type& val) {
        base[tail] = val;
        AddMod(++tail, cap);
        HandleFull();
    }
    size_t size() {
        return head <= tail ? tail - head : (tail + cap -  head);
    }
	//(*this)[0] is the head
    value_type& operator [] (size_t i) {
        i += head;
        AddMod(i, cap);
        return base[i];
    }
    const value_type& operator [] (size_t i) const {
        return (*this)[i];
    }
};

#endif


