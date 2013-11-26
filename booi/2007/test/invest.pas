{ 
TASK:invest
LANG:Pascal
}
const  infile = '';
      outfile = '';
       eff  : integer = 2;
         k    = 3;

type efm = array [1..k] of extended;
     arr = array [1..k] of integer;
const e : efm = (0,0.5,1);

var t,x : longint;
    p   : extended;
    maxu : extended;
    a,best : arr;

Procedure InX;
 begin
 readln(t,p,x);
 p := p/100;
 end;

procedure bt(cy : integer; X,U : extended);
 var i : integer;
     mu,nu : extended;

 begin
 if cy > t then
  begin
  if u > maxu then
   maxu := u;
  exit;
  end;
 mu := X*P;
 for i := 0 to eff do
  begin
  nu := i/eff*mu;
  bt(cy+1,X+mu-nu,U+nu);
  end;
 end;

procedure probe;
 var kap, u,mu,nu : extended;
     i,j : integer;
 begin
 kap := x;
 u := 0;
 for j := 1 to k do
  for i := 1 to a[j] do
   begin
   mu := kap * p;
   nu := e[j]*mu;
   kap := kap + mu-nu;
   u := u + nu;
   end;
 if u > maxu then
  begin
  best := a;
  maxu := u;
  end;
 end;

procedure track(h,ry : integer);
 var i : integer;
 begin
 if h = k then
  begin
  a[h] := ry;
  probe;
  exit;
  end;

 for i := 0 to ry do
  begin
  a[h] := i;
  track(h+1,ry-i);
  end;
 end;

procedure F_algor;
 begin
 track(1,t);
 end;

Procedure DoWork;
 var j,i : integer;
     Kap,U : extended;
 begin
{ bt(1,x,0);
 writeln('BT says : ',maxu:1:6);}


 maxu := 0;
 kap := x;
 u := t * kap * p;
 if u > maxu then maxu := u;
 for j := 1 to t do
  begin
  kap := kap * (p+1);
  u := (t-j) * kap * p;
  if u > maxu then maxu := u;
  end;
 end;

Procedure OutX;
 var
     s : string;
 begin
 str(maxu:1:8,s);
 s := copy(s,1,length(s)-2);
 writeln(s);
 end;

BEGIN
maxu := 0;
InX;
DoWork;
OutX;
END.
