
#  name: Aleena Zahra
#  roll number: 23i2514
#  section: DS-B
import heapq
import time
import os
from colorama import init, Fore, Back

init(autoreset=True)

STONE = 1
DESK = 2
INK = 4
WALL = -1


class Maze:
    def __init__(self):

        self.grid = [
            [1,1,1,1,-1,1,1,1,1,1],
            [1,4,4,1,-1,1,2,2,1,1],
            [1,4,1,1,1,1,-1,2,1,1],
            [1,1,1,-1,-1,1,1,1,1,1],
            [-1,-1,1,1,1,1,1,1,-1,-1],
            [1,1,1,1,4,4,1,1,1,1],
            [1,2,2,1,4,1,1,-1,-1,1],
            [1,2,1,1,1,-1,1,1,4,1],
            [1,1,1,-1,-1,1,4,4,4,1],
            [1,1,1,1,-1,1,1,1,1,1],
        ]

        self.rows = 10
        self.cols = 10

        self.start = (0,0)
        self.goal = (9,9)

    def in_bounds(self,r,c):
        return 0 <= r < self.rows and 0 <= c < self.cols

    def claustrophobic(self,r,c):
        directions = [(1,0),(-1,0),(0,1),(0,-1)]
        wall_count = 0

        for dr,dc in directions:
            nr,nc = r+dr,c+dc
            if self.in_bounds(nr,nc) and self.grid[nr][nc] == WALL:
                wall_count += 1

        return wall_count > 2

    def passable(self,r,c):
        return self.grid[r][c] != WALL and not self.claustrophobic(r,c)

    def cost(self,r,c):
        return self.grid[r][c]

    def neighbors(self,node):
        r,c = node
        directions = [(1,0),(-1,0),(0,1),(0,-1)]

        result = []

        for dr,dc in directions:
            nr,nc = r+dr,c+dc
            if self.in_bounds(nr,nc) and self.passable(nr,nc):
                result.append((nr,nc))

        return result

    def transition(self,nr,nc,ink_active,consecutive):
        tile_cost = self.grid[nr][nc]

        if tile_cost == INK:
            consecutive += 1
        else:
            consecutive = 0

        if consecutive >= 2:
            ink_active = True

        if tile_cost == STONE:
            ink_active = False
            consecutive = 0

        move_cost = tile_cost + (2 if ink_active else 0)

        return move_cost,ink_active,consecutive

    def draw(self,explored=set(),frontier=set(),path=set()):
        os.system('cls' if os.name=='nt' else 'clear')

        for r in range(self.rows):
            for c in range(self.cols):

                cell = (r,c)

                if cell == self.start:
                    print(Back.BLUE+" S ",end="")
                elif cell == self.goal:
                    print(Back.YELLOW+" G ",end="")
                elif cell in path:
                    print(Back.GREEN+f" {self.grid[r][c]} ",end="")
                elif cell in frontier:
                    print(Back.MAGENTA+" F ",end="")
                elif cell in explored:
                    print(Back.CYAN+" E ",end="")
                elif self.grid[r][c] == WALL:
                    print(Back.BLACK+"   ",end="")
                elif self.grid[r][c] == DESK:
                    print(Fore.RED+" 2 ",end="")
                elif self.grid[r][c] == INK:
                    print(Fore.RED+" 4 ",end="")
                else:
                    print(" 1 ",end="")

            print()


        time.sleep(0.5)


def reconstruct_path(parent,start,goal):

    path=[]
    node=goal

    while node != start:
        path.append(node)
        node = parent[node]

    path.append(start)
    return path[::-1]


def manhattan(a,b):
    return abs(a[0]-b[0]) + abs(a[1]-b[1])


