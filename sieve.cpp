vi spf;
void sieve(int n) {
    spf.resize(n + 1);
    for (int i = 0; i <= n; i++) spf[i] = i; 
    for (int i = 2; i * i <= n; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= n; j += i) {
                if (spf[j] == j) spf[j] = i; 
            }
        }
    }
}
vector<int> prime(int x) {
    vector<int> ret;
    while (x != 1) {
        ret.push_back(spf[x]);
        x = x / spf[x];
    }
    return ret;
}

vi mob((int)1e6 + 1, 0);
    mob[1] = -1;
    for(int i=1;i<=1e6;i++) {
        if(mob[i]) {
            mob[i] = -mob[i];
            for(int j=2*i;j<=1e6;j+=i) mob[j] += mob[i];
        }
    }
Euler Totient from 1 to n 
phi[i] -> numbers coprime with n from 1 to n

void precompute() {
    for (int i = 1; i < MAX_N; i++) { phi[i] = i; }
    for (int i = 2; i < MAX_N; i++) {
        // If i is prime
        if (phi[i] == i) {
            for (int j = i; j < MAX_N; j += i) { phi[j] -= phi[j] / i; }
        }
    }
}