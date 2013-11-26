procedure PrintInserted;
var i,t:integer;
   begin
     for t:=1 to n do
       begin
         for i:=1 to n do
         write(Inserted[t,i],' ');
         writeln;
       end;
   end;
procedure Insert_Inserted;
var i,t:integer;
   begin
     for t:=1 to n do
       for i:=1 to n do
       Inserted[t,i]:=Insert[t,i];
   end;
procedure ClearUsed;
var l:integer;
   begin
     for l:=1 to n do
       used[l]:=false;
   end;
function CheckSudoku_Column:boolean;
var
    w,e,y,t,x:integer;
   begin
     ClearUsed;
     x:=0;
     for w:=1 to n do
       begin
         for e:=1 to n do
           begin
             t:=Inserted[e,w];
             used[t]:=true;
           end;
         for y:=1 to n do
           if used[y]=false then x:=1;
         if x=1 then break
                else ClearUsed;
       end;
     if x=0 then CheckSudoku_Column:=true
            else CheckSudoku_Column:=false;
   end;
function CheckSudokuSquare:boolean;
var i,p,t,ch:integer;
   begin
     ch:=0;
     for i:=1 to 2 do
       begin
         for p:=1 to 2 do
            begin
              x:=inserted[p,i];
              masivS[1,x]:=true;
            end;
         for p:=3 to 4 do
            begin
              x:=inserted[p,i];
              masivS[2,x]:=true;
            end;
       end;
     for i:=3 to 4 do
        begin
          for p:=1 to 2 do
             begin
               x:=inserted[p,i];
               masivS[3,x]:=true;
             end;
          for p:=3 to 4 do
             begin
               x:=inserted[p,i];
               masivS[4,x]:=true;
             end;
        end;
     for i:=1 to 4 do
        for p:=1 to 4 do
           if masiv[i,p]=true then ch:=ch+1;
     if ch=16 then CheckSudokuSquare:=true
              else CheckSudokuSquare:=false;
   end;
function CheckSudoku:boolean;
   begin
     if( CheckSudoku_Column=true ) and ( CheckSudokuSquare=true)
        then CheckSudoku:=true
        else CheckSudoku:=false;
   end;
function Check:boolean;
var i,t,x:integer;
   begin
     Insert_Inserted;
     x:=1;
     for i:=1 to n do
       begin
         for t:=1 to n do
         if Inserted[i,t]=0 then
           begin
             inserted[i,t]:=a[i,x];
             x:=x+1;
           end;
         x:=1;
       end;
     if CheckSudoku=true then PrintInserted;
   end;