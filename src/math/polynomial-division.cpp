vll get_inv(const vll& v, int deg){
    if (deg == 1) return vll(1, fastpow(v[0], MOD - 2));

    if (deg & 1){
        vll a = get_inv(v, deg - 1);
        ll c = 0;
        for (int i = 1; i < deg - 1; i++) c = (c + a[i] * v[deg - 1 - i]) % MOD;
        ll h1 = v[deg - 1];
 
        ll b = MOD - (h1 * a[0] + c) % MOD * a[0] % MOD;
        if (b == MOD) b = 0; a.push_back(b);
        return a;
    }

    vll a = get_inv(v, deg >> 1);
    vll h0(v.begin(), v.begin() + (deg >> 1));
    vll h1(v.begin() + (deg >> 1), v.begin() + deg);
    vll ah0 = mult(a, h0); ah0.push_back(0);
    vll c(ah0.begin() + (deg >> 1), ah0.begin() + deg);
    vll h1a = mult(h1, a);
    vll b_ = mult(a, add(h1a, c));

    vll b(b_.begin(), b_.begin() + (deg >> 1));
    for (ll e : b) a.push_back(e ? MOD - e : 0);
    return a;
}
 
vll divide(const vll& F, const vll& G, bool newg = false){
    static vll G_INV;
    const int N = (int)F.size() - 1, M = (int)G.size() - 1; // deg of F, G
    if (N < M) return vll();
    if (N == M) return vll(1, F.back()*fastpow(G.back(), MOD - 2) % MOD);

    vll f = F;
    if (G_INV.empty() || newg)
        vll g = G; reverse(g.begin(), g.end());
        while (g.size() < N - M + 1) g.push_back(0);
        G_INV = get_inv(g, N - M + 1);
    }

    reverse(f.begin(), f.end());
    vll ret = mult(f, G_INV);
    ret.resize(N - M + 1);
    reverse(ret.begin(), ret.end());

    return ret;
}
