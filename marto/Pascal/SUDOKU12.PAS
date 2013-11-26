program Permute_repeating_numbers;
var
   a:array[1..3,1..3]of integer;
   n:integer;
procedure permute(r,c:integer);
var i:integer;
   begin
     for i:=1 to n do
       begin
         a[r,c]:=i;
         if (c=n) and (r<n) then permute(r+1,1);
         if c<n then permute(r,c+1);
         if (c=n) and (r=n) and (a[r,c]=n) then exit;
       end;
   end;
begin
  read(n);
  permute(1,1);
end.