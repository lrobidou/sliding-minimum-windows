import json
import matplotlib.pyplot as plt

def removesuffix(s: str, suffix: str) -> str:
    # suffix='' should not call s[:-0].
    if suffix and s.endswith(suffix):
        return s[:-len(suffix)]
    else:
        return s[:]

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
        "list_of_random_integers.json",
        "list_of_increasing_integers.json",
        "list_of_decreasing_integers.json",
    ]
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
                removesuffix(filename, ".json").replace("_", " ")
                + f" (size of window: {w})"
            )
            plt.title(title)
            plt.legend(loc="best")
            plt.xlabel("size of input vector")
            plt.ylabel("time (seconds), for 10000 instances")
            plt.savefig("figs/" + title + ".png")
            plt.clf()


if __name__ == "__main__":
    main()
