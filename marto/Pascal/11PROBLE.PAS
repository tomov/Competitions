var
   a:array[1..20,1..30]of char;
   r,c,i,j:integer;
   count:longint;
   x,y:byte;
procedure ReadA;
var i,j:byte;
    t:boolean;
   begin
     t:=false;
     Readln(R,C);
     for i:=1 to R do
        for j:=1 to C do
           begin
             readln(a[i,j]);
             if t=false then
               if a[i,j]='B' then
                 begin
                   x:=i;
                   y:=j;
                   t:=true;
                 end;
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
  readA;
  Walk(x,y);
  writeln(count);
end.