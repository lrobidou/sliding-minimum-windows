#include "min.hpp"

#include <deque>
#include <iostream>
#include <optional>
std::vector<int> sliding_window_minimum_naive(const std::vector<int>& ARR, uint64_t K) {
    // naive approach:
    // compute the min in each window independently
    std::vector<int> res;
    res.reserve(ARR.size() - K + 1);

    for (std::size_t j = 0; j < ARR.size() - K + 1; j++) {  // j : start of the window
        int min = ARR[j];
        for (std::size_t k = j; k < j + K; k++) {  // k : current position in the tab
            if (ARR[k] < min) {
                min = ARR[k];
            }
        }
        res.push_back(min);
    }
    return res;
}

std::vector<int> sliding_window_minimum_keep_last_min(const std::vector<int>& ARR, uint64_t K) {
    // same as naive approach but keep the current minimum
    // to prevent unnecessary recomputation
    std::vector<int> res;
    res.reserve(ARR.size() - K + 1);
    int min = ARR[0];
    std::size_t i_min = 0;

    for (int j = 1; j < K; j++) {
        if (ARR[j] < min) {
            min = ARR[j];
            i_min = j;
        }
    }
    res.push_back(min);

    for (std::size_t i = K; i < ARR.size(); i++) {
        if (i_min == i - K) {
            i_min = i - K + 1;
            min = ARR[i_min];
            for (std::size_t j = i - K + 2; j < i; j++) {
                if (ARR[j] < min) {
                    i_min = j;
                    min = ARR[i_min];
                }
            }
        }
        if (ARR[i] < min) {
            i_min = i;
            min = ARR[i_min];
        }
        res.push_back(min);
    }
    return res;
}

std::vector<int> sliding_window_minimum_deque(const std::vector<int>& ARR, uint64_t K) {
    // using a deque
    // pair<int, int> represents the pair (ARR[i], i)
    std::vector<int> res;
    std::deque<std::pair<int, int>> window;
    for (int i = 0; i < ARR.size(); i++) {
        while (!window.empty() && window.back().first >= ARR[i]) {
            window.pop_back();
        }

        window.push_back(std::make_pair(ARR[i], i));

        while (window.front().second + K <= i) {
            window.pop_front();
        }

        if (i >= K - 1) {
            res.push_back(window.front().first);
        }
    }
    return res;
}

std::vector<int> sliding_window_minimum_deque_pre_alloc(const std::vector<int>& ARR, uint64_t K) {
    // using a deque
    // pair<int, int> represents the pair (ARR[i], i)
    // the result vector is preallocated
    std::vector<int> res;
    res.reserve(ARR.size() - K + 1);
    std::deque<std::pair<int, int>> window;
    for (int i = 0; i < ARR.size(); i++) {
        while (!window.empty() && window.back().first >= ARR[i])
            window.pop_back();
        window.push_back(std::make_pair(ARR[i], i));

        while (window.front().second + K <= i)
            window.pop_front();

        if (i >= K - 1) {
            res.push_back(window.front().first);
        }
    }
    return res;
}

std::vector<int> sliding_window_minimum_deque_in_place(std::vector<int>& ARR, uint64_t K) {
    // using a deque
    // pair<int, int> represents the pair (ARR[i], i)
    // the result vector is preallocated
    // std::vector<int> res;
    // res.reserve(ARR.size() - K + 1);
    std::deque<std::pair<int, int>> window;
    for (int i = 0; i < ARR.size(); i++) {
        while (!window.empty() && window.back().first >= ARR[i])
            window.pop_back();
        window.push_back(std::make_pair(ARR[i], i));

        while (window.front().second + K <= i)
            window.pop_front();

        if (i >= K - 1) {
            ARR[i - (K - 1)] = window.front().first;
        }
    }

    for (std::size_t i = 0; i < K - 1; i++) {
        ARR.pop_back();
    }
    return ARR;
}

template <typename T>
class Rotation {
   private:
    int _size;
    std::vector<T> _content;
    std::optional<std::size_t> _back;
    std::optional<std::size_t> _front;
    int _nb;

   public:
    Rotation(int size);
    // template <typename T>
    T get_front();
    T get_back();
    bool empty();
    // void remove_front();

    void push_back(T element);
    void remove_front();
    void remove_back();
    void print();
};

template <typename T>
Rotation<T>::Rotation(int size) : _size(size + 1), _back(std::nullopt), _front(std::nullopt), _nb(0) {
    for (std::size_t i = 0; i < this->_size; i++) {
        this->_content.push_back(std::make_pair(0, 0));
    }
}

template <typename T>
T Rotation<T>::get_front() {
    return this->_content[this->_front.value()];
}

template <typename T>
T Rotation<T>::get_back() {
    return this->_content[this->_back.value()];
}

template <typename T>
bool Rotation<T>::empty() {
    return (!this->_back.has_value());
}

