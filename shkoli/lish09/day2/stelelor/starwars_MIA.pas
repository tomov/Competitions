{ Mugurel Ionut Andreica - Bucuresti, ROMANIA }

{$S-,I-,R-,Q-,N+}
{$M 30000,0,655360}
Program _starwars_;

const filein='starwars.in';
      fileout='starwars.out';
      MAXN=100;
      infinit=10000;
      timelimit=17;
      maxperm=500;
      maxsets=500;
      maxpdeg=1;
      MISiter=160;
      maxtry=22;

type plist=^list;
     list=record
            vec:integer;
            urm:plist;
          end;

var sol,sact,perm,indepset,ncol,lstset:array[1..MAXN] of integer;
    asoc,deg,lst,lst2,marc,dego,nin,tata:array[1..MAXN] of integer;
    cmin:array[1..MAXN,1..3] of integer;
    used,color:array[1..MAXN] of boolean;
    edge:array[1..MAXN] of plist;
    a:array[1..MAXN,1..MAXN] of boolean;
    min,sum,i,j,k,m,n,p,nset,v,nv,ncomp,nedge,ninset,maxset,maxiter:integer;
    aux:plist;
    ok,oki:boolean;

    t2:longint absolute 0:$046c;
    t1:longint;

procedure print;
begin
assign(output,fileout);
rewrite(output);
min:=0;
for i:=1 to n do
  begin
    writeln(sol[i]);
    min:=min+sol[i];
  end;
close(output);

{
assign(output,'');
rewrite(output);
writeln(min);
writeln(t2-t1);
close(output);
}
halt(0);
end;

procedure bkt(niv:integer);
var s:integer;
begin
if (t2-t1>=timelimit) then
  print;

if (niv=n+1) then
  begin
    sum:=0;
    for i:=1 to n do
      sact[i]:=0;

    for i:=1 to n do
      begin
        for j:=1 to n do
          color[j]:=true;

        aux:=edge[perm[i]];
        while (aux<>nil) do
          begin
            j:=aux^.vec;
            if (sact[j]>0) then
              color[sact[j]]:=false;

            aux:=aux^.urm;
          end;

        for j:=1 to n do
          if (color[j]) then
            begin
              sact[perm[i]]:=j;
              break;
            end;

        sum:=sum+sact[perm[i]];
      end;

    if (sum<min) then
      begin
        min:=sum;
        for i:=1 to n do
          sol[i]:=sact[i];
      end;
  end
else
  begin
    for s:=1 to n do
      if (not used[s]) then
        begin
          used[s]:=true;
          perm[niv]:=s;
          bkt(niv+1);
          used[s]:=false;
        end;
  end;
end;

procedure randompermutations(n:integer);
begin
randomize;
for k:=1 to maxperm do
  begin
    if (t2-t1>=timelimit) then
      print;

    fillchar(used,sizeof(used),false);
    for i:=1 to n do
      begin
        repeat
          j:=random(n)+1;
        until (not used[j]);

        perm[i]:=j;
        used[j]:=true;
      end;

    sum:=0;
    fillchar(sact,sizeof(sact),0);

    for i:=1 to n do
      begin
        for j:=1 to n do
          color[j]:=true;

        aux:=edge[lst[perm[i]]];
        while (aux<>nil) do
          begin
            j:=aux^.vec;
            if (sact[j]>0) then
              color[sact[j]]:=false;

            aux:=aux^.urm;
          end;

        for j:=1 to n do
          if (color[j]) then
            begin
              sact[lst[perm[i]]]:=j;
              break;
            end;

        sum:=sum+sact[lst[perm[i]]];
        if (sum>=min) then
          break;
      end;

    if (sum<min) then
      begin
        min:=sum;
        for i:=1 to n do
          sol[lst[i]]:=sact[lst[i]];
      end;
  end;
end;

