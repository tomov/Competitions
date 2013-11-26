Program Namirane_Na_NOD;
var a,b,c,i:integer;
 begin
  writeln('a=','b=');
   read(a,b);
    if a=b then writeln('Nai Golemiat Obsht Delitel e ',a);
   c:=a;
      if c>b then c:=b;
       for i:=c downto 1 do
          begin
           if (a mod i=0) and (b mod i=0) then break;
          end;
  writeln('Nai Golemiat Obsht Delitel e ',i);
 end.