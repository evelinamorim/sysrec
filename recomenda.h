/*
 * =====================================================================================
 *
 *       Filename:  recomenda.h
 *
 *    Description:  arquivo de classes  com a organizacao para o algoritmo preditor 
 *    de notas para filme
 *
 *        Version:  1.0
 *        Created:  08/25/14 19:39:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "le.h"
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

#ifndef __RECOMENDA_H_
#define __RECOMENDA_H_

//constante que define o numero de usuarios que comporao a predicao dos filmes
#define K 5
//numero de itens na base, assumindo que existem tbm ids menores ou iguais a esta qtd
#define NITEMS 1682

typedef struct sim_usu{
    unsigned int usu;
    float sim;
}sim_usu_t;

typedef struct nota_item{
    float nota;
    int item_id;
}nota_item_t;


class Recomenda{
    //similaridades de um usuario corrente em relacao a todos os outros
    vector<sim_usu_t> similaridade; 
    unordered_map<unsigned int, float> media_lst;
    vector<nota_item_t> items;
    int conta_items[NITEMS];
    float soma_media[NITEMS];

    public:
	float nota_media(vector<Notas_t> unotas);
	void  computa_nota_media(unordered_map< unsigned int,vector<Notas_t> > n);
        float pearson(unsigned int a,unsigned int b,unordered_map< unsigned int,vector<Notas_t> > n);
        void computa_similaridade(unsigned int uid,unordered_map< unsigned int,vector<Notas_t> > n);
	vector<int> dif_items(unsigned int a,unsigned int b,unordered_map< unsigned int,vector<Notas_t> > n);
        void computa_nota(unsigned int uid,unordered_map< unsigned int,vector<Notas_t> > n);

	//funcoes de teste
	void imprime_similaridade();
        void imprime_predicao();
};

#endif

