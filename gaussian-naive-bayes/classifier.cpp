#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>
#include <map>
#include "classifier.h"

using namespace std;

GNB::GNB() {
  // Initializing stats
  for (int i = 0; i < label_names.size(); i++) {
    stats[label_names[i]] = {{0,0}, {0,0}, {0,0}};
  }
}

GNB::~GNB() {}

double GNB::normal_pdf(double v, double m, double s) {
  return 1/sqrt(2*M_PI*pow(s,2))*exp(-pow((v-m),2)/(2*pow(s,2)));
}

void GNB::train(vector<vector<double>> data, vector<string> labels) {
  /*
   *  Refer to https://www.johndcook.com/blog/standard_deviation/
   *  for accurately calculating running mean and variance
   *   Mk = Mk-1+ (xk – Mk-1)/k
   *   Sk = Sk-1 + (xk – Mk-1)*(xk – Mk)
   *
   *  Trains the classifier with N data points and labels.
   *
   *  INPUTS
   *  data - array of N observations
   *    - Each observation is a tuple with 4 values: s, d, s_dot and d_dot.
   *    - Example : [
   *        [3.5, 0.1, 5.9, -0.02],
   *        [8.0, -0.3, 3.0, 2.2],
   *        ...
   *      ]
   *
   *  labels - array of N labels
   *    - Each label is one of "left", "keep", or "right".
   */

  total_samples = data.size();

  for (int i = 0; i < total_samples; i++) {
    vector<double> obs = {fmod(data[i][1],4), data[i][2], data[i][3]};
    string label = labels[i];
    label_counts[label] += 1;

    for (int j = 0; j < obs.size(); j++) {
      double new_mean;
      double new_ms;
      if (label_counts[label] == 1) {
        new_mean = obs[j];
        new_ms = 0;
      } else {
        double mean  = stats[label][j][0];
        double ms  = stats[label][j][1];
        new_mean = mean + (obs[j] - mean) / label_counts[label];
        new_ms = ms + (obs[j] - mean)*(obs[j] - new_mean);
      }

      stats[label][j][0] = new_mean;
      stats[label][j][1] = new_ms;
    }
  }

  for (int i = 0; i < label_names.size(); i++) {
    string label = label_names[i];
    for (int j = 0; j < stats[label].size(); j++) {
      double sig = sqrt((stats[label][j][1] / (label_counts[label] - 1)));
      /* cout << sig << endl; */
      stats[label][j][1] = sig;
    }
  }
}

string GNB::predict(vector<double> sample) {
  /*
   * Once trained, this method is called and expected to return
   * a predicted behavior for the given observation.
   *
   * INPUTS
   * Observation - a 4 tuple with s, d, s_dot, d_dot.
   *  example: [3.5, 0.1, 8.5, -0.2]
   *
   * OUTPUT
   * Label representing the best guess of the classifier.
   * Can be one of "left", "keep" or "right".
   */

  /* vector<double> obs = sample; // {sample[1], sample[2], sample[3]}; */
  vector<double> obs = {fmod(sample[1],4), sample[2], sample[3]};

  // No need to normalize, just picking the top

  double bestProd = 0;
  int bestLabel = 0;

  for (int i = 0; i < label_names.size(); i++) {
    string label = label_names[i];

    double product = 1;
    for (int j = 0; j < obs.size(); j++) {
      product *= normal_pdf(obs[j], stats[label][j][0], stats[label][j][1]);
    }

    if (product > bestProd) {
      bestProd = product;
      bestLabel = i;
    }
  }

  /* cout << label_names[bestLabel] << ": " << sample[1] << "," << sample[2] << "," << sample[3] << endl; */
  return label_names[bestLabel];
}

