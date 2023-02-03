#include <assert.h>
#include <sys/stat.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "min.hpp"

inline bool fileExists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

inline void ensureExists(const std::string& filename) {
    if (!fileExists(filename)) {
        std::filesystem::create_directories("json");
    }
}

std::vector<int> rd_vect(int size) {
    std::vector<int> in;
    in.reserve(size);
    auto [rng, uni] = rd(0, 100);
    for (int i = 0; i < size; i++) {
        in.push_back(uni(rng));
    }
    return in;
}

std::vector<int> inc_vect(int size) {
    std::vector<int> in;
    in.reserve(size);
    auto [rng, uni] = rd(0, 100);
    for (int i = 0; i < size; i++) {
        in.push_back(i);
    }
    return in;
}

std::vector<int> dec_vect(int size) {
    std::vector<int> in;
    in.reserve(size);
    auto [rng, uni] = rd(0, 100);
    for (int i = 0; i < size; i++) {
        in.push_back(size - 1 - i);
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

int64_t test_sliding_window_minimum_deque_in_place(const std::vector<std::vector<int>> vs, uint64_t w) {
    std::vector<std::vector<int>> vs_copy = vs;

    auto start = high_resolution_clock::now();
    for (auto& v : vs_copy) {
        sliding_window_minimum_deque_in_place(v, w);
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

void printv(std::vector<int> v) {
    for (const auto& x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

std::string write_json_string(const std::vector<int>& sizes, const std::vector<uint64_t>& window_sizes, int nb_test, std::vector<int> (*func)(int)) {
    std::string s;
    s.reserve(55932);  // approx size of json output
    s += "{\n";
    for (const auto& size : sizes) {
        // std::cout << size << "\n";
        s += "    \"" + std::to_string(size) += "\": {\n";
        for (const auto& w : window_sizes) {
            s += "        \"" + std::to_string(w) + "\": {\n";

            // let's creat nb_test tests vectors
            std::vector<std::vector<int>> vector_tests;
            vector_tests.reserve(nb_test);
            for (int i = 0; i < nb_test; i++) {
                vector_tests.push_back(func(size));
            }

            s += "            \"recomputing\": " + std::to_string(test_sliding_window_minimum_naive(vector_tests, w)) + ",\n";
            s += "            \"computing from last min\": " + std::to_string(test_sliding_window_minimum_keep_last_min(vector_tests, w)) + ",\n";
            s += "            \"fixed windows\": " + std::to_string(test_sliding_window_minimum_not_in_place(vector_tests, w)) + ",\n";
            s += "            \"fixed windows in place\": " + std::to_string(test_sliding_window_minimum(vector_tests, w)) + ",\n";
            s += "            \"deque\": " + std::to_string(test_sliding_window_minimum_deque(vector_tests, w)) + ",\n";
            s += "            \"deque in place\": " + std::to_string(test_sliding_window_minimum_deque_in_place(vector_tests, w)) + ",\n";
            s += "            \"deque rotation\": " + std::to_string(test_sliding_window_minimum_deque_rotation(vector_tests, w)) + "\n";
            if (w == window_sizes[window_sizes.size() - 1]) {
                s += "        }\n";
            } else {
                s += "        },\n";
            }
        }
        if (size == sizes[sizes.size() - 1]) {
            s += "    }\n";
        } else {
            s += "    },\n";
        }
    }
    s += "}\n";
    return s;
}

void check_equality_solution() {
    // checks that every algorithm returns the same results

    for (int i = 0; i < 1; i++) {
        auto [rng0, uni0] = rd(100, 1000);
        auto size = 20;
        auto [rng1, uni1] = rd(1, size);
        auto w = 5;
        // some algorithms are in place, so we must copy the input
        const auto v = rd_vect(size);
        auto vcopy = v;
        auto vcopy2 = v;

        auto r0 = sliding_window_minimum_naive(v, w);
        auto r1 = sliding_window_minimum_keep_last_min(v, w);
        auto r2 = sliding_window_minimum_not_in_place(v, w);
        auto r3 = sliding_window_minimum(vcopy, w);
        auto r4 = sliding_window_minimum_not_in_place_pre_alloc(v, w);
        auto r5 = sliding_window_minimum_deque(v, w);
        auto r6 = sliding_window_minimum_deque_pre_alloc(v, w);
        auto r7 = sliding_window_minimum_deque_rotation(v, w);
        auto r8 = sliding_window_minimum_deque_in_place(vcopy2, w);

        assert(r0 == r1);
        assert(r0 == r2);
        assert(r1 == r3);
        assert(r0 == r4);
        assert(r0 == r5);
        assert(r0 == r6);
        assert(r0 == r7);
        assert(r0 == r8);
    }
}

int main() {
    // checks that all algorithms give the same result
    check_equality_solution();

    ensureExists("json");

    // number of repetition per experiment
    // one experiment being a test for a specific fixed window size and input vector
    int nb_test = 10000;
    // windows sizes that are tested
    std::vector<uint64_t> window_sizes = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20};
    // sizes of input vector
    std::vector<int> sizes = {100, 150, 200, 250, 300, 350, 400, 450};  //, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000};

    std::ofstream list_of_random_integers("json/benchmark_input_is_vectors_of_random_integers.json");
    std::ofstream list_of_increasing_integers("json/benchmark_input_is_vectors_of_increasing_integers.json");
    std::ofstream list_of_decreasing_integers("json/benchmark_input_is_vectors_of_decreasing_integers.json");

    std::cout << "benchmark for input consisting of vectors of random integers... " << std::flush;
    list_of_random_integers << write_json_string(sizes, window_sizes, nb_test, &rd_vect);
    std::cout << "done." << std::endl;

    std::cout << "benchmark for input consisting of vectors of increasing integers... " << std::flush;
    list_of_increasing_integers << write_json_string(sizes, window_sizes, nb_test, &inc_vect);
    std::cout << "done." << std::endl;

    std::cout << "benchmark for input consisting of vectors of decreasing integers... " << std::flush;
    list_of_decreasing_integers << write_json_string(sizes, window_sizes, nb_test, &dec_vect);
    std::cout << "done." << std::endl;

    std::cout << std::endl;
    std::cout << "Results are stored in json/*.json files." << std::endl;
}
