program Namirane_Korenite_Na_Kvadratno_Uravnenie;
var
   K:array[1..10000]of real;
   a1,b1,c1,x1,x2,D:real;
   n,num,i:integer;
procedure Find(a,b,c:real);
   begin
     if (a=0) and (b<>0) then
       begin
         x1:=(-c)/b;
         Num:=Num+1;
         K[Num]:=x1;
         exit;
       end;
    if (a=0) and (b=0) and (c=0) then exit;
    if (a=0) and (b=0) and (c<>0) then exit;
    if (a<>0) and (b<>0) then
      begin
        D:=(sqr (b) + (4*a*c)*(-1));
        if D<0 then exit
               else begin
                       x1:=((b*(-1)) + sqrt (D))/2*a;
                       x2:=((b*(-1)) - sqrt (D))/2*a;
                       if x1=x2 then
                         begin
                           Num:=Num+1;
                           K[Num]:=x1;
                           exit;
                         end
                                else
                         begin
                           Num:=Num+1;
                           K[Num]:=x1;
                           Num:=Num+1;
                           K[Num]:=x2;
                           exit;
                         end;
               end;
      end;
   end;
procedure BubbleSort;
var j:integer;
    t:real;
   begin
     repeat
       t:=k[1];
       for j:=2 to Num do
          if k[j-1]>k[j] then
            begin
              t:=k[j-1];
              k[j-1]:=k[j];
              k[j]:=t;
            end
     until t=k[1];
   end;
 begin
  Num:=0;
  read(n);
  for i:=1 to n do
     begin
       read(a1,b1,c1);
       Find(a1,b1,c1);
     end;
  BubbleSort;
  for i:=1 to num do
     write(k[i]:2:3,' ');
 end.