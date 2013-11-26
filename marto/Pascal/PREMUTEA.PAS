var
   a:array[1..15]of integer;
   b:array[1..10000]of integer;
   n,RaiseNum,t:integer;
procedure CopyA_B;
var i:integer;
   begin
     for i:=1 to n do
       b[i]:=a[i];
   end;
procedure Print;
var i:integer;
   begin
     for i:=1 to n do
       write(a[i],' ');
     writeln;
   end;
function CheckNums(j:integer):integer;
var i,p,g,q:integer;
   begin
     g:=1;
     for i:=1 to j-1 do
       begin
         q:=i+1;
         for p:=q to j do
         if a[i]=a[p] then g:=0;
       end;
     if g=1 then CheckNums:=1;
   end;
function CheckPerms(fin:integer):integer;
var i,g:integer;
   begin
     g:=0;
     for i:=1 to fin do
       if a[i]=b[i] then g:=g+1;
     if g=n then CheckPerms:=0
       else begin
         CheckPerms:=1;
         CopyA_B;
       end;
   end;
procedure CheckRaise;
var i,g,w:integer;
   begin
     g:=0;
     for i:=1 to n-1 do
       if a[i]<a[i+1] then g:=g+1;
     if g=RaiseNum then
       begin
         w:=CheckPerms(n);
         if w=1 then
         begin

           t:=t+1;
         end;
       end;
   end;
procedure Permute(k:integer);
var i,f:integer;
   begin
      for i:=1 to n do
        begin
          a[k]:=i;
          f:=CheckNums(n);
          if f=1 then CheckRaise;
          if k<n then Permute(k+1);
       end;
   end;
begin
   t:=0;
   read(n,RaiseNum);
   permute(1);
   writeln(t);
end.