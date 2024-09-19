#include <bits/stdc++.h>

using namespace std;

// Function to multiply two polynomials in GF(2)
vector<double> multiplyPolynomials(const vector<double> &poly1, const vector<double> &poly2)
{
  vector<double> result(poly1.size() + poly2.size() - 1, 0);
  for (size_t i = 0; i < poly1.size(); ++i)
  {
    for (size_t j = 0; j < poly2.size(); ++j)
    {
      result[i + j] += poly1[i] * poly2[j];
      result[i + j] = fmod(result[i + j], 2); // Reduce coefficient modulo 2
    }
  }
  return result;
}

// Function to add two polynomials in GF(2)
vector<double> addPolynomials(const vector<double> &poly1, const vector<double> &poly2)
{
  vector<double> result(max(poly1.size(), poly2.size()), 0);
  for (size_t i = 0; i < poly1.size(); ++i)
  {
    result[i] += poly1[i];
  }
  for (size_t i = 0; i < poly2.size(); ++i)
  {
    result[i] += poly2[i];
  }
  for (size_t i = 0; i < result.size(); ++i)
  {
    result[i] = fmod(result[i], 2); // Reduce coefficient modulo 2
  }
  return result;
}

// Function to calculate the characteristic polynomial in GF(2)
vector<vector<double>> calculatePolynomial(const vector<double> &d, const vector<double> &a, const vector<double> &b)
{
  int n = d.size();
  vector<vector<double>> Delta(n + 1);

  // Initial conditions
  Delta[0] = {1};       // Δ−1 = 1
  Delta[1] = {d[0], 1}; // Δ0 = x + d0

  for (int k = 2; k <= n; ++k)
  {
    vector<double> term1 = multiplyPolynomials({d[k - 1], 1}, Delta[k - 1]);
    vector<double> term2 = (b[k - 2] == 1 && a[k - 1] == 1) ? Delta[k - 2] : vector<double>({0});
    Delta[k] = addPolynomials(term1, term2);
  }

  return Delta;
}

// Function to print the polynomial in a readable format
void printPolynomial(const vector<double> &poly)
{
  bool isFirstTerm = true;
  int degree = poly.size() - 1;
  for (int i = degree; i >= 0; --i)
  {
    if (poly[i] != 0)
    {
      if (!isFirstTerm && poly[i] > 0)
        cout << " + ";
      if (!isFirstTerm && poly[i] < 0)
        cout << " - ";
      if (i == degree || abs(poly[i]) != 1)
        cout << abs(poly[i]);
      if (i > 0)
        cout << "x";
      if (i > 1)
        cout << "^" << i;
      isFirstTerm = false;
    }
  }
  if (isFirstTerm) // If no terms were printed, the polynomial is zero
  {
    cout << "0";
  }
  cout << endl;
}

int main()
{
  cout << "Welcome to Cellular Automata Characterisation Tool and Characteristics Polynomial Generation" << endl;
  cout << "--------------------------------------------------------------------------------" << endl;
  cout << "Enter the number of cells in the cellular automata: ";
  int n;
  cin >> n;
  vector<vector<int>> grid(n, vector<int>(n, 0));
  vector<int> rule(n, 90); // Default to rule 90
  for (int i = 0; i < n; i++)
  {
    if (i % 2 == 0)
      rule[i] = 90;
    else
      rule[i] = 150;
  }

  // Build the grid based on rules
  for (int i = 0; i < n; i++)
  {
    if (rule[i] == 90) // Rule 90: left and right
    {
      if (i > 0)
        grid[i][i - 1] = 1;
      if (i < n - 1)
        grid[i][i + 1] = 1;
    }
    else if (rule[i] == 150) // Rule 150: left, itself, and right
    {
      grid[i][i] = 1;
      if (i > 0)
        grid[i][i - 1] = 1;
      if (i < n - 1)
        grid[i][i + 1] = 1;
    }
  }

  // Display the Cellular Automata Matrix
  cout << "The Cellular Automata Matrix is :" << endl;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cout << grid[i][j] << " ";
    }
    cout << endl;
  }

  vector<double> d(n), a(n), b(n - 1);
  for (int i = 0; i < n; i++)
  {
    d[i] = grid[i][i];
    if (i == 0)
    {
      a[i] = 0;
    }
    else
    {
      a[i] = grid[i][i - 1];
    }
    if (i != n - 1)
    {
      b[i] = grid[i][i + 1];
    }
  }

  vector<vector<double>> polynomials = calculatePolynomial(d, a, b);

  cout << "The characteristic polynomial is: ";
  printPolynomial(polynomials[n]);

  return 0;
}
