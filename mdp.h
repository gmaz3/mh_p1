#ifndef MDP_H
#define MDP_H

#include <set>
#include <vector>

using namespace std;

class maximumDiversityProblem
{
    private:
    //Matriz de distancias
    vector<vector<double>> distances;
    //Tamanio del conjunto de los datos
    int n;
    //Conjunto solucion
    set<int> solution;
    //Numero de elementos que tenemos que escoger del conjunto para generar la solucion
    int m;

    public:
    //Constructor por defecto
    maximumDiversityProblem();

    //Lee los datos del problema
    void readData(string path);


    set<int> findGreedySolution();

    double evaluation();

};

#endif
