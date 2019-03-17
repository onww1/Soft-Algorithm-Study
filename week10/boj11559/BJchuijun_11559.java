package break_codingtest;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

// . -2
// R 34
// G 23
// B 18
// P 32
// Y 41

/**
 * boj 11559 Puyo Puyo
 * 
 *
 */
public class BJchuijun_11559 {
	static int[][] map;
	static boolean[][] visit;
	static int[] dx = {1, 0, -1, 0};
	static int[] dy = {0, 1, 0, -1};
	static boolean endflag;
	static int totalans;
	public static void main(String[] args) throws IOException {

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		map = new int[12][6];
		
		String str;
		for(int i = 0; i < 12; i++) {
			str = br.readLine();
			for(int j = 0; j < 6; j++) {
				map[i][j] = str.charAt(j) - '0';
			}
		}
		totalans = 0;
		endflag = true;
		while(endflag) {
			endflag = false;
			for(int i = 0; i < 12; i++) {
				for(int j = 0; j < 6; j++) {
					if(map[i][j] > 0) {
						bfs(i,j);
						
					}
				}
			}
			if(endflag) {
				totalans++;
				gobottom();
			}
		}
		System.out.println(totalans);
	}
	public static void gobottom() {
		int tempy;
		boolean flag = false;
		for(int i = 0; i < 6; i++) {
			for(int j = 11; j >= 1; j--) {
				flag = false;
				if(map[j][i] < 0) {
					tempy = j;
					while(map[--tempy][i] < 0) {
						if(tempy == 0) {
							flag = true;
							j = 0;
							break;
						}
					}
					if(!flag) {
						map[j][i] = map[tempy][i];
						map[tempy][i] = -2;
					}
				}
			}
		}
	}
	public static void bfs(int cy, int cx) {
		int curN = map[cy][cx];
		int cost = 1;
		Queue<pos> q = new LinkedList<pos>();
		Queue<pos> bombq = new LinkedList<pos>();
		visit = new boolean[12][6];
		visit[cy][cx] = true;
		pos p;
		q.offer(new pos(cy,cx));
		bombq.offer(new pos(cy,cx));
		int ny, nx;
		while(!q.isEmpty()) {
			p = q.poll()	;
			for(int i = 0; i<4; i++) {
				ny = p.y + dy[i];
				nx = p.x + dx[i];
				if(isRanged(ny,nx) && !visit[ny][nx] && map[ny][nx] == curN) {
					cost++;
					visit[ny][nx] = true;
					q.offer(new pos(ny,nx));
					bombq.offer(new pos(ny,nx));
				}
			}
		}
		if(cost >= 4) {
			endflag = true;
			pos bombp;
			while(!bombq.isEmpty()) {
				bombp = bombq.poll();
				map[bombp.y][bombp.x] = -2;
			}
		}
	}
	public static boolean isRanged(int y, int x) {
		if(y >= 0 && y < 12 && x >= 0 && x < 6) {
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
