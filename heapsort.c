#include <stdio.h>

int pai(int i)
{
   return (i - 1) / 2;
}

int esquerda(int i)
{
   return (i * 2) + 1;
}

int direita(int i)
{
   return (i * 2) + 2;
}

void trocar(int V[], int a, int b)
{
   int aux = V[a];
   V[a] = V[b];
   V[b] = aux;
}

void imprimir(int V[], int size)
{
   int i;
   for (i = 0; i < size; i++)
   {
      printf("%d ", V[i]);
   }
   printf("\n");
}

void min_heapify(int V[], int size, int i)
{
   int e = esquerda(i), d = direita(i), menor;

   if (e < size && V[e] < V[i])
      menor = e;
   else
      menor = i;
   if (d < size && V[d] < V[menor])
      menor = d;
   if (menor != i)
   {
      trocar(V, i, menor);
      min_heapify(V, size, menor);
   }
}

void build_min_heap(int V[], int size)
{
   for (int i = (size / 2) - 1; i >= 0; i--)
      min_heapify(V, size, i);
}

void heap_sort(int V[], int size)
{
   build_min_heap(V, size);
   for (int i = (size - 1); i >= 1; i--)
   {
      trocar(V, 0, i);
      size = i;
      min_heapify(V, size, 0);
   }
}

int heap_minimum(int V[])
{
   return V[0];
}

int heap_extract_min(int V[], int size)
{
   if (size < 1){
      printf("Error : Heap Underflow");
      return 0;
   }

   int min = V[0];
   V[0] = V[size - 1];
   size -= 1;
   min_heapify(V, size, 0);
   return min;
}

void heap_decrease_key(int V[], int i, int chave)
{
   if (chave > V[i]){
      printf("Erro : Chave maior que atual");
      return;
   }

   V[i] = chave;
   while(i > 0 && V[pai(i)] > V[i]){
      trocar(V, i, pai(i));
      i = pai(i);
   }
}

void min_heap_insert(int V[], int size, int chave)
{
   size += 1;
   V[size-1] = heap_minimum(V);
   heap_decrease_key(V, size-1, chave);
}

// Max-Heap-Insert (V, Size, chave)
// Size = Size+1;
// V[Size−1] = −∞;
// Heap-Increase-Key (V, Size−1, chave);

int main()
{
   int i;

   int size = 10;

   int V[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

   printf("Vetor inicial : ");
   imprimir(V, size);

   // heap_sort(V, size);
   build_min_heap(V, size);
   printf("%d\n", heap_extract_min(V, size));
   heap_decrease_key(V, 8, 1);

   min_heap_insert(V, size-1, 0);
   printf("Vetor ordenado: ");
   imprimir(V, size);

   return 0;
}