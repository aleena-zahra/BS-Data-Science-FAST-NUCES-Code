# aleena zahra 23i2514 ds-b assignment 2 question 2

import time
import copy
from collections import deque


# CSP Solver Class

class CSPSolver:
    def __init__(self):
        """
        Initialize CSP components.
        """
        self.variables = []
        self.domains = {}
        self.constraints = {}
        self.backtracks = 0

    def add_variable(self, var, domain):
        """Add variable and its domain."""
        self.variables.append(var)
        self.domains[var] = list(domain)

    def add_constraint(self, var1, var2, constraint_fn):
        """Add a binary constraint."""
        self.constraints[(var1, var2)] = constraint_fn
        self.constraints[(var2, var1)] = lambda b, a: constraint_fn(a, b)

    def is_consistent(self, var, value, assignment):
        """Check consistency of var=value with assignment."""
        for (v1, v2), constraint in self.constraints.items():
            if v1 == var and v2 in assignment:
                if not constraint(value, assignment[v2]):
                    return False
        return True

    def select_unassigned_variable(self, assignment, use_heuristics=False):
        unassigned = [v for v in self.variables if v not in assignment]

        if not use_heuristics:
            return unassigned[0]

        # MRV
        min_domain = min(len(self.domains[v]) for v in unassigned)
        mrv_vars = [v for v in unassigned if len(self.domains[v]) == min_domain]

        if len(mrv_vars) == 1:
            return mrv_vars[0]

        # Degree heuristic
        def degree(var):
            return sum(
                1 for (v1, v2) in self.constraints
                if var in (v1, v2)
                and v1 not in assignment
                and v2 not in assignment
            )

        return max(mrv_vars, key=degree)

    def order_domain_values(self, var, assignment):
        """Return domain values (simple order)."""
        return self.domains[var]

    def backtrack(self, assignment, use_fc=False, use_heuristics=False):
        if len(assignment) == len(self.variables):
            return assignment

        var = self.select_unassigned_variable(assignment, use_heuristics)

        for value in self.order_domain_values(var, assignment):
            if self.is_consistent(var, value, assignment):
                assignment[var] = value
                saved_domains = copy.deepcopy(self.domains)

                if use_fc:
                    if not self.forward_check(var, value, assignment):
                        self.domains = saved_domains
                        del assignment[var]
                        #self.backtracks += 1
                        continue

                result = self.backtrack(assignment, use_fc, use_heuristics)
                if result:
                    return result

                self.domains = saved_domains
                del assignment[var]
        self.backtracks += 1

        return None

    def forward_check(self, var, value, assignment):
        for (v1, v2), constraint in self.constraints.items():
            if v1 == var and v2 not in assignment:
                self.domains[v2] = [
                    v for v in self.domains[v2]
                    if constraint(value, v)
                ]
                if not self.domains[v2]:
                    return False
        return True

    def revise(self, xi, xj):
        revised = False
        constraint = self.constraints.get((xi, xj))
        if not constraint:
            return False

        for x in self.domains[xi][:]:
            if not any(constraint(x, y) for y in self.domains[xj]):
                self.domains[xi].remove(x)
                revised = True
        return revised

    def ac3(self):
        queue = deque(self.constraints.keys())

        while queue:
            xi, xj = queue.popleft()
            if self.revise(xi, xj):
                if not self.domains[xi]:
                    return False
                for (xk, xl) in self.constraints:
                    if xl == xi and xk != xj:
                        queue.append((xk, xi))
        return True

    def solve(self, use_fc=False, use_heuristics=False,silent=False):
        self.backtracks = 0
        start = time.time()
        original_domains = copy.deepcopy(self.domains)
        if not self.ac3():
            print("AC-3 found CSP unsolvable")
            return None

        if not silent:
            print("AC-3 complete.")
            #  Check if domains actually changed
            if original_domains == self.domains:
                print("Domains unchanged (AC-3 did not prune any values for this problem)")
            else:
                print("Reduced domains:")
                for v in self.variables:
                    print(f"  {v} : {self.domains[v]}")

        solution = self.backtrack({}, use_fc, use_heuristics)
        end = time.time()
        
        # Only print the full block if not in compare queens mode
        if not silent:
            print(f"Solution: {solution}")
            print(f"Backtracks: {self.backtracks}")
            print(f"Time: {end - start:.4f}s\n")

        return solution
    

