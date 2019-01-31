/*
 * 시간복잡도 : O(logN) [ N은 K입니다. ]
 * 공간복잡도 : O(logN) [arrayList]
 * 
 * x+?가 x|?이기 위해서는 x의 비트가 0인 부분들로 구성되어야 합니다.
 * ex) x=101(2) ?=10(2)
 * 그래서 1부터 2씩 곱하면서 x의 해당 비트가 0일 경우
 * ArrayList에 그 비트가 나타내는 수치를 저장했습니다.
 * 2^(arr.size)를 해준 이유는 이진수에서는 해당 자리가 0,1인 경우의 수 2가지가 있기 때문에
 * 자리수가 늘어날 때마다 총 경우의 수가 2배가 되기 때문입니다.
 * ex) 한 자리수 : 0 / 1 두 자리수 : 00 / 01 / 10 / 11
 * 
 * 그리고 다음으로 저장된 비트들을 통해 k번째를 찾아가는 구문을 만들었습니다.
 * arr의 맨 뒷부분부터 보며 2^(해당자리수 index)를 하고 이 수와 현재 k를 비교하면
 * 해당 비트가 0인지 1인지 알 수 있습니다.
 * ex) k=6  1xx(4개) 0xx(4개)
 *     6>=4 이므로 전자가 맞다는 것을 알 수 있습니다.
 * 해당 비트가 포함된다면 arr.get(i)를 하여 그 자리에 저장된 수를 더해줬습니다.
 */
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		Scanner scan=new Scanner(System.in);
		long x=scan.nextLong();
		long k=scan.nextLong();
		long curNum=1; // 현재 내가 확인하는 비트의 수를 저장하기 위한 변수
		long result=0;
		ArrayList<Long> arr=new ArrayList<>();
		while((long)Math.pow(2, arr.size())<=k) {
			if((x|curNum)!=x) { // 현재 수(자리수)와 x의 비트가 다르다면
				arr.add(curNum); // 리스트에 해당 비트를 추가하고
			}
			curNum*=2; // 다음 비트 확인
		}
		for(int i=arr.size()-1;i>=0;i--) {
			if(k==0) { break; } // k가 0이라면 k번째 수를 찾은 것
			else {
				if(k>=(long)Math.pow(2, i)) { // 5번째 자리에 수가 있고 없을 때의 경우의 수 차이는 2^5
					result+=arr.get(i); // 해당 값보다 크면 해당 비트가 1이라는 뜻이므로 값을 추가합니다.
					k-=(long)Math.pow(2, i); // 나머지 자리를 살피기 위해 k 감소 !
				}
			}
		}
		System.out.println(result);
	}
}
