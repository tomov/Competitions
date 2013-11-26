type
    tip=-1..1;
var
   a:array[1..100,1..100]of tip;
   n,s,d,y,k,t,u:integer;
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
procedure Print;
var row,col:integer;
  begin
    for row:=1 to n do
      begin
      for col:=1 to n do
        if a[row,col]=1 then write(row,' ',col,' ');
        if col=n then writeln;
      end;
  end;
  begin
    read(n,s,d);
    a[s,d]:=1;
    Fill_Up_Left(s,d);
    Fill_Up_Right(s,d);
    Fill_Down_Left(s,d);
    Fill_Down_Right(s,d);
    Fill_Up_Down_Left_Right(s,d);
    for t:=1 to n do
      begin
        for u:=1 to n do
          if a[t,u]=0 then
          begin
            a[t,u]:=1;
            Fill_Up_Left(t,u);
            Fill_Up_Right(t,u);
            Fill_Down_Left(t,u);
            Fill_Down_Right(t,u);
            Fill_Up_Down_Left_Right(t,u);
          end;
      end;
    Print;
  end.