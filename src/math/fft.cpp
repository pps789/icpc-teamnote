const double PI = acos(-1);

void fft(double *r, double *im, int N, bool f) {
    for (int i = 1, j = 0; i < N; i++) {
        int k; for (k = N >> 1; j >= k; k >>= 1) j -= k;
        j += k; if (i < j) swap(r[i], r[j]), swap(im[i], im[j]);
    }
    for (int i = 1; i < N; i <<= 1) {
        double w = PI / i; if (f) w = -w;
        double c = cos(w), s = sin(w);
        for (int j = 0; j < N; j += i << 1) {
            double yr = 1, yi = 0;
            for (int k = 0; k < i; k++) {
                double zr = r[i + j + k] * yr - im[i + j + k] * yi;
                double zi = r[i + j + k] * yi + im[i + j + k] * yr;
                r[i + j + k] = r[j + k] - zr;
                im[i + j + k] = im[j + k] - zi;
                r[j + k] += zr; im[j + k] += zi;
                tie(yr, yi) = make_pair(yr * c - yi * s, yr * s + yi * c);
            }
        }
    }
}    

// Compute Poly(a)*Poly(b), write to r; Indexed from 0
// O(n*logn)
int mult(int *a, int n, int *b, int m, int *r) {
    const int maxn = 1048576;
    static double ra[maxn], rb[maxn], ia[maxn], ib[maxn];
    int fn = 1;
    while (fn < n + m) fn <<= 1; // n + m: interested length
    for (int i = 0; i < n; ++i) ra[i] = a[i], ia[i] = 0;
    for (int i = n; i < fn; ++i) ra[i] = ia[i] = 0;
    for (int i = 0; i < m; ++i) rb[i] = b[i], ib[i] = 0;
    for (int i = m; i < fn; ++i) rb[i] = ib[i] = 0;
    fft(ra, ia, fn, false);
    fft(rb, ib, fn, false);
    for (int i = 0; i < fn; ++i) {
        double real = ra[i] * rb[i] - ia[i] * ib[i];
        double imag = ra[i] * ib[i] + rb[i] * ia[i];
        ra[i] = real, ia[i] = imag;
    }
    fft(ra, ia, fn, true);
    for (int i = 0; i < fn; ++i) r[i] = (int)floor(ra[i] / fn + 0.5);
    return fn;
}