template <typename T>
void Rotation<T>::push_back(T element) {
    if (this->_nb == this->_size) {
        exit(1);
    }
    this->_nb += 1;
    if (!this->_front.has_value()) {
        this->_front = 0;
        this->_back = 0;
        this->_content[0] = element;
    } else {
        this->_back = this->_back.value() + 1;
        if (this->_back.value() == this->_size) {
            this->_back = 0;
        }
        this->_content[this->_back.value()] = element;
    }
}

template <typename T>
void Rotation<T>::remove_front() {
    if (this->_nb == 0) {
        exit(1);
    }
    this->_nb -= 1;
    if (this->_nb == 0) {
        this->_front = std::nullopt;
        this->_back = std::nullopt;
    } else {
        this->_front = this->_front.value() + 1;
        if (this->_front.value() == this->_size) {
            this->_front = 0;
        }
    }
}

template <typename T>
void Rotation<T>::remove_back() {
    if (this->_nb == 0) {
        exit(1);
    }
    this->_nb -= 1;
    if (this->_nb == 0) {
        this->_front = std::nullopt;
        this->_back = std::nullopt;
    } else {
        this->_back = this->_back.value() - 1;
        if (this->_back.value() == -1) {
            this->_back = this->_size - 1;
        }
    }
}

template <typename T>
void Rotation<T>::print() {
    if (this->empty()) {
        std::cout << "empty" << std::endl;
        return;
    }
    size_t i = this->_back.value();
    while (true) {
        std::cout << "(" << this->_content[i].first << ", " << this->_content[i].second << ") ";
        if (i == this->_front.value()) {
            break;
        } else {
            i--;
            if (i == -1) {
                i = this->_size;
            }
        }
        // std::cout << std::endl;
    }
    // for (size_t i = 0; i < this->_size; i++) {
    //     std::cout << this->_content[i] << " ";
    // }
    std::cout << std::endl;
}

// def remove_front(self):
//     if self.nb ==0:
//         raise ValueError("nope")
//     self.nb -= 1
//     if self.nb == 0:
//         self.front = None
//         self.back = None
//     else:
//         self.front += 1
//         if self.front == self.size:
//             self.front = 0

// def __str__(self):
//     print(self.content)
//     return " ".join([str(x) for x in self.content])

std::vector<int> sliding_window_minimum_deque_rotation(const std::vector<int>& ARR, uint64_t K) {
    // using a deque

    Rotation<std::pair<int, int>> window_rotation(K);

    std::optional<std::size_t> back = std::nullopt;
    std::optional<std::size_t> front = std::nullopt;

    std::size_t previous_back = 0;

    std::vector<int> res;
    res.reserve(ARR.size() - K + 1);
    std::deque<std::pair<int, int>> window;
    for (int i = 0; i < ARR.size(); i++) {
        // window_rotation.print();
        while (!window.empty() && window.back().first >= ARR[i]) {
            window.pop_back();
        }

        while (!window_rotation.empty() && window_rotation.get_back().first >= ARR[i]) {
            window_rotation.remove_back();
        }

        window.push_back(std::make_pair(ARR[i], i));
        window_rotation.push_back(std::make_pair(ARR[i], i));

        while (window.front().second + K <= i) {
            window.pop_front();
        }

        while (window_rotation.get_front().second + K <= i) {
            window_rotation.remove_front();
        }

        if (i >= K - 1) {
            // std::cout << "adding front" << std::endl;
            res.push_back(window_rotation.get_front().first);
        }
    }
    return res;
}

// std::vector<int> sliding_window_minimum_deque_rotation_in_place(std::vector<int>& ARR, uint64_t K) {
//     // using a deque
//     // pair<int, int> represents the pair (ARR[i], i)
//     // the result vector is preallocated

//     Rotation<std::pair<int, int>> window_rotation(K);

//     std::optional<std::size_t> back = std::nullopt;
//     std::optional<std::size_t> front = std::nullopt;

//     std::size_t previous_back = 0;

//     std::vector<int> res;
//     res.reserve(ARR.size() - K + 1);
//     std::deque<std::pair<int, int>> window;
//     for (int i = 0; i < ARR.size(); i++) {
//         while (!window.empty() && window.back().first >= ARR[i]) {
//             window.pop_back();
//         }

//         while (!window_rotation.empty() && window_rotation.get_back().first >= ARR[i]) {
//             window_rotation.remove_back();
//         }

//         window.push_back(std::make_pair(ARR[i], i));

//         while (window.front().second + K <= i) {
//             window.pop_front();
//         }

//         while (window_rotation.get_front().second + K <= i) {
//             window_rotation.remove_front();
//         }

//         if (i >= K - 1) {
//             // ARR.push_back(window.front().first);
//         }
//     }
//     return res;
// }

