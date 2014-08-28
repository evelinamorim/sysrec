/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  metodo main  para a tarefa de programacao 
 *
 *        Version:  1.0
 *        Created:  08/22/14 10:18:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include "le.h"

using namespace std;

int main(int argc,char** argv){
    string arquivoUsuario = argv[1];
    string arquivoItem = argv[2];
    string arquivoNotas = argv[3];

    if (argc != 4){
	cout<<"*** Error *** Wrong Number of Arguments "<<endl;
	cout<<"Usage: ./tp1 userfilename itemfilename ratingfilename"<<endl;
	return -1;
	    
    }
    Le leObj(arquivoUsuario,arquivoItem,arquivoNotas); 
    vector<unsigned int> u,i;
    //vale a pena fazer o indice filmes->usuarios?
    //Como percorrer usuario por usuario e comparando cada um?
    //Nearest neighboor
    unordered_map< unsigned int,vector<Notas_t> > n;
    leObj.le_tudo(u,i,n);

    //TESTES
    //leObj.imprime_notas(n);
    //leObj.imprime_usuarios(u);
    //leObj.imprime_itens(i);

    //cout<<arquivoUsuario<<" "<<arquivoItem<<" "<<arquivoNotas<<endl;
    return 0;
}