def australia_map():
    csp = CSPSolver()
    colors = ['R', 'G', 'B']

    regions = ['WA', 'NT', 'SA', 'Q', 'NSW', 'V', 'T']
    for r in regions:
        csp.add_variable(r, colors)

    adj = [
        ('WA','NT'), ('WA','SA'), ('NT','SA'), ('NT','Q'),
        ('SA','Q'), ('SA','NSW'), ('SA','V'),
        ('Q','NSW'), ('NSW','V')
    ]

    for a, b in adj:
        csp.add_constraint(a, b, lambda x, y: x != y)

    print("Solving: Australia Map Coloring")
    csp.solve(use_fc=True, use_heuristics=True)

australia_map()


def n_queens(n):
    csp = CSPSolver()
    for i in range(n):
        csp.add_variable(f"Q{i}", range(n))

    for i in range(n):
        for j in range(i + 1, n):
            csp.add_constraint(
                f"Q{i}", f"Q{j}",
                lambda a, b, i=i, j=j: a != b and abs(a - b) != abs(i - j)
            )
    return csp

def compare_queens():
    print("Problem: 4-Queens\n")
    print("┌────────────────────────────────────────┬────────────┬────────┐")
    print("│ Mode                                   │ Backtracks │ Time   │")
    print("├────────────────────────────────────────┼────────────┼────────┤")

    for label, fc, h in [
        ("Backtracking only", False, False),
        ("Backtracking + Forward Checking", True, False),
        ("Backtracking + FC + MRV + Degree", True, True),
    ]:
        csp = n_queens(4)
        start = time.time()
        csp.solve(use_fc=fc, use_heuristics=h,silent=True)
        t = (time.time() - start) * 1000
        print(f"│ {label:<38} │ {csp.backtracks:^10} │ {t:>5.1f}ms │")

    print("└────────────────────────────────────────┴────────────┴────────┘")

compare_queens()

def solve_sudoku(grid):
    """
    grid: A 9x9 list of lists where 0 represents an empty cell.
    """
    csp = CSPSolver()
    
    # 1. Variables: Cell names 'R1C1', 'R1C2', etc.
    # 2. Domains: {1..9} for empty cells, [fixed_value] for known cells.
    for r in range(9):
        for c in range(9):
            var_name = f"R{r}C{c}"
            if grid[r][c] == 0:
                csp.add_variable(var_name, range(1, 10))
            else:
                csp.add_variable(var_name, [grid[r][c]])

    # 3. Constraints
    def not_equal(a, b): return a != b

    for r in range(9):
        for c in range(9):
            v1 = f"R{r}C{c}"
            
            # Row constraints
            for c2 in range(c + 1, 9):
                csp.add_constraint(v1, f"R{r}C{c2}", not_equal)
            
            # Column constraints
            for r2 in range(r + 1, 9):
                csp.add_constraint(v1, f"R{r2}C{c}", not_equal)
            
            # 3x3 Box constraints
            box_r, box_c = (r // 3) * 3, (c // 3) * 3
            for r2 in range(box_r, box_r + 3):
                for c2 in range(box_c, box_c + 3):
                    v2 = f"R{r2}C{c2}"
                    if v1 != v2:
                        # Ensure we don't add the same constraint twice
                        if (v1, v2) not in csp.constraints:
                            csp.add_constraint(v1, v2, not_equal)

    print("\nSolving: Sudoku Puzzle")
    # Use heuristics (MRV) because Sudoku is very slow without it!
    solution=csp.solve(use_fc=True, use_heuristics=True)
    if solution:
        print_sudoku(solution)

# Example puzzle (0 = empty)
easy_sudoku = [
    [5, 3, 0, 0, 7, 0, 0, 0, 0],
    [6, 0, 0, 1, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9]
]
def print_sudoku(solution):
    """Prints the CSP solution dictionary as a 9x9 grid."""
    if not solution:
        print("No solution found.")
        return

    print("+" + "-------+" * 3)
    for r in range(9):
        row_str = "| "
        for c in range(9):
            val = solution.get(f"R{r}C{c}", ".")
            row_str += str(val) + " "
            if (c + 1) % 3 == 0:
                row_str += "| "
        print(row_str)
        if (r + 1) % 3 == 0:
            print("+" + "-------+" * 3)
solve_sudoku(easy_sudoku)
