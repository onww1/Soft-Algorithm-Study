package break_codingtest;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

// # 35
// * 42
// @ 64
// . 46
public class BJchuijun_5427 {

	static int[][] map;
	static int H, W;
	static int[] dx = { 1, 0, -1, 0 };
	static int[] dy = { 0, 1, 0, -1 };
	static Queue<pos> fq;

	public static void main(String[] args) throws NumberFormatException, IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		StringBuilder sb = new StringBuilder();
		int T = Integer.parseInt(br.readLine());
		String str;
		int res;
		for (int t = 1; t <= T; t++) {
			st = new StringTokenizer(br.readLine());
			W = Integer.parseInt(st.nextToken());
			H = Integer.parseInt(st.nextToken());
			fq = new LinkedList<>();
			map = new int[H][W];
			int sy = 0, sx = 0;
			int curN;
			for (int i = 0; i < H; i++) {
				str = br.readLine();
				for (int j = 0; j < W; j++) {
					curN = str.charAt(j) - 0;
					map[i][j] = curN;
					if (curN == 42) {
						fq.offer(new pos(i, j));
					}
					if (curN == 64) {
						sy = i;
						sx = j;
					}
				}
			}
			res = bfs(sy, sx);
			if (res < 0) {
				sb.append("IMPOSSIBLE");
			} else {
				sb.append(res);
			}
			sb.append("\n");
		}
		System.out.print(sb.toString());
	}

	public static int bfs(int cy, int cx) {
		Queue<pos> q = new LinkedList<>();
		boolean visit[][] = new boolean[H][W];
		visit[cy][cx] = true;
		q.offer(new pos(cy, cx, 1));
		pos p;
		int ny, nx;
		int curstep = 0;
		while (!q.isEmpty()) {
			p = q.poll();
			if(curstep != p.cost) {
				Fire();
				curstep = p.cost;
			}
			
			for (int i = 0; i < 4; i++) {
				ny = p.y + dy[i];
				nx = p.x + dx[i];
				if (isRanged(ny, nx)) {
					if (!visit[ny][nx] && map[ny][nx] != 35 && map[ny][nx] != 42) {
						visit[ny][nx] = true;
						q.offer(new pos(ny, nx, p.cost + 1));
					}
				} else {
					return p.cost;
				}
			}
		}
		return -1;
	}

	public static void Fire() {
		int size = fq.size();
		pos p;
		int ny, nx;
		for (int i = 0; i < size; i++) {
			p = fq.poll();
			for (int j = 0; j < 4; j++) {
				ny = p.y + dy[j];
				nx = p.x + dx[j];
				if (isRanged(ny, nx) && map[ny][nx] != 35 && map[ny][nx] != 42) {
					map[ny][nx] = 42;
					fq.offer(new pos(ny, nx));
				}
			}
		}
	}

	public static boolean isRanged(int y, int x) {
		if (y >= 0 && y < H && x >= 0 && x < W) {
			return true;
		}
		return false;
	}

	static class pos {
		int y;
		int x;
		int cost;

		pos(int y, int x) {
			this.y = y;
			this.x = x;
		}

		pos(int y, int x, int cost) {
			this.y = y;
			this.x = x;
			this.cost = cost;
		}

	}

}
