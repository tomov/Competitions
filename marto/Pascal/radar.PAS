{
PROG: radar
LANG: PASCAL
}
var
   S,RadaR:string;
   step:integer;
   inp,out:text;
function Palindromic(a:string):string;
var b:string;
    i,en:integer;
   begin
     en:=length(a);
     b:=a[en];
     for i:=1 to en do
        if i<en then b:=b+a[en-i];
     Palindromic:=b;
   end;
function Add(a,b:string):string;
var temp1,temp2,Sum:longint;
    ch:integer;
    c:string;
   begin
     val(a,temp1,ch);
     val(b,temp2,ch);
     Sum:=temp1+temp2;
     Str(Sum,c);
     Add:=c;
   end;
function Check(a:string):boolean;
var i,t:integer;
   begin
     Check:=true;
     if length(a) mod 2 = 1 then
       begin
         t:=(length(a) div 2)+1;
         for i:=1 to (length(a) div 2) do
            if a[t-1]<>a[t+1] then Check:=false;
       end
                            else
       begin
         t:=length(a)-1;
         for i:=1 to (length(a) div 2) do
            begin
              if a[i]<>a[i+t] then Check:=false;
              t:=t-2;
            end;
       end;
   end;
procedure FindRadaR(Str:string);
var
   Str1:string;
   begin
     step:=step+1;
     Str1:=Palindromic(Str);
     Str:=Add(Str1,Str);
     if Check(Str)=true then
       begin
          Radar:=Str;
          writeln(out,step,' ',RadaR);
          close(out);
          halt;
       end
                         else FindRadar(Str);
   end;
begin
  assign(inp,'radar.in');
  reset(inp);
  readln(inp,S);
  close(inp);
  step:=0;
  assign(out,'radar.out');
  rewrite(out);
  FindRadaR(S);
end.