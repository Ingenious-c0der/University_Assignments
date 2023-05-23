from collections import deque

# For Queue
# PopLeft and Append 

# Class representing a graph using adjacency list representation
class Graph:
    def __init__(self):
        # Dictionary to store the adjacency list
        self.adj_list = {}

    # Function to add an edge to the graph
    def add_edge(self, vertex, edge):
        if vertex in self.adj_list:
            self.adj_list[vertex].append(edge)
        else:
            self.adj_list[vertex] = [edge]

    # Recursive function for DFS traversal
    def dfs_recursive(self, vertex, visited):
        # Mark the current vertex as visited
        visited.add(vertex)
        print(vertex, end=" ")

        # Check if the vertex has any adjacent vertices
        if vertex in self.adj_list:
            # Recur for all the adjacent vertices
            for adjacent_vertex in self.adj_list[vertex]:
                if adjacent_vertex not in visited:
                    self.dfs_recursive(adjacent_vertex, visited)

    # DFS traversal starting from a given vertex
    def dfs(self, start_vertex):
        visited = set()  # Set to keep track of visited vertices
        self.dfs_recursive(start_vertex, visited)
        print()

    # BFS traversal starting from a given vertex
    def bfs(self, start_vertex):
        visited = set()  # Set to keep track of visited vertices
        queue = deque()  # Queue for BFS

        # Mark the start vertex as visited and enqueue it
        visited.add(start_vertex)
        queue.append(start_vertex)

        while queue:
            # Dequeue a vertex from the queue and print it
            vertex = queue.popleft()
            print(vertex, end=" ")

            if vertex in self.adj_list:
                # Get all adjacent vertices of the dequeued vertex
                # If a neighbor has not been visited, mark it as visited and enqueue it
                for adjacent_vertex in self.adj_list[vertex]:
                    if adjacent_vertex not in visited:
                        visited.add(adjacent_vertex)
                        queue.append(adjacent_vertex)

        print()


graph = Graph()

# Add edges to the graph
graph.add_edge('A', 'B')
graph.add_edge('A', 'C')
graph.add_edge('A', 'D')
graph.add_edge('B', 'E')
graph.add_edge('C', 'F')
graph.add_edge('D', 'G')

# Perform DFS starting from vertex 'A'
print("DFS traversal:")
graph.dfs('A')

# Perform BFS starting from vertex 'A'
print("BFS traversal:")
graph.bfs('A')