#include <fstream>
#include <vector>
#include <iostream>
#include <unordered_set>

#define NUM_SAMPLES 10000
using namespace std;
// Supposed that weights are real numbers, I don't use dynamic programming solution here.
float opt_knapsack(vector<float>& happiness, vector<float>& weight, float W, int index) {
  if( W <= 0 || index < 0 ) {
    return 0;
  } else {
    float index_included_sol = 0;
    float index_excluded_sol = 0;
    if( weight[index] <= W ){
      index_included_sol = opt_knapsack(happiness, weight, W-weight[index], index-1) + happiness[index];
    }
    index_excluded_sol = opt_knapsack(happiness, weight, W, index-1);
    return max(index_included_sol, index_excluded_sol);
  }
}

int main() {
  ifstream file("input.txt");
  if (!file.is_open()) {
    cerr << "Error opening file" << endl;
    return 1;
  }
  ofstream outFile("OPT.txt", ios::app);
  if (!outFile) {
    cerr << "Error opening output file" << endl;
    return 1;
  }
  for (int i = 0; i < NUM_SAMPLES; i++) {
    // input
    float W;
    unsigned int n;
    if (!(file >> W >> n)){
      cerr << "Error reading file" << endl;
      return 1;
    }
    vector<float> happiness(n);
    vector<float> weight(n);
    for (unsigned int i = 0; i < n; i++) {
      if(!(file >> happiness[i] >> weight[i])){
        cerr << "Error reading values of happiness or weight" << endl;
        return 1;
      }
    }
    float OPT = opt_knapsack(happiness, weight, W, n-1);
    // output
    outFile << OPT << "\n";
  }
  file.close();
  outFile.close();
  return 0;
}