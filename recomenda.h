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

using namespace std;

#ifndef __RECOMENDA_H_
#define __RECOMENDA_H_

class Recomenda{
    //matriz de similaridade entre usuarios
    vector< vector<float> > similaridade; 
    vector<float> nota_media;
    public:
	float nota_media(vector<Notas_t> unotas);
	float pearson(vector<Notas_t> a,vector<Notas_t> b);
};

#endif

