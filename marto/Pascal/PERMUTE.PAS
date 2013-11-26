program Permute_without_repeating;
var
   a:array[0..100]of integer;
   now,v:integer;
procedure writeperm;
var i:integer;
  begin
    for i:=1 to v do
      write(a[i],' ');
    writeln;
  end;
procedure permute(k:integer);
var t:integer;
   begin
     now:=now+1;
     a[k]:=now;
     if now=v then writeperm;
     for t:=1 to v do
       if a[t]=0 then permute(t);
     now:=now-1;
     a[k]:=0;
   end;
begin
  read(v);
  now:=-1;
  permute(0);
end.