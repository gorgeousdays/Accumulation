//回文数判断
import java.util.Scanner;
public class palindromic_number {
	static boolean judge(String s){
        for (int i = 0; i < s.length() / 2; i++)
            if (s.charAt(i) != s.charAt(s.length() - i - 1))
                return false;
        return true;
    }
    public static void main(String[] args) {
		System.out.println("You will exit if enter e.");
		System.out.print("Please enter the number:");	
        Scanner in = new Scanner(System.in);	
        String str = "";
        while (!in.hasNext("e")){
			
            str = in.nextLine();
            if (judge(str))
                System.out.println("Yes");
            else
                System.out.println("No");
			System.out.print("Please enter the number:");	
        }
    }
}



