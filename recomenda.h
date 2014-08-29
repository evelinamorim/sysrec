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
//numero de itens na base
#define NITENS 1682

typedef struct sim_usu{
    unsigned int usu;
    float sim;
}sim_usu_t;

bool compara_sim_usu(sim_usu_t a,sim_usu_t b){
   return (a.sim<b.sim);
}

class Recomenda{
    //similaridades de um usuario corrente em relacao a todos os outros
    vector<sim_usu> similaridade; 
    unordered_map<unsigned int, float> media_lst;
    int items[NITENS];

    public:
	float nota_media(vector<Notas_t> unotas);
	void  computa_nota_media(unordered_map< unsigned int,vector<Notas_t> > n);
        float pearson(unsigned int a,unsigned int b,unordered_map< unsigned int,vector<Notas_t> > n);
        void computa_similaridade(unsigned int uid,unordered_map< unsigned int,vector<Notas_t> > n);
	vector<int> dif_items(unsigned int a,unsigned int b,unordered_map< unsigned int,vector<Notas_t> > n);
};

#endif

