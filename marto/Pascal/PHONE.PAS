var
   a:array[0..4,0..4]of boolean;
   TelNum:array[0..4]of string;
   Cost:array[0..4]of real;
   TotalCost:array[1..10000]of real;
   Button,Temp:array[0..4,1..11]of integer;
   K,EndNum:string;
   M,Sum,MinCost:real;
   N,P,p1,q,q1,o:integer;
function Check(x,y:integer):boolean;
var i,j,g,count:integer;
   begin
     Count:=0;
     for i:=1 to Button[x,11] do
        begin
          g:=Button[x,i];
          for j:=1 to Temp[y,11] do
             if Temp[y,j]=g then Count:=Count+1;
        end;
     if Count=length(TelNum[y]) then Check:=true
                             else Check:=false;
   end;
procedure PossibleCalls;
var S:string;
    i,j:integer;
    f:boolean;
   begin
    for i:=0 to N do
       begin
         S:=TelNum[i];
         for j:=1 to length(S) do
            Temp[i,j]:=ord(S[j])-ord('0');
         Temp[i,11]:=Length(S);
       end;
    for i:=0 to N do
       for j:=0 to N do
          if j<>i then
            begin
              f:=Check(i,j);
              a[i,j]:=f;
            end;
   end;
Procedure FindCost(t:integer);
var i:integer;
   begin
     if a[t,N+1]=true then
       begin
         o:=o+1;
         Sum:=Sum+Cost[t];
         TotalCost[o]:=Sum;
         Sum:=Sum-Cost[t];
         exit;
       end;
     for i:=0 to N do
        begin
          if a[t,i]=true then
            begin
              Sum:=Sum+Cost[t];
              FindCost(i);
              Sum:=Sum-Cost[t];
            end;
        end;
   end;
procedure FindMinCost;
var i:integer;
   begin
     MinCost:=TotalCost[1];
     for i:=1 to o do
        if MinCost>TotalCost[i] then MinCost:=TotalCost[i];
   end;
begin
  readln(N);
  for q:=0 to N do
     begin
       readln(TelNum[q]);
       read(Cost[q]);
       read(P);
       for q1:=1 to P do
          read(Button[q,q1]);
       readln;
       Button[q,11]:=P;
     end;
  readln(TelNum[N+1]);
  N:=N+1;
  PossibleCalls;
  N:=N-1;
  Sum:=0;
  o:=0;
  FindCost(0);
  FindMinCost;
  writeln(MinCost:3:2);
end.