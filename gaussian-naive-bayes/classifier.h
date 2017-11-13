#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>
#include <map>

using namespace std;

class GNB {
  public:

    vector<string> labels = {"left", "keep", "right"};

    /*
     * For each class:
     *       s       |      d       |    sdot      |    ddot
     *  {#, mu, sig} | {#, mu, sig} | {#, mu, sig} | {#, mu, sig}
     */
    map<string, vector<vector<float>>> distributions;

    GNB();

    virtual ~GNB();

    void train(vector<vector<double> > data, vector<string>  labels);

    string predict(vector<double>);
};

#endif

