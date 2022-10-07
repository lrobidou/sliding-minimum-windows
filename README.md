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
./sliding > list_of_random_integers.json
```

By default, the input vector is random. You change this by modyfying `main.cpp`:
```cpp
        in.push_back(uni(rng));
        // in.push_back(i);
        // in.push_back(size - 1 - i);
```
uncomment the first line to push random elements<br>
uncomment the seconf line to push increasing elements<br>
uncomment the third line to push decreasing elements

Do not forget to recompile each time you modify the source.
```
g++ main.cpp min.cpp -o sliding -O3
./sliding > list_of_random_integers.json
# modify main.cpp
g++ main.cpp min.cpp -o sliding -O3
./sliding > list_of_decreasing_integers.json
# modify main.cpp
g++ main.cpp min.cpp -o sliding -O3
./sliding > list_of_increasing_integers.json
```

Then, plot the graphs:
```
python sliding.py
```
(python 3 is required, as well as matplotlib)

