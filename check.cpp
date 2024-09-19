#include <bits/stdc++.h>
using namespace std;

bool check(int n)
{
  unordered_set<int> oddNumbers;
  for (int i = 1; i < n; i += 2)
  {
    oddNumbers.insert(i);
  }

  unordered_map<int, int> mp;
  int i = 0;
  mp[0] = 1; // Start with position 0
  int count = 0;

  while (count < n / 2)
  {
    if ((2 * i + 1) <= n - 1)
    {
      i = 2 * i + 1;
    }
    else
    {
      i = 2 * n - (2 * i + 1);
    }

    if (mp.find(i) == mp.end())
    {
      mp[i] = 1;
      count++;
    }
    else
    {
      // cout<<i<<"danger"<<endl;
      return false; // Sequence repeats
    }
    // cout<<i<<endl;
    // Remove the odd number from the set if it is present
    oddNumbers.erase(i);
  }

  // cout << "Size: " << mp.size() << endl;

  // If all odd numbers are covered, it is a maximal length CA
  return oddNumbers.empty();
}
void printInGridAndWriteToFile(const vector<int> &store, int columns, const string &filename)
{
  ofstream outFile(filename);
  if (!outFile)
  {
    cerr << "Error opening file for writing: " << filename << endl;
    return;
  }

  int space = 1;
  for (int j = 0; j < store.size(); j++)
  {
    if (space % columns == 0)
    {
      cout << setw(4) << store[j] << endl;
      outFile << setw(4) << store[j] << endl;
    }
    else
    {
      cout << setw(4) << store[j] << " ";
      outFile << setw(4) << store[j] << " ";
    }
    space++;
  }
  if (space % columns != 1)
  {
    cout << endl; // Ensure the last line ends properly
    outFile << endl;
  }

  outFile.close();
}

int main()
{
  cout << "Enter the maximum limit" << endl;
  int maxi;
  cin >> maxi;
  vector<int> store;
  for (int i = 2; i <= maxi; i += 2)
  {
    if (check(i))
    {
      store.push_back(i);
    }
  }
  cout << "The maximal length CA's are: " << endl;
  cout << "--------------------------------------" << endl;
  string filename;
  cout << "Enter the filename to write the grid: ";
  cin >> filename;

  printInGridAndWriteToFile(store, 10, filename);
  return 0;
}
