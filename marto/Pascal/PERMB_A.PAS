program Permute_withuot_repeating_numbers;
var
   a,b,insert,inserted,masiv:array[1..4,1..4]of integer;
   masivS:array[1..4,1..4]of boolean;
   used:array[1..4]of boolean;
   n,z,f:integer;
procedure ReadInsert;
var p,q,t:integer;
   begin
     read(p,q,t);
     while (p<>0) and (q<>0) do
       begin
         insert[p,q]:=t;
         read(p,q,t);
       end;
   end;
procedure FindNonInserted;
var i,p,x,num:integer;
   begin
     for i:=1 to n do
       for p:=1 to n do
         if insert[i,p]<>0 then
         begin
           x:=Insert[i,p];
           masiv[i,x]:=x;
         end;
     num:=1;
     for i:=1 to n do
       for p:=1 to n do
         begin
           if masiv[i,p]=0 then
              begin
                b[i,num]:=p;
                num:=num+1;
              end;
           if p=n then num:=1;
         end;
   end;
function FindEndNum(r:integer):integer;
var i:integer;
   begin
     for i:=1 to n+1 do
       if (b[r,i]=0)or(i>n) then break;
     i:=i-1;
     FindEndNum:=i;
   end;
function CheckA(r,c,k:integer):boolean;
var i,g:integer;
   begin
     g:=0;
     for i:=1 to c do
        if a[r,i]=k then g:=1;
     if g=1 then CheckA:=true
            else CheckA:=false;
   end;
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
var i,p,t,ch,x:integer;
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
           if masivS[i,p]=true then ch:=ch+1;
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
procedure permute(r,c,EndNum:integer);
var i,fin:integer;
    z:boolean;
   begin
     for i:=1 to EndNum do
       begin
         z:=CheckA(r,c,b[r,i]);
         if z=false then
         begin
           a[r,c]:=b[r,i];
           if r=n then Check;
           if (c=EndNum) and (r<n) then
           begin
             fin:=FindEndNum(r+1);
             permute(r+1,1,fin);
           end;
           if c<EndNum then permute(r,c+1,EndNum);
         end;
       end;
   end;
begin
  read(n);
  ReadInsert;
  FindNonInserted;
  f:=FindEndNum(1);
  permute(1,1,f);
end.