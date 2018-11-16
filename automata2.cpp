#include "pila_operadores.cpp"
#include "fila_operandos.cpp"
#include "pila_resultado.cpp"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
using namespace std;

string num = "";
string pru = "";
string expresion;
int cont;

bool numero();
bool variable();
bool operador();
bool signo();
bool error();
bool parentesis();
bool isoper(char car);
void jerarquia(char car);
bool isvar(string var);
bool isnum(string num);
bool isoperad(string oper);
double evaluar();

bool inicio(string exp){
    expresion=exp;
    cont = 0;
    num = "";
    if(isalpha(expresion[cont])){
        variable();
    }
    else if(isdigit(expresion[cont])){
        numero();
    }
    else if(expresion[cont]==43||expresion[cont]==45){// + -
        signo();
    }
    else if (expresion[cont] == 35){ //#
        operador();
    }
    else if(expresion[cont]=40){//(
        parentesis();
    }
    else{
        error();
    }
}

bool numero(){
    num += expresion[cont];
    cont++;
    if(isalpha(expresion[cont])){
        crear_fila(num);
        num = "";
        variable();
    }
    else if(isdigit(expresion[cont])){
        numero();
    }
    else if(isoper(expresion[cont])){
        crear_fila(num);
        num = "";
        operador();
    }
    else if(expresion[cont]==40){
        crear_pila('(');
        expresion[cont]='*';
        crear_fila(num);
        num = "";
        operador();
    }
    else if(expresion[cont]==41){
        crear_fila(num);
        num = "";
        parentesis();
    }
    else if(expresion[cont]=='\0'){
        crear_fila(num);
        num="";
        cout<<"aceptado"<<endl;
        while(!pila_Vacia()){
            pru=cima_pila();
            crear_fila(pru);
            pop();
        }
        return true;
    }
    else{
        error();
    }

}

bool variable(){
    crear_fila(expresion[cont]+"\0");
    cont++;
    if(isalpha(expresion[cont])){
        variable();
    }
    else if(isdigit(expresion[cont])){
        numero();
    }
    else if(isoper(expresion[cont])){
        operador();
    }
    else if(expresion[cont]==40){//este convertiria el parentesis en una multiplicacion
        expresion[cont]='*';
        operador();
    }
    else if (expresion[cont] == 41){
        parentesis();
    }
    else if(expresion[cont]=='\0'){
        cout<<"aceptado"<<endl;
        while(!pila_Vacia()){
            pru=cima_pila();
            crear_fila(pru);
            pop();
        }
        return true;
    }
    else{
        error();
    }
}

bool operador(){
    jerarquia(expresion[cont]);
    cont++;
    if(isalpha(expresion[cont]))
        variable();
    else if(isdigit(expresion[cont]))
        numero();
    else if(expresion[cont]=='+'&&expresion[cont-1]=='#')
        signo();
    else if((expresion[cont]=='+'||expresion[cont]=='-')&&(expresion[cont-1]=='^'))
        signo();
    else if(expresion[cont]==40)
        parentesis();
    else if(expresion[cont]==35)
        operador();    
    else
        error();
}

bool signo(){
    if(expresion[cont]==43||expresion[cont]==45||expresion[cont]==35){
        if(isdigit(expresion[cont+1])){
            numero();
        }
        else if(isalpha(expresion[cont+1])){
            variable();
        }
        else{
            error();
        }
    }
    else{
        error();
    }
}

bool parentesis(){
    if(expresion[cont]==40){
        crear_pila(expresion[cont]);
        cont++;
        if(expresion[cont]=='+'||expresion[cont]=='-')
            signo();
        else if(isalpha(expresion[cont]))
            variable();
        else if(isdigit(expresion[cont]))
            numero();
        else if(expresion[cont]==35)
            operador();
        else if(expresion[cont]==40)
            parentesis();
        else
            error();
    }
    else if(expresion[cont]==41){
        while(cima_pila()!=40){
            pru = cima_pila();
            crear_fila(pru);
            pop();
        }
        pop();
        cont++;
        if (isalpha(expresion[cont]))
            variable();
        else if (isdigit(expresion[cont]))
            numero();
        else if (isoper(expresion[cont]))
            operador();
        else if(expresion[cont]=='\0'){
            cout << "Aceptado" << endl;
            while (!pila_Vacia())
            {
                pru = cima_pila();
                crear_fila(pru);
                pop();
            }
            //vaciar_fila();
            return true;
        }
        else
            error();
    }
    else{
        error();
    }
    
}

