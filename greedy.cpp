#include <iostream>
#include <fstream>
#include <set>
#include <vector>

#include "mdp.h"

#define MAX 100000

using namespace std;

int main()
{
    cout << "Test para greedy\n" << endl;

    maximumDiversityProblem gd;

    gd.readData("datos/MDG-a_1_n500_m50.txt");
    // gd.readData("datos/matrix.txt");

    auto sol = gd.findGreedySolution();

    auto it = sol.begin();

    cout << "La solucion tiene valor de: " << gd.evaluation() << endl;

    for(it; it!=sol.end(); it++){
        cout << *it + 1 << endl;
    }

    return 0;
}


maximumDiversityProblem::maximumDiversityProblem():n(0), m(0)
{
}

void maximumDiversityProblem::readData(string path)
{
    ifstream file;
    file.open(path);

    //Leemos el numero de filas y columnas
    file >> n >> m;

    //Inicializamos la matriz a 0
    distances.resize(n);

    int zeros[n] = {0};

    for(int i=0; i < n; i++){
        distances[i] = vector<double>(zeros,zeros+n);
    }

    //Leemos el fichero completo e introducimos los valores a la matriz
    int i, j;
    double value;

    while(!file.eof()){
      file >> i >> j >> value;
      distances[i][j] = value;
      distances[j][i] = value; // Matriz simetrica pq es mas sencillo medir distancias
    }

    // //Mostrar matriz de distancias
    // for(int i=0; i<distances.size(); i++){
    //   for(int j=0; j<distances.size(); j++){
    //     cout << distances[i][j] << "\t";
    //   }
    //   cout << endl;
    // }
    //   cout << endl;

    file.close();
}

set<int> maximumDiversityProblem::findGreedySolution()
{
  if(!distances.empty()){
      double max_cum_dist = 0;
      int item_idx = -1;

      //Seleccionamos el elemento mas alejado del resto.
      //Para cada elemento elemento
      for(int i=0; i<n; i++){
          double cum_distance = 0;
          //Calculamos la distancia acumulada
          for(int j=0; j<n; j++){
              cum_distance += distances[i][j];
          }

          if(cum_distance > max_cum_dist){
              max_cum_dist = cum_distance;
              item_idx = i;
          }
      }

      solution.insert(item_idx);
      // cout << item_idx + 1 << endl;

      //Mientras la solucion no este completa
      while(solution.size() < m){
          item_idx = -1;
          double max_dist = -1;

          //Recorremos todos los elementos del conjunto principal
          for(int i = 0; i<n; i++){
              double distance = MAX;
              //Si i no esta en seleccionados
              if(solution.find(i) == solution.end()){
                  auto it = solution.begin();
                  //Nos quedamos con la distancia mas pequena de i a los elementos de seleccionados
                  for(it; it!=solution.end(); it++){
                      if(distances[i][*it] < distance){
                          distance = distances[i][*it];
                      }
                  }

                  //Si la distancia de este elemento es mayor que el maximo actual
                  if(distance > max_dist){
                      max_dist = distance;
                      item_idx = i;
                  }
              }
          }

          //Al final insertamos el de mayor distancia acumulada
          solution.insert(item_idx);
          // cout << item_idx + 1 << endl;

      }

  }else{
    cout << "Error: Se deben leer antes las distancias" << endl;
  }

  return solution;
}

double maximumDiversityProblem::evaluation()
{
    double value = -1;
    //Si hemos generado la solucion
    if(solution.size() == m){
        set<int>::iterator it = solution.begin();
        auto end = prev(solution.end(),1);
        value = 0;

        for(it; it != end; it++){
            auto sub_it = next(it,1);
            for(sub_it; sub_it != solution.end(); sub_it++){
                value += distances[*it][*sub_it];
            }
        }
    }

    return value;
}
