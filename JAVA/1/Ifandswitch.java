//if与switch的实现
import java.util.Scanner;
import java.lang.Math;

public class Ifandswitch{
	public static double useif(double x){
		if(x>=0&&x<1) 
			return x*x-1;
		else if(x>=1&&x<3)
			return Math.pow(x,3)-2*x-2;
		else if(x>=3&&x<5)
			return x*x-x*Math.sin(x);
		else if(x>=5&&x<7)
			return x+1;
		else return x-1;
	}
	public static double useswitch(double x){
		int y=(int)x;
		switch(y){
            case 0:
               return x*x-1;
            case 1:
            case 2:
	            return Math.pow(x,3)-2*x-2;
			case 3:
			case 4:
			    return x*x-x*Math.sin(x);
			case 5:
			case 6:
			    return x+1;
            default:
                return x-1;
        }
	}
	public static void main(String[] argv){
		Scanner cin=new Scanner(System.in);
		System.out.println("You will exit if enter e.");
		System.out.print("Please enter the number:");	
		while(!cin.hasNext("e")){
		    double x=cin.nextDouble();
		    System.out.println("f(x) used if:"+useif(x));	
		    System.out.println("f(x) used switch:"+useswitch(x));
		    System.out.print("Please enter the number:");
		}
		cin.close();	
	}
}