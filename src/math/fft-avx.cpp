#include <immintrin.h>
#pragma GCC target("avx2")
#pragma GCC target("fma")

const double PI = acos(-1);

__m256d mult(__m256d a, __m256d b) {
    __m256d c = _mm256_movedup_pd(a);
    __m256d d = _mm256_shuffle_pd(a, a, 15);
    __m256d cb = _mm256_mul_pd(c, b);
    __m256d db = _mm256_mul_pd(d, b);
    __m256d e = _mm256_shuffle_pd(db, db, 5);
    __m256d r = _mm256_addsub_pd(cb, e);
    return r;
}

void fft(__m128d a[], int N, bool f) {
    for (int i = 1, j = 0; i < N; i++) {
        int k; for (k = N >> 1; j >= k; k >>= 1) j -= k;
        j += k; if (i < j) swap(a[i], a[j]);
    }
    for (int i = 1; i < N; i <<= 1) {
        double angle = PI / i; if (f) angle = -angle;
        __m256d w; w[0] = cos(angle), w[1] = sin(angle);
        for (int j = 0; j < N; j += i << 1) {
            __m256d y; y[0] = 1; y[1] = 0;
            for (int k = 0; k < i; k++) {
                y = _mm256_permute2f128_pd(y, y, 0);
                w = _mm256_insertf128_pd(w, a[i + j + k], 1);
                y = mult(y, w);
                __m128d vw = _mm256_extractf128_pd(y, 1);
                __m128d u = a[j + k];
                a[j + k] = _mm_add_pd(u, vw);
                a[i + j + k] = _mm_sub_pd(u, vw);
            }
        }
    }
}

int mult(int *a, int n, int *b, int m, int *r) {
    const int maxn = 1048576;
    static __m128d fv[maxn];
    int fn = 1;
    while (fn < n + m) fn <<= 1;
    for (int i = 0; i < fn; i++) fv[i][0] = fv[i][1] = 0;
    for (int i = 0; i < n; i++) fv[i][0] = a[i];
    for (int i = 0; i < m; i++) fv[i][1] = b[i];
    fft(fv, fn, false);
    for(int i = 0; i < fn; i += 2) {
        __m256d a;
        a = _mm256_insertf128_pd(a, fv[i], 0);
        a = _mm256_insertf128_pd(a, fv[i + 1], 1);
        a = mult(a, a);
        fv[i] = _mm256_extractf128_pd(a, 0);
        fv[i + 1] = _mm256_extractf128_pd(a, 1);
    }
    fft(fv, fn, true);
    for (int i = 0; i < fn; i++) r[i] = round(fv[i][1] / fn * 0.5);
    return fn;
}
