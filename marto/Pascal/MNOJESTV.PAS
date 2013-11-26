var
   a:array[1..20,0..20]of byte;
   Temp:array[1..1000]of byte;
   m,k:byte;
procedure readM(m:byte);
var i,j:byte;
   begin
     for i:=1 to m do
        begin
          read(a[i,0]);
          for j:=1 to a[i,0] do
             read(a[i,j]);
        end;
   end;
procedure Multiply;
var i,j:byte;
    count:byte;
   begin
     count:=0;
     for i:=1 to a[1,0] do
        begin
          for j:=1 to a[2,0] do
             if (a[1,i]<>0) and (a[2,j]<>0) then
               begin
                 count:=count+1;
                 Temp[count]:=a[1,i]+a[2,j];
               end
                                        else
               begin
                 if a[1,i]=0 then
                   begin
                     count:=count+1;
                     Temp[count]:=a[2,j];
                   end
                             else
                     begin     x
                       count:=count+1;
                       Temp[count]:=a[1,i];
                     end;
               end;
        end;
   end;
begin
  read(m,k);
  readM(m);
  Multiply;
end.