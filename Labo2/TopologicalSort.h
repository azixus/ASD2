/*
 * File:   TopologicalSort.h
 * Author: Olivier Cuisenaire
 *
 * Created on 08. octobre 2014, 14:07
 *
 * A implementer
 * Classe permettant le tri topologique d'un graphe oriente
 */

#ifndef ASD2_TopologicalSort_h
#define ASD2_TopologicalSort_h

#include "DirectedCycle.h"
#include "ParcoursEnProfondeur.h"
#include <list>
#include <vector>
#include <exception>
#include <algorithm>

template < typename GraphType >
class TopologicalSort {
private:
	/* A DEFINIR */
	std::vector<int> topologie;

public:
    //constructeur
    TopologicalSort(const GraphType & g) {
        /* vous devez verifier la presence d'un cycle, auquel cas il faut lancer une  GraphNotDAGException*/
        DirectedCycle<GraphType> dc(g);

        if (dc.HasCycle())
            throw GraphNotDAGException(dc.Cycle());

        DFS<GraphType> dfs(g);

        dfs.visitGraph([] (int){}, [this](int v) { this->topologie.push_back(v); });
        
	std::reverse(topologie.begin(), topologie.end());
    }
    
    //tableau contenant l'ordre de parcours des indexes des sommets dans le graphe
    const std::vector<int>& Order() {
        /* A IMPLEMENTER */
        //return ...
        return topologie;
    }
    
    //exception si le graphe n'est pas un DAG (Directed Acyclic Graph)
    class GraphNotDAGException : public std::exception {
        
    private:
        //indexes des sommets du cycle qui empeche le tris topologique
        const std::list<int> cycle;
        
    public:
        GraphNotDAGException(const std::list<int> cycle) noexcept : exception(), cycle(cycle) {
            
        }
        
        virtual const char* what() const noexcept {
            return "Topological sort impossible : the graph is not a DAG";
        }
        
        const std::list<int>& Cycle() const noexcept {
            return cycle;
        }
    };
};


#endif
