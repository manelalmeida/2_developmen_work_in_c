#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

typedef struct Dynvec {
    
    void *data;
    size_t length;
    size_t capacity;
    size_t elem_size;
}dynvec;

static void dynvec_resize(dynvec *v, size_t new_capacity) {
    
    void *new_data = realloc(v->data, new_capacity * v->elem_size);
    
    if (new_data) {
        v->data = new_data;
        v->capacity = new_capacity;
    }
}

dynvec* dynvec_create(size_t elem_size) {
    
    dynvec *v = malloc(sizeof(dynvec));
    if (!v) {
        return NULL;
    }
    v->elem_size = elem_size;
    v->length = 0;
    v->capacity = 4;
    v->data = malloc(v->capacity * v->elem_size);
    return v;
}

void dynvec_push(dynvec *v, void *elem) {
    
    if (v->length == v->capacity){ 
        dynvec_resize(v, v->capacity * 2);
    }
    
    memcpy((char *)v->data + (v->length * v->elem_size), elem, v->elem_size);
    v->length++;
}

void* dynvec_get(dynvec *v, size_t index) {
    
    if (index >= v->length){
        return NULL;
    }
    return (char *)v->data + (index * v->elem_size);
}

size_t dynvec_length(dynvec *v) { 
    return v->length; 
}

void dynvec_free(dynvec *v) {
    
    if (v) { 
        free(v->data);
        free(v); 
    }
}

dynvec* dynvec_filter(dynvec *v, bool (*predicate)(void *)) {
    
    dynvec *novo = dynvec_create(v->elem_size);
    
    for (size_t i = 0; i < v->length; i++) {
        void *item = dynvec_get(v, i);
            if (predicate(item)){ 
            dynvec_push(novo, item);
            }
    }
    return novo;
}

void swap(void *a, void *b, size_t size) {
    char temp[size];
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

int partition(dynvec *v, int low, int high, int (*cmp)(const void *, const void *)) {

    char *base = (char *)v->data;
    size_t size = v->elem_size;

    void *pivot = base + high * size;

    int i = low - 1;

    for (int j = low; j < high; j++) {

        void *elem_j = base + j * size;

        if (cmp(elem_j, pivot) < 0) {
            i++;
            void *elem_i = base + i * size;
            swap(elem_i, elem_j, size);
        }
    }

    void *elem_i1 = base + (i + 1) * size;
    swap(elem_i1, pivot, size);

    return i + 1;
}

void quicksort_rec(dynvec *v, int low, int high, int (*cmp)(const void *, const void *)) {

    if (low < high) {

        int pi = partition(v, low, high, cmp);

        quicksort_rec(v, low, pi - 1, cmp);
        quicksort_rec(v, pi + 1, high, cmp);
    }
}

void quicksort_dynvec(dynvec *v, int (*cmp)(const void *, const void *)){

   if (v->length > 1) {
        quicksort_rec(v, 0, v->length - 1, cmp);
    } 
}

int cmp_lexicografico(const void *a, const void *b){

}

typedef struct {
    
    int x;
    int y;
} Ponto;

typedef struct {
    
    Ponto p1;
    Ponto p2;
} Aresta;

int calcula_det(Ponto A, Ponto B, Ponto P){

}

void processa_regiao(Ponto A, Ponto B, dynvec *candidatos, dynvec *arestas_finais){

}

int main(){

    dynvec *v = dynvec_create(sizeof(Ponto));

    quicksort_dynvec(v, cmp_lexicografico);

    dynvec_free(v);
    return 0;
}
