var
   FirstNum,SecondNum:string;
   Sign:boolean;
   Bigger:byte;
   x,y,Longer:integer;
procedure Change;
var i:byte;
   begin
     for i:=1 to 254 do
        Firstnum[i]:=FirstNum[i+1];
     Sign:=true;
   end;
procedure FindBigger;
var i:byte;
   begin
     Bigger:=0;
     x:=length(FirstNum);
     y:=length(SecondNum)-1;
     if x>y then Bigger:=1;
     if y>x then Bigger:=2;
     if x=y then
       for i:=1 to x do
            if FirstNum[i]<>SecondNum[i+1] then
              begin
                if FirstNum[i]>SecondNum[i+1] then Bigger:=1
                                              else Bigger:=2;
                break;
              end;
   end;
procedure Fill_Up_FirstNum;
var
   i,Temp:byte;
   Num:char;
   begin
     for i:=1 to x do
        begin
          Temp:=ord(FirstNum[i]) - ord('0');
          Temp:=9 - Temp;
          if Temp<>0 then
             begin
               Num:=chr( ord(Temp) + ord('0') );
               FirstNum[i]:=Num;
             end;
        end;
   end;
procedure Fill_Up_SecondNum;
var
   i,Temp:byte;
   Num:char;
   begin
     for i:=1 to y do
        begin
          Temp:=ord(SecondNum[i]) - ord('0');
          Temp:=9 - Temp;
          if Temp<>0 then
             begin
               Num:=chr( ord(Temp) + ord('0') );
               SecondNum[i]:=Num;
             end;
        end;
   end;
begin
  readln(FirstNum);
  readln(SecondNum);
  if FirstNum[1]='-' then Change;
  FindBigger;
  Fill_Up_FirstNum;
  Fill_Up_SecondNum;

end.