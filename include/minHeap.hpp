#ifndef MINHEAP_HPP
#define MINHEAP_HPP

struct State
{
    int no;
    double custo;
    int portaisRestantes;
};

class MinHeap
{
private:
    State *heapArray;
    int tamanho;
    int capacidade;

    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize();

public:
    MinHeap(int initialCapacity);
    ~MinHeap();

    bool empty();
    void push(State state);
    State top();
    void pop();
};

#endif
