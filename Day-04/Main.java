import java.io.*;
import java.nio.file.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        // Read input (replace with your actual input file path or use System.in)
        List<String> lines = Files.readAllLines(Paths.get("input.txt"));

        int rows = lines.size();
        int cols = lines.get(0).length();

        char[][] grid = new char[rows][cols];
        for (int i = 0; i < rows; i++) {
            grid[i] = lines.get(i).toCharArray();
        }

        int accessible = 0;

        // 8 possible directions (including diagonals)
        int[] dr = {-1, -1, -1,  0, 0,  1, 1, 1};
        int[] dc = {-1,  0,  1, -1, 1, -1, 0, 1};

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '@') {
                    int neighbors = 0;
                    for (int d = 0; d < 8; d++) {
                        int nr = r + dr[d];
                        int nc = c + dc[d];
                        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == '@') {
                            neighbors++;
                        }
                    }
                    if (neighbors < 4) {
                        accessible++;
                    }
                }
            }
        }

        System.out.println("Number of rolls accessible by forklift: " + accessible);
    }
}