package break_codingtest;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class BJchuijun_2980 {

	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int N = Integer.parseInt(st.nextToken());
		int end = Integer.parseInt(st.nextToken());
		int D, R, G;
		int delay = 0, sum = 0;
		for(int i = 0 ; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			D = Integer.parseInt(st.nextToken()) + delay;
			R = Integer.parseInt(st.nextToken());
			G = Integer.parseInt(st.nextToken());
			sum = R+G;
			if(D > sum) {
				D = D%sum;
			}
			if(D >= R) {
				continue;
			}else {
				delay += (R-D);
			}
		}
		System.out.println(end+delay);
	}

}
