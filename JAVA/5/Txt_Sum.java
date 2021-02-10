//文本文件计算求和
import javax.swing.JProgressBar;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.*;
import javax.swing.*;
 
import java.io.*;
 
public class Txt_Sum{
	public static void main(String []agre){
		try{
			long start=System.currentTimeMillis();
			FileReader fr=new FileReader("05test.txt");
			BufferedReader br=new BufferedReader(fr);
			String strLine;
			int lineCount=0;
			while(br.ready()){
				strLine=br.readLine();
				lineCount++;
			}
			fr.close();
			br.close();

			JFrame frm=new JFrame("Reading");
	        final JProgressBar aJProgressBar=new JProgressBar(0,lineCount);
	        aJProgressBar.setStringPainted(true);
    		aJProgressBar.setBackground(Color.white);
    		aJProgressBar.setForeground(Color.green);
    		
    		frm.setSize(500,150);
    		Toolkit tk=Toolkit.getDefaultToolkit();
    		Dimension dm=tk.getScreenSize();
    		frm.setLocation((int)(dm.getWidth()-frm.getWidth())/2,(int)(dm.getHeight()-frm.getHeight())/2);
    		
    		frm.add(aJProgressBar,BorderLayout.NORTH);	
    		frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    		frm.setVisible(true);
			
    		
			FileReader fr2=new FileReader("05test.txt");
			BufferedReader br2=new BufferedReader(fr2);		
			int count=0;
			double sum=0;
			JTextField jf=new JTextField();
			frm.add(jf,BorderLayout.CENTER);
			frm.setVisible(true);
			
			while(br2.ready()){
				count++;
				strLine=br2.readLine();
				String s[]=strLine.split("=");  
				double d=Double.parseDouble(s[1]);
				sum=sum+d;
			
				long end=System.currentTimeMillis();
				try{
					Thread.sleep(1);
					}
				catch(InterruptedException ignoreException){					
				};
		    	double time=(double)(end-start)/1000;
		    	double time1=((double)(lineCount-count)/count)*time;
		    	jf.setText("Now calculating Var"+s[0]+"..."+count+"/"+lineCount+"  " +
			    				   "        have used"+String.format("%.1f",time)+"s"+"     about still needed"+String.format("%.1f",time1)+"s");
		    	int value=aJProgressBar.getValue();
		    	aJProgressBar.setValue(value+1);
			}	
			frm.dispose();
			System.out.print(String.format("%.2f",sum));
			fr2.close();
			br2.close();
		}
		catch(IOException e){
			e.printStackTrace();			
		}
	}
}