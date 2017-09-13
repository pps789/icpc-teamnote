const double PI = 3.14159265358979323846;

void fft(complex<double> *a, int N, bool f) {
    complex<double> x, y, z;
    for (int i = 1, j = 0; i < N; i++) {
        for (int k = N >> 1; j >= k; k >>= 1) j -= k;
        j += k;
        if (i < j) swap(a[i], a[j]);
    }
    for (int i = 1; i < N; i <<= 1) {
        double w = f ? -PI / i : PI / i;
        complex<double> x{ cos(w), sin(w) };
        for (int j = 0; j < N; j += i << 1) {
            complex<double> y = 1;
            for (int k = 0; k < i; k++) {
                z = a[i + j + k] * y;
                a[i + j + k] = a[j + k] - z;
                a[j + k] += z;
                y *= x;
            }
        }
    }
    if (f) for (int i = 0; i < N; i++) a[i] /= N;
}

// Compute Poly(a)*Poly(b), write to r; Indexed from 0
// O(n*logn)
int mult(int *a, int n, int *b, int m, int *r) {
    const int MAXN = 1048576;
    static complex<double> A[MAXN], B[MAXN];
    int fn = 1;
    while (fn < n + m) fn <<= 1; // n + m: interested length
    for (int i = 0; i < n; i++) A[i] = a[i];
    for (int i = n; i < fn; i++) A[i] = 0;
    for (int i = 0; i < m; i++) B[i] = b[i];
    for (int i = m; i < fn; i++) B[i] = 0;
    fft(A, fn, false);
    fft(B, fn, false);
    for (int i = 0; i < fn; ++i) A[i] *= B[i];
    fft(A, fn, true);
    for (int i = 0; i < fn; ++i) r[i] = (int)round(A[i].real());
    return fn;
}
