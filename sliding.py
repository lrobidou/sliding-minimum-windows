import json
import matplotlib.pyplot as plt


def main():
    filenames = [
        "list_of_random_integers.json",
        "list_of_increasing_integers.json",
        "list_of_decreasing_integers.json",
    ]
    dicts = []
    for filename in filenames:
        with open(filename) as fichier:
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
                    "+",
                    linestyle=loosely_dashed,
                    label=strategy,
                    markersize=12,
                    markeredgewidth=4,
                )
            title = (
                filename.removesuffix(".json").replace("_", " ")
                + f" (size of window: {w})"
            )
            plt.title(title)
            plt.legend(loc="best")
            plt.xlabel("size of input vector")
            plt.ylabel("time (seconds), for 10000 instances")
            plt.savefig(title + ".png")
            plt.clf()


if __name__ == "__main__":
    main()
