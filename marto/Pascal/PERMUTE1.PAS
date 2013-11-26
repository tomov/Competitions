var
   a,b:array[1..100]of integer;
   n,St,i,En,m:integer;
   used:array[1..100]of boolean;
procedure cleanUsed;
begin
   for i:=St to En do
      used[i]:=false;
end;
procedure permute(k,StartNum,EndNum:integer);
var
   i:integer;
  begin
      for i:=StartNum to EndNum do
      begin
        if not used[i] then
        begin
           a[k]:=i;
           used[i]:=true;
           if k=n then used[i]:=false;
        end;
        if k<n then
        permute(k+1,StartNum,EndNum);
      end;
  end;
begin
  read(n,St,En);
  permute(1,St,En);
end.