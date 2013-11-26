{$N+}
const
 bignum=10000;
var
 t:text;  {  dx1*dy2-dx2*dy1;}
 fl:boolean;
 i,j,k,l,n,tc,tcn:longint;
 tx,ti,ty,x,y,px,py:array [1..300] of integer;
 tp,p:array [1..300] of extended;
 x1,y1,x2,y2:array [1..124] of integer;
 pp,w:extended;

 function oreant(x1,y1,x2,y2,x3,y3:integer):integer;
  var
   dx1,dy1,dx2,dy2,dd:integer;
  begin
    dx1:=x2-x1; dy1:=y2-y1;
    dx2:=x3-x1; dy2:=y3-y1;
    dd:=dx1*dy2-dx2*dy1;
    if dd<0 then oreant:=-1 else
    if dd>0 then oreant:=1 else
    oreant:=0;
  end;

 function pres(x11,y11,x12,y12,x21,y21,x22,y22:integer):boolean;
  var
   dx1,dy1,dx2,dy2:integer;
  begin
    if (oreant(x11,y11,x22,y22,x12,y12)<>oreant(x11,y11,x21,y21,x12,y12))and
       (oreant(x21,y21,x11,y11,x22,y22)<>oreant(x21,y21,x12,y12,x22,y22)) then pres:=true
    else pres:=false;
  end;
begin
{  assign(t,'square.in');
  reset (t);}
  readln ({t,}n);
  for i:=1 to n do
   begin
     readln({t,}x[i*4-3],y[i*4-3]);
     x[i*4-2]:=x[i*4-3]+5; y[i*4-2]:=y[i*4-3];
     x[i*4-1]:=x[i*4-3]+5; y[i*4-1]:=y[i*4-3]+5;
     x[i*4-0]:=x[i*4-3]; y[i*4-0]:=y[i*4-3]+5;
     x1[i*4-3]:=x[i*4-3]; y1[i*4-3]:=y[i*4-3]; x2[i*4-3]:=x[i*4-2]; y2[i*4-3]:=y[i*4-2];
     x1[i*4-2]:=x[i*4-2]; y1[i*4-2]:=y[i*4-2]; x2[i*4-2]:=x[i*4-1]; y2[i*4-2]:=y[i*4-1];
     x1[i*4-1]:=x[i*4-1]; y1[i*4-1]:=y[i*4-1]; x2[i*4-1]:=x[i*4-0]; y2[i*4-1]:=y[i*4-0];
     x1[i*4-0]:=x[i*4-0]; y1[i*4-0]:=y[i*4-0]; x2[i*4-0]:=x[i*4-3]; y2[i*4-0]:=y[i*4-3];
     px[i*2-1]:=x[i*4-3]+5; py[i*2-1]:=y[i*4-3];
     px[i*2]:=x[i*4-3]; py[i*2]:=y[i*4-3]+5;
     p[i*2-1]:=bignum;
     p[i*2]:=bignum;
   end;
  {close (t);}
  px[n*2+1]:=100; py[n*2+1]:=100; p[n*2+1]:=bignum;

  tc:=1; tx[1]:=0; ty[1]:=0; tp[1]:=0;
  repeat
    for i:=1 to tc do
     for k:=1 to n*2+1 do
      begin
        w:=sqrt(sqr(px[k]-tx[i])+sqr(py[k]-ty[i]));
        if tp[i]+w<p[k] then
         begin
           fl:=true;
           for j:=1 to n*4 do
            if (j<>k*2)and(j<>k*2-1)and(j<>ti[i]*2)and(j<>ti[i]*2-1) then
             if pres(tx[i],ty[i],px[k],py[k],x1[j],y1[j],x2[j],y2[j]) then begin fl:=false; break; end;
           if fl then
            begin
              inc(tcn);
              tx[tc+tcn]:=px[k]; ty[tc+tcn]:=py[k];
              tp[tc+tcn]:=tp[i]+w;
              ti[tc+tcn]:=k;
              p[k]:=tp[tc+tcn];
            end;
         end;
      end;

    for i:=1 to tcn do
     begin tx[i]:=tx[i+tc]; ty[i]:=ty[i+tc]; tp[i]:=tp[i+tc]; ti[i]:=ti[i+tc]; end;
    tc:=tcn; tcn:=0;
  until tc=0;

  writeln(p[n*2+1]:0:5);
end.