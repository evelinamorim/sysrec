/*
 * =====================================================================================
 *
 *       Filename:  recomenda.cpp
 *
 *    Description:  este arquivo contem o algorithmo que predita a nota de um dado filme 
 *    de um dado usuario
 *
 *        Version:  1.0
 *        Created:  08/25/14 19:38:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "recomenda.h"

float Recomenda::nota_media(vector<Notas_t> unotas){
    float m = 0.0;
    vector<Notas_t>::iterator it = unotas.begin();
    int nnotas = 0;

    while (it != unotas){
	m += (*it).nota;
	nnotas++;
	it++;
    } 
    return (m/nnotas);
}

void Recomenda::computa_nota_media(unordered_map< unsigned int,vector<Notas_t> > n){

    unordered_map< unsigned int,vector<Notas_t> >::iterator it = n.begin();

    while (it!=n.end()){
	s_usu[it->fisrt].media = nota_media(it->second);
	it++;
    }
}

float Recomenda::pearson(unsigned int a,unsigned int b,unordered_map< unsigned int,vector<Notas_t> > n){
    // compararar usuario a e b
    int na = n[a].size();
    int nb = n[b].size();
    float sim = 0.0;
    float sim_num = 0.0;
    float normab = 0.0;
    float normaa = 0.0;

    for (int i = 0;i<na;i++){
	for (int j = 0;j<nb;j++){
	    if (n[a][i].item_id == n[b][j].item_id){
		sim_num += (n[a][i].nota - media_lst[a])*(n[b][j]-media_lst[b])

	        //calcular a norma de b soh uma vez
	        if (i == 0){
		   normab +=  (n[b][j]-media_lst[b])*(n[b][j]-media_lst[b]);
	        }
	    }
	}
	normaa += (n[a][i]-media_lst[a])*(n[a][j]-media_lst[a]);
    }


    return (sim_num/(sqrt(normaa)*sqrt(normab)))
}

void Recomenda::computa_similaridade(unsigned int uid,unordered_map< unsigned int,vector<Notas_t> > n){
    //monta a matriz de similaridade entre usuarios dado um usuario
    unordered_map< unsigned int, vector<Notas_t> >::iterator it = n.begin();

    memset(items,0,NITENS*sizeof(int));
    similaridade.clear();

    while (it!=n.end()){
	if (it->first!=uid){
	    //TODO: evitar recalcular, como?
	    sim_usu_t x;
	    x.usu = it->first;
	    x.sim = pearson(uid,it->first,n);
	    similaridade.push_back(x);
	}
	it++;
    }
    //ordenar por similaridade
    sort(similaridade.begin(),similaridade.end(),compara_sim_usu);
}

vector<int> dif_items(unsigned int a,unsigned int b,unordered_map< unsigned int,vector<Notas_t> > n){
    vector<int> i;

    return i;
}