std::vector<int> sliding_window_minimum_not_in_place(const std::vector<int>& ARR, uint64_t w) {
    // not in place (the response is a copy)
    uint64_t nbWin = ARR.size() / w;
    std::size_t size = ARR.size();
    int nb_elem_last_window = ARR.size() % w;

    std::vector<int> min_left;
    for (std::size_t i = 0; i < size; i++) {
        if (i % w == 0) {
            min_left.push_back(ARR[i]);
        } else {
            min_left.push_back(std::min(min_left[i - 1], ARR[i]));
        }
    }

    std::vector<int> min_right(ARR.size());

    for (std::size_t s = 0; s < nbWin; s++) {
        min_right[s * w + w - 1] = ARR[s * w + w - 1];
        for (int j = w - 2; j >= 0; j--) {
            min_right[s * w + j] = std::min(min_right[s * w + j + 1], ARR[s * w + j]);
        }
    }

    if (nb_elem_last_window) {
        std::size_t start = nbWin * w;
        min_right[size - 1] = ARR[size - 1];
        for (int j = nb_elem_last_window - 2; j >= 0; j--) {
            min_right[start + j] = std::min(min_right[start + j + 1], ARR[start + j]);
        }
    }

    std::vector<int> response;
    for (std::size_t i = 0; i < size - w + 1; i++) {
        response.push_back(std::min(min_right[i], min_left[i + w - 1]));
    }

    return response;
}

std::vector<int> sliding_window_minimum_not_in_place_pre_alloc(const std::vector<int>& ARR, uint64_t w) {
    // preallocating memory whenever it is possible
    uint64_t nbWin = ARR.size() / w;
    std::size_t size = ARR.size();
    int nb_elem_last_window = ARR.size() % w;

    std::vector<int> min_left(size);
    for (std::size_t i = 0; i < size; i++) {
        if (i % w == 0) {
            min_left[i] = ARR[i];
        } else {
            min_left[i] = std::min(min_left[i - 1], ARR[i]);
        }
    }

    std::vector<int> min_right(size);

    for (std::size_t s = 0; s < nbWin; s++) {
        min_right[s * w + w - 1] = ARR[s * w + w - 1];
        for (int j = w - 2; j >= 0; j--) {
            min_right[s * w + j] = std::min(min_right[s * w + j + 1], ARR[s * w + j]);
        }
    }

    if (nb_elem_last_window) {
        std::size_t start = nbWin * w;
        min_right[size - 1] = ARR[size - 1];
        for (int j = nb_elem_last_window - 2; j >= 0; j--) {
            min_right[start + j] = std::min(min_right[start + j + 1], ARR[start + j]);
        }
    }

    std::vector<int> response(size - w + 1);
    for (std::size_t i = 0; i < size - w + 1; i++) {
        response[i] = std::min(min_right[i], min_left[i + w - 1]);
    }

    return response;
}

std::vector<int> sliding_window_minimum(std::vector<int>& ARR, uint64_t w) {
    // basically, the minimum in the sliding window is the minimum of two "offseted" vectors (min_left and min_right)
    // but:
    // min_left is computed on the fly (we only store its required element)
    // min_right is stored in the vector passed as parameter
    // the response is computed in the ARR vector directly to avoid memory allocation.
    // OPTIMIZE throw errors instead of returning empty response
    if (ARR.size() < w) {
        return {};
    }
    if (w == 0) {
        return ARR;
    }
    if (w == 1) {
        return ARR;
    }

    uint64_t nbWin = ARR.size() / w;
    int nb_elem_last_window = ARR.size() % w;

    int min_left = ARR[0];
    for (uint64_t i = 0; i < w; i++) {
        min_left = std::min(min_left, ARR[i]);
    }

    for (uint64_t i = 0; i < nbWin - 1; i++) {
        int start_window = i * w;
        for (int indice = start_window + w - 2; indice >= start_window; indice--) {
            // we compute "min_right" here, directly in ARR vector
            ARR[indice] = std::min(ARR[indice + 1], ARR[indice]);
        }

        for (uint64_t j = 0; j < w; j++) {
            ARR[start_window + j] = std::min(ARR[start_window + j], min_left);
            min_left = (j == 0) ? ARR[start_window + w + j] : std::min(min_left, ARR[start_window + w + j]);
        }
    }

    // last window

    // compute min_right for last window
    int start_window = (nbWin - 1) * w;
    for (int indice = start_window + w - 2; indice >= start_window; indice--) {
        ARR[indice] = std::min(ARR[indice + 1], ARR[indice]);
    }

    // compute the min for the last window
    for (int j = 0; j < nb_elem_last_window; j++) {
        ARR[start_window + j] = std::min(ARR[start_window + j], min_left);
        min_left = (j == 0) ? ARR[start_window + w + j] : std::min(min_left, ARR[start_window + w + j]);
    }

    ARR[start_window + nb_elem_last_window] = std::min(ARR[start_window + nb_elem_last_window], min_left);
    for (std::size_t i = 0; i < w - 1; i++) {
        ARR.pop_back();
    }

    return ARR;
}