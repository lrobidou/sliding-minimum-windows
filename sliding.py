import json
import matplotlib.pyplot as plt

def get_marker(strategy):
    d = {
        "computing from last min" : "1",
        "fixed windows" : "2",
        "fixed windows in place" : "3",
        "deque" : "4",
        "deque in place" : ".",
        "deque rotation" : "+",
        "recomputing" : "*"
    }
    return d[strategy]

def main():
    filenames = [
        "benchmark_input_is_vectors_of_random_integers.json",
        "benchmark_input_is_vectors_of_increasing_integers.json",
        "benchmark_input_is_vectors_of_decreasing_integers.json",
    ]
    fig_names = {
        "benchmark_input_is_vectors_of_random_integers.json": "benchmark execution on input consisting of random integers",
        "benchmark_input_is_vectors_of_increasing_integers.json": "benchmark execution on input consisting of increasing integers",
        "benchmark_input_is_vectors_of_decreasing_integers.json": "benchmark execution on input consisting of decreasing integers",
    }
    dicts = []
    for filename in filenames:
        with open("json/" + filename) as fichier:
            dicts.append(json.load(fichier))
    sizes = sorted([int(x) for x in dicts[0].keys()])
    ws = sorted([int(x) for x in dicts[0][str(sizes[0])].keys()])
    loosely_dashed = (0, (5, 10))

    for w in ws:

        for d, filename in zip(dicts, filenames):
            res = {}
            sizes = sorted([int(x) for x in d.keys()])
            for size in sizes:
                data_for_every_strategy = d[str(size)][str(w)]
                for strategy, t in data_for_every_strategy.items():
                    res[strategy] = res.get(strategy, []) + [t]
            for strategy in data_for_every_strategy:
                plt.plot(
                    sizes,
                    res[strategy],
                    get_marker(strategy),
                    linestyle=loosely_dashed,
                    label=strategy,
                    markersize=10,
                    markeredgewidth=4,
                )
            title = (
                fig_names[filename] + f"\n(size of window: {w})"
            )
            plt.title(title)
            plt.legend(loc="best")
            plt.xlabel("size of input vector")
            plt.ylabel("time (micro seconds), for 10000 instances")
            plt.savefig("figs/" + title + ".png")
            plt.clf()


if __name__ == "__main__":
    main()
