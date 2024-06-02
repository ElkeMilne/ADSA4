#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <algorithm>

using namespace std;

static vector<vector<int>> country = {};
static vector<vector<int>> build = {};
static vector<vector<int>> destroyCost = {}; 
static int cost = 0;

vector<int> addToSet(vector<int> set, int num) {
    for (auto value : set) {
        if (num == value) { 
            return set;
        }
    }
    set.push_back(num); 
    return set;
}

int buildToMinST(int n) { 
    vector<tuple<int, int, int>> edges; 
    vector<int> set;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) { 
            edges.push_back(make_tuple(build[i][j], i, j));
        }
    }
    sort(edges.begin(), edges.end());

    int numEdges = 0;
    int index = 0;
    while (numEdges < n - 1 && index < edges.size()) {
        int u = get<1>(edges[index]);
        int v = get<2>(edges[index]);
        if (find(set.begin(), set.end(), u) == set.end() || find(set.begin(), set.end(), v) == set.end()) {
            addToSet(set, u);
            addToSet(set, v);
            cost += get<0>(edges[index]);
            numEdges++;
        }
        index++;
    }
    return cost;
}

int main() {
    string countryString, buildString, destroyString;
    cin >> countryString >> buildString >> destroyString;

    stringstream sc(countryString), sb(buildString), sd(destroyString);
    string token;
    
    while (getline(sc, token, ',')) {
        vector<int> countryRow, buildRow, destroyRow;
        for (int i = 0; i < token.size(); i++) {
            countryRow.push_back(token[i] - '0');
            char b = buildString[i];
            buildRow.push_back(isupper(b) ? b - 'A' : b - 'a' + 26);
            char d = destroyString[i];
            destroyRow.push_back(isupper(d) ? d - 'A' : d - 'a' + 26);
        }
        country.push_back(countryRow);
        build.push_back(buildRow);
        destroyCost.push_back(destroyRow);
    }
    cout << buildToMinST(country.size()) << endl;
    return 0;
}
