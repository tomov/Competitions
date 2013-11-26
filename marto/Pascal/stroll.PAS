{
PROG: stroll
LANG: PASCAL
}
var
   a:array[1..20,1..30]of char;
   r,c,i,j,poss:integer;
   count:longint;
   x,y:byte;
   inp,out:text;
   cc:char;
procedure ReadA;
var i,j:byte;
    t:boolean;
   begin
     t:=false;
     Readln(inp,R,C);
     for i:=1 to R do
     begin
        poss:=1;
        for j:=1 to 2*C-2 do
           begin
             read(inp,cc);
             if(cc<>' ') then
             begin
               a[i,poss]:=cc;
               inc(poss);
             end;
             if t=false then
               if a[i,j]='B' then
                 begin
                   x:=i;
                   y:=j;
                   t:=true;
                 end;
           end;
        readln(inp,a[i,poss]);
     end;
   end;
procedure Walk(x,y:integer);
var i,j:byte;
    x1,y1:char;
   begin
     if y<C then y1:=a[x,y+1]
            else y1:='0';
     if x<R then x1:=a[x+1,y]
            else x1:='0';
     if y1='.' then Walk(x,y+1);
     if y1='B' then count:=count+1;
     if x1='.' then Walk(x+1,y);
     if x1='B' then count:=count+1;
   end;
begin
  count:=0;
  assign(inp,'stroll.in');
  reset(inp);
  readA;
  close(inp);
  Walk(x,y);
  assign(out,'stroll.out');
  rewrite(out);
  writeln(out,count);
  close(out);
end.