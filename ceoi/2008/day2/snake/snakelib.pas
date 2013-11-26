unit snakelib;

interface

function get_speed : longint;
procedure ask_snake(U1 : longint; U2 : longint; var A1 : char; var A2 : char);
procedure tell_length(L : longint);

implementation

const MAXN = 12121;
   MAXLEN = 12122;
   MAXCALL1 = 13;
   MAXCALL2 = 42;
   MAXSPEED = 10;
   
INPUT_FILE_NAME = 'snake.in';
   LOG_FILE_NAME = 'snake.log';

var initialised : boolean;
   infile, logfile : text;

Len, Tail, K : longint;
   turn : longint;

procedure die(Message : string);
var ior : longint;

begin
   if not initialised then
   begin
      assign(logfile, LOG_FILE_NAME);
      {$I-} rewrite(logfile); {$I+}
      ior := ioresult;
      if ior <> 0 then 
      begin
	 writeln('Error opening snake.log for writing.');
	 halt(1);
      end;
   end;
   writeln('An error has occured: ', Message, '. Please check snake.log');
   writeln(logfile, 'Error ', Message, '!');
   close(logfile);
   halt(1);
end;

function inttostr(i : longint) : string;
var s : string;
begin
   str(i, s);
   inttostr := s;
end;

procedure initialise;
var tmp : string;
   ior : longint;
begin
   assign(logfile, LOG_FILE_NAME);
   {$I-} rewrite(logfile); {$I+}
   ior := ioresult;
   if ior <> 0 then 
   begin
      writeln('Error opening snake.log for writing.');
      halt(1);
   end;

   assign(infile, INPUT_FILE_NAME);
   {$I-} reset(infile); {$I+}
   ior := ioresult;
   if ior <> 0 then die('could not open snake.in');
   read(infile, Len, Tail, K);
   close(infile);
   if Len > MAXLEN then begin tmp := 'the snake length must be at most ' + inttostr(MAXLEN); die(tmp); end;
   if Len < 1 then die('the snake must have a positive length');
   if Tail + Len - 1 > MAXN then begin tmp := 'all parts of the snake must initially be within the hearing distance ' + inttostr(MAXN); die(tmp); end;
   if Tail < 0 then die('the initial distance between you and the snake cannot be negative');
   if K < 0 then die('the snake speed cannot be a negative number');
   if K > MAXSPEED then begin tmp := 'the snake speed cannot exceed ' + inttostr(MAXSPEED); die(tmp); end;

   initialised := true;
end;


function get_speed : longint;
begin
   if initialised then die('do not call get_speed more than once');
   if not initialised then initialise;
   writeln(logfile, 'get_speed. reply: ', inttostr(K));
   get_speed := K;
end;

function eval(p : longint) : char;
var a : char;
   tmp : string;
begin
   if p < 0 then die('the position cannot have a negative value');
   if p > MAXN then begin tmp := 'the position cannot exceed ' + inttostr(MAXN); die(tmp); end;
   if p < Tail then begin a := 'b' end
   else if (p >= Tail + Len) then begin a := 'f' end
   else begin a := 's'; end;
   eval := a;
end;

procedure ask_snake(U1 : longint; U2 : longint; var A1 : char; var A2 : char);
var tmp : string;
begin
   inc(turn);
   if not initialised then die('you need to call get_speed first');
   write(logfile, turn:2, ': ask_snake(', U1, ', ', U2, '). reply: ');
   if turn >= MAXCALL2 then begin tmp := 'you cannot ask the snake more than ' + inttostr(MAXCALL2 - 1) + ' times'; die(tmp); end;

   if (turn mod 2 = 0) AND (Tail + K + Len < MAXN) then inc(Tail, K);
   A1 := eval(U1);
   A2 := eval(U2);
   writeln(logfile, A1, ' ', A2);
   writeln(logfile, '    (the snake currently covers units ', Tail, ' - ', Tail + Len - 1, ')');
end;

procedure tell_length(L : longint);
begin
   if not initialised then die('you need to call get_speed first');
   writeln(logfile, 'tell_length(', L, ')');
   if L < 1 then die('the snake length is always a positive number');
   if abs(L - Len) > K then 
      writeln(logfile, 'Wrong! Your estimate is not good enough')
   else
   begin
      writeln(logfile, 'Your estimate is within the allowed range! You needed to ask the snake ', turn, ' times.');
      if (turn <= MAXCALL1) then 
	 writeln(logfile, 'You will get full score for this test')
      else 
	 writeln(logfile, 'You will get half score for this test');
   end;
   close(logfile); 
   halt(0);
end;

begin
   initialised := false;
   turn := 0;
end.
