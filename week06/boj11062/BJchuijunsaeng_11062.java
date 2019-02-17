/*
 *	BOJ_11062 카드게임
 * 
 *	cards[n] : 입력 카드 배열
 *	dp[s][e] : left(s)와 right(e)에서 얻을 수 있는 최고점수.
 *	sum : s~e 범위의 카드 점수의 합계
 *	go(s, e, sum) : s, e 범위에서 얻을 수 있는 최고의 점수
 *
 *	
 *	temp = Math.max(sum - go(s + 1, e, sum - cards[s]), 
 *					sum - go(s, e-1, sum - cards[e]));
 *	현재 가지고있는 카드의 합계에서 다음 턴에 얻을 수 있는 최고 점수를 뺀 max
 * 	근우 턴에서 명우 턴의 최고 점수를 빼주고, 명우 턴에서 다시 근우 턴에서 얻을 수 있는 최고 점수를 빼줌
 * 	s == e 이면 return cards[s];
 * 	
 * 	temp를 dp[s][e]에 저장해 주어 중복 탐색 막아줍니당.
 * 
 */



import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class bjoon_11062_3 {
	static int[] cards;
	static int[][] dp;
	static int N;
	public static void main(String[] args) throws NumberFormatException, IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		int T = Integer.parseInt(br.readLine());
		
		int N = 0, sum;
		
		for(int t = 1; t<= T; t++) {
			N = Integer.parseInt(br.readLine());
			cards = new int[N];
			dp = new int[N][N];
			st = new StringTokenizer(br.readLine());
			sum = 0;
			for(int i = 0; i < N; i++) {
				cards[i] = Integer.parseInt(st.nextToken());
				sum+= cards[i];
			}
			int res = go(0, N-1, sum);
			
			System.out.println(res);
		}
	}
	public static int go(int s, int e, int sum) {
		int temp;
		if(dp[s][e] != 0){
			return dp[s][e]; 
		}
		if(s >= e) {
			return cards[s];
		}else {
			temp = Math.max(sum - go(s + 1, e, sum - cards[s]), sum - go(s, e-1, sum - cards[e]));
			dp[s][e] = temp;
			return temp;
		}	
	}
}
