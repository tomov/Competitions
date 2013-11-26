var
   a,b,c:array[1..1000]of longint;
   n,i:longint;
function EndOfArrayB(q:longint):longint;
var m:longint;
  begin
    for m:=1 to 440000 do
      if b[m]=0 then break;
     EndOfArrayB:=m-1;
  end;
function EndOfArrayC(p:longint):longint;
var m:longint;
  begin
    for m:=1 to 440000 do
      if c[m]=0 then break;
     EndOfArrayC:=m-1;
  end;
begin
  read(n);
  for i:=1 to n do
   read(c[i]);
  writeln(EndOfArrayC(1));
end.
