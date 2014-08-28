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

float Recomenda::pearson(vector<Notas_t> a,vector<Notas_t> b){

}


