#include <iostream>
#include <cstring>
#include "Pilha.h"

using namespace std;

// Função para validar uma expressão matemática
bool validarExpressao(char* expressao) {
    // Cria uma pilha vazia
    Pilha_Construtor();

    for (int i = 0; i < strlen(expressao); i++) {
        char caractere = expressao[i];

        // Se encontrar um caractere de abertura, empilha-o
        if (caractere == '(' || caractere == '[') {
            Pilha_Empilhar(caractere);
        } 
        // Se encontrar um caractere de fechamento, verifica se a pilha está vazia ou se o topo da pilha não combina
        else if (caractere == ')' || caractere == ']') {
            if (Pilha_Vazia()) {
                Pilha_Destrutor();
                return false;
            }

            TipoDado topo;
            if (!Pilha_Topo(topo)) {
                Pilha_Destrutor();
                return false;
            }

            // Verifica se o caractere de fechamento combina com o caractere de abertura no topo da pilha
            if ((caractere == ')' && topo != '(') || (caractere == ']' && topo != '[')) {
                Pilha_Destrutor();
                return false;
            }

            // Desempilha o caractere de abertura
            Pilha_Desempilhar(topo);
        }
    }

    // Verifica se a pilha está vazia ao final da expressão
    bool resultado = Pilha_Vazia();
    Pilha_Destrutor();
    return resultado;
}

int main() {
    char expressao[100];
    cout << "Digite uma expressao matematica: ";
    cin.getline(expressao, 100);

    if (validarExpressao(expressao)) {
        cout << "A expressao eh valida." << endl;
    } else {
        cout << "A expressao nao eh valida." << endl;
    }

    return 0;
}

#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

typedef char TipoDado;

// Estrutura de dados para uma célula da pilha
struct TipoCelula {
    TipoDado Item;
    TipoCelula* Prox;
};

// Funções para operações de pilha
void Pilha_Construtor();
void Pilha_Destrutor();
bool Pilha_Vazia();
int Pilha_Tamanho();
bool Pilha_Empilhar(TipoDado Elemento);
bool Pilha_Desempilhar(TipoDado& Elemento);
bool Pilha_Topo(TipoDado& Elemento);

#endif // PILHA_H_INCLUDED

// Pilha.cpp
#include "Pilha.h"

// Ponteiro para o topo da pilha
TipoCelula* Topo = nullptr;
int Contador = 0;

// Construtor da pilha
void Pilha_Construtor() {
    Topo = nullptr;
    Contador = 0;
}

// Destrutor da pilha
void Pilha_Destrutor() {
    while (Topo != nullptr) {
        TipoCelula* Temp = Topo;
        Topo = Topo->Prox;
        free(Temp);
    }
    Contador = 0;
}

// Verifica se a pilha está vazia
bool Pilha_Vazia() {
    return Topo == nullptr;
}

// Retorna o tamanho da pilha
int Pilha_Tamanho() {
    return Contador;
}

// Empilha um elemento
bool Pilha_Empilhar(TipoDado Elemento) {
    TipoCelula* Nova = (TipoCelula*) malloc(sizeof(TipoCelula));
    if (Nova == nullptr) {
        return false;
    }
    Nova->Item = Elemento;
    Nova->Prox = Topo;
    Topo = Nova;
    Contador++;
    return true;
}

// Desempilha um elemento
bool Pilha_Desempilhar(TipoDado& Elemento) {
    if (Pilha_Vazia()) {
        return false;
    }
    TipoCelula* Temp = Topo;
    Topo = Topo->Prox;
    Elemento = Temp->Item;
    free(Temp);
    Contador--;
    return true;
}

// Retorna o elemento no topo da pilha
bool Pilha_Topo(TipoDado& Elemento) {
    if (Pilha_Vazia()) {
        return false;
    }
    Elemento = Topo->Item;
    return true;
}