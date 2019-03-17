package break_codingtest;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BJchuijun_3006 {
	static int[] arr;
	
	public static void main(String[] args) throws NumberFormatException, IOException {

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		arr = new int[N+1];
		int [] cnt = new int[N+1];
		for(int i = 1; i <= N; i++) {
			arr[i] = Integer.parseInt(br.readLine());
		}
		for(int i = 1; i <= N/2; i++) {
			for(int j = i; j <= N; j++) {
				if(i == arr[j]) {
					cnt[i*2-1] = j - i;
					godown(i,j);
					break;
				}
			}
			for(int j = N-i+1; j >= i+1; j--) {
				if(N-i+1 == arr[j]) {
					cnt[i*2] = (N-i+1) - j;
					goup(N-i+1,j);
					break;
				}
			}
		}
		for(int i = 1; i <= N; i++) {
			System.out.println(cnt[i]);
		}
	}
	public static void godown(int num, int idx) {
		for(int i = idx; i > num; i--) {
			arr[i] = arr[i-1];
		}
		arr[num] = num;
	}
	public static void goup(int num, int idx) {
		for(int i = idx; i < num; i++) {
			arr[i] = arr[i+1];
		}
		arr[num] = num;
	}

}