procedure maxindepsets(n:integer);
begin
randomize;
for k:=1 to maxsets do
  begin
    if (t2-t1>=timelimit) then
      print;

    fillchar(used,sizeof(used),false);
    for i:=1 to n do
      begin
        if (k=1) then
          j:=i
        else
          repeat
            j:=random(n)+1;
          until (not used[j]);

        perm[i]:=j;
        used[j]:=true;
      end;

    fillchar(indepset,sizeof(indepset),0);
    fillchar(nin,sizeof(nin),0);
    fillchar(asoc,sizeof(asoc),0);
    fillchar(ncol,sizeof(ncol),0);

    nset:=0;
    m:=n;

    while (m>0) do
      begin
        inc(nset);

        for i:=1 to n do
          if (indepset[lst[perm[i]]]=0) then
            begin
              ok:=true;

              aux:=edge[lst[perm[i]]];
              while (aux<>nil) do
                begin
                  j:=aux^.vec;
                  if (indepset[j]=nset) then
                    begin
                      ok:=false;
                      break;
                    end;

                  aux:=aux^.urm;
                end;

              if (ok) then
                begin
                  dec(m);
                  indepset[lst[perm[i]]]:=nset;
                  inc(nin[nset]);
                end;
            end;
      end;

    for i:=1 to nset do
      ncol[i]:=i;

    for i:=1 to nset-1 do
      for j:=i+1 to nset do
        if (nin[ncol[i]]<nin[ncol[j]]) then
          begin
            m:=ncol[i]; ncol[i]:=ncol[j]; ncol[j]:=m;
          end;

    for i:=1 to nset do
      asoc[ncol[i]]:=i;

    sum:=0;
    for i:=1 to n do
      begin
        sact[lst[i]]:=asoc[indepset[lst[i]]];
        sum:=sum+sact[lst[i]];

        if (sum>=min) then
          break;
      end;

    if (sum<min) then
      begin
        min:=sum;
        for i:=1 to n do
          sol[lst[i]]:=sact[lst[i]];
      end;
  end;
end;

procedure mindegfirst(n:integer);
var kk:integer;
begin
randomize;
for kk:=1 to maxpdeg do
  begin
    if (t2-t1>=timelimit) then
      print;

    fillchar(used,sizeof(used),false);
    for i:=1 to n do
      begin
        repeat
          j:=random(n)+1;
        until (not used[j]);

        perm[i]:=j;
        used[j]:=true;
      end;

    fillchar(dego,sizeof(dego),0);
    fillchar(asoc,sizeof(asoc),0);

    for i:=1 to n do
      begin
        m:=n+1;
        k:=0;

        for j:=1 to n do
          if (asoc[lst[perm[j]]]=0) and (deg[lst[perm[j]]]<m) then
            begin
              k:=lst[perm[j]]; m:=deg[lst[perm[j]]];
            end;

        asoc[k]:=1;
        dego[i]:=k;
      end;

    sum:=0;
    fillchar(sact,sizeof(sact),0);

    for i:=1 to n do
      begin
        for j:=1 to n do
          color[j]:=true;

        aux:=edge[dego[i]];
        while (aux<>nil) do
          begin
            j:=aux^.vec;
            if (sact[j]>0) then
              color[sact[j]]:=false;

            aux:=aux^.urm;
          end;

        for j:=1 to n do
          if (color[j]) then
            begin
              sact[dego[i]]:=j;
              break;
            end;

        sum:=sum+sact[dego[i]];
        if (sum>=min) then
          break;
      end;

    if (sum<min) then
      begin
        min:=sum;
        for i:=1 to n do
          sol[dego[i]]:=sact[dego[i]];
      end;
  end;
end;