bool error(){
    cout<<"erronea"<<endl;
    while(!pila_Vacia()){
        pru=cima_pila();
        crear_fila(pru);
        pop();
    }
    vaciar_fila();
    return false;
}

bool isoper(char car)
{
    if (car == '+' || car == '-' || car == '*' || car == '/' || car == '^' || car == '#')
    {
        return true;
    }
    else
    {
        return false;
    }
}

void jerarquia(char car){
    if(pila_Vacia()){
        crear_pila(car);
    }
    else if((car=='+'||car=='-')&&(cima_pila()=='*'||cima_pila()=='/'||cima_pila()=='^'||cima_pila()=='#')){
        pru=cima_pila();
        crear_fila(pru);
        pop();
        crear_pila(car);
    }
    else if ((car == '*' || car == '/') && (cima_pila() == '^' || cima_pila() == '#')){
        pru = cima_pila();
        crear_fila(pru);
        pop();
        crear_pila(car);
    }
    else{
        crear_pila(car);
    }
}

double evaluar(){
    if (!fila_vacia()){
        if (isvar(cima_fila())){
            crear_res(stof(cima_fila()));
            desencolar();
            evaluar();
        }
        else if (isoperad(cima_fila())){
            char ayu=cima_fila()[0];
            switch (ayu){
                case '+':{
                    double op1 = cimaRes->result;
                    pop_res();
                    double op2 = cimaRes->result;
                    pop_res();
                    double resulta = op1 + op2;
                    crear_res(resulta);
                    break;
                }
                case '-':{
                    double op1 = cimaRes->result;
                    pop_res();
                    double op2 = cimaRes->result;
                    pop_res();
                    double resulta = op2 - op1;
                    crear_res(resulta);
                    break;
                }
                case '*':
                {
                    double op1 = cimaRes->result;
                    pop_res();
                    double op2 = cimaRes->result;
                    pop_res();
                    double resulta = op1 * op2;
                    crear_res(resulta);
                    break;
                }
                case '/':
                {
                    double op1 = cimaRes->result;
                    pop_res();
                    double op2 = cimaRes->result;
                    pop_res();
                    double resulta = op2 / op1;
                    crear_res(resulta);
                    break;
                }
                case '#':
                {
                    double op1 = cimaRes->result;
                    pop_res();
                    double resulta = sqrt(op1);
                    crear_res(resulta);
                    break;
                }
                case '^':
                {
                    double op1 = cimaRes->result;
                    pop_res();
                    double op2 = cimaRes->result;
                    pop_res();
                    double resulta =pow(op2,op1);
                    crear_res(resulta);
                    break;
                }
            }
            desencolar();
            evaluar();
        }
        else if (isnum(cima_fila())){
            crear_res(stof(cima_fila()));
            desencolar();
            evaluar();
        }
        else
        {
            cout << "Cometio Error" << endl;
        }
        return cimaRes->result;
    }
    else
    {
        //cout << "pila Vacia, Termino de Evaluar" << endl;
    }
}

bool isvar(string var)
{
    for (int i = 0; i < var.size(); i++)
    {
        if ((var[i] < 91 && var[i] > 65) || (var[i] < 123 && var[i] > 96)){}
        else
        {
            return false;
        }
    }
    return true;
}

bool isnum(string num){
    for (int i = 0; i < num.size(); i++){
        if ((num[i] > 47 && num[i] < 58)||num[i]==43||num[i]==45){}
        else
        {
            return false;
        }
    }
    return true;
}

bool isoperad(string oper){
    for (int i = 0; i < oper.size(); i++){
        if (oper[i] == '+' || oper[i] == '-' || oper[i] == '*' || oper[i] == '/' || oper[i] == '^' || oper[i] == '#'){}
        else
        {
            return false;
        }
    }
    return true;
}