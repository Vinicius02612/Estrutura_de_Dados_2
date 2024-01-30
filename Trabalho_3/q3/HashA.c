#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "HashFunc.h"

typedef struct funcionario{
    char *mat;
    char *nome, *funcao;
    float Salario;
}Funcionario;

typedef struct hash{
    int hash,qtd, tamanho;
    Funcionario **Vetor_de_funcs;
}Hash;

//(a) Função Hashing: rotação de 2 dígitos
int funcao_hash_a(char *matricula, int tamanho){

    //rotação de 2 dígitos para a esquerda
    char temp = matricula[tamanho];
    memmove(matricula, matricula + 2, 4);
    matricula[4] = temp;
    matricula[5] = "\0";

    // extrai o 2, 4 e 6 dígitos
    int numero = (matricula[1] - '0') * 100 + (matricula[3] - '0') * 10 + (matricula[5] - '0');

    // resto da divisão pelo tamanho do vetor destino
    int resultado = numero % tamanho;
    return resultado;
    
}

int trata_colisao_a(int hash,char digito){
    int colidiu;
    colidiu = hash + atoi(&digito);
    return colidiu;
}

Hash *cria_tabela_hash(int tamanho){

    Hash *hs = (Hash*)malloc(sizeof(Hash));

    if(hs != NULL){
        int i;
        
        hs->tamanho = tamanho;
        hs->Vetor_de_funcs =(Funcionario**)malloc(tamanho * sizeof(Funcionario*));
        hs->hash = 

        hs->qtd = 0;

        for(i  = 0; i < hs->tamanho; i++){
            hs->Vetor_de_funcs[i] =  NULL;
        }
        
    }
    return hs;
}



int sondagem_linear(int pos, int i, int tamanho){
    /* metodo de espalhamento linear espalha os elementos de forma sequencial */
    return ((pos + i) & 0x7FFFFFFF) % tamanho;
}

int chave_de_divisao(int chave, int tamanho){
    /* 
    Metodo de divisão, consiste em calcular o resto da divisão do valor inteiro que 
    representa a elemento pelo tamanho da tabela

    Ou seja a posição é calculada utlizando uma simples operação  de modulo.

    Como é resto de divisão, valores diferentes podem resultar na mesma posição
    */
    return (chave & 0x7FFFFFFF) % tamanho;
}

int insere_func_hash(Hash *hs, Funcionario fc){
    int status, chave, i, pos, nova_posicao, colidiu = 0;
    if(hs == NULL || hs->qtd == hs->tamanho){
        status = 0;
    }
    
    chave = fc.mat;
    char *toString = atoi(chave);
    pos = funcao_hash_a(toString, hs->tamanho);

    for(i = 0; i < hs->tamanho; i++){
        // usa espalhamento linear em caso de colisão
        nova_posicao = trata_colisao_a(pos,hs->Vetor_de_funcs[i]->mat[0]);
        if(hs->Vetor_de_funcs[nova_posicao] == NULL){
            Funcionario *func = (Funcionario*)malloc(sizeof(Funcionario));
            *func = fc;
            hs->Vetor_de_funcs[nova_posicao] = func;
            hs->qtd += 1;
        }else{
            colidiu += 1;
        }
    }
    return colidiu, status;

}

int busca_hash__func(Hash *hs, int matricula, Funcionario *func){
    int status, chave, i, pos, nova_posicao;
    pos = chave_de_divisao(matricula, hs->tamanho);

    for(i = 0; i < hs->tamanho;i++){
        nova_posicao = sondagem_linear(pos, i, hs->tamanho);
        if(hs->Vetor_de_funcs[nova_posicao] == 0){
            status = 0; // não encontrou ninguem
        }

        if(hs->Vetor_de_funcs[nova_posicao]->mat == matricula){
            *func = *(hs->Vetor_de_funcs[nova_posicao]);
            status = 1;
        }
    }

    return status;
}