//判断素数
import java.lang.Math;
public class Judgeprime{
	public static boolean judge(int num){
	    if(num<2)
			return false;
		for(int i=2;i<=Math.sqrt(num);i++){
            if(num%i==0)
				return false;
		}
		return true;
	}
	public static void main(String[] argv){
		int k=0;
		for(int i=100;i<=200;i++){
	        if(judge(i)){
                System.out.print(i+" ");
                k++;
if(k==10){
				System.out.print('\n');
				k=0;
			}				
			}
			
		}
	}
}