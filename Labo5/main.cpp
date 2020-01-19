/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: stéphane
 *
 * Created on January 10, 2020, 1:57 PM
 */

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <chrono>
#include <list>
#include <unordered_set>
#include "Dictionary.h"

#include "Util.h"
using namespace std;

std::list<string> donnees;

#define DICTIONARY "dictionary.txt"
#define INPUT_FILE "input_wikipedia.txt"
#define USE_TST

int main() {
    lectureDonnees(INPUT_FILE, donnees);
    ofstream myfile;
    myfile.open("correct.txt");

#ifdef USE_TST
    DicoTST dico(DICTIONARY);
#else
    DicoSTL dico(DICTIONARY);
#endif

    list<string> perm;
    for (const string& d : donnees) {
        if (dico.contains(d))
            continue;

        myfile << "*" << d << endl;
        methode1(d, perm);
        for (const string& p : perm) {
            if (dico.contains(p)) {
                myfile << "1:" << p << endl;
            }
        }

        perm.clear();
        methode2(d, perm);
        for (const string& p : perm) {
            if (dico.contains(p)) {
                myfile << "2:" << p << endl;
            }
        }

        perm.clear();
        methode3(d, perm);
        for (const string& p : perm) {
            if (dico.contains(p)) {
                myfile << "3:" << p << endl;
            }
        }

        perm.clear();
        methode4(d, perm);
        for (const string& p : perm) {
            if (dico.contains(p)) {
                myfile << "4:" << p << endl;
            }
        }
    }

    std::cout << "Temps de creation du dico:  " << dico.getCreation() << " microseconds" << std::endl;
    std::cout << "Temps de search du dico:  " << dico.getSearch() << " microseconds" << std::endl;
    return 0;
}

