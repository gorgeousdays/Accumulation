//实现英文与数字相互转化
import java.util.*;
import java.lang.Math;

public class Translation{
	
    public static String x[]={"zero","one","two", "three","four","five","six","seven","eight","nine"} ;
    public static String y[]={"ten","eleven","twelve","thirteen","fourteen","fifteen", "sixteen","seventeen","eighteen","nineteen"};
    public static String z[]={"twenty","thirty","forty","fifty","sixty","seventy", "eighty","ninety"}; 
	
	public static void num_to_words(String s){
		int num;
		//if num is a minus
		if(s.charAt(0)=='-')
			num=-Integer.parseInt(s.replace("-", ""));
		else num=Integer.parseInt(s);
		
	    if(num>=0&&num<10){
		    System.out.println(x[num]);
		}
		else if(num>=10&&num<20){
			System.out.println(y[num-10]);
		}
		else if(num>=20&&num<100){
		    System.out.print(z[num/10-2]+" ");
			num=num%10;
			if(num!=0)
			System.out.println(x[num]  );
		}
		else if(num>=100){
		    System.out.println("Your number is too big to change!Please input again");
		}
		else if(num<0){
		    System.out.println("Your number is too small to change!Please input again");
		}
	}
	
	public static void words_to_num(String s){
		String s1,s2;
		int flag=0;//use to judge whether have two words
		int i,j,k;
		for(i=0;i<s.length();i++){
			if(s.charAt(i)==' '){
			    flag=1;
				break;
			}
		}
		//sperate two words
		if(flag==0){
			s1=s.substring(0,s.length());
			s2=" ";
	    }
		else{
			s1=s.substring(0,i);
	        s2=s.substring(i+1,s.length());
	    }
		
		for(j=0;j<10;j++){
			//if the second word is wrong,it can't give the answer
			if(s1.equals(x[j])){
				if(s2.trim().isEmpty())
					System.out.println(j);
				else flag=-1;
				break;
			}
			else if(s1.equals(y[j])){
				if(s2.trim().isEmpty())
				    System.out.println(j+10);
			    else  flag=-1;
				break;
			}
			else if(s1.equals(z[j])){
				if(s2.trim().isEmpty())
				System.out.println((j+2)*10);
			    else{
					for(k=0;k<10;k++){
						if(s2.equals(x[k])){
							System.out.println((j+2)*10+k);
							break;
						}
					}
					if(k==10)
						flag=-1;
				}
				break;
			}
		}
		//if it can't find the number.It must be a wrong input
		if(j==10) flag=-1;
		if(flag==-1){
		  System.out.println("Wrong Input!Please input again!");
		}
	}
	
	public static void judge_models(String s){
	    s=s.trim();//clear the blank at the end of the words
		//using regex
		if (s.isEmpty())
			System.out.println("You can't input the blank!Please input again");
		else if(s.replace("-", "").matches("^[0-9]+$"))
			num_to_words(s);
		else
			words_to_num(s);
	}
	
	public static void main(String[] argv){
		Scanner cin=new Scanner(System.in);
		System.out.println("You will exit if enter e.");
		System.out.print("Please enter the number or words:");	
		while(!cin.hasNext("e")){
			String s=cin.nextLine();
			judge_models(s);
		    System.out.print("Please enter the number or words:");
		}
		cin.close();
	}
}