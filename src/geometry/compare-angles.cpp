int ccw(pair<int, int> p1, pair<int, int> p2) {
    auto ret = p1.first * 1ll * p2.second - p2.first * 1ll * p1.second;
    return ret > 0 ? 1 : (ret < 0 ? -1 : 0);
}

bool upper(pair<int, int> p) {
    return tie(p.second, p.first) > tuple<int, int>();
}

// sorting criterion: [0 ~ 2 * pi)
sort(dat.begin(), dat.end(), [](pair<int, int> a, pair<int, int> b){
    if (upper(a) != upper(b)) return upper(a) > upper(b);
    if (ccw(a, b)) return ccw(a, b) > 0;

    // optional: closest to farthest
    return hypot(a.first, a.second) < hypot(b.first, b.second);
});
