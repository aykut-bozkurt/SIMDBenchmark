#pragma once

static void init_vector(float* a, size_t size) {
    for (int i=0; i<size; i++) {
        a[i] = i;
    }
}

static void init_vector(int* a, size_t size) {
    for (int i=0; i<size; i++) {
        a[i] = i;
    }
}
