#include <fstream>
#include <iostream>
#include <vector>
#include <random>

#define NUM_SAMPLES 10000
using namespace std;

int partition(vector<int>& happiness, vector<int>& weight, vector<float>& h_w_quotient, int p, int r) {
  float x = h_w_quotient[r];
  int i = p-1;
  for (int j = p; j < r; j++) {
    if (h_w_quotient[j] >= x) {
      i++;
      swap(h_w_quotient[i], h_w_quotient[j]);
      swap(happiness[i], happiness[j]);
      swap(weight[i], weight[j]);
    }
  }
  swap(h_w_quotient[i+1], h_w_quotient[r]);
  swap(happiness[i+1], happiness[r]);
  swap(weight[i+1], weight[r]);
  return i+1;
}

void quick_sort(vector<int>& happiness, vector<int>& weight, vector<float>& h_w_quotient, int p, int r) {
  if (p < r) {
    int q = partition(happiness, weight, h_w_quotient, p, r);
    quick_sort(happiness, weight, h_w_quotient, p, q-1);
    quick_sort(happiness, weight, h_w_quotient, q+1, r);
  }
}

void generate(int W, int n) {
  // vector
  vector<int> happiness;
  vector<int> weight;
  vector<float> h_w_quotient;
  // open output file
  ofstream outFile("input.txt", ios::app);
  if (!outFile) {
    cerr << "Error opening file for output" << endl;
    exit(1);
  }
  // write W and n 
  outFile << W << " " << n << "\n";
  // random number generator setup
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distr(1, 100);
  // for efficiency
  happiness.reserve(n);
  weight.reserve(n);
  h_w_quotient.reserve(n);
  // generate random numbers 
  for (int i=0; i<n; i++) {
    happiness.push_back(distr(gen));
    weight.push_back(distr(gen));
    h_w_quotient.push_back((float)happiness[i]/weight[i]);
  }
  // sorting
  quick_sort(happiness, weight, h_w_quotient, 0, n-1);
  // write to file 
  for (int i=0; i<n; i++) {
    outFile << happiness[i] << " " << weight[i] << "\n";
  }
  outFile.close();
}

int main() {
  // W: the upper bound of the sum of the weights
  // n: the number of strawberries
  // num_samples: the number of samples to be generated
  int W = 250;
  int n = 10;
  for (int i = 0; i < NUM_SAMPLES; i++)
  {
    generate(W,n);
  }
  return 0;
}