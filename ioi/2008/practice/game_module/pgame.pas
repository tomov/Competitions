{
  This program describes how to use the library for the task "game".
  It plays randomly.
}

uses pgamelib;

var
   list: array [0..2010] of longint;
   n, left, right, i, city: longint;

begin
   initialize();
   n := getN();
   for i:=0 to n-1 do
      list[i] := getValue(i);
	
   left := 0;
   right := n-1;
	
   while true do
	begin
	   city := random(99999) mod (right-left) + left;
	   if move(city) = 0 then
	      right := city
	   else
	      left := city + 1;
	end;
end.
