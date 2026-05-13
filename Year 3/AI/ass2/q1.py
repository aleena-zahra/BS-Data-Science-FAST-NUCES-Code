# aleena zahra 23i2514 ds-b assignment 2 question 1


import random

def knapsack_ga(weights, values, sizes, max_weight=10, max_size=10,
                pop_size=50, max_gen=200, mut_prob=0.01):
    """Solve a constrained knapsack problem using a genetic algorithm.

    Args:
        weights (list[int | float]): Weight of each item.
        values (list[int | float]): Value of each item.
        sizes (list[int | float]): Size/volume of each item.
        max_weight (int | float): Maximum allowed total weight.
        max_size (int | float): Maximum allowed total size.
        pop_size (int): Number of individuals in each generation.
        max_gen (int): Number of generations to evolve.
        mut_prob (float): Per-gene mutation probability.

    Returns:
        tuple[list[int], int | float]: Best binary solution and its fitness.
    """

    n = len(weights)

    def random_individual():
        """Generate a random binary chromosome of length n."""
        # Each gene indicates whether the corresponding item is selected.
        return [random.randint(0, 1) for _ in range(n)]

    def fitness(ind):
        """Compute total value if constraints are satisfied, else return 0."""
        # Convert a binary chromosome into aggregate weight, size, and value.
        total_w = sum(ind[i] * weights[i] for i in range(n))
        total_s = sum(ind[i] * sizes[i] for i in range(n))
        total_v = sum(ind[i] * values[i] for i in range(n))

        # Penalize infeasible solutions by assigning zero fitness.
        if total_w > max_weight or total_s > max_size:
            return 0
        return total_v

    def roulette_selection(pop, fits):
        """Select one individual with probability proportional to fitness."""
        total = sum(fits)
        # If all fitness values are zero, fall back to a random pick.
        if total == 0:
            return random.choice(pop)
        r = random.uniform(0, total)
        acc = 0
        for ind, f in zip(pop, fits):
            acc += f
            if acc >= r:
                return ind
        return pop[-1]

    def crossover(p1, p2):
        """Create two children by single-point crossover."""
        point = random.randint(1, n - 1)
        return (
            p1[:point] + p2[point:],
            p2[:point] + p1[point:]
        )

    def mutate(ind):
        """Flip each gene with probability mut_prob."""
        return [
            1 - g if random.random() < mut_prob else g
            for g in ind
        ]

    # Initialize the starting population.
    population = [random_individual() for _ in range(pop_size)]

    # Evolve the population across generations.
    for _ in range(max_gen):
        fitnesses = [fitness(ind) for ind in population]

        new_pop = []
        while len(new_pop) < pop_size:
            # Select parents, recombine, then mutate offspring.
            p1 = roulette_selection(population, fitnesses)
            p2 = roulette_selection(population, fitnesses)
            c1, c2 = crossover(p1, p2)
            new_pop.extend([mutate(c1), mutate(c2)])

        # Keep population size fixed.
        population = new_pop[:pop_size]

    # Return the best individual found after evolution.
    best = max(population, key=fitness)
    return best, fitness(best)

# run example
if __name__ == "__main__":
    # Example 1 (kept for reference).
    weights = [2, 3, 4, 5]
    values = [3, 4, 5, 6]
    sizes = [1, 2, 3, 4]
    max_weight = 5
    max_size = 3

    # Example 2 (used in execution below).
    weights = [1, 3, 7, 4, 5, 6]
    values = [14, 23, 8, 9, 17, 15]
    sizes = [1, 1, 1, 1, 1, 1]
    max_weight = 10
    max_size = 10

    # Run the GA and print the best feasible solution.
    solution, value = knapsack_ga(weights, values, sizes, max_weight, max_size)
    print("Best solution:", solution)
    print("Best value:", value)