#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <filesystem>

#define NUM_SAMPLES 10000

using namespace std;
//----------------------------------------------------------------
// Entry point
//----------------------------------------------------------------
int main(void) {
  ifstream file("input.txt");
  if (!file.is_open()) {
    cerr << "Error opening file" << endl;
    return 1;
  }
  ofstream outFile("SOL.txt", ios::app);
  if (!outFile){
    cerr << "Error opening file" << endl;
    return 1;
  }
  for (int i = 0; i < NUM_SAMPLES; i++) {
    // Input
    unordered_set<unsigned int> berry_indices;
    float W;
    unsigned int n;
    if (!(file >> W >> n)) {
      cerr << "Error reading w or n" << endl;
      return 1;
    }
    float happiness[n];
    float weight[n];
    for (unsigned int i = 0; i < n; i++) {
      if (!(file >> happiness[i] >> weight[i])) {
        cerr << "Error reading happiness or weight arrays" << endl;
        return 1;
      }
    }
    // Greedy algorithm
    float sum_s_weight = 0;
    float sum_s_happiness = 0;
    for (int j = 0; j < n; j++) {
      if ( sum_s_weight + weight[j] <= W ) {
        berry_indices.insert(j);
      } else {
        if ( happiness[j] >= sum_s_happiness && weight[j] <= W ) {
          berry_indices.clear();
          berry_indices.insert(j);
          sum_s_happiness = happiness[j];
        }
        break;
      }
      sum_s_weight += weight[j];
      sum_s_happiness += happiness[j];
    }
    // Output
    float SOL = sum_s_happiness;
    outFile << SOL << endl;
  }
  file.close();
  outFile.close();
  return 0;
}