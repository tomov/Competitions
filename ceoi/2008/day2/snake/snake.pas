program Snake;
uses snakelib;

var K : longint;
		a1, a2 : char;

begin

K := get_speed;
writeln('the snake''s speed is ', K);

writeln('asking the snake if it covers units 0 and 11');
ask_snake(0, 11, a1, a2);
writeln('and the snake says: ', a1, ' ', a2);

writeln('asking the snake if it covers units 2 and 10');
ask_snake(2, 10, a1, a2);
writeln('and the snake says: ', a1, ' ', a2);

writeln('asking the snake if it covers units 4 and 9');
ask_snake(4, 9, a1, a2);
writeln('and the snake says: ', a1, ' ', a2);

writeln('asking the snake if it covers units 6 and 10');
ask_snake(6, 10, a1, a2);
writeln('and the snake says: ', a1, ' ', a2);

writeln('tell the snake that you guess its length to be 6');
tell_length(6);
end.
