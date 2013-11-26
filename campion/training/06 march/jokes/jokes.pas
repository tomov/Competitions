program p;
const fin='jokes.in';
      fout='jokes.out';
var f:text;
    i,j,n:integer;
    a:array[0..501,0..501] of integer;
    sort:boolean;

function mai_mare(l1,l2:integer):boolean;
var j:integer;
begin
  mai_mare:=false;
  for j:=1 to n do
    if a[l1,j]>a[l2,j] then
      begin
        mai_mare:=true;
        break;
      end;
end;

procedure schimba(l1,l2:integer);
var j,aux:integer;
begin
  for j:=0 to n do
    begin
      aux:=a[l1,j];
      a[l1,j]:=a[l2,j];
      a[l2,j]:=aux;
    end;
end;

begin
  assign(f,fin); reset(f);
  readln(f,n);
  for i:=1 to n do
    begin
      for j:=1 to n do
        read(f,a[i,j]);
      readln(f)
    end;
  close(f);
  for i:=1 to n do
    begin
      for j:=1 to n do
        if a[j,i]>a[i,i] then
          a[i,i]:=a[j,i];
      a[i,0]:=i;
    end;
  repeat
    sort:=true;
    for i:=1 to n-1 do
      if mai_mare(i,i+1) then
        begin
          schimba(i,i+1);
          sort:=false;
        end;
  until sort;
  assign(f,fout); rewrite(f);
  for i:=1 to n-1 do
    write(f,a[i,0],' ');
  writeln(f, a[n,0]);
  close(f);
end.
