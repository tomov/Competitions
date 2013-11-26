program Permute_without_repeating;
var
   a:array[0..10,0..10]of integer;
   done:array[1..10]of boolean;
   now,v:integer;
procedure ClearNext(r:integer);
var i:integer;
   begin
     for i:=1 to v do
       a[r,i]:=0;
   end;
function CheckArrayZero:boolean;
var i,p,k:integer;
   begin
     k:=0;
     for i:=1 to v do
       for p:=1 to v do
       if a[i,p]=0 then k:=1;
     if k=0 then CheckArrayZero:=true
            else CheckArrayZero:=false;
   end;
procedure writeperm;
var i,p:integer;
  begin
    writeln;
    for i:=1 to v do
      for p:=1 to v do
      begin
        write(a[i,p],' ');
        if p=v then writeln;
      end;
  end;
function CheckZero(r:integer):boolean;
var i,k:integer;
   begin
     k:=0;
     for i:=1 to v do
       if a[r,i]=0 then k:=1;
     if k=0 then CheckZero:=true
            else CheckZero:=false;
   end;
function LastPerm(r:integer):boolean;
var i,k:integer;
    zero:boolean;
   begin
     zero:=CheckZero(r);
     if zero=true then
       begin
         k:=1;
         for i:=1 to v-1 do
           if a[r,i] = ( a[r,i+1] + 1 ) then k:=k+1;
         if k=v then LastPerm:=true
                else LastPerm:=false;
       end
                  else LastPerm:=false;
   end;
procedure permute(p,k:integer);
var t,j:integer;
    LastNow:boolean;
   begin
     for j:=p+1 to v do
       done[j]:=false;
     now:=now+1;
     a[p,k]:=now;
     for t:=1 to v do
       if (a[p,t]=0)  then permute(p,t);
     if ( now=v )and( p<v ) then
     begin
       LastNow:=LastPerm(p);
       if ( LastNow=false )or( done[p]=false )
       then
         begin
           now:=-1;
           ClearNext(p+1);
           permute(p+1,0);
           LastNow:=LastPerm(p);
           if LastNow=true then done[p]:=true;
         end;
         if LastNow=false then
           begin
             if now>0 then now:=now-1
                      else now:=-1;
             a[p,k]:=0;
           end
                          else exit;
       end
       else begin
         LastNow:=LastPerm(p);
         if LastNow=true then exit;
         if now>0 then now:=now-1
                  else now:=-1;
         a[p,k]:=0;
            end;
   end;
begin
  read(v);
  now:=-1;
  permute(1,0);
end.