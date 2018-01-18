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

    vector<string> label_names = {"left", "keep", "right"};

    double total_samples = 0;

    map<string, double> label_counts = {
      {"left", 0},
      {"keep", 0},
      {"right", 0},
    };

    /*
     * For each class:
     *     s    |    d    |   sdot  |   ddot
     *  {mu, s} | {mu, s} | {mu, s} | {mu, s}
     */
    map<string, vector<vector<double>>> stats;

    GNB();

    virtual ~GNB();

    void train(vector<vector<double> > data, vector<string>  labels);

    double normal_pdf(double v, double mu, double stdd);

    string predict(vector<double>);
};

#endif

