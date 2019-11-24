/* 
 * File:   DiGraph.h
 * Author: Cuisenaire
 *
 * Created on 7. octobre 2014, 16:54
 * 
 * Implementation d'un graphe oriente par liste d'adjacence
 */

#ifndef TRAINGRAPHWRAPPER_H
#define	TRAINGRAPHWRAPPER

#include "TrainNetwork.h"
#include "EdgeWeightedGraphCommon.h"
#include "EdgeWeightedGraph.h"

class TrainGraphWrapper{
private:
    const TrainNetwork* tn;
    const std::function<int(TrainNetwork::Line)> weigthFunc;
    
public:  
    //Définition du type des arrête(Edge) ici elles seront de type WeightedEdge
    typedef WeightedEdge<int> Edge;
    /**
     * Contructeur de la classe TrainGraphWrapper
     * @param tn variable de type TrainNetwork étant le réseau ferroviaire pour lequel crée un graphe
     * @param weigthFunc fonction permettant de définir le poids des arêtes du graphe
     */
    TrainGraphWrapper(const TrainNetwork& tn, std::function<int(TrainNetwork::Line)> weigthFunc) : tn(&tn), weigthFunc(weigthFunc) {}
    /**
     * Renvoie la taille du graphe du réseau ferroviaire
     * @return un entier étant le nombre de sommet du graphe
     */
    int V() const{ 
        return tn->cities.size(); 
    }
    /**
     * Permet d'appliquer une fonction sur chaque arrête du graphe
     * @param f la function à appliquer à toutes les arrêtes 
     */
    template <typename Func>
    void forEachEdge(Func f) const{
        for(TrainNetwork::Line l : tn->lines){
            int weight = weigthFunc(l);
            Edge edge(l.cities.first, l.cities.second, weight);
            f(edge);
        }
    }
    /**
     * Permet d'appliquer une fonction sur chaque arrête adjacente du graphe 
     * @param v entier répresentant le sommet auquel le parcours des ses adjacents est effectué
     * @param f la function à appliquer à toutes les arrêtes 
     */
    template <typename Func>
    void forEachAdjacentEdge(int v, Func f) const{
        int weight = 0;       
        for(int i : tn->cities.at(v).lines){
            TrainNetwork::Line l = tn->lines.at(i);
            weight = weigthFunc(l);
            Edge edge(l.cities.first, l.cities.second, weight);
            f(edge);
        }
    }
};

#endif	/* DIGRAPH_H */
