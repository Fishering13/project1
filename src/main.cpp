#include <iostream>
using namespace std;
int main ()
{
    unsigned int a;
    cout << "Enter number: " ;
    cin >> a;
    int res = 0;
    for (int i = 31; i >= 0; --i)
        if ((a >> i) & 1)
            res++;
    cout << "Bits: " << res << "\n";
    cout << "Huits: " << res * 200 << "\n";
return 0;
}