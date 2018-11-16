#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

struct resultado{
    double result;
    resultado *next;
};

struct resultado *cimaRes=NULL;

bool pilaRes_vacia(){
    if (cimaRes == NULL)
        return true;
    else
        return false;
}

void push_res(struct resultado *nuevo){
    if (pilaRes_vacia()){
        cimaRes = nuevo;
    }
    else{
        nuevo->next = cimaRes;
        cimaRes = nuevo;
    }
}

void crear_res(double elemento){
    struct resultado *nuevo = new(resultado);
    nuevo->result=elemento;
    nuevo->next=NULL;
    push_res(nuevo);
}

void pop_res(){
    if (pilaRes_vacia()){
        cout << "PILA VACIA" << endl;
    }
    else{
        struct resultado *aux = new(resultado);
        aux = cimaRes;
        cimaRes = cimaRes->next;
        delete (aux);
    }
}

