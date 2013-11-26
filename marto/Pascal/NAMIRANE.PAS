program Namirane_Korenite_Na_Kvadratno_Uravnenie;
var a,x,b,c,x1,x2,D:real;
 begin
  writeln('a= ','b= ','c= ');
  read(a,b,c);
   if (a=0) and (b<>0) then
    begin
     x:=(-c)/b;
     writeln('x=',x:5:3);
    end;
    if (a=0) and (b=0) and (c=0) then writeln('Vsiako x e reshenie');
    if (a=0) and (b=0) and (c<>0) then writeln('Niama Reshenie');
    if (a<>0) then
    begin
       D:=(sqr (b) + (4*a*c)*(-1));
       if D<0 then writeln('Niama Reshenie')
       else
       begin
          x1:=((b*(-1)) + sqrt (D))/2*a;
          x2:=((b*(-1)) - sqrt (D))/2*a;
          if x1=x2 then writeln('x1=x2=',x1:5:3)
          else
          begin
             writeln('x1=',x1:5:3);
             writeln('x2=',x2:5:3);
          end;
       end;
    end;
 end.