procedure maxdeglast(n:integer);
var kk:integer;
begin
randomize;
for kk:=1 to maxpdeg do
  begin
    if (t2-t1>=timelimit) then
      print;

    fillchar(used,sizeof(used),false);
    for i:=1 to n do
      begin
        repeat
          j:=random(n)+1;
        until (not used[j]);

        perm[i]:=j;
        used[j]:=true;
      end;

    fillchar(dego,sizeof(dego),0);
    fillchar(asoc,sizeof(asoc),0);

    for i:=n downto 1 do
      begin
        m:=0;
        k:=0;

        for j:=1 to n do
          if (asoc[lst[perm[j]]]=0) and (deg[lst[perm[j]]]>m) then
            begin
              k:=lst[perm[j]]; m:=deg[lst[perm[j]]];
            end;

        asoc[k]:=1;
        dego[i]:=k;
      end;

    sum:=0;
    fillchar(sact,sizeof(sact),0);

    for i:=1 to n do
      begin
        for j:=1 to n do
          color[j]:=true;

        aux:=edge[dego[i]];
        while (aux<>nil) do
          begin
            j:=aux^.vec;
            if (sact[j]>0) then
              color[sact[j]]:=false;

            aux:=aux^.urm;
          end;

        for j:=1 to n do
          if (color[j]) then
            begin
              sact[dego[i]]:=j;
              break;
            end;

        sum:=sum+sact[dego[i]];
        if (sum>=min) then
          break;
      end;

    if (sum<min) then
      begin
        min:=sum;
        for i:=1 to n do
          sol[dego[i]]:=sact[dego[i]];
      end;
  end;
end;

procedure compute(nod:integer);
var aux:plist;
    i,c,c2:integer;
begin
cmin[nod,1]:=1;
cmin[nod,2]:=2;
cmin[nod,3]:=3;

aux:=edge[nod];
while (aux<>nil) do
  begin
    i:=aux^.vec;
    if (i<>tata[nod]) then
      begin
        tata[i]:=nod;
        compute(i);

        for c:=1 to 3 do
          begin
            sum:=infinit;
            for c2:=1 to 3 do
              if (c2<>c) and (cmin[i,c2]<sum) then
                sum:=cmin[i,c2];

            cmin[nod,c]:=cmin[nod,c]+sum;
          end;
      end;

    aux:=aux^.urm;
  end;
end;

procedure colornode(nod,colour:integer);
var aux:plist;
    i,c,c2:integer;
begin
sol[nod]:=colour;

aux:=edge[nod];
while (aux<>nil) do
  begin
    i:=aux^.vec;
    if (i<>tata[nod]) then
      begin
        sum:=infinit;
        for c:=1 to 3 do
          if (c<>colour) and (cmin[i,c]<sum) then
            begin
              sum:=cmin[i,c];
              c2:=c;
            end;

        colornode(i,c2);
      end;

    aux:=aux^.urm;
  end;
end;

procedure specialMIS(n:integer);
begin
fillchar(used,sizeof(used),false);
fillchar(indepset,sizeof(indepset),0);
fillchar(sact,sizeof(sact),0);

randomize;
m:=n;
nset:=0;
sum:=0;
while (m>0) do
  begin
    inc(nset);
    ninset:=0;
    maxset:=0;

    maxiter:=m*MISiter;
    for k:=1 to maxiter do
      begin
        if (t2-t1>=timelimit) then
          print;

        i:=random(100);
        if (i<25) and (ninset>2) then
          begin
            { Elimina un nod din MIS }
            repeat
              i:=random(m)+1;
            until (indepset[lst[i]]=nset);

            indepset[lst[i]]:=0;
            dec(ninset);
          end
        else
        if (ninset<m) then
          begin
            { Adauga un nod din MIS }
            for j:=1 to maxtry do
              begin
                repeat
                  i:=random(m)+1;
                until (indepset[lst[i]]=0);

                ok:=true;
                aux:=edge[lst[i]];
                while (aux<>nil) do
                  begin
                    p:=aux^.vec;
                    if (indepset[p]=nset) then
                      begin
                        ok:=false;
                        break;
                      end;

                    aux:=aux^.urm;
                  end;

                if (ok) then
                  begin
                    indepset[lst[i]]:=nset;
                    inc(ninset);
                    break;
                  end;
              end;
          end;

        if (ninset>maxset) then
          begin
            maxset:=0;
            for i:=1 to m do
              if (indepset[lst[i]]=nset) then
                begin
                  inc(maxset);
                  lstset[maxset]:=lst[i];
                end;
          end;
      end;

    if (maxset=0) then
      begin
        sum:=infinit;
        break;
      end
    else
      begin
        m:=m-maxset;

        nin[nset]:=maxset;

        for i:=1 to n do
          if (indepset[lst[i]]=nset) then
            indepset[lst[i]]:=0;

        for i:=1 to maxset do
          begin
            indepset[lstset[i]]:=nset;
          end;

        maxset:=0;
        for i:=1 to n do
          if (indepset[lst[i]]=0) then
            begin
              inc(maxset);
              lst[maxset]:=lst[i];
            end;
      end;
  end;

