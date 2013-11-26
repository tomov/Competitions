var
   a:array[1..3,1..3]of integer;
procedure Print;
var i,p:integer;
   begin
     for i:=1 to 3 do
       for p:=1 to 3 do
       begin
         write(a[i,p],' ');
         if p=3 then writeln;
       end;
   end;
procedure permute(r,c:integer);
var i,p:integer;
  begin
    for i:=1 to 3 do
      begin
        a[r,c]:=i;
        if (c=3) and (r<3) then permute(r+1,1);
        if (c<3) then permute(r,c+1);
      end;
  end;
begin
  permute(1,1);
end.