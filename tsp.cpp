#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_map>
#include <algorithm>


using namespace std;



void minimumPath(vector<vector<int>> adjacency, unordered_map<int, string>edgeCity, vector<int> costOf);

void find_combinations(vector<int> a, int n, vector<vector<int>> &combinations);


int main() {
  int vertices, edgeCities, cost, firstCost, lastCost;
  string cities, beginHere, endHere;
  unordered_map<string, int>cityEdge;
  unordered_map<int, string>edgeCity;
  vector<int>costOf;


  // Take in cities
  cin >> vertices;
  for (int i = 0; i<vertices; i++) {
    cin >> cities;
    cityEdge[cities] = i;
    edgeCity[i] = cities;
    if (i != 0) {
      costOf.push_back(i);
    }
  }

  //Create a vector of vectors for adjacency list
  vector<vector<int>>adjacency(vertices);
  for (auto it = adjacency.begin(); it < adjacency.end(); it++) {
    *it = vector<int>(vertices);
    fill(it->begin(), it->end(), -1);
  }

  // Create the adjacency list
  for (int k = 0; k<vertices; k++) {
    adjacency[k][k] = -1;
  }

  // get the edge cost in the right position
  cin >> edgeCities;
  for (int k = 0; k<edgeCities; k++) {
    cin >> beginHere;
    cin >> endHere;
    cin >> cost;

    firstCost = cityEdge[beginHere];
    lastCost = cityEdge[endHere];

    adjacency[firstCost][lastCost] = cost;
  }

  // Look for the minimum path
  minimumPath(adjacency, edgeCity, costOf);
}
void minimumPath(vector<vector<int>> adjacency, unordered_map<int, string> edgeCity, vector<int> costOf) {

  vector<vector<int>>combinations;
  vector<int>quickest(costOf.size());
  int costLess, sum, cityBefore, count;
  bool legit;

  // Get all possible combinations
  find_combinations(costOf, costOf.size(), combinations);


  // Find the minimum traversal cost.
  costLess = -1;
  // Going through each permutation
  for (auto cities = combinations.begin(); cities < combinations.end(); cities++) {
    legit = true;
    sum = 0;
    // Check each city and see if it has a path to the city before it
    for (auto myLocation = cities->begin(); myLocation < cities->end()-1; myLocation ++) {
      // For paths that do not exist
      if (adjacency[*myLocation][*(myLocation+1)] == -1) {
        legit = false;
        break;
      }
      // Get the path sum
      else {
        sum += adjacency[*myLocation][*(myLocation+1)];
      }
    }
    // If a valid path has been found and sum is smaller than the costLess, set sum to costLess.
    if (legit) {
      if (sum < costLess || costLess == -1) {
        quickest = *cities;
        costLess = sum;
      }
    }
  }

  if (costLess == -1) {
    cout << "Path:" << endl;
    cout << "Cost:-1" << endl;
  }
  else {
    // When the shortest path is found, state it
    cout << "Path:";
    for (auto locateCity = quickest.begin(); locateCity < quickest.end(); locateCity++) {
      cout << edgeCity[*locateCity];
      if (locateCity != quickest.end()-1) {
        cout << "->";
      }
    }
    cout << endl;
    cout << "Cost:" << costLess << endl;
  }
}

void add(vector<int> a, int n, vector<vector<int>> &combinations)
{
  // Since you have to start and end with the same city, insert the first city (0) into the beginning and end of the vector.
  a.insert(a.begin(), 0);
  a.push_back(0);

  // Add the permutation to the vector of combinations.
  combinations.push_back(a);
}

// Function to find the combinations
void find_combinations(vector<int> a, int n, vector<vector<int>> &combinations)
{
    //sort the array
    sort(a.begin(), a.end());

    // Look for the combinations
    do
    {
      add(a, n, combinations);
    } while (next_permutation(a.begin(), a.end()));
}