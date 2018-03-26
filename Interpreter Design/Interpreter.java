
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Paths;
import java.util.*;

public class interpreter {
	public static void interpreter(String inFile,String outFile){
		try{
			Scanner in;
			in = new Scanner(Paths.get(inFile));
			PrintWriter out;
			out = new PrintWriter(outFile);
			
			String newLine="";
			List<String> expr=new ArrayList<String>();
			Stack<String> stack1=new Stack<String>();
			Stack<String[][]> bindList=new Stack<String[][]>();
			Stack<String[][]> funcList=new Stack<String[][]>();
			
			bindList.push(new String[10][2]);
			funcList.push(new String[40][40]);
			//bindList.peek()=new String[100][2];
			
			while(in.hasNextLine())
			{
				newLine=in.nextLine();
				//stack1.push(newLine);
				//System.out.printf("%s\n",newLine);
				expr.add(newLine);
				//System.out.printf("%s\n",stack1.peek());
			}
			
			while(!expr.isEmpty()){
				run(expr,stack1,bindList,funcList);
				expr.remove(0);
			}
			
			int stack1size=stack1.size();
			for(int i=0;i<stack1size;i++){
				String pTmp=deleteQ(keepU(stack1.peek()));
				
				if(i==stack1size-1)
					out.write(pTmp);
				else
					out.write(pTmp+"\n");
				
				System.out.printf("%s\n",pTmp);
				stack1.pop();
				}
			//System.out.printf("__________________\n");
			/*
			while(!funcList.isEmpty()){
			for(int i=0;i<(funcList.peek()).length;i++){
				for(int j=0;j<20;j++)
					System.out.printf("%s ",funcList.peek()[i][j]);
				System.out.printf("\n");
			}
			funcList.pop(); 
			 */
			
			/*
			while(!bindList.isEmpty()){
				for(int i=0;i<(bindList.peek()).length;i++){
					for(int j=0;j<2;j++)
						System.out.printf("%s ",bindList.peek()[i][j]);
					System.out.printf("\n");
				}
				bindList.pop();
			System.out.printf("|||||||||||\n");
			}*/
			
			//System.out.printf("%b\n",isFunc("addZ",funcList.peek()));
			in.close();
			out.close();
		}
		catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	

	
public static boolean isInt(String str){  
	for (int i = 0;i<str.length();i++){    
		if(str.charAt(i)=='-' && i==0)
			i++;
		if (!Character.isDigit(str.charAt(i))){  
				return false;  
		}  
	}  
	return true;  
}

public static boolean isBool(String str){  
	if(str==":true:"||str==":false:")
		return true;
	else
		return false;
}
	
public static boolean toBool (String str){  
	if(str==":true:")
		return true;
	if(str==":false:")
		return false;
	return false;
}

public static boolean isString(String str){  
	if(str.length()>=2 && str.charAt(0)=='\"'&&str.charAt(str.length()-1)=='\"')
		return true;
	else
		return false;
}

public static String deleteQ(String str){  
	if(str.length()>=2 && str.charAt(0)=='\"'&&str.charAt(str.length()-1)=='\"')
		return str.substring(1,str.length()-1 );
	return str;
}

public static String deleteU(String str){
	if (isUnit(str))
		return str.substring(6);
	else
		return str;
	
}

public static String keepU(String str){
	if (isUnit(str))
		return str.substring(0,6);
	else
		return str;
	
}

public static boolean isUnit(String str){
	if (str.charAt(0)==':'&&str.charAt(1)=='u'&&str.charAt(2)=='n'&&str.charAt(3)=='i'&&str.charAt(4)=='t'&&str.charAt(5)==':')
		return true;
	return false;
}

public static boolean isName(String str){  
	
	for (int i = 0;i<str.length();i++){    
		if(Character.isDigit(str.charAt(i)) && i==0)
			return false;
		if (!Character.isAlphabetic(str.charAt(i))&&!Character.isDigit(str.charAt(i))){  
			return false;  
		} 
	}  
	return true; 
}

public static boolean isinList(String a, String[][] bL){  
	int i=0;
	while(bL[i][0]!=null){
		if(bL[i][0].equals(a))
			return true;
		i++;
	}
	
	return false; 
}

public static boolean isFunc(String a, String[][] fL){  
	int i=0;
	while(fL[i][0]!=null){
		if(deleteU(fL[i][0]).equals(a))
			return true;
		i+=3;
	}
	
	return false; 
}

public static void Save(String a, String b ,String[][] bL){
	if (isinList(b,bL))
		{Save(a,getV(b,bL),bL);return;}
	int i=0;
	while(bL[i][0]!=null){
		if(bL[i][0].equals(a))
			break;
		i++;
	}
	bL[i][0]=a;
	bL[i][1]=b;
}

public static String getV(String a,String[][] bL){
	int i=0;
	a=deleteU(a);
	while(bL[i][0]!=null){
		if(bL[i][0].equals(a))
			return bL[i][1];
		i++;
	}
	return a;
}

public static boolean isLet(String str){
	if (str.charAt(0)==':'&&str.charAt(1)=='L'&&str.charAt(2)=='e'&&str.charAt(3)=='t'&&str.charAt(4)==':')
		return true;
	return false;
}

public static String deleteL(String str){
	if (isLet(str))
		return str.substring(5);
	else
		return str;
	
}

public static String addL(String str){
		return ":Let:"+str;
	
}

public static String[][] copyList(String[][] source){
	String[][] target=new String[source.length][source[0].length];
	
	for(int i=0;i<source.length;i++)
		for(int j=0;j<source[0].length;j++)
			target[i][j]=source[i][j];
	return target;
}

public static int funcPos(String a, String[][] fL){  
	int i=0;
	while(fL[i][0]!=null){
		if(fL[i][0].equals(a))
			return i;
		i+=3;
	}
	
	return 0; 
}


public static void run(List<String> expr,Stack<String> aa, Stack<String[][]> bb, Stack<String[][]> ff){
		String act=expr.get(0);
		String tmp=act;
		
		if (act.indexOf(" ")!=-1){
			tmp=act.substring(0,act.indexOf(" "));
			//System.out.printf("%s\n",tmp);
		}
		switch (tmp){
		case "add":{
			int a;
			int b;
			//System.out.printf("%d\n",aa.size());
			if(aa.size()>=2){
				if (isInt(getV(aa.peek(),bb.peek()))){
					a=Integer.parseInt(getV(aa.peek(),bb.peek()));
					aa.pop();
					if(isInt(getV(aa.peek(),bb.peek()))){
						b=Integer.parseInt(getV(aa.peek(),bb.peek()));
						aa.pop();
						aa.push(Integer.toString(a+b));
					}
					else{
						aa.push(Integer.toString(a));
						aa.push(":error:");
					}
				}
				else
					aa.push(":error:");
			}
			else
				aa.push(":error:");
			break;}
		case "sub":{
			int a;
			int b;
			//System.out.printf("%d\n",aa.size());
			if(aa.size()>=2){
				if (isInt(getV(aa.peek(),bb.peek()))){
					a=Integer.parseInt(getV(aa.peek(),bb.peek()));
					aa.pop();
					if(isInt(getV(aa.peek(),bb.peek()))){
						b=Integer.parseInt(getV(aa.peek(),bb.peek()));
						aa.pop();
						aa.push(Integer.toString(b-a));
					}
					else{
						aa.push(Integer.toString(a));
						aa.push(":error:");
					}
				}
				else
					aa.push(":error:");
			}
			else
				aa.push(":error:");
			break;}
		case "mul":{
			int a;
			int b;
			//System.out.printf("%d\n",aa.size());
			if(aa.size()>=2){
				if (isInt(getV(aa.peek(),bb.peek()))){
					a=Integer.parseInt(getV(aa.peek(),bb.peek()));
					aa.pop();
					if(isInt(getV(aa.peek(),bb.peek()))){
						b=Integer.parseInt(getV(aa.peek(),bb.peek()));
						aa.pop();
						aa.push(Integer.toString(a*b));
					}
					else{
						aa.push(Integer.toString(a));
						aa.push(":error:");
					}
				}
				else
					aa.push(":error:");
			}
			else
				aa.push(":error:");
			break;}
		case "div":{
			int a;
			int b;
			//System.out.printf("%d\n",aa.size());
			if(aa.size()>=2){
				if (isInt(getV(aa.peek(),bb.peek()))&& Integer.parseInt(getV(aa.peek(),bb.peek()))!=0){
					a=Integer.parseInt(getV(aa.peek(),bb.peek()));
					aa.pop();
					if(isInt(getV(aa.peek(),bb.peek()))){
						b=Integer.parseInt(getV(aa.peek(),bb.peek()));
						aa.pop();
						aa.push(Integer.toString(b/a));
					}
					else{
						aa.push(Integer.toString(a));
						aa.push(":error:");
					}
				}
				else
					aa.push(":error:");
			}
			else
				aa.push(":error:");
			break;}
		case "rem":
		{
			int a;
			int b;
			//System.out.printf("%d\n",aa.size());
			if(aa.size()>=2){
				if (isInt(getV(aa.peek(),bb.peek())) && Integer.parseInt(getV(aa.peek(),bb.peek()))!=0){
					a=Integer.parseInt(getV(aa.peek(),bb.peek()));
					aa.pop();
					if(isInt(getV(aa.peek(),bb.peek()))){
						b=Integer.parseInt(getV(aa.peek(),bb.peek()));
						aa.pop();
						aa.push(Integer.toString(b%a));
					}
					else{
						aa.push(Integer.toString(a));
						aa.push(":error:");
					}
				}
				else
					aa.push(":error:");
			}
			else
				aa.push(":error:");
			break;}
		case "neg":{
			int a;
			if (aa.size()>=1){
				if(isInt(getV(aa.peek(),bb.peek()))){
					a=Integer.parseInt(getV(aa.peek(),bb.peek()));
					aa.pop();
					aa.push(Integer.toString(0-a));
					}
				else{
					aa.push(":error:");}
					
			}
			else{aa.push(":error:");}
			break;}
		case "and":{
			boolean a;
			boolean b;
			//System.out.printf("%d\n",aa.size());
			if(aa.size()>=2){
				if (isBool(getV(aa.peek(),bb.peek()))){
					a=toBool(getV(aa.peek(),bb.peek()));
					aa.pop();
					if(isBool(getV(aa.peek(),bb.peek()))){
						b=toBool(getV(aa.peek(),bb.peek()));
						aa.pop();
						if(a&&b) aa.push(":true:"); 
						else aa.push(":false:");
					}
					else{
						if (a) aa.push(":true:"); else aa.push(":false:");
						aa.push(":error:");
					}
				}
				else
					aa.push(":error:");
			}
			else
				aa.push(":error:");
			break;}
		case "or":{
			boolean a;
			boolean b;
			//System.out.printf("%d\n",aa.size());
			if(aa.size()>=2){
				if (isBool(getV(aa.peek(),bb.peek()))){
					a=toBool(getV(aa.peek(),bb.peek()));
					aa.pop();
					if(isBool(getV(aa.peek(),bb.peek()))){
						b=toBool(getV(aa.peek(),bb.peek()));
						aa.pop();
						if(a||b) aa.push(":true:"); 
						else aa.push(":false:");
					}
					else{
						if (a) aa.push(":true:"); else aa.push(":false:");
						aa.push(":error:");
					}
				}
				else
					aa.push(":error:");
			}
			else
				aa.push(":error:");
			break;}
		case "lessThan":{
			int a;
			int b;
			//System.out.printf("%d\n",aa.size());
			if(aa.size()>=2){
				if (isInt(getV(aa.peek(),bb.peek()))){
					a=Integer.parseInt(getV(aa.peek(),bb.peek()));
					aa.pop();
					if(isInt(getV(aa.peek(),bb.peek()))){
						b=Integer.parseInt(getV(aa.peek(),bb.peek()));
						aa.pop();
						if(a>b) aa.push(":true:"); else aa.push(":false:");
					}
					else{
						aa.push(Integer.toString(a));
						aa.push(":error:");
					}
				}
				else
					aa.push(":error:");
			}
			else
				aa.push(":error:");
			break;}
		case "equal":{
			int a;
			int b;
			//System.out.printf("%d\n",aa.size());
			if(aa.size()>=2){
				if (isInt(getV(aa.peek(),bb.peek()))){
					a=Integer.parseInt(getV(aa.peek(),bb.peek()));
					aa.pop();
					if(isInt(getV(aa.peek(),bb.peek()))){
						b=Integer.parseInt(getV(aa.peek(),bb.peek()));
						aa.pop();
						if(a==b) aa.push(":true:"); else aa.push(":false:");
					}
					else{
						aa.push(Integer.toString(a));
						aa.push(":error:");
					}
				}
				else
					aa.push(":error:");
			}
			else
				aa.push(":error:");
			break;}
		case "not":{
			if(aa.size()>=1){
				if(isBool(getV(aa.peek(),bb.peek())))
					if(getV(aa.peek(),bb.peek())==":false:"){
						aa.pop();
						aa.push(":true:");
					}
					else{
						aa.pop();
						aa.push(":false:");
					}
				else
					aa.push(":error:");
			}
			else 
				aa.push(":error:");
			break;}
		case "pop":
			if(!aa.isEmpty())
				aa.pop();
			else
				aa.push(":error:");
			break;
		case "push":{
			String a=act.substring(act.indexOf(" ")+1);
			if(isInt(a)||isString(a)||isName(a))
				aa.push(a);
			else
				aa.push(":error:");
			break;}
		case "swap":{
			String a;
			String b;
			//System.out.printf("%d\n",aa.size());
			if(aa.size()>=2){
				a=aa.peek();
				aa.pop();
				b=aa.peek();
				aa.pop();
				aa.push(a);
				aa.push(b);
			}
			else
				aa.push(":error:");
			break;}
		case ":true:":
			aa.push(":true:");
			break;
		case ":false:":
			aa.push(":false:");
			break;
		case "if":{
			String a;
			String b;
			if(aa.size()>=3){
				a=aa.peek();
				aa.pop();
				b=aa.peek();
				aa.pop();
				if(getV(aa.peek(),bb.peek())==":true:")
					{aa.pop();aa.push(a);}
				else if(getV(aa.peek(),bb.peek())==":false:")
				{aa.pop();aa.push(b);}
				else{
					aa.push(b);
					aa.push(a);
					aa.push(":error:");
				}
			}
			else{
				aa.push(":error:");
			}
			break;}
		case "bind":{
			String a;
			String b;
			if(aa.size()>=2){
				a=aa.peek();
				aa.pop();
				b=aa.peek();
				if(isName(b)&&(isInt(a)||isString(a)||isBool(a)||isUnit(a)||isinList(a,bb.peek()))){
					aa.pop();
					aa.push(":unit:"+b);
					Save(b,a,bb.peek());
				}
				else{
					aa.push(a);
					aa.push(":error:");
				}
			}
			else
				aa.push(":error:");
			break;}
		case "error":
			aa.push(":error:");
			break;
		case "quit":case"return":
			break;
		case "let":{
			bb.push(copyList(bb.peek()));
			ff.push(copyList(ff.peek()));
			
			if(aa.isEmpty())
				;
			else{
				String aa1=addL(aa.peek());
				aa.pop();
				aa.push(aa1);
			}
			break;
		}
		case "end":{
			String a;
			if(aa.isEmpty())
				;
			else{
				if(isLet(aa.peek())){
					String aa1=deleteL(aa.peek());
					aa.pop();
					aa.push(aa1);
				}
				else{
					a=aa.peek();
					while(!aa.isEmpty()&&!isLet(aa.peek()))
						aa.pop();
					if(!aa.isEmpty()){
						String aa1=deleteL(aa.peek());
						aa.pop();
						aa.push(aa1);
					}
					aa.push(a);
				}
			}
			bb.pop();
			ff.pop();
			break;
		}
		case "fun":{
			//System.out.printf("%s\n",act.substring(act.indexOf(" ")+1));
			
			int para=0;
			int record=0;
			int mm=0;
			//String func_Name="qewqewqsad";
			
			String nameAndpara=act.substring(act.indexOf(" ")+1);
			String func_Name=nameAndpara.substring(0, nameAndpara.indexOf(" "));
			String func_Para=nameAndpara.substring(nameAndpara.indexOf(" ")+1);
			try{
			while(ff.peek()[para][0]!=null){
				if(ff.peek()[para][0].equals(func_Name))
					break;
				para+=3;
			}
			}catch (Exception e) {
				// TODO Auto-generated catch block
				//e.printStackTrace();
			}
			
			
			
			for(int i=0;i<bb.peek().length;i++){
				ff.peek()[para+2][2*i]=bb.peek()[i][0];
				ff.peek()[para+2][2*i+1]=bb.peek()[i][1];
			}
			
			
			ff.peek()[para][0]=func_Name;
			ff.peek()[para][1]=func_Para;
			
			expr.remove(0);
			while(!(expr.get(0).equals("funEnd"))||mm!=0){
				if(expr.get(0).length()>=4&&(expr.get(0).substring(0,4).equals("fun ")||expr.get(0).substring(0,4).equals("inOu")))
					mm++;
				if(expr.get(0).equals("funEnd"))
					mm--;
				ff.peek()[para+1][record]=expr.get(0);
				record++;
				expr.remove(0);
			}
			
			aa.push(":unit:"+func_Name);
			//expr.remove(0);
			break;
		}
		
		case "inOutFun":{
			//System.out.printf("%s\n",act.substring(act.indexOf(" ")+1));
			
			int para=0;
			int record=0;
			
			while(ff.peek()[para][0]!=null){
				para+=3;
			}
			
			for(int i=0;i<bb.peek().length;i++){
				ff.peek()[para+2][2*i]=bb.peek()[i][0];
				ff.peek()[para+2][2*i+1]=bb.peek()[i][1];
			}
			
			
			String nameAndpara=act.substring(act.indexOf(" ")+1);
			String func_Name=nameAndpara.substring(0, nameAndpara.indexOf(" "));
			String func_Para=nameAndpara.substring(nameAndpara.indexOf(" ")+1);
			
			ff.peek()[para][0]=":unit:"+func_Name;
			ff.peek()[para][1]=func_Para;
			
			expr.remove(0);
			while(!expr.get(0).equals("funEnd")){
				ff.peek()[para+1][record]=expr.get(0);
				record++;
				expr.remove(0);
			}
			
			aa.push(":unit:"+func_Name);
			//expr.remove(0);
			break;
		}
		case "call":{
			String a;
			String b;
			
			if(aa.size()>=2){
				a=aa.peek();
				aa.pop();
				b=aa.peek();
				if((isName(b)||isInt(b)||isString(b)||isBool(b)||isUnit(b))&&isFunc(getV(a,bb.peek()),ff.peek())){					
					int pos=funcPos(a,ff.peek());
					//System.out.printf("12323\n");
					int j;int reflag=0;int m=0;
					Stack<String> funcStack=new Stack<String>();
					Stack<String[][]> funcbL=new Stack<String[][]>();
					List<String> funcCon= new ArrayList<String>();
					funcbL.push(new String[10][2]);
				
					for(j=0;ff.peek()[pos+2][2*j]!=null;j+=1){
						funcbL.peek()[j][0]=ff.peek()[pos+2][2*j];
						funcbL.peek()[j][1]=ff.peek()[pos+2][2*j+1];
					}
					
					funcbL.peek()[j][0]=ff.peek()[pos][1];
					funcbL.peek()[j][1]=getV(b,bb.peek());
					
					for(m=0;ff.peek()[pos+1][m]!=null;m++){
						funcCon.add(ff.peek()[pos+1][m]);
					}
					if(funcCon.get(m-1).equals("return"))
						reflag=1;
					
					if(isUnit(ff.peek()[pos][0])){
						while(!funcCon.isEmpty()){
							run(funcCon,funcStack,funcbL,ff);
							funcCon.remove(0);
						}
					
						aa.pop();
						String result=getV(funcStack.peek(),funcbL.peek());
						if(reflag==1)
							aa.push(result);
						if (isName(b))
							Save(b,result,bb.peek());
					}
					else{
						while(!funcCon.isEmpty()){
							run(funcCon,funcStack,funcbL,ff);
							funcCon.remove(0);
						}
					
						aa.pop();
						aa.push(getV(funcStack.peek(),funcbL.peek()));}
					
				}
				else{
					aa.push(a);
					aa.push(":error:");
				}
			}
			else{
				aa.push(":error:");
			}
			break;
		}
		default:
			aa.push(":error:");
			break;
		}
	}
	
}
