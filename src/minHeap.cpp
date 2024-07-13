#include "../include/minHeap.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

// Função para trocar dois elementos no heapArray
void swap(State &a, State &b)
{
    State temp = a;
    a = b;
    b = temp;
}

MinHeap::MinHeap(int capacidadeInicial)
    : tamanho(0), capacidade(capacidadeInicial)
{
    heapArray = new State[capacidade];
}

MinHeap::~MinHeap()
{
    delete[] heapArray;
}

bool MinHeap::empty()
{
    return tamanho == 0;
}

void MinHeap::resize()
{
    capacidade *= 2;
    State *newHeapArray = new State[capacidade];
    for (int i = 0; i < tamanho; ++i)
    {
        newHeapArray[i] = heapArray[i];
    }
    delete[] heapArray;
    heapArray = newHeapArray;
}

void MinHeap::push(State state)
{
    if (tamanho == capacidade)
    {
        resize();
    }
    heapArray[tamanho] = state;
    // std::cout << "Heap push: Nó " << state.no << " com custo " << state.custo << " e " << state.portaisUsados << " portais usados." << std::endl;
    heapifyUp(tamanho);
    ++tamanho;
}

State MinHeap::top()
{
    if (empty())
    {
        throw std::runtime_error("Heap underflow");
    }
    return heapArray[0];
}

void MinHeap::pop()
{
    if (empty())
    {
        throw std::runtime_error("Heap underflow");
    }
    // std::cout << "Heap pop: Nó " << heapArray[0].no << " com custo " << heapArray[0].custo << " e " << heapArray[0].portaisUsados << " portais usados." << std::endl;
    heapArray[0] = heapArray[tamanho - 1];
    --tamanho;
    heapifyDown(0);
}

void MinHeap::heapifyUp(int index)
{
    if (index == 0)
        return;
    int parent = (index - 1) / 2;
    if (heapArray[index].custo < heapArray[parent].custo)
    {
        swap(heapArray[index], heapArray[parent]);
        heapifyUp(parent);
    }
}

void MinHeap::heapifyDown(int index)
{
    int filhoEsq = 2 * index + 1;
    int filhoDir = 2 * index + 2;
    int menor = index;

    if (filhoEsq < tamanho && heapArray[filhoEsq].custo < heapArray[menor].custo)
    {
        menor = filhoEsq;
    }

    if (filhoDir < tamanho && heapArray[filhoDir].custo < heapArray[menor].custo)
    {
        menor = filhoDir;
    }

    if (menor != index)
    {
        swap(heapArray[index], heapArray[menor]);
        heapifyDown(menor);
    }
}