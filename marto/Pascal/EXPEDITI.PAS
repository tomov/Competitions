program Expedition;
var
   used:array[1..100,1..100]of boolean;
   b:array[1..100]of integer;
   t,n,k,r,s,lop:integer;
procedure print;
var h:integer;
  begin
    for h:=1 to k do
    write(b[h],' ');
  end;
function check(z:integer):integer;
var x,y,g:integer;
  begin
    g:=0;
    for x:=1 to t do
    begin
      y:=b[x];
      if used[y,z]=true then g:=1;
    end;
    check:=g
  end;
procedure find(d:integer);
var i,che:integer;
  begin
    b[1]:=d;
    t:=1;
    for i:=d to n do
    begin
      che:=check(i);
      if che=0 then
      begin
        t:=t+1;
        b[t]:=i;
      end;
    end;
    if t>=k then print
    else if (d-1)>(n-k) then writeln('Not Possible')
                         else find(d+1);
  end;
begin
  read(n,k);
  repeat
  read(r,s);
  used[r,s]:=true;
  used[s,r]:=true;
  until (s=0) and (r=0);
  for lop:=1 to n do
  used[lop,lop]:=true;
  find(1)
end.