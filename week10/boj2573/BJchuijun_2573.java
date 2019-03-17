package break_codingtest;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class BJchuijun_2573 {

	static int[][] land;
	static int[][] landSea;
	static int[][] visits;
	static int landCount;
	static int R;
	static int C;
	static int visitCount;
	static int year;

	static Queue<mark> q;
	static int[] dx = { 1, 0, -1, 0 }; // 우 하 좌 상
	static int[] dy = { 0, 1, 0, -1 };

	public static void main(String[] args) throws IOException {

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;

		int curyear = 0;
		st = new StringTokenizer(br.readLine());
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());

		land = new int[R][C];
		landSea = new int[R][C];
		visits = new int[R][C];

		q = new LinkedList<>();

		landCount = 0;

		for (int i = 0; i < R; i++) {
			st = new StringTokenizer(br.readLine());
			for (int j = 0; j < C; j++) {
				land[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		while (true) {
			visitCount = 0;
			q.clear();
			for (int i = 0; i < R; i++) {
				for (int j = 0; j < C; j++) {
					if (land[i][j] != 0) {
						q.add(new mark(i, j));
						landSea[i][j] = findSea(i, j);
						visits[i][j] = 0;
					}
				}
			}
			landCount = q.size();
			if (landCount == 0) {
				year = 0;
				break;
			}
			bfs();
			if (visitCount != landCount) {
				year = curyear;
				break;
			} else {
				for (int i = 0; i < R; i++) {
					for (int j = 0; j < C; j++) {
						land[i][j] -= landSea[i][j];
						if (land[i][j] < 0)
							land[i][j] = 0;
					}
				}
			}
			curyear++;
		}
		System.out.println(year);
	}
	static void bfs() {
		int cx, cy, x, y;
		mark sm = q.poll();
		q.clear();
		q.offer(sm);

		while (!q.isEmpty()) {

			mark cm = q.poll();
			if (visits[cm.y][cm.x] != 1) {
				visits[cm.y][cm.x] = 1;
				visitCount++;

				for (int i = 0; i < 4; i++) {
					cx = cm.x;
					cy = cm.y;
					x = cx + dx[i];
					y = cy + dy[i];

					if (land[y][x] > 0 && visits[y][x] == 0) {
						q.offer(new mark(y, x));
					}
				}
			}
		}
	}

	static int findSea(int sy, int sx) {

		int cx, cy, x, y;
		cy = sy;
		cx = sx;
		int seaCount = 0;

		for (int i = 0; i < 4; i++) {
			y = cy + dy[i];
			x = cx + dx[i];

			if (y < 0 || y >= R || x < 0 || x >= C)
				continue;

			if (land[y][x] == 0) {
				seaCount++;
			}

		}

		return seaCount;

	}

}

class mark {
	int x;
	int y;

	public mark(int y, int x) {
		this.y = y;
		this.x = x;
	}

}
