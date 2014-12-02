#pragma once

_Monitor MPRNG {
  public:
    MPRNG(unsigned seed = 1009) { srand(seed); }
    void seed(unsigned seed) { srand(seed); }
    unsigned operator()() {
        return rand(); // [0, UINT_MAX]
    }
    unsigned operator()(unsigned u) {
        return operator()() % u; // [0, u)
    }
    unsigned operator()(unsigned l, unsigned u) {
        return operator()(u - l) + l; // [l, u)
    }
};

extern MPRNG mprng;
