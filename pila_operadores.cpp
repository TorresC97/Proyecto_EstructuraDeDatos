#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

struct pila_Operador{
    char operador;
    pila_Operador *next;
};

struct pila_Operador *top=NULL;

bool pila_Vacia(){
    if(top==NULL)
        return true;
    else
        return false;
}

void push(pila_Operador *nuevo){
    if(pila_Vacia()){
        top=nuevo;
    }
    else{
        nuevo->next=top;
        top=nuevo;
    }
}

void crear_pila(char elemento){
    struct pila_Operador *nuevo = new(pila_Operador);
    nuevo->operador = elemento;
    nuevo->next=NULL;
    push(nuevo);
}

void pop(){
    if(pila_Vacia()){
        cout << "PILA VACIA" << endl;
    }
    else{
        struct pila_Operador *aux = new(pila_Operador);
        aux=top;
        top=top->next;
        delete(aux);
    }
}

char cima_pila(){
    return top->operador;
}