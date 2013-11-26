program robot;

var
   response      : string;
   width, height : longint;
   
begin
   repeat
      writeln('left');
      flush(output);
      readln(response);
   until response = 'fail';

   width := 0;
   repeat
      width := width+1;
      writeln('right');
      flush(output);
      readln(response);
   until response = 'fail';
   
   repeat
      writeln('up');
      flush(output);
      readln(response);
   until response = 'fail';

   height := 0;
   repeat
      height := height+1;
      writeln('down');
      flush(output);
      readln(response);
   until response = 'fail';
   
   writeln(width*height);
   flush(output);
end.
