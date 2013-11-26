var
   g:array[1..100]of boolean;
   a:array[1..100,1..100]of integer;
   i,p,n,S1,S2,m:integer;
procedure Equal(b:integer);
var
   S1,S2:integer;
  begin
    S1:=0;
    S2:=0;
    for p:=1 to b do
      begin
        for i:=1 to b do
          begin
            S1:=S1+a[i,p];
            S2:=S2+a[p,i];
            if S1=S2 then g[p]:=true;
          end;
      end;
    for i:=1 to b do
      writeln(g[i]);
  end;
begin
  writeln('red ','kolona');
  read(n,m);
  for i:=1 to n do
    for p:=1 to m do
      read(a[i,p]);
    if n>m then Equal(m)
           else Equal(n);
end.