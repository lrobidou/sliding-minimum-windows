# sliding-minimum-windows
Benchmark of algorithms for finding minimum in sliding windows

## How to compile
```bash
git clone https://github.com/lrobidou/sliding-minimum-windows
cd sliding-minimum-windows
g++ main.cpp min.cpp -o sliding -O3
```

Execute the benchmark:
```
./sliding
```

It will create 3 json files in the json folder. On file contains the benchmark for a random input vector, another one the benchmark for increasing input vector and the last one the benchmark for a decreasing input vector.

Then, plot the graphs:
```
python sliding.py
```
(python 3 is required, as well as matplotlib)

The python script will output its graph in the figs folder.

# Algorithms tested
- the naive one: recompute each window
- keeping a reference to the last min value: recompute each windows from the last minimum value only
- the fixed window approach (not in place), as described in the paper
- **our proposal**: the fixed window approach in place, as described in the paper
- deque: a deque-based solution
- deque in place: the deque approach, but with in place (preventing dynamic memory allocation for the output vector)
- rotation deque: a deque that reuse the memory of old element to limit memory allocation of the deque itself