def ucs(maze,visualize=False):

    start_state = (maze.start[0],maze.start[1],False,0)

    pq=[]
    heapq.heappush(pq,(0,start_state))

    parent={}
    cost_so_far={start_state:0}

    explored=set()
    nodes_expanded=0

    while pq:

        cost,state = heapq.heappop(pq)

        if state in explored:
            continue

        explored.add(state)
        nodes_expanded+=1

        r,c,ink_active,consecutive = state

        if (r,c) == maze.goal:
            path = reconstruct_path(parent,start_state,state)
            return [(s[0],s[1]) for s in path],cost,nodes_expanded

        for nr,nc in maze.neighbors((r,c)):

            move_cost,new_ink,new_con = maze.transition(nr,nc,ink_active,consecutive)

            new_state = (nr,nc,new_ink,new_con)
            new_cost = cost + move_cost

            if new_state not in cost_so_far or new_cost < cost_so_far[new_state]:

                cost_so_far[new_state]=new_cost
                parent[new_state]=state
                heapq.heappush(pq,(new_cost,new_state))

        if visualize:
            frontier={s[1][:2] for s in pq}
            maze.draw(explored,frontier)

    return None,float('inf'),nodes_expanded


def astar(maze,visualize=False):

    start_state = (maze.start[0],maze.start[1],False,0)

    pq=[]
    heapq.heappush(pq,(0,start_state))

    parent={}
    g_cost={start_state:0}

    explored=set()
    nodes_expanded=0

    while pq:

        _,state = heapq.heappop(pq)

        if state in explored:
            continue

        explored.add(state)
        nodes_expanded+=1

        r,c,ink_active,consecutive = state

        if (r,c) == maze.goal:
            path = reconstruct_path(parent,start_state,state)
            return [(s[0],s[1]) for s in path],g_cost[state],nodes_expanded

        for nr,nc in maze.neighbors((r,c)):

            move_cost,new_ink,new_con = maze.transition(nr,nc,ink_active,consecutive)

            new_state = (nr,nc,new_ink,new_con)
            tentative_g = g_cost[state] + move_cost

            if new_state not in g_cost or tentative_g < g_cost[new_state]:

                g_cost[new_state]=tentative_g
                f = tentative_g + manhattan((nr,nc),maze.goal)

                parent[new_state]=state
                heapq.heappush(pq,(f,new_state))

        if visualize:
            frontier={s[1][:2] for s in pq}
            maze.draw(explored,frontier)

    return None,float('inf'),nodes_expanded


def beam_search(maze,width=3,visualize=False):

    start_state = (maze.start[0],maze.start[1],False,0)

    frontier=[(start_state,0)]
    parent={}

    explored=set()
    nodes_expanded=0

    while frontier:

        candidates=[]

        for state,g in frontier:

            if state in explored:
                continue

            explored.add(state)
            nodes_expanded+=1

            r,c,ink_active,consecutive = state

            if (r,c)==maze.goal:
                path=reconstruct_path(parent,start_state,state)
                return [(s[0],s[1]) for s in path],g,nodes_expanded

            for nr,nc in maze.neighbors((r,c)):

                move_cost,new_ink,new_con = maze.transition(nr,nc,ink_active,consecutive)

                new_state=(nr,nc,new_ink,new_con)
                new_cost=g+move_cost
                f=new_cost+manhattan((nr,nc),maze.goal)

                if new_state not in explored:
                    parent[new_state]=state
                    candidates.append((new_state,new_cost,f))

        candidates.sort(key=lambda x:x[2])

        frontier=[(s,g) for s,g,_ in candidates[:width]]

        if visualize:
            maze.draw(explored,{s[0][:2] for s in frontier})

    return None,float('inf'),nodes_expanded


def run_algorithm(name,func,maze):

    print(f"\nRunning {name}...")
    time.sleep(1)

    start=time.time()

    path,cost,expanded = func(maze)

    elapsed=time.time()-start

    maze.draw(path=set(path))
    time.sleep(1)

    return {
        "name":name,
        "cost":cost,
        "expanded":expanded,
        "time":elapsed
    }


if __name__=="__main__":

    maze=Maze()

    results=[]

    results.append(run_algorithm("Uniform Cost Search",ucs,maze))
    results.append(run_algorithm("A* Search",astar,maze))
    results.append(run_algorithm("Beam Search (W=3)",beam_search,maze))

    print("\nAlgorithm comparision\n")
    print("Algorithm                     Cost    Nodes Expanded    Time")

    for r in results:
        print(f"{r['name']:<30} {r['cost']:<7} {r['expanded']:<15} {r['time']:.4f}s")
