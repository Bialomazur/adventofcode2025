import java.io.*;
import java.util.*;

public class Main {
    static class Point {
        int x, y, z, id;

        Point(int x, int y, int z, int id) {
            this.x = x;
            this.y = y;
            this.z = z;
            this.id = id;
        }
    }

    static class Edge implements Comparable<Edge> {
        int a, b;
        long distSq;

        Edge(int a, int b, long distSq) {
            this.a = a;
            this.b = b;
            this.distSq = distSq;
        }

        @Override
        public int compareTo(Edge other) {
            return Long.compare(this.distSq, other.distSq);
        }
    }

    static class DSU {
        int[] parent;
        int[] size;

        DSU(int n) {
            parent = new int[n];
            size = new int[n];
            for (int i = 0; i < n; i++) {
                parent[i] = i;
                size[i] = 1;
            }
        }

        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        boolean union(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);

            if (rootX == rootY) {
                return false;
            }

            if (size[rootX] < size[rootY]) {
                parent[rootX] = rootY;
                size[rootY] += size[rootX];
            } else {
                parent[rootY] = rootX;
                size[rootX] += size[rootY];
            }
            return true;
        }

        int getSize(int x) {
            return size[find(x)];
        }
    }

    public static void main(String[] args) {
        try {
            List<Point> points = new ArrayList<>();
            BufferedReader br = new BufferedReader(new FileReader("input.txt"));
            String line;
            int id = 0;

            // Read all points
            while ((line = br.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty()) continue;

                String[] parts = line.split(",");
                int x = Integer.parseInt(parts[0].trim());
                int y = Integer.parseInt(parts[1].trim());
                int z = Integer.parseInt(parts[2].trim());

                points.add(new Point(x, y, z, id++));
            }
            br.close();

            int n = points.size();

            // Generate all edges with squared distances
            List<Edge> edges = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                Point p1 = points.get(i);
                for (int j = i + 1; j < n; j++) {
                    Point p2 = points.get(j);
                    long dx = p1.x - p2.x;
                    long dy = p1.y - p2.y;
                    long dz = p1.z - p2.z;
                    long distSq = dx * dx + dy * dy + dz * dz;
                    edges.add(new Edge(i, j, distSq));
                }
            }

            // Sort edges by distance (squared distance is fine for comparison)
            Collections.sort(edges);

            // Initialize DSU
            DSU dsu = new DSU(n);

            // Process exactly 1000 edges (even if they don't result in a union)
            int edgesProcessed = 0;
            int edgeIndex = 0;

            while (edgesProcessed < 1000 && edgeIndex < edges.size()) {
                Edge edge = edges.get(edgeIndex);
                dsu.union(edge.a, edge.b); // Try to union, but count regardless of success
                edgesProcessed++;
                edgeIndex++;
            }

            // If we run out of edges before reaching 1000, we have a problem
            if (edgesProcessed < 1000) {
                System.err.println("Warning: Only " + edgesProcessed + " edges available, need 1000");
            }

            // Count circuit sizes
            Map<Integer, Integer> circuitSizes = new HashMap<>();
            for (int i = 0; i < n; i++) {
                int root = dsu.find(i);
                circuitSizes.put(root, dsu.getSize(i));
            }

            // Get all circuit sizes and sort descending
            List<Integer> sizes = new ArrayList<>(circuitSizes.values());
            Collections.sort(sizes, Collections.reverseOrder());

            // Multiply the three largest circuits
            long result = 1L;
            for (int i = 0; i < Math.min(3, sizes.size()); i++) {
                result *= sizes.get(i);
            }

            System.out.println(result);

        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
            System.exit(1);
        }
    }
}