var
   a,b,c:array[1..1000]of longint;
   n,e,w,g,h,x,q,a1,b1:longint;
   v,z,p,fin1,fin2,i,fin,t,s:longint;
function d2(r1:longint):longint;
  begin
    a1:=(r1+1)*2;
    while n>a1 do
      q:=d2(a1);
    d2:=a1;
  end;
function d3(p1:longint):longint;
  begin
    b1:=(p1+1)*3;
    while n>b1 do
      x:=d3(b1);
    d3:=b1;
  end;
function d2_(r:longint):longint;
  begin
    a1:=(r+1)*2;
    e:=e+1;
    b[e]:=a1;
    while n>a1 do
      q:=d2_(a1);
    d2_:=a1;
  end;
function d3_(p:longint):longint;
  begin
    b1:=(p+1)*3;
    w:=w+1;
    a[w]:=b1;
    while n>b1 do
      x:=d3_(b1);
    d3_:=b1;
  end;
function EndOfArrayA:longint;
var m:longint;
  begin
    for m:=1 to 440000 do
      if a[m]=0 then break;
     EndOfArrayA:=m-1;
  end;
function EndOfArrayB:longint;
var m:longint;
  begin
    for m:=1 to 440000 do
      if b[m]=0 then break;
     EndOfArrayB:=m-1;
  end;
procedure Add;
var x:integer;
  begin
    for i:=1 to fin do
      begin
        x:=b[i];
        a[fin1+i]:=x;
      end;
  end;
procedure AddC;
var x:integer;
  begin
    for i:=1 to v do
      begin
        x:=c[i];
        a[v+i]:=x;
      end;
  end;
procedure Sort(l, r: Integer);
var
  i, j, x, y: integer;
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
procedure SortC(l, r: Integer);
var
  i, j, x, y: integer;
begin
  i := l; j := r; x := c[(l+r) DIV 2];
  repeat
    while c[i] < x do i := i + 1;
    while x < c[j] do j := j - 1;
    if i <= j then
    begin
      y := c[i]; c[i] := c[j]; c[j] := y;
      i := i + 1; j := j - 1;
    end;
  until i > j;
  if l < j then Sort(l, j);
  if i < r then Sort(i, r);
end;
begin
  read(n);
  w:=0;
  g:=d3_(0);
  h:=d2_(0);
  fin1:=EndOfArrayA;
  fin2:=EndOfArrayB;
  if fin1>fin2 then fin:=fin1
               else fin:=fin2;
  Add;
  v:=fin1+fin2;
  Sort(1,v);
  for i:=1 to (n+v) do
    begin
      t:=d2(a[i]);
      s:=d3(a[i]);
      if t>s then a[v+i]:=s
             else a[v+i]:=t;
      Sort(1,v+i);
    end;
  Sort(1,v+n);
  for p:=1 to (v+n) do
      if a[p]>=n then begin
        writeln(a[p]);
        break;
        end;
end.