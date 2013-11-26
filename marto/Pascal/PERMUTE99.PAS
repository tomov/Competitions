var
   n,x1,x2,x3,NumOfNums:integer;
   a:array[1..100]of integer;
procedure permute(k:integer);
var
   i,p:integer;
begin
   if k<n then
      for i:=1 to 9 do
      begin
         if k=1 then
         begin
            a[k]:=i;
            permute(k+1);
         end
         else
         begin
            p:=10*a[k-1]+i;
            if(p mod x1=0)or(p mod x2=0)or(p mod x3=0)then
            begin
               a[k]:=i;
               permute(k+1);
            end;
         end;
      end
   else
      for i:=0 to 9 do
      begin
         p:=10*a[k-1]+i;
         if(p mod x1=0)or(p mod x2=0)or(p mod x3=0)then
         begin
            NumOfNums:=NumOfNums+1;
            a[k]:=i;
         end;
      end;
end;
begin
   readln(n,x1,x2,x3);
   permute(1);
   writeln(NumOfNums);
end.