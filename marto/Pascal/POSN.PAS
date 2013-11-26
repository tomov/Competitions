 var
   a:array[1..64812]of char;
   next:longint;
procedure FillNums;
var S,Temp:string;
    i,j,t:longint;
   begin
     next:=0;
     S:='';
     for i:=1 to 15000 do
        begin
          if length(S)<245 then
            begin
              str(i,Temp);
              S:=S+Temp;
            end
                           else
            begin
             t:=next;
              for j:=1 to length(S) do
                   a[t+j]:=S[j];
              writeln(next);
              next:=next+length(S);
              str(i,S);
            end;
        end;
   end;
begin
  FillNums;
end.
