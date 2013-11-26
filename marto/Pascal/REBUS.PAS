var
   a:array[1..10] of byte;
   used:array[0..9] of boolean;
   Letter,Sign:array[1..10] of char;
   n:byte;
   S,Temp:string;
   f:integer;
Procedure FindNumOfLetters;
var i,j:integer;
    t:char;
    v:boolean;
   begin
     N:=0;
     v:=false;
     for i:=1 to length(S) do
        begin
          t:=S[i];
          if (t<>'+') and (t<>'-') and (t<>'=') then
            begin
               for j:=1 to 10 do
                  if Letter[j]=t then v:=true;
               if v=false then
                 begin
                   N:=N+1;
                   Letter[N]:=S[i];
                 end;
               v:=false;
            end
                                                else
            Sign[i]:=S[i];
        end;
   end;
function SubtractNums(x,y:integer):string;
var i,j:integer;
   begin

   end;
function AddNums(x,y:integer):string;
var i,j:integer;
   begin

   end;
procedure CheckRebus;
var i,j:integer;
    ch:char;
    t,l:string;
   begin
     for i:=1 to n do
        for j:=1 to length(S) do
           if S[j]=letter[i] then
             begin
               ch:=chr( a[i]+ord('0') );
               Temp[j]:=ch;
             end;
     for i:=1 to length(Temp) do
        if (Temp[i]='-') or (Temp[i]='+') then
          begin
            if (Temp[1]='0') or (Temp[i+1]='0') then exit;
            for j:=i to length(Temp) do
               if (Temp[j]='-') or (Temp[j]='+') then break;
            j:=j-1;
            if Temp[i]='-' then t:=SubtractNums(i-1,j)
                           else t:=AddNums(i-1,j);
            l:=t;
            for j:=i to length(Temp) do
               l:=l+Temp[j];
            Temp:=l;
          end;
     j:=pos('=',Temp);

   end;
procedure variate(k:byte);
var i:byte;
   begin
     if k=n then used[a[k]]:=false;
     for i:=0 to 9 do
        begin
          if used[i]=false then
            begin
              a[k]:=i;
              used[i]:=true;
              if k<n then variate(k+1);
              CheckRebus;
              used[i]:=false;
            end;
        end;
   end;
begin
  readln(S);
  Temp:=S;
  FindNumOfLetters;
  variate(1);
end.