import numpy as np
import math


def main(square_size):
    end_node = square_size**2 - 1

    # pareto
    a, m = 3, 1
    s = np.random.pareto(a, 100) + m
    with open("paredo.csv", "w") as f:
        for x in s:
            x = max(1, x)
            x = min(20, x)
            f.write(str(0)+",0,"+str(end_node)+","+str(int(x))+"\n")

    # normal
    mu, sigma = 10, 4
    n = np.random.normal(mu, sigma, 100)
    with open("normal.csv", "w") as f:
        for x in n:
            x = max(1, x)
            x = min(20, x)
            f.write(str(0)+",0,"+str(end_node)+","+str(int(x))+"\n")

    # uniform
    u = np.random.uniform(0, 20, 100)
    with open("uniform.csv", "w") as f:
        for x in u:
            x = max(1, x)
            x = min(20, x)
            f.write(str(0)+",0,"+str(end_node)+","+str(int(x))+"\n")


if __name__ == "__main__":
    main(4)
