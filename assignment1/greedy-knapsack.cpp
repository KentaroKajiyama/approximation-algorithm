#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <filesystem>

using namespace std;
//----------------------------------------------------------------
// Entry point
//----------------------------------------------------------------
int main(void) {
  // Input
  ifstream file("input.txt");
  if (!file.is_open()) {
    cerr << "Error opening file" << endl;
    return 1;
  }
  unordered_set<unsigned int> berry_indices;
  unsigned int n;
  unsigned long W;
  if (!(file >> W >> n)) {
    cerr << "Error reading w or n" << endl;
    return 1;
  }
  unsigned long happiness[n];
  unsigned long weight[n];
  for (unsigned int i = 0; i < n; i++) {
    if (!(file >> happiness[i] >> weight[i])) {
      cerr << "Error reading happiness or weight arrays" << endl;
      return 1;
    }
  }
  file.close();
  // Greedy algorithm
  unsigned long sum_s_weight = 0;
  unsigned long sum_s_happiness = 0;
  for (int j = 0; j < n; j++) {
    if ( sum_s_weight + weight[j] <= W ) {
      berry_indices.insert(j);
    } else {
      if ( happiness[j] >= sum_s_happiness && weight[j] <= W ) {
        berry_indices.clear();
        berry_indices.insert(j);
      }
      break;
    }
    sum_s_weight += weight[j];
    sum_s_happiness += happiness[j];
  }
  // Output
  vector<unsigned int> outputs(berry_indices.begin(), berry_indices.end());
  sort(outputs.begin(), outputs.end());
  cout << "greedy solutions:";
  for (int num: outputs) {
    cout << num << " ";
  }
  cout << endl;

  return 0;
}