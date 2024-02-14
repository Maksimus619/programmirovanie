#include <iostream>
using namespace std;


int main()
{
  int z = 5; 
  int** a = new int*[z];
  for (int i = 0; i < z; i++) a[i] = new int[z];
  for (int i = 0; i < z; i++) {
    for (int j = 0; j < z; j++) a[i][j] = rand()%10;
  }
  for (int i = 0; i < z ; i++) {
    for (int j = 0; j < z; j++) cout << a[i][j] << " ";
    cout << endl;
  }
  cout << kolvo;
  cout << endl;
  cout << endl;
  cout << endl;
  int kolvo = 0;
  for (int i = 1 ; i <= n; i++) kolvo += i;
  int l = 0;
  int* d = new int[kolvo];
  for (int k = 1;  k <= n; k++) {
    for (int i = 0; i < k; i++) {
      d[l] = a[i][n-k+1];
      l++;
    }
  }
  for (int i = 0; i < kolvo; i++) cout << d[i] << " ";
  cout << endl;
}