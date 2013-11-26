program SimpleEnoughQuestion;
var
   high,low:array[1..100,1..100]of boolean;
   a:array[1..100,1..100]of integer;
   j,q,y,e,w,x:integer;
procedure FindHigh;
var t,u,z:integer;
  begin
    for t:=1 to j do
    begin
      for u:=1 to q do
        if y<a[t,u] then y:=a[t,u];
      for z:=1 to q do
        if y=a[t,z] then high[t,z]:=true;
      y:=-1;
    end;
  end;
procedure FindLow;
var d,f,g:integer;
  begin
    for d:=1 to j do
    begin
      for f:=1 to q do
        if x>a[d,f] then x:=a[d,f];
      for g:=1 to q do
        if x=a[d,g] then low[d,g]:=true;
      x:=10000;
    end;
  end;
function divide(po:integer):integer;
  begin
    if j mod po = 0 then divide:=j div po
                    else divide:=(j div po)+1;
  end;
procedure Check;
var v,h,l,n,m,i:integer;
  begin
    n:=0;
    m:=0;
    for i:=1 to j do
      for v:=1 to q do
        begin
          if high[v,i]=true then n:=n+1;
          if low[v,i]=true then m:=m+1;
          if v=q then
            begin
              h:=divide(2);
              if (n=0) and (m>=h) then write(i,' ')
              else
                begin
                  n:=0;
                  m:=0;
                end;
            end;
        end;
  end;
begin
  read(j,q);
  for e:=1 to j do
    for w:=1 to q do
      read(a[e,w]);
  y:=-1;
    FindHigh;
  x:=10000;
    FindLow;
  Check;
end.