package break_codingtest;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.reflect.Array;
import java.util.Arrays;

public class BJchuijun_1614 {

	public static void main(String[] args) throws NumberFormatException, IOException {

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		long finger = Integer.parseInt(br.readLine())-1;
		long fcnt = Integer.parseInt(br.readLine());
		long res = 0;
		if(finger == 0 || finger == 4) {
			res = fcnt*8 + finger;
		}else {
			if(fcnt % 2 == 0) {
				res = fcnt*4 + finger; // fcnt/2*8 == fcnt*4
			}else {
				res = (fcnt-1)/2*8 + 8 - finger;
			}
		}
		System.out.println(res);
		
	}

}
