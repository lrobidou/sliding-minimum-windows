#include <assert.h>

#include <chrono>
#include <iostream>

#include "min.hpp"

std::vector<int> rd_vect(int size) {
    std::vector<int> in;
    in.reserve(size);
    auto [rng, uni] = rd(0, 100);
    for (int i = 0; i < size; i++) {
        in.push_back(uni(rng));
        // in.push_back(i);
        // in.push_back(size - 1 - i);
    }
    return in;
}
using namespace std::chrono;

int64_t test_sliding_window_minimum_naive(const std::vector<std::vector<int>> vs, uint64_t w) {
    auto start = high_resolution_clock::now();
    for (const auto& v : vs) {
        sliding_window_minimum_naive(v, w);
    }
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int64_t test_sliding_window_minimum_keep_last_min(const std::vector<std::vector<int>> vs, uint64_t w) {
    auto start = high_resolution_clock::now();
    for (const auto& v : vs) {
        sliding_window_minimum_keep_last_min(v, w);
    }
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int64_t test_sliding_window_minimum_not_in_place(const std::vector<std::vector<int>> vs, uint64_t w) {
    auto start = high_resolution_clock::now();
    for (const auto& v : vs) {
        sliding_window_minimum_not_in_place(v, w);
    }
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int64_t test_sliding_window_minimum(const std::vector<std::vector<int>> vs, uint64_t w) {
    std::vector<std::vector<int>> vs_copy = vs;

    auto start = high_resolution_clock::now();
    for (auto& v : vs_copy) {
        sliding_window_minimum(v, w);
    }
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int64_t test_sliding_window_minimum_not_in_place_pre_alloc(const std::vector<std::vector<int>> vs, uint64_t w) {
    auto start = high_resolution_clock::now();
    for (const auto& v : vs) {
        sliding_window_minimum_not_in_place_pre_alloc(v, w);
    }
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int64_t test_sliding_window_minimum_deque(const std::vector<std::vector<int>> vs, uint64_t w) {
    auto start = high_resolution_clock::now();
    for (const auto& v : vs) {
        sliding_window_minimum_deque(v, w);
    }
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int64_t test_sliding_window_minimum_deque_pre_alloc(const std::vector<std::vector<int>> vs, uint64_t w) {
    auto start = high_resolution_clock::now();
    for (const auto& v : vs) {
        sliding_window_minimum_deque_pre_alloc(v, w);
    }
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int64_t test_sliding_window_minimum_deque_rotation(const std::vector<std::vector<int>> vs, uint64_t w) {
    auto start = high_resolution_clock::now();
    for (const auto& v : vs) {
        sliding_window_minimum_deque_rotation(v, w);
    }
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int main() {
    // int size = 3000;
    int nb_test = 10000;
    std::vector<uint64_t> window_sizes = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 100};

    uint64_t total_duration_naive_1 = 0;
    uint64_t total_duration_p = 0;
    uint64_t total_duration_no_in_place = 0;
    uint64_t total_duration_no_in_place_pre_alloc = 0;
    uint64_t total_duration_in_place = 0;
    uint64_t total_duration_deque = 0;
    uint64_t total_duration_deque_pre_alloc = 0;

    std::vector<int> sizes = {100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000};

    // lest's check that every function returns the same result

    {
        for (int i = 0; i < 1; i++) {
            auto [rng0, uni0] = rd(100, 1000);
            auto size = 20;
            auto [rng1, uni1] = rd(1, size);
            auto w = 5;
            const auto v = rd_vect(size);
            auto vcopy = v;

            auto r0 = sliding_window_minimum_naive(v, w);
            auto r1 = sliding_window_minimum_keep_last_min(v, w);
            auto r2 = sliding_window_minimum_not_in_place(v, w);
            auto r3 = sliding_window_minimum(vcopy, w);
            auto r4 = sliding_window_minimum_not_in_place_pre_alloc(v, w);
            auto r5 = sliding_window_minimum_deque(v, w);
            auto r6 = sliding_window_minimum_deque_pre_alloc(v, w);
            auto r7 = sliding_window_minimum_deque_rotation(v, w);

            assert(r0 == r1);
            assert(r0 == r2);
            assert(r1 == r3);
            assert(r0 == r4);
            assert(r0 == r5);
            assert(r0 == r6);
            assert(r0 == r7);
            exit(0);
        }
    }

    std::cout << "{" << std::endl;
    for (const auto& size : sizes) {
        std::cout << "    \"" << size << "\": {" << std::endl;
        for (const auto& w : window_sizes) {
            std::cout << "        \"" << w << "\": {" << std::endl;

            // let's creat nb_test tests vectors
            std::vector<std::vector<int>> vector_tests;
            vector_tests.reserve(nb_test);
            for (int i = 0; i < nb_test; i++) {
                vector_tests.push_back(rd_vect(size));
            }

            std::cout << "            \"recomputing\": " << test_sliding_window_minimum_naive(vector_tests, w) / 1000 << "," << std::endl;
            std::cout << "            \"computing from last min\": " << test_sliding_window_minimum_keep_last_min(vector_tests, w) / 1000 << "," << std::endl;
            std::cout << "            \"fixed windows\": " << test_sliding_window_minimum_not_in_place(vector_tests, w) / 1000 << "," << std::endl;
            std::cout << "            \"fixed windows in place\": " << test_sliding_window_minimum(vector_tests, w) / 1000 << "," << std::endl;
            std::cout << "            \"deque\": " << test_sliding_window_minimum_deque(vector_tests, w) / 1000 << std::endl;
            if (w == window_sizes[window_sizes.size() - 1]) {
                std::cout << "        }" << std::endl;
            } else {
                std::cout << "        }," << std::endl;
            }
        }
        if (size == sizes[sizes.size() - 1]) {
            std::cout << "    }" << std::endl;
        } else {
            std::cout << "    }," << std::endl;
        }
    }
    std::cout << "}" << std::endl;
}
