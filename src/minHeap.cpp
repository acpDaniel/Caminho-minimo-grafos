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

// Construtor da classe MinHeap, inicializa o heap com uma capacidade inicial fornecida
MinHeap::MinHeap(int capacidadeInicial)
    : tamanho(0), capacidade(capacidadeInicial)
{
    heapArray = new State[capacidade];
}

// Destrutor da classe MinHeap, libera a memória alocada para o heapArray
MinHeap::~MinHeap()
{
    delete[] heapArray;
}

// Função que verifica se o heap está vazio
bool MinHeap::empty()
{
    return tamanho == 0;
}

// Função que redimensiona o heapArray dobrando a sua capacidade atual
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

// Função que insere um novo elemento no heap e mantém a propriedade do heap
void MinHeap::push(State state)
{
    if (tamanho == capacidade)
    {
        resize();
    }
    heapArray[tamanho] = state;
    heapifyUp(tamanho);
    ++tamanho;
}

// Função que retorna o menor elemento do heap (raiz) sem removê-lo
State MinHeap::top()
{
    if (empty())
    {
        throw std::runtime_error("Heap underflow");
    }
    return heapArray[0];
}

// Função que remove o menor elemento do heap e mantém a propriedade do heap
void MinHeap::pop()
{
    if (empty())
    {
        throw std::runtime_error("Heap underflow");
    }
    heapArray[0] = heapArray[tamanho - 1];
    --tamanho;
    heapifyDown(0);
}

// Função auxiliar para manter a propriedade do heap após a inserção de um novo elemento
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

// Função auxiliar para manter a propriedade do heap após a remoção do elemento da raiz
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
