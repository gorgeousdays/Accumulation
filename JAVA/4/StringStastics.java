//文本字符串个数统计
import java.io.*;

public class StringStastics{
	static String str;
	static char letter[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
		'A','B','C','D','E','F','G','H','I','G','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	static int total[]=new int[26];
	static void stastics_or(String a){
		int length=a.length();
	        int num=0;
	        for(int i=0;i<length-1;i++){
	        	if(a.charAt(i)=='o'&&a.charAt(i+1)=='r')
	        		num++;	  	        		
	        }
	        System.out.println("\nThe total number of 'or' is "+num);
	}
	static void static_three(String a){
		String[] split = a.split(" ");
		int len=split.length;
		int num=0;
		for(int i=0;i<len;i++){
			if(split[i].length()==3)
				num++;
		}
		System.out.println("\nThe total number of words with length 3 is "+num);
	}
	static void the_first_words(String a){
		String[] split = a.split(" ");
		int len=split.length;
		for(int i=0;i<len;i++)
			for(int j=0;j<52;j++)
			    if(split[i].length()>0&&split[i].charAt(0)==letter[j])
					total[j%26]++;
		for(int i=0;i<26;i++)
			System.out.println("The total number of words start with the letter "+letter[i]+" is  "+total[i]);			
	}
	public static void main(String args[]){
		try{
			FileReader fr=new FileReader("story.txt");	
			BufferedReader br=new BufferedReader(fr); 
			StringBuffer article=new StringBuffer();
		    
			while(br.ready()){
				str=br.readLine();
				str=str.replaceAll("[(,.?!:)-]"," ");
				article.append(str);
			}
			br.close();
			fr.close();
		
			String a= article.toString();
			
			the_first_words(a);
			stastics_or(a);
			static_three(a);
		}
		catch(IOException e){
			e.printStackTrace();
		}
    }
}