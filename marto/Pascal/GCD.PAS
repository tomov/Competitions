var a,b:integer;
function gcd(u,v:integer):integer;
  begin
    if v=0 then gcd:=u
           else gcd:=gcd(v, u mod v)
  end;
  begin
    writeln('a= ','b=');
    read(a,b);
    writeln(gcd(abs(a) , abs(b)));
  end.