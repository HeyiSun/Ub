fun pushstring (a:string list, m:string)=
	case a of (x::xs)=>(m::x::xs)
	|nil=>[m];

fun isInt (a:string)=
	let
		val charas=explode(a);


		fun isListInt(b:char list)=
			case b of (x::xs)=> if(xs=nil) then Char.isDigit(x) else ( Char.isDigit(x) andalso isListInt(xs) )
				|_=>false;


		fun isIntFirst(b:char list)=
			case b of (x::xs)=> if( (x= #"-") orelse (Char.isDigit x) ) then ( if (xs=nil) then (if(x= #"-") then false else true) else isListInt(xs)) else false
				|_=>false;	
	in
		isIntFirst(charas) 
	end

fun pushnum (a:string list ,m:string)=
	case a of  (x::xs)=>if isInt(m) then (m::x::xs) else (":error:"::x::xs) 
	| nil => [m];


fun deleten(m:char list)=
	case m of (x::xs) => ( case xs of ( #"\n"::nil) => (x::nil) | _=>x::deleten(xs) )
			|_=> nil; 

fun deleteQ(m:string)=
	let
		val charas= explode(m);
		
		fun deleteFirstQ(n:char list)=
			case n of (x::xs)=> (if x= #"\""then xs else (x::xs))
				|nil=> nil;

		fun deleteLastQ(n:char list)=
			case n of (x::y::xs)=> (x::deleteLastQ(y::xs))
				|(x::nil)=> if x= #"\"" then nil else (x::nil)
				|nil=>nil;
	in
		implode(deleteLastQ(deleteFirstQ(charas)))
	end

fun isU(m:string)=
	let 
		val charas=explode(m);

		fun isisu(n:char list)=
			case n of ( #":" :: #"u" :: #"n" :: #"i" :: #"t" :: #":" ::xs) => true
							|_=> false;
	in
		isisu(charas)
	end

fun deleteU(m:string)=
	let 
		val charas=explode(m);

		fun deleteu(n:char list)=
			case n of ( #":" :: #"u" :: #"n" :: #"i" :: #"t" :: #":" ::xs) => implode(xs)
							|_=> implode(charas);
	in
		if isU(m) then deleteu(charas) else m
	end

fun keepU(m:string)=
	let 
		val charas=explode(m);

		fun keepu(n:char list)=
			case n of ( #":" :: #"u" :: #"n" :: #"i" :: #"t" :: #":" ::xs) => ":unit:"
							|_=> implode(charas);
	in
		keepu(charas)
	end

fun AddPtr(m:string list)=
	case m of (x::xs)=>((":ptr:"^x)::xs)
		|nil=>nil;

fun dePtr(m:string)=
	case explode(m) of ( #":" :: #"p":: #"t":: #"r":: #":"::xs)=> implode(xs)
				|_=> m;

fun AddLet(m:string list)=
	case m of (x::xs)=>((":Let:"^x)::xs)
		|nil=>nil;

fun isLet(m:string)=
	case explode(m) of ( #":" :: #"L":: #"e":: #"t":: #":"::xs)=> true
				|_=>false;
fun deleteL(m:string)=
	case explode(m) of ( #":" :: #"L":: #"e":: #"t":: #":"::xs)=> implode(xs)
				|_=> m;

fun isPush(m:string)=
	let 
		val charas=explode(m);

		fun ispush(n:char list)=
			case n of ( #"p" :: #"u" :: #"s" :: #"h" :: #" " ::xs) => true
							|_=> false;
	in
		ispush(charas)
	end


fun deleteP(m:string)=
	case explode(m) of ( #"p" :: #"u":: #"s":: #"h":: #" "::xs)=> implode(xs)
					|_=> m;

fun isString (m:string)=
	let
		val charas= explode(m);
		
		fun isFirstQ(n:char list)=
			case n of (x::xs)=> (if x= #"\""then true else false)
				|nil=> false;

		fun isLastQ(n:char list)=
			case n of (x::y::xs)=> isLastQ(y::xs)
				|(x::nil)=> if x= #"\"" then true else false
				|nil=>false;
	in
		isLastQ(charas) andalso isFirstQ(charas)
	end

fun isName (a:string)=
	let
		val charas=explode(a);

		fun isListName(b: char list)=
			case b of (x::xs)=>if(xs=nil) then ((Char.isAlpha x) orelse (Char.isDigit x)) else ( ((Char.isAlpha x) orelse (Char.isDigit x)) andalso isListName(xs) )
				|_=>false;

		fun isNameFirst(b:char list)=
			case b of (x::y::xs)=> if (Char.isAlpha x) then isListName(y::xs) else false
				|(x::nil)=> Char.isAlpha x
				|_=>false;
		
	in
		isNameFirst(charas)
	end


fun pop (a:string list)=
	case a of nil=> (":error:" :: nil)
		|(x::xs) => if ((x=":error:") andalso (xs=nil)) then (":error:"::nil) else xs;

fun isBool(a:string)=
	case a of ":true:"=>true
		|":false:"=> true
		|_=>false;

fun isError(a:string)=
	case a of ":error:" => true
		|_=>false;

fun push(a:string list, m: char list)=
	if(isInt(implode(m)) orelse isName(implode(m)) orelse isString(implode(m)) orelse isBool(implode(m)) orelse isError(implode(m)) ) then (
	case a of (x::xs)=>(implode(m)::x::xs)
		|nil=>[implode(m)])
	else (case a of (x::xs)=>(":error:"::x::xs)
			|nil=>(":error:"::nil));

fun StrtoInt(a:string)= 
	let
		val charas=explode(a);

		fun helper #"1"= (1:int)
		|helper #"2"= 2
		|helper #"3"= 3
		|helper #"4"= 4
		|helper #"5"= 5
		|helper #"6"= 6
		|helper #"7"= 7
		|helper #"8"= 8
		|helper #"9"= 9
		|helper #"0"= 0
		|helper _= 0;
		fun strtoint(n:int,m:char list)=
			case m of (x::xs)=> if (xs=nil) then (n*10+helper(x)) else strtoint(10*n+helper(x), xs)
				|nil=>0;
		fun detectNeg(q:char list)=
			case charas of ( #"-"::xs) => 0-strtoint(0,xs)
				|_=>strtoint(0,charas);
	in
		detectNeg(charas)
	end


fun turnNeg(a:string)=
	let
		val charas=explode(a);
		
		fun turnneg(m:char list)=
			case m of ( x::xs) => if (x= #"~") then ( #"-"::xs) else (x::xs)
				|_=>nil; 
	in
		implode (turnneg(charas))
	end

fun GetValue(p:string, q: string list list)=
	let
		val mm=deleteL(p);
		fun getvalue(m:string, n: string list list)=
			if (isU(m) orelse isName(m)) then(  
				case n of (x::xs)=>(case x of (a::b::nil)=> if(deleteU(a)=m) then b else GetValue(m,xs)
						|_=>m)
					|_=>m
			)else m; 
	in 
		getvalue(mm,q)
	end
fun UpdateList(m1:string,m2:string,n:string list list)=
	if(isName(m2) orelse isU(m2)) then UpdateList(m1,GetValue(deleteU(m2),n),n) else (
	case n of (x::xs)=> (case x of (a::b::nil)=> if(a=m1) then ((a::m2::nil)::xs) else (x::UpdateList(m1,m2,xs))
				|_=>nil)
		|_=> ((m1::m2::nil)::nil));

fun isBind(m:string list)=
	case m of (x::y::xs)=> if ((not (isError(deleteL(x)))) andalso (not (isError(deleteL(y)))) andalso isName(deleteL(y)) andalso (isName(deleteL(x)) orelse isInt(deleteL(x)) orelse isString(deleteL(x)) orelse isBool(deleteL(x)) orelse isU(deleteL(x))) ) then true else false
			|(x::nil)=> false 
			|nil=> false;

fun Save(p:string list, q: string list list list, flag:int)=
	let

		fun FF(m:string list list list)=
			case m of (x::xs)=>x
				|_=>nil;

		fun save(m:string list, n:string list list)=
			case m of (x::y::xs)=>if isBind(m) then 
				(
					UpdateList(deleteL(y),deleteL(x),n)
				)
				else n
			|_=> n; 
		
		fun saveFirst(n:string list list list, flag:int, para:string list list)=
			case n of (x::xs)=>(case flag of 1=>(save(p,para)::xs)
					                |_=> (x::saveFirst(xs,flag-1,(if(xs=nil) then x else (case xs of (m::ms)=>m|_=>nil)))))
				|nil=>saveFirst([nil],flag,para);
	in
		saveFirst(q,flag,FF(q))
	end

fun And(a:string list, b: string list list)=
	case a of nil=>(":error:"::nil)
		|(x::nil)=>(":error:"::x::nil)
		|(x::y::xs)=> if (isBool(GetValue(x,b)) andalso isBool(GetValue(y,b))) then (( if ( GetValue(x,b) =":false:" orelse GetValue(y,b)=":false:") then ":false:" else ":true:")::xs) else (":error:"::x::y::xs);

fun Or(a:string list, b: string list list)=
	case a of nil=>(":error:"::nil)
		|(x::nil)=>(":error:"::x::nil)
		|(x::y::xs)=> if (isBool(GetValue(x,b)) andalso isBool(GetValue(y,b))) then (( if (GetValue(x,b)=":true:" orelse GetValue(y,b)=":true:") then ":true:" else ":false:")::xs) else (":error:"::x::y::xs);

fun Not(a:string list, b: string list list)=
	case a of nil=>(":error:"::nil)
		|(x::xs)=> if isBool(GetValue(x,b)) then ( (if GetValue(x,b)=":true:" then ":false:" else ":true:") ::xs) else (":error:"::x::xs);

fun Equal(a:string list, b: string list list)=
	case a of nil=>(":error:"::nil)
		|(x::nil)=>(":error:"::x::nil)
		|(x::y::xs)=> if (isInt(GetValue(x,b)) andalso isInt(GetValue(y,b))) then  (   (if(StrtoInt(GetValue(x,b))=StrtoInt(GetValue(y,b))) then ":true:" else ":false:"   )    ::xs) else (":error:"::x::y::xs) ;

fun Lessthan(a:string list, b: string list list)=
	case a of nil=>(":error:"::nil)
		|(x::nil)=>(":error:"::x::nil)
		|(x::y::xs)=> if (isInt(GetValue(x,b)) andalso isInt(GetValue(y,b))) then  (   (if(StrtoInt(GetValue(y,b))<StrtoInt(GetValue(x,b))) then ":true:" else ":false:"   )    ::xs) else (":error:"::x::y::xs) ;

fun Add(a:string list, b: string list list)=
	case a of nil=>(":error:"::nil)
		|(x::nil)=>(":error:"::x::nil)
		|(x::y::xs)=>if (isInt(GetValue(x,b)) andalso isInt(GetValue(y,b))) then (     turnNeg(      Int.toString(StrtoInt(GetValue(x,b))+StrtoInt(GetValue(y,b)))     )   ::xs) else (":error:"::x::y::xs);

fun Mul(a:string list, b: string list list)=
	case a of nil=>(":error:"::nil)
		|(x::nil)=>(":error:"::x::nil)
		|(x::y::xs)=> if (isInt(GetValue(x,b)) andalso isInt(GetValue(y,b))) then  (    turnNeg(      Int.toString(StrtoInt(GetValue(x,b))*StrtoInt(GetValue(y,b)))    )    ::xs) else (":error:"::x::y::xs) ;


fun Sub(a:string list, b: string list list)=
	case a of nil=>(":error:"::nil)
		|(x::nil)=>(":error:"::x::nil)
		|(x::y::xs)=> if (isInt(GetValue(x,b)) andalso isInt(GetValue(y,b))) then (      turnNeg(      Int.toString(StrtoInt(GetValue(y,b))-StrtoInt(GetValue(x,b)))    )    ::xs)  else (":error:"::x::y::xs) ;   

fun Neg(a:string list, b: string list list)=
	case a of nil=>(":error:"::nil)
		|(x::xs)=> if isInt(GetValue(x,b)) then (    turnNeg( Int.toString(0-StrtoInt(GetValue(x,b))) )     ::xs) else (":error:"::x::xs);


fun Rem(a:string list, b: string list list)=		
	case a of nil=>(":error:"::nil)
	|(x::nil)=>(":error:"::x::nil)
	|(x::y::xs)=> if (isInt(GetValue(x,b)) andalso isInt(GetValue(y,b))) then (      turnNeg(      Int.toString(   StrtoInt(GetValue(y,b)) mod StrtoInt(GetValue(x,b))  )    )    ::xs)  else (":error:"::x::y::xs) ;   

fun Div(a:string list, b: string list list)=
	case a of nil=>(":error:"::nil)
	|(x::nil)=>(":error:"::x::nil)
	|(x::y::xs)=> if (GetValue(x,b)="0") then (":error:"::x::y::xs) else (        if (isInt(GetValue(x,b)) andalso isInt(GetValue(y,b))) then (      turnNeg(      Int.toString(   StrtoInt(GetValue(y,b)) div StrtoInt(GetValue(x,b))  )    )    ::xs)  else (":error:"::x::y::xs)                      );   

fun Swap(a:string list)=		
	case a of nil=>(":error:"::nil)
	|(x::nil)=>(":error:"::x::nil)
	|(x::y::xs)=> (y::x::xs); 

fun error(a:string list)=
	case a of (x::xs)=> (":error:"::x::xs)
		|nil=>(":error:"::nil);

fun If(a:string list, b: string list list)=
	case a of (x::y::z::xs)=>if (isBool(GetValue(z,b))) then (if (GetValue(z,b)=":true:") then (x::xs) else (y::xs)) else (":error:"::x::y::z::xs)
		|(x::y::nil)=>(":error:"::x::y::nil)
		|(x::nil)=>(":error:"::x::nil)
		|nil=>(":error:"::nil);

fun End(m:string list)=
	case m of (x::y::xs)=> if isLet(x) then (deleteL(x)::y::xs) else (
				if isLet(y) then (x::deleteL(y)::xs) else End(x::xs) 
			)
		|(x::nil)=> (deleteL(x)::nil)
		|nil=>nil;

fun findEnd(m:string list)=
	case m of (x::xs)=>if(x="funEnd") then xs else findEnd(xs)
		|_=>m;

fun saveFunc(m:string list,fL:string list list)=
	let
		fun dropEnd(n:string list)=
			case n of (x::xs)=>if(x="funEnd") then nil else (x::dropEnd(xs))
				|_=>nil;
	in
		[dropEnd(m)]@fL
	end


fun argList(m:char list)=
	let
		fun arglist(p:char list, q: char list )=
			case p of (x::xs) => ( if (x= #" ") then (implode(q)::arglist(xs,[])) else arglist(xs,q@[x])  )   
				|nil=> implode(q)::nil;   
	in
		arglist(m,[])
	end	

fun quit(a:string list, outFile:string)=
	let
		val outStream = TextIO.openOut outFile;
		fun quitt(a:string list)=
			case a of (x::xs) =>if (xs = nil) then (TextIO.output(outStream, deleteQ(keepU(x)));quitt(xs);TextIO.closeOut outStream) else (TextIO.output(outStream, deleteQ(keepU(x))^"\n");quitt(xs);TextIO.closeOut outStream)
				|nil=>(TextIO.closeOut outStream);
	in
		quitt(a)
	end

fun findFunc(m:string list list, n:string)=
	case m of(x::y::xs)=>(case x of (a::bs)=> (if (dePtr(a)=n) then y else findFunc(xs,n))
				|_=>nil) 
		|_=>nil;

fun findArg(m:string list list, n:string)=
	case m of(x::y::xs)=>(case x of (a::b::bs)=> (if (dePtr(a)=n) then b else findArg(xs,n))
				|_=>"") 
		|_=>"";

fun applyArg(m:string list,n:string, p:string)=
	case m of (x::xs)=>if x=("push "^n)  then ("push "^p)::applyArg(xs,n,p) else x::applyArg(xs,n,p)
		|nil=>nil;

fun subPara(m:string list, b:string list list)=
	case m of (x::xs)=>if isPush(x) then ("push "^GetValue(deleteP(x),b))::subPara(xs,b) else x:: subPara(xs,b)
			|_=>nil;

fun isinFL(m:string,n:string list list)=
	case n of (x::y::xs)=>(case x of (a::bs)=> if(dePtr(a)=m) then true else isinFL(m,xs)
				|_=>false)
		|_=>false;

fun notPtr(m:string,n:string list list)=
	case n of (x::y::xs)=>(case x of (a::bs)=> if(a=m) then true else isinFL(m,xs)
				|_=>false)
		|_=>false;

fun isCall(m:string list,fL:string list list)=
	case m of (x::y::xs)=>( if( (isName(y) orelse isU(y) orelse isBool(y) orelse isString(y) orelse isInt(y)) andalso isinFL(x,fL)  ) then true else false  )
		|_=>false;


fun choseList(m:string list list list, n:int)=
		case m of (x::xs)=> (case n of 1=> x
				|_=>choseList(xs,n-1))
			|nil=> nil;

fun interpreter(input:string, output:string)=
let
	val inStream = TextIO.openIn input;
	val readLine = TextIO.inputLine inStream
	
	val stack1=[]:string list ;
	val stack2=[]:string list;
	val bindList=[]: string list list list;
	val functionList=[[[]]]:string list list list;
	val flag=1:int;
	

	fun DeleteList(m:string list list list)=
		case m of (x::y::xs)=> (x::DeleteList(y::xs))
			|_=> nil;

	fun Bind(m:string list)=
		case m of (x::y::xs)=> if isBind(m) then ((":unit:"^y)::xs) else (":error:"::x::y::xs)
			|(x::nil)=> (":error:"::x::nil) 
			|nil=> (":error:"::nil)
	
	fun Write(m:string list, c:string )=
		case m of (x::xs)=>(x::Write(xs,c))
			|nil=>(implode(deleten(explode(c)))::nil);

	fun readTxt(readLine : string option, stack2:string list)=
		case readLine of 
			NONE=>(TextIO.closeIn inStream;stack2)
			|SOME(c)=>readTxt(TextIO.inputLine inStream, Write(stack2,c));

	fun helper(stack2:string list,stack1:string list, bL:string list list list, fg:int, fL:string list list list)=
		case stack2 of nil=>(TextIO.closeIn inStream; stack1)
			|(x::xn)=>( case explode(x) of 
				( #"p":: #"u":: #"s":: #"h":: #" "::xs) => helper(xn,push(stack1, deleten(xs)),bL,fg,fL  )
			                |( #"a":: #"n":: #"d"::xs)=>  helper(xn,And(stack1,choseList(bL,fg)),bL,fg,fL)
				|( #"l":: #"e":: #"s":: #"s":: #"T":: #"h":: #"a":: #"n"::xs)=>  helper(xn,Lessthan(stack1,choseList(bL,fg)),bL,fg,fL)
				|( #"e":: #"q":: #"u":: #"a":: #"l"::xs)=>  helper(xn,Equal(stack1,choseList(bL,fg)),bL,fg,fL)
				|( #"o":: #"r"::xs)=>  helper(xn,Or(stack1,choseList(bL,fg)),bL,fg,fL)
				|( #"n":: #"o":: #"t"::xs)=>  helper(xn,Not(stack1,choseList(bL,fg)),bL,fg,fL)
				|( #"a":: #"d":: #"d"::xs)=>  helper(xn,Add(stack1,choseList(bL,fg)),bL,fg,fL)
				|( #"s":: #"u":: #"b"::xs)=>  helper(xn,Sub(stack1,choseList(bL,fg)),bL,fg,fL)

				|( #"r":: #"e":: #"m"::xs)=>  helper(xn,Rem(stack1,choseList(bL,fg)),bL,fg,fL)
				|( #"d":: #"i":: #"v"::xs)=>  helper(xn,Div(stack1,choseList(bL,fg)),bL,fg,fL)
				|( #"m":: #"u":: #"l"::xs)=>  helper(xn,Mul(stack1,choseList(bL,fg)),bL,fg,fL)
				|( #"n":: #"e":: #"g"::xs)=>  helper(xn,Neg(stack1,choseList(bL,fg)),bL,fg,fL)
				|( #"p":: #"o":: #"p"::xs)=>  helper(xn,pop(stack1),bL,fg,fL)
				|( #"s":: #"w":: #"a":: #"p"::xs)=>  helper(xn,Swap(stack1),bL,fg,fL)
				|( #":":: #"f":: #"a":: #"l":: #"s":: #"e":: #":"::xs)=>  helper(xn,push(stack1, #":":: #"f":: #"a":: #"l":: #"s":: #"e":: #":"::nil),bL,fg,fL)
				|( #":":: #"t":: #"r":: #"u":: #"e":: #":"::xs)=>  helper(xn,push(stack1,  #":":: #"t":: #"r":: #"u":: #"e":: #":"::nil),bL,fg,fL)
				|( #":":: #"e":: #"r":: #"r":: #"o":: #"r":: #":"::xs)=>  helper(xn,push(stack1, #":":: #"e":: #"r":: #"r":: #"o":: #"r":: #":"::nil),bL,fg,fL)
				|( #"q":: #"u":: #"i":: #"t"::xs)=>stack1
				|( #"b":: #"i":: #"n":: #"d"::xs)=> helper(xn,Bind(stack1),Save(stack1,bL,fg),fg,fL)
				|( #"i":: #"f"::xs)=> helper(xn,If(stack1,choseList(bL,fg)),bL,fg,fL)
				|( #"l":: #"e":: #"t"::xs)=> helper(xn,AddLet(stack1),Save(nil,bL,fg+1),(fg+1),[hd fL]@fL)
				|( #"e":: #"n":: #"d"::xs)=> helper(xn,End(stack1),DeleteList(bL),(fg-1),List.drop(fL,1))  
				|( #"f":: #"u":: #"n":: #" " ::xs)=>  helper(findEnd(xn),[":unit:"^hd(argList(xs))]@stack1,bL,fg,[[argList(xs)]@saveFunc(subPara(xn,choseList(bL,fg)),hd(fL))]@List.drop(fL,1))            
				|( #"i":: #"n":: #"O":: #"u":: #"t":: #"F":: #"u":: #"n":: #" " ::xs)=>  helper(findEnd(xn),[":unit:"^hd(argList(xs))]@stack1,bL,fg,[[AddPtr(argList(xs))]@saveFunc(subPara(xn,choseList(bL,fg)),hd(fL))]@List.drop(fL,1))    
				|( #"r":: #"e":: #"t":: #"u":: #"r":: #"n" ::xs)=> stack1
			(*	|( #"c":: #"a":: #"l":: #"l" ::xs)=>helper(xn,push(pop(pop(stack1)),explode(hd (helper( findFunc(fL,hd(stack1)),[],[[[findArg(fL,hd(stack1)),hd(pop(stack1))]]],fg,fL)))),bL,fg,fL)   *)
 				|( #"c":: #"a":: #"l":: #"l" ::xs)=>if(isCall(stack1,hd(fL))) then helper(xn,push(pop(pop(stack1)),explode(hd (helper( applyArg(findFunc(hd(fL),hd(stack1)),findArg(hd(fL),hd(stack1)),GetValue(hd(pop(stack1)),choseList(bL,fg))),[],[],1,fL)))),if notPtr(hd(stack1),hd fL) then bL else Save([hd (helper( applyArg(findFunc(hd(fL),hd(stack1)),findArg(hd(fL),hd(stack1)),GetValue(hd(pop(stack1)),choseList(bL,fg))),[],[],1,fL)),hd(pop(stack1))],bL,fg),fg,fL) else helper(xn,push(stack1,  #":":: #"e":: #"r":: #"r":: #"o":: #"r":: #":"::nil),bL,fg,fL)       
				|_=>helper(xn,push( stack1, #":":: #"e":: #"r":: #"r":: #"o":: #"r":: #":"::nil),bL,fg,fL)    ); 
			
in
	  (*helper(readTxt(readLine, stack2),stack1, bindList,flag,functionList)    *)
	 quit(helper(readTxt(readLine, stack2),stack1, bindList, flag,functionList), output)    
end









