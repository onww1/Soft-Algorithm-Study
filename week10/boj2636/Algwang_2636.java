import java.util.Scanner;

public class Main {
   private static int N , M , count , res;
   private static int arr[][];
   private static int next[][];
   private static boolean visited[][];
   
   private static int dx[] = {-1,1,0,0};
   private static int dy[] = {0,0,-1,1};
   public static void main(String[] args) {
      Scanner sc = new Scanner(System.in);
      N = sc.nextInt();
      M = sc.nextInt();
      arr = new int[N][M];
      res = 0;
      for (int i = 0; i < N; i++) {
         for (int j = 0; j < M; j++) {
            arr[i][j] = sc.nextInt();
            if (arr[i][j] == 1) {
               count++;
            }
         }
      }
      int pcount = 0;
      while(count != 0) {
         next = arr.clone();
         visited = new boolean[N][M];
         pcount = count;
         nextTime(0, 0);
         arr = next.clone();
         res++;
      }
      System.out.println(res);
      System.out.println(pcount);
   }
   private static void nextTime(int x , int y) {
      visited[x][y] = true;
      for (int i = 0; i < dx.length; i++) {
         if (x + dx[i] >=0 && x+dx[i] < N && y + dy[i] >=0 && y+dy[i] < M && arr[x+dx[i]][y+dy[i]] == 0 && !visited[x+dx[i]][y+dy[i]]) {
            nextTime(x+dx[i],y+dy[i]);
         }
         if (x + dx[i] >=0 && x+dx[i] < N && y + dy[i] >=0 && y+dy[i] < M && arr[x+dx[i]][y+dy[i]] == 1 && !visited[x+dx[i]][y+dy[i]]) {
            visited[x+dx[i]][y+dy[i]] = true;
            next[x+dx[i]][y+dy[i]] = 0;
            count--;
         }
      }
   }
}
