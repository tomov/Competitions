type
    tip=-1..1;
var
   a,b:array[1..100,1..100]of tip;
   n:integer;
procedure CopyA_B;
var i,p:integer;
  begin
    for i:=1 to n do
      for p:=1 to n do
        b[i,p]:=a[i,p];
  end;
procedure CopyB_A;
var i,p:integer;
  begin
    for i:=1 to n do
      for p:=1 to n do
        a[i,p]:=b[i,p];
  end;
procedure ClearArray;
var i,p:integer;
   begin
     for i:=1 to n do
       for p:=1 to n do
         a[i,p]:=0;
   end;
procedure Print;
var i,p:integer;
  begin
    writeln(' Vazmojnost ');
    for i:=1 to n do
      begin
        for p:=1 to n do
          if a[i,p]=1 then write(i,' ',p,' ');
        writeln;
      end;
  end;
procedure Fill_Up_Left(r,c:integer);
var i,g,h:integer;
  begin
    if (r<>1) and (c<>1) then
    begin
      for i:=1 to n do
        begin
          g:=r-i;
          h:=c-i;
          a[g,h]:=-1;
          if (g=1) or (h=1) then break;
        end;
    end;
  end;
procedure Fill_Up_Right(r,c:integer);
var i,g,h:integer;
  begin
    if (r<>1) and (c<>n) then
    begin
      for i:=1 to n do
        begin
          g:=r-i;
          h:=c+i;
          a[g,h]:=-1;
          if (g=1) or (h=n) then break;
        end;
    end;
  end;
procedure Fill_Down_Left(r,c:integer);
var i,g,h:integer;
  begin
    if (r<>n) and (c<>1) then
    begin
      for i:=1 to n do
        begin
          g:=r+i;
          h:=c-i;
          a[g,h]:=-1;
          if (g=n) or (h=1) then break;
        end;
    end;
  end;
procedure Fill_Down_Right(r,c:integer);
var i,g,h:integer;
  begin
    if (r<>n) and (c<>n) then
    begin
      for i:=1 to n do
        begin
          g:=r+i;
          h:=c+i;
          a[g,h]:=-1;
          if (g=n) or (h=n) then break;
        end;
    end;
  end;
procedure Fill_Up_Down_Left_Right(r,c:integer);
var i,g:integer;
  begin
    for i:=1 to n do
      begin
      a[i,c]:=-1;
      a[r,i]:=-1;
      end;
    a[r,c]:=1;
  end;
function CheckQueens(s,d:integer):integer;
var i,p,k,e,t,w:integer;
  begin
    Fill_Up_Left(s,d);
    Fill_Up_Right(s,d);
    Fill_Down_Left(s,d);
    Fill_Down_Right(s,d);
    Fill_Up_Down_Left_Right(s,d);
    k:=1;
    for i:=1 to n do
      begin
      for p:=1 to n do
        if a[i,p]=0 then
        begin
          a[i,p]:=1;
          Fill_Up_Left(i,p);
          Fill_Up_Right(i,p);
          Fill_Down_Left(i,p);
          Fill_Down_Right(i,p);
          Fill_Up_Down_Left_Right(i,p);
          k:=k+1;
        end;
      end;
    if k=n then CheckQueens:=1
           else CheckQueens:=0;
  end;
procedure FindQueens;
var w,p,f:integer;
   begin
     for w:=1 to n do
       begin
         a[1,w]:=1;
         CopyA_B;
         f:=CheckQueens(1,w);
         if f=1 then Print;
         ClearArray;
       end;
   end;
begin
  read(n);
  FindQueens;
end.