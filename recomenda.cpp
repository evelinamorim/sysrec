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

bool compara_sim_usu(sim_usu_t a,sim_usu_t b){
   return (a.sim>b.sim);
}

bool compara_nota_item(nota_item_t a,nota_item_t b){

    return (a.nota>b.nota); 
}

float Recomenda::nota_media(vector<Notas_t> unotas){
    float m = 0.0;
    vector<Notas_t>::iterator it = unotas.begin();
    int nnotas = 0;

    while (it != unotas.end()){
	m += (*it).nota;
	nnotas++;
	it++;
    } 
    return (m/nnotas);
}

void Recomenda::computa_nota_media(unordered_map< unsigned int,vector<Notas_t> > n){

    unordered_map< unsigned int,vector<Notas_t> >::iterator it = n.begin();

    while (it!=n.end()){
	media_lst[it->first] = nota_media(it->second);
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
		sim_num += (n[a][i].nota - media_lst[a])*(n[b][j].nota-media_lst[b]);

	    }

	    //calcular a norma de b soh uma vez
	    if (i == 0){
	       // cout<<n[b][j].nota<<" "<<media_lst[b]<<" "<<j<<" "<<i<<endl;
	       normab +=  (n[b][j].nota-media_lst[b])*(n[b][j].nota-media_lst[b]);
	    }
	}
	//cout<<"--> "<<normab<<" "<<i<<endl;
	normaa += (n[a][i].nota-media_lst[a])*(n[a][i].nota-media_lst[a]);
    }

    //normab com zeros
    //cout<<sim_num<<" "<<normaa<<" "<<normab<<endl;
    return (sim_num/(sqrt(normaa)*sqrt(normab)));
}

void Recomenda::computa_similaridade(unsigned int uid,unordered_map< unsigned int,vector<Notas_t> > n){
    //monta a matriz de similaridade entre usuarios dado um usuario
    unordered_map< unsigned int, vector<Notas_t> >::iterator it = n.begin();

    //memset(items,0,NITEMS*sizeof(int));
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

void Recomenda::computa_nota(unsigned int uid,unordered_map< unsigned int,vector<Notas_t> > n){
    //computa nota de todos os filmes de um dados usuario uid
    //memset(items,0,NITEMS*sizeof(float));
    memset(conta_items,0,NITEMS*sizeof(int));
    memset(soma_media,0,NITEMS*sizeof(float));

    items.clear();

    for (int i=0;i<NITEMS;i++){
	nota_item_t tt;
	tt.item_id = i;
	tt.nota = 0;
	items.push_back(tt);
    }
    //setar os filmes que nao precisam ser preditos
    vector<Notas_t>::iterator it_notas = n[uid].begin();

    while (it_notas!=n[uid].end()){
	items[(*it_notas).item_id].nota = -1;
	it_notas++;
    }

    //percorrer os usuarios dos mais similares aos menos similares
    vector<sim_usu_t>::iterator it_sim = similaridade.begin();

    while(it_sim!=similaridade.end()){
	 int usu = (*it_sim).usu;
         float sim_a_b = (*it_sim).sim;
         vector<Notas_t>::iterator it_usu_sim = n[usu].begin();

	 while (it_usu_sim!=n[usu].end()){
	     int item_usu = (*it_usu_sim).item_id;
	     if (items[item_usu].nota!=-1 && conta_items[item_usu] < K && sim_a_b>0){
		 items[item_usu].nota += sim_a_b*((*it_usu_sim).nota-media_lst[usu]);
		 soma_media[item_usu] += sim_a_b;
		 //tem gente com similaridade negativa entrando...pode?
		 if (item_usu==814)
		    cout<<item_usu<<" "<<items[item_usu].nota<<" "<<sim_a_b<<" "<<((*it_usu_sim).nota-media_lst[usu]) <<" "<<soma_media[item_usu]<<endl;
		 conta_items[item_usu] +=1;
	     }
	     it_usu_sim++;
	 }

	it_sim++;
    }

    for(int i=0;i<NITEMS;i++){
	if (items[i].nota != -1){
	    if (conta_items[i]!=0){
	         items[i].nota = media_lst[uid] + (items[i].nota/soma_media[i]);
	    }else{
	         //caso o filme nao tenha sido rankeado, entao ele recebera a media do usuario como 
	        //predicao
	        items[i].nota = media_lst[uid];
	    }
	}

    }
    //TODO:notas muito altas e baixas???
    sort(items.begin(),items.end(),compara_nota_item);
} 

vector<int> Recomenda::dif_items(unsigned int a,unsigned int b,unordered_map< unsigned int,vector<Notas_t> > n){
    vector<int> i;

    return i;
}

void Recomenda::imprime_predicao(){
    //imprime a predicao de filmes
    for (int i=0;i<NITEMS;i++){
	cout<<items[i].item_id<<" "<<items[i].nota<<endl;
    }
}

void Recomenda::imprime_similaridade(){
    vector<sim_usu_t>::iterator it = similaridade.begin();

    while (it != similaridade.end()){
	cout<<(*it).usu<<" "<<(*it).sim<<endl;
	it++;
    }
}
