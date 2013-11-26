program Namirane_Na_Faktoriel;
var x:integer;
function Faktoriel(a:integer):integer;
 var b,i:integer;
  begin
    b:=1;
    for i:=1 to a do
      b:=b*i;
    Faktoriel:=b;
  end;
begin
writeln('x=');
read(x);
writeln(x,'!=',Faktoriel(abs(x)));
end.