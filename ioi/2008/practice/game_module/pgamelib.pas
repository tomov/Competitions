{ This sample library can be used for testing purposes. }

unit pgamelib;

interface
uses BaseUnix;
procedure initialize;
function getN : longint; 
function getValue(city: longint) : longint;
function move(city : longint) : longint;

implementation

const
	MAXN = 2010;

var
	initialized : boolean;
	n : longint;
	list : array [0..MAXN] of longint;
	left, right, score : longint;
	
procedure initialize;
var
	i : longint;
begin
	if initialized then
	begin
		writeln('ERROR: Cannot Initialize Twice.');
		flush(output);
		FpExit(0);
	end;

	initialized := true;
	readln(n);
	for i:=0 to n-1 do
		readln(list[i]);
	
	left := 0;
	right := n-1;
	score := 0;
	randomize;
	writeln('Initialization Complete.');
end;


function getN : longint;
begin
	if initialized <> true then
	begin
		writeln('Error: Cannot call getN() before initialize().');
		flush(output);
		FpExit(0);
	end;
	writeln('getN() returns ', n);
	getN := n;
end;


function getValue(city: longint) : longint;
begin
	if initialized <> true then
	begin
		writeln('ERROR: Cannot call getValue() before initialize().');
		flush(output);
		FpExit(0);
	end;
	if (city<0) or (city>=n) then
	begin
		writeln('ERROR: City ', city, ' is invalid.');
		flush(output);
		FpExit(0);
	end;
	writeln('getValue(', city, ') returns ', list[city]);
	getValue := list[city];
end;

function move(city : longint) : longint;
var
	i, response: longint;
begin
	writeln('Your move is: put the bastions after city ',city);
	if not ((city>=left) and (city<right)) then
	begin
		writeln('ERROR: Your move is invalid.');
		flush(output);
		FpExit(0);
	end; 
	
	{ You may change the response choice to have a better opponent. }
	response := random(99999) mod 2;

	if response = 0 then
	begin
		for i:=left to city do
		begin
			score := score + list[i];
			right := city;
		end;
	end
	else
	begin
		for i:= city+1 to right do
		begin
			score := score + list[i];
		end;
		left := city + 1;
	end;
	if response <> 0 then
	begin
		writeln('Opponent attacks from: ', 'Left.');
	end
	else
	begin
		writeln('Opponent attacks from: ', 'Right.');
	end;

	writeln('New interval is: [', left, ',', right, '].');
	writeln('Total score at this moment is ', score, '.');
	if left>=right then
	begin
		writeln('Final total score is ', score, '.');
		flush(output);
		FpExit(0);
	end;
	move := response;
end;

begin
	initialized := false;
end.
