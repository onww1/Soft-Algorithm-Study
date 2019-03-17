package break_codingtest;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;
public class BJchuijun_2636 {
	static int [][] map;
	static boolean [][] visited;
	static int [] dx = {1, 0, -1, 0};
	static int [] dy = {0, 1, 0, -1};
	static int chCnt, H, W;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		StringBuilder sb = new StringBuilder();
		H = Integer.parseInt(st.nextToken());
		W = Integer.parseInt(st.nextToken());
		map = new int[H][W];
		int curCheeze = 0;
		chCnt = 0;
		for(int i = 0; i < H; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < W; j++) {
				curCheeze = Integer.parseInt(st.nextToken());
				map[i][j] = curCheeze;
				if(curCheeze == 1) {
					chCnt++;
				}
			}
		}
		int someHoursLater = 0, leftCh = 0;
		while(chCnt > 0) {
			leftCh = chCnt;
			visited = new boolean[H][W];
			gonggi(0,0);
			someHoursLater++;
		}
		sb.append(someHoursLater).append("\n").append(leftCh);
		System.out.println(sb.toString());
	}
	public static void gonggi(int cy, int cx) {
		Queue<pos> q = new LinkedList<>();
		visited[cy][cx] = true;
		q.offer(new pos(cy,cx));
		pos p;
		int ny, nx;
		while(!q.isEmpty()) {
			p = q.poll();
			for(int i = 0; i < 4; i++) {
				ny = p.y + dy[i];
				nx = p.x + dx[i];
				if(isRanged(ny, nx) && !visited[ny][nx]) {
					visited[ny][nx] = true;
					if(map[ny][nx] == 1) {
						map[ny][nx] = 0;
						chCnt--;
					}else {
						q.offer(new pos(ny,nx));
					}
				}
			}
		}
	}
	public static boolean isRanged(int y, int x) {
		if(y >= 0 && y < H && x >= 0 && x < W) {
			return true;
		}
		return false;
	}
	static class pos{
		int y;
		int x;
		pos(int y, int x){
			this.y = y;
			this.x = x;
		}
	}
}