#include <iostream>
using namespace std;

int main()
{
  int a, b, c, d, l, e, s, n, y, z;

  cout << "Enter number: \t";
  cin >> n;

  for (a = 1; a <= n; a++)
  {
    for (s = 1; s <= n - a; s++)
    {
      cout << " ";
    }

    for (c = 1; c <= 2 * a - 1; c++)
    {
      cout << "*";
    }

    cout << endl;
  }

  // second part
  for (b = n - 1; b >= 1; b--)
  {
    for (d = 1; d <= n - b; d++)
    {
      cout << " ";
    }

    for (e = 1; e <= 2 * b - 1; e++)
    {
      cout << "*";
    }

    cout << endl;
  }

  cout << endl
       << endl;

  for (a = 1; a <= n; a++)
  {
    for (s = 1; s <= n - a; s++)
    {
      cout << " ";
    }

    cout << "*";

    for (z = 1; z <= a * 2 - 3; z++)
    {
      cout << " ";
    }

    if (a > 1)
      cout << "*";
    cout << endl;
  }

  // second part
  for (b = n - 1; b >= 1; b--)
  {
    for (d = 1; d <= n - b; d++)
    {
      cout << " ";
    }

    cout << "*";

    for (y = 1; y <= b * 2 - 3; y++)
    {
      cout << " ";
    }
    if (b > 1)
      cout << "*";
    cout << endl;
  }
  cout << endl
       << endl
       << endl;

  for (c = 1; c <= n; c++)
  {

    for (l = n; l >= 1; l--)
      cout << "*";
    cout << endl;

    for (b = 1; b <= n - 1; b++)
    {

      for (a = c * (n - 1); a >= 1; a--)
      {
        cout << " ";
      }

      cout << "*" << endl;
    }
    for (a = c * (n - 1); a >= 1; a--)
      cout << " ";
  }

  return 0;
}