for i:=1 to nset do
  ncol[i]:=i;

for i:=1 to nset-1 do
  for j:=i+1 to nset do
    if (nin[ncol[i]]<nin[ncol[j]]) then
      begin
        m:=ncol[i]; ncol[i]:=ncol[j]; ncol[j]:=m;
      end;

for i:=1 to nset do
  asoc[ncol[i]]:=i;

{ Rebuild the original LST }

sum:=0;
for i:=1 to n do
  begin
    sact[lst2[i]]:=asoc[indepset[lst2[i]]];
    sum:=sum+sact[lst2[i]];

    if (sum>=min) then
      break;
  end;

if (sum<min) then
  begin
   min:=sum;
    for i:=1 to n do
      sol[lst2[i]]:=sact[lst2[i]];
  end;
end;

procedure df(nod:integer);
var aux:plist;
    i:integer;
begin
marc[nod]:=ncomp;
aux:=edge[nod];
while (aux<>nil) do
  begin
    i:=aux^.vec;
    inc(nedge);

    if (marc[i]=0) then
      df(i);

    aux:=aux^.urm;
  end;
end;

begin
t1:=t2;
assign(input,filein);
reset(input);
read(n,m);

fillchar(a,sizeof(a),false);
fillchar(deg,sizeof(deg),0);
for i:=1 to n do
  edge[i]:=nil;

for k:=1 to m do
  begin
    read(i,j);
    a[i,j]:=true;
    a[j,i]:=true;

    new(aux);
    aux^.vec:=j;
    aux^.urm:=edge[i];
    edge[i]:=aux;

    new(aux);
    aux^.vec:=i;
    aux^.urm:=edge[j];
    edge[j]:=aux;

    inc(deg[i]);
    inc(deg[j]);
  end;
close(input);

fillchar(sol,sizeof(sol),0);

if (n<=9) then
  begin
    fillchar(used,sizeof(used),false);
    min:=infinit;
    bkt(1);
  end
else
  begin
    fillchar(marc,sizeof(marc),0);
    ncomp:=0;

    for v:=1 to n do
      if (marc[v]=0) then
        begin
          inc(ncomp);
          nedge:=0;
          df(v);
          nedge:=nedge shr 1;

          nv:=0;
          for i:=1 to n do
            if (marc[i]=ncomp) then
              begin
                inc(nv);
                lst[nv]:=i;
                lst2[nv]:=i;
              end;

          if (nedge=nv-1) then
            begin
              { If the current connected component is a tree, then
                use a polynomial sum-colouring algorithm, which uses
                at most 3 colours (although a tree is 2-colourable) }

              fillchar(tata,sizeof(tata),0);
              compute(lst[1]);

              if (cmin[lst[1],1]<=cmin[lst[1],2]) and
                 (cmin[lst[1],1]<=cmin[lst[1],3]) then
                begin
                  colornode(lst[1],1);
                end
              else
              if (cmin[lst[1],2]<=cmin[lst[1],1]) and
                 (cmin[lst[1],2]<=cmin[lst[1],3]) then
                begin
                  colornode(lst[1],2);
                end
              else
              if (cmin[lst[1],3]<=cmin[lst[1],1]) and
                 (cmin[lst[1],3]<=cmin[lst[1],2]) then
                begin
                  colornode(lst[1],3);
                end;
            end
          else
            begin
              { If the current connected component is not a tree, then
                use several heuristics & choose the best solution }

              min:=infinit;

              randompermutations(nv);
              maxindepsets(nv);
              mindegfirst(nv);
              maxdeglast(nv);

              specialMIS(nv);
            end;
        end;
  end;

print;
end.