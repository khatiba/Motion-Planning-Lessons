#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>
#include <map>
#include "classifier.h"

using namespace std;

GNB::GNB() {
  // Initializing the distributions
  for (int i = 0; i < labels.size(); i++) {
    distributions[labels[i]] = {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}};
  }
}

GNB::~GNB() {}

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

  for (int i = 0; i < data.size(); i++) {
    string label = labels[i];
    vector<double> obs = data[i];

    for (int j = 0; j < distributions[label].size(); j++) {
      float count = distributions[label][j][0] + 1;
      float mean  = distributions[label][j][1];
      float stdd  = distributions[label][j][2];

      float new_mean = mean + (obs[j] - mean) / count;
      float new_stdd = stdd + (obs[j] - mean)*(obs[j] - new_mean);

      distributions[label][j][0] = count;
      distributions[label][j][1] = new_mean;
      distributions[label][j][2] = new_stdd;
    }
  }

}

string GNB::predict(vector<double> sample) {
  /*
     Once trained, this method is called and expected to return
     a predicted behavior for the given observation.

     INPUTS

     observation - a 4 tuple with s, d, s_dot, d_dot.
     - Example: [3.5, 0.1, 8.5, -0.2]

     OUTPUT

     A label representing the best guess of the classifier. Can
     be one of "left", "keep" or "right".
     """
    TODO - complete this
  */

  return labels[1];
}

