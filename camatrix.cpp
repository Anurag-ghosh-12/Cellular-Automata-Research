#include <bits/stdc++.h>

using namespace std;
// By Anurag Ghosh
vector<double> multiplyPolynomials(const vector<double> &poly1, const vector<double> &poly2)
{
  vector<double> result(poly1.size() + poly2.size() - 1, 0);
  for (size_t i = 0; i < poly1.size(); ++i)
  {
    for (size_t j = 0; j < poly2.size(); ++j)
    {
      result[i + j] += poly1[i] * poly2[j];
    }
  }
  return result;
}

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
  return result;
}

vector<vector<double>> calculatePolynomial(const vector<double> &d, const vector<double> &a, const vector<double> &b)
{
  int n = d.size();
  vector<vector<double>> Delta(n + 1);

  // Initially
  Delta[0] = {1};       // Δ−1 = 1
  Delta[1] = {d[0], 1}; // Δ0 = x + d0

  for (int k = 2; k <= n; ++k)
  {
    vector<double> term1 = multiplyPolynomials({d[k - 1], 1}, Delta[k - 1]);
    vector<double> term2 = (b[k - 2] == 1 && a[k - 1] == 1) ? Delta[k - 2] : vector<double>({0});

    // for (int j = 0; j < term2.size(); j++)
    // {
    //   cout << term2[j] << " ";
    // }
    // cout << endl;
    Delta[k] = addPolynomials(term1, term2);
    // printPolynomial(Delta)
  }

  return Delta;
}

// polynomial
void printPolynomial(const vector<double> &poly)
{
  int degree = poly.size() - 1;
  for (int i = degree; i >= 0; --i)
  {
    if (poly[i] != 0)
    {
      if (i != degree && poly[i] > 0)
        cout << " + ";
      if (i != degree && poly[i] < 0)
        cout << " - ";
      if (i == degree || abs(poly[i]) != 1)
        cout << abs(poly[i]);
      if (i > 0)
        cout << "x";
      if (i > 1)
        cout << "^" << i;
    }
  }
  cout << endl;
}

int main()
{
  cout << "Welcome to Cellular Automata Characterisation Tool and Characteristics Polynomial Generation" << endl;
  cout << "--------------------------------------------------------------------------------" << endl;
  cout << "Enter the number of cells in the cellular automata :";
  int n;
  cin >> n;
  vector<vector<int>> grid(n, vector<int>(n, 0));
  vector<int> rule(n);
  for (int i = 0; i < n; i++)
  {
    cout << "Enter the rule (Valid : 0,60,90,102,150,170,204,240) for cell " << i + 1 << " : ";
    cin >> rule[i];
    if (rule[i] != 0 && rule[i] != 60 && rule[i] != 90 && rule[i] != 102 && rule[i] != 150 && rule[i] != 170 && rule[i] != 204 && rule[i] != 240)
    {
      cout << "Non Linear rule entered. Please enter a valid rule again" << endl;
      i--;
    }
    // if (i % 2 == 0)
    // {
    //   rule[i] = 90;
    // }
    // else
    // {
    //   rule[i] = 150;
    // }
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (i == j) // only main diagonal
      {
        int r = rule[i];
        switch (r)
        {
        case 0:
          break;
        case 60: // left itself
          if (i == 0)
          {
            grid[i][j] = 1;
          }
          else
          {
            grid[i][j] = 1;
            grid[i][j - 1] = 1; // left
          }
          break;
        case 90: // left right
          if (i == n - 1)
          {
            grid[i][j - 1] = 1;
          }
          else if (i == 0)
          {
            grid[i][j + 1] = 1;
          }
          else
          {
            grid[i][j - 1] = 1;
            grid[i][j + 1] = 1; // right
          }
          break;
        case 102: // itself right
          if (i == n - 1)
          {
            grid[i][j] = 1; // itself
          }
          else
          {
            grid[i][j] = 1;     // itself
            grid[i][j + 1] = 1; // right
          }
          break;
        case 150: // all
          if (i == 0)
          {
            grid[i][j] = 1;
            grid[i][j + 1] = 1; // right
          }
          else if (i == n - 1)
          {
            grid[i][j] = 1;
            grid[i][j - 1] = 1; // left
          }
          else
          {
            grid[i][j] = 1;
            grid[i][j - 1] = 1; // left
            grid[i][j + 1] = 1; // right
          }
          break;
        case 170: // right
          if (i != n - 1)
          {
            grid[i][j + 1] = 1; // right
          }
          break;
        case 204:
          grid[i][j] = 1;
          break;
        case 240: // left
          if (i != 0)
          {
            grid[i][j - 1] = 1;
          }
          break;
        }
      }
    }
  }
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
  // for (int i = 0; i < n; i++)
  // {
  //   cout << a[i] << " ";
  // }
  // cout << endl;
  // for (int i = 0; i < n - 1; i++)
  // {
  //   cout << b[i] << " ";
  // }
  // cout << endl;
  vector<vector<double>> polynomials = calculatePolynomial(d, a, b);

  cout << "The characteristic polynomial is: " << endl;

  for (int i = 0; i <= n; i++)
  {
    for (int j = 0; j < polynomials[i].size(); j++)
    {
      if (i == n)
      {
        // if ((int)polynomials[i][j] % 2)
        //   cout << "x^" << j << "+";
        cout << (int)polynomials[i][j] % 2 << "   ";
      }
    }
  }
  cout << endl;
  for (int j = 0; j < polynomials[n].size(); j++)
  {
    cout << "x^" << j << " ";
  }
  return 0;
}