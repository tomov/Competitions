var
   a,b:array[1..1000]of longint;
   c:array[1..1000]of boolean;
   x,y,m,n,g:longint;
procedure check;
var i,p:longint;
  begin
    x:=0;
    for i:=1 to n do
    for p:=1 to n do
    if a[i]=a[p] then
    if c[p]=false then
    begin
      x:=x+1;
      c[p]:=false;
    end;
  end;
begin
  read(n,g);
  for m:=1 to n do
    read(a[m]);
  for m:=1 to g do
    read(b[m]);
  if n=g then
    begin
      check;
      if x=n then writeln('The Two Arrays Are Equal')
             else writeln('The Two Arrays Are Not The Equal');
    end;
end.