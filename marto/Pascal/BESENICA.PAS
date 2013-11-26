var
   word,guess:string;
   long:integer;
procedure besenica;
var
   character:char;
   i,p,z,g,num,k:integer;
   begin
     for i:=1 to 2*long do
       begin
         readln(character);
           for p:=1 to long do
           begin
             z:=pos(character,word);
             if z<>0 then
	     begin
	       word[z]:='1';
               guess[z]:=character;
             end;
           end;
         for g:=1 to long do
           if word[g]<>'1' then write('_')
                           else write(guess[g]);
         num:=0;
         for k:=1 to long do
           if word[k]='1' then num:=num+1;
         if num=long then break;
       end;
   end;
begin
  readln(word);
  long:=length(word);
  besenica;
end.