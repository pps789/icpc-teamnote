const int A = 7, B = 26, P = A << B | 1, R = 3;

int Pow(int x, int y) {
    int r = 1;
    while (y) {
        if (y & 1) r = r * 1ll * x % P;
        x = x * 1ll * x % P;
        y >>= 1;
    }
    return r;
}

void fft(int *a, int N, bool f) {
    for (int i = 1, j = 0; i < N; i++) {
        int k; for (k = N >> 1; j >= k; k >>= 1) j -= k;
        j += k; if (i < j) swap(a[i], a[j]);
    }
    for (int i = 1; i < N; i <<= 1) {
        int x = Pow(f ? Pow(R, P - 2) : R, P / i >> 1);
        for (int j = 0; j < N; j += i << 1) {
            int y = 1;
            for (int k = 0; k < i; k++) {
                int z = a[i + j + k] * 1ll * y % P;
                a[i + j + k] = a[j + k] - z;
                if (a[i + j + k] < P) a[i + j + k] += P;
                a[j + k] += z;
                if (a[j + k] >= P) a[j + k] -= P;
                y = y * 1ll * x % P;
            }
        }
    }
}
