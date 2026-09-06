// 2021-07-07 15:20:27 
import java.io.*;
import java.util.HashMap;

public class Main {
    public static boolean searching;
    public static BufferedReader bi;
    public static BufferedWriter bw;
    public static void main(String[] args) throws IOException {
        bi = new BufferedReader(new InputStreamReader(System.in));
        bw = new BufferedWriter(new OutputStreamWriter(System.out));

        // depth first search
        searching = true;
        Node startNode = new Node(0, 0);
        Node.nodeMap.put(startNode.posKey(), startNode);
        if (!startNode.search(0)) {
            bw.write("no way out" + '\n');
            bw.flush();
        }
    }

    public static class Node {
        public static HashMap<String, Node> nodeMap = new HashMap<>();
        public int x;
        public int y;
        public Node(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public boolean search(int prevI) throws IOException {
            int[][] offsets = new int[][] { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
            String[] commands = new String[] { "left", "up", "right", "down" };
            for (int i = prevI; i < 4 + prevI; i++) {
                int[] o = offsets[i % 4];
                int x = this.x + o[0];
                int y = this.y + o[1];
                String key = x + "," + y;
                if (!nodeMap.containsKey(key)) {
                    // send command
                    bw.write(commands[i % 4] + '\n');
                    bw.flush();

                    // handle response
                    String response = bi.readLine();
                    if (response.equals("ok")) {
                        Node node = new Node(x, y);
                        nodeMap.put(key, node);
                        if (node.search(i % 4)) // recursive call
                            return true;

                        // undo move
                        bw.write(commands[(i + 2) % 4] + '\n');
                        bw.flush();
                        response = bi.readLine();
                        if (!response.equals("ok"))
                            throw new Error("YABE");
                    } else if (response.equals("solved")) {
                        return true;
                    }
                }
            }
            return false;
        }

        public String posKey() {
            return x + "," + y;
        }
    }
}