#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

struct fila_Operandos{
    string operando;
    fila_Operandos *next;
};

struct fila_Operandos *front=NULL;
struct fila_Operandos *back=NULL;

bool fila_vacia(){
    if(front==NULL)
        return true;
    else
        return false;
}

void encolar(struct fila_Operandos *nuevo){
    if(fila_vacia()){
        front=nuevo;
        back=nuevo;
    }
    else{
        back->next=nuevo;
        back=nuevo;
    }
}

void crear_fila(string elemento){
    struct fila_Operandos *nuevo = new(fila_Operandos);
    nuevo->operando=elemento;
    nuevo->next = NULL;
    encolar(nuevo);
}

void desencolar(){
    if(fila_vacia()){
        cout << "FILA VACIA" << endl;
    }
    else{
        struct fila_Operandos *aux=new(fila_Operandos);
        aux=front;
        front=front->next;
        delete(aux);
    }
}

void vaciar_fila(){
    if(fila_vacia()){
        cout << "ERROR, fila Vacia" << endl;
    }
    else{
        while(!fila_vacia()){
            cout << front->operando;
            desencolar();
        }
        cout << "\n" << endl;
    }
}

string cima_fila(){
    return front->operando;
}