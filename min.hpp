#include <random>
#include <tuple>
#include <vector>
template <typename T>
inline std::tuple<std::mt19937, std::uniform_int_distribution<T>> rd(T min, T max) {  // TODO move to utils
    std::random_device rd;                                                            // only used once to initialise (seed) engine
    std::mt19937 rng(rd());                                                           // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<T> uni(min, max);                                   // guaranteed unbiased
    return {rng, uni};
}

std::vector<int> sliding_window_minimum_naive(const std::vector<int>& in, uint64_t window_size);
std::vector<int> sliding_window_minimum_keep_last_min(const std::vector<int>& in, uint64_t window_size);
std::vector<int> sliding_window_minimum_not_in_place(const std::vector<int>& in, uint64_t window_size);
std::vector<int> sliding_window_minimum_not_in_place_pre_alloc(const std::vector<int>& in, uint64_t window_size);
std::vector<int> sliding_window_minimum_deque(const std::vector<int>& ARR, uint64_t K);
std::vector<int> sliding_window_minimum_deque_pre_alloc(const std::vector<int>& ARR, uint64_t K);
std::vector<int> sliding_window_minimum_deque_in_place(std::vector<int>& ARR, uint64_t K);
std::vector<int> sliding_window_minimum_deque_rotation(const std::vector<int>& ARR, uint64_t K);
std::vector<int> sliding_window_minimum(std::vector<int>& in, uint64_t window_size);