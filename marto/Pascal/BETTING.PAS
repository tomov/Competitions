var
   a:array[1..100000000]of int64;
   n,y,fin,fin1:int64;
   i,x,z:longint;
function EndOfArray:longint;
var v:longint;
  begin
    for v:=1 to 440000 do
      if a[v]=0 then break;
     EndOfArray:=v-1;
  end;
function d2(m:longint):longint;
var p:longint;
  begin
    p:=(m+1)*2;
    d2:=p;
  end;
function d3(n:longint):longint;
var q:longint;
  begin
    q:=(n+1)*3;
    d3:=q;
  end;
procedure Sort(l, r: longint);
var
  i, j, x, y: longint;
begin
  i := l; j := r; x := a[(l+r) DIV 2];
  repeat
    while a[i] < x do i := i + 1;
    while x < a[j] do j := j - 1;
    if i <= j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      i := i + 1; j := j - 1;
    end;
  until i > j;
  if l < j then Sort(l, j);
  if i < r then Sort(i, r);
end;
begin
  read(n);
  a[1]:=2;
  a[2]:=3;
  for i:=1 to n div 4 do
    begin
      x:=d2(a[i]);
      y:=d3(a[i]);
      fin:=EndOfArray;
      a[fin+1]:=x;
      a[fin+2]:=y;
      Sort(1,fin+2)
    end;
  fin:=EndOfArray;
  Sort(1,fin);
  z:=0;
  x:=0;
  fin:=EndOfArray;
  for i:=1 to fin do
  begin
    if a[i]=a[i+1] then x:=x+1;
    if a[i]>=n then
    begin
      writeln(a[i],' Prize Money');
      z:=i-x;
      writeln(z,' Number of Bettings');
      break;
    end;
  end;
end.