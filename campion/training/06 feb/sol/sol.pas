program sol_dpa;
var
    x,y,s:array[1..1000]of longint;
    f:text;
    k,i,j,n,max,nr:integer;
    a,b,c:longint;
begin
assign(f,'sol.in');
reset(f);
readln(f,n);
for i:=1 to n do
 readln(f,x[i],y[i]);
close(f);
max:=0;
for i:=1 to n-1 do
 for j:=i+1 to n do
  begin
   a:=y[j]-y[i];
   b:=x[i]-x[j];
   c:=y[i]*(x[j]-x[i])-x[i]*(y[j]-y[i]);
   nr:=0;
   for k:=1 to n do
    if a*x[k]+b*y[k]+c=0 then
     nr:=nr+1;
   if max<nr then
    max:=nr;
  end;
assign(f,'sol.out');
rewrite(f);
writeln(f,max);
close(f);
end.