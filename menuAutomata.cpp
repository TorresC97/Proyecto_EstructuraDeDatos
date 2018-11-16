#include "automata2.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main(){
    bool x = true;
    string expresion;
    do{
        cout << "Ingrese su expresion" << endl;
        cin >> expresion;
        x=inicio(expresion);
    }while(!x);
    cout << "El resultado es: " <<  evaluar() << endl;
    cout << "Termino"<< endl;
    //system("PAUSE()");
    return 0;
}