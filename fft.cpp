#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

// FFT function: computes the DFT (or inverse DFT if invert==true) in-place.
void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if(n == 1)
        return;
    
    // Divide into even and odd indices
    vector<cd> a0(n/2), a1(n/2);
    for (int i = 0; 2*i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);
    
    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2*i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i+n/2] = a0[i] - w * a1[i];
        if(invert) {
            a[i] /= 2;
            a[i+n/2] /= 2;
        }
        w *= wn;
    }
}

// Multiply two polynomials using FFT (i.e. compute convolution)
vector<long long> multiply(const vector<int> & a, const vector<int> & b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    // n is next power of two greater than or equal to a.size() + b.size()
    while(n < (int)(a.size() + b.size()))
        n <<= 1;
    fa.resize(n);
    fb.resize(n);
    
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);
    
    vector<long long> res(n);
    for (int i = 0; i < n; i++)
        res[i] = (long long)round(fa[i].real());
    return res;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    vector<int> signal(n), mask(m);
    
    // Read the signal
    for (int i = 0; i < n; i++){
        cin >> signal[i];
    }
    // Read the mask
    for (int j = 0; j < m; j++){
        cin >> mask[j];
    }
    
    // Reverse the mask to prepare for convolution to get cross-correlation.
    vector<int> mask_rev(mask.rbegin(), mask.rend());
    
    // Compute convolution: conv[k] = sum_{i} signal[i] * mask_rev[k-i]
    vector<long long> conv = multiply(signal, mask_rev);
    
    // According to the derivation, for shift s (which is our mask position),
    // conv[m-1+s] = sum_{j} signal[s+j]*mask[j]
    // We need to output conv[0]...conv[n+m-2] which corresponds to s from -m+1 to n-1.
    // They are already in left-to-right order.
    for (int i = 0; i < n + m - 1; i++){
        cout << conv[i] << (i == n + m - 2 ? "\n" : " ");
    }
    
    return 0;
}
