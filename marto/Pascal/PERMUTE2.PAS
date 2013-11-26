var
   a,Inserted:array[1..9,1..9]of integer;
   n,m,t:integer;
procedure Inserted_A;
var i,p:integer;
  begin
    for i:=1 to 9 do
      for p:=1 to 9 do
      a[i,p]:=Inserted[i,p];
  end;
procedure Print;
var i,p:integer;
   begin
     for i:=1 to 9 do
       for p:=1 to 9 do
       begin
         write(a[i,p],' ');
         if p=9 then writeln;
       end;
   end;
function CheckArray:boolean;
var i,p,zero:integer;
   begin
     zero:=0;
     for i:=1 to 9 do
       for p:=1 to 9 do
       if a[i,p]=0 then zero:=1;
     if zero=0 then CheckArray:=true
               else CheckArray:=false;
   end;
function CheckRow(r,num:integer):boolean;
var
   i,k:integer;
  begin
    k:=0;
    for i:=1 to 9 do
      if a[r,i]=num then k:=1;
    if k=0 then CheckRow:=false
           else CheckRow:=true;
  end;
function CheckColumn(c,num:integer):boolean;
var
   i,k:integer;
  begin
    k:=0;
    for i:=1 to 9 do
      if a[i,c]=num then k:=1;
    if k=0 then CheckColumn:=false
           else CheckColumn:=true;
  end;
function CheckSquare(r,c,num:integer):boolean;
var
   i,p,w,q:integer;
  begin
    if r mod 3 <> 0 then w:=(r div 3)+1
                      else w:=r div 3;
    if c mod 3 <> 0 then q:=(c div 3)+1
                      else q:=c div 3;
    CheckSquare:=false;
  end;
procedure permute(r,c:integer);
var
   i:integer;
   x,y,z,NumOfZero:boolean;
  begin
    if a[r,c]=0 then
    for i:=1 to 9 do
      begin
        x:=CheckRow(r,i);
        y:=CheckColumn(c,i);
        z:=CheckSquare(r,c,i);
          if ( x=false ) and ( y=false ) and ( z=false ) then a[r,c]:=i;
        if ( c=9 ) and ( r<9 ) then r:=r+1;
        if ( c<9 ) then permute(r,c+1);
      end;
    Print;
  end;
begin
read(m,n,t);
  while (m<>0) and (n<>0) do
    begin
      a[n,m]:=t;
      Inserted [n,m]:=t;
      read(n,m,t);
    end;
  permute(1,1);
end.