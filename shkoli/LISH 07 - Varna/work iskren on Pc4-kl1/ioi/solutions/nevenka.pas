
{
HIO 2004
Zadatak NEVENKA
}

{
    Da bi oni dosli sto blize Nevenki, oni moraju
    doci sto prije do svake crkve, dakle najblizim
    putem. Iz ovog mozemo zakljuciti da ce svi ici
    najblizim putom do bilo koje crkve. Dakle
    trebamo napraviti dijkstru(algoritam za najblizi
    put od nekog cvora u grafu do svih drugih cvorova)
    za sve kafice i za Nevenku. Trazimo minimalnu
    razliku do bilo koje crkve i to ispisemo.
    Slozenost je O((b_kaf+1) * (N*N)).
}

var br_cr, br_kaf, n, nev, i, j, k, m, tre, best, b1, b2: longint;
    veze: array[1..1000, 1..1000] of integer;
    kafici, crkve: array[1..200] of integer;

function min(a, b: longint): longint;
begin
   if (a < b) then min := a else min := b;
end;

procedure dijkstra(grad: integer);
var bio, dulj: array[1..1000] of integer;
    i, j, tre, t: integer;
begin
    for i := 1 to n do begin
        bio[i] := 0; dulj[i] := 10000;
    end; dulj[grad] := 0;

    for i := 1 to n do begin
        tre := 20000;
        for j := 1 to n do if ((dulj[j] < tre) and (bio[j] = 0)) then begin
              tre := dulj[j]; t := j;
        end; bio[t] := 1;
        for j := 1 to n do if (dulj[j] > dulj[t]+veze[t, j]) then dulj[j] := dulj[t] + veze[t, j];
    end;
    for i := 1 to n do begin
        veze[grad, i] := min(veze[grad, i], dulj[i]);
        veze[i, grad] := veze[grad, i];
    end;

end;

begin
   best := 1000000;
   read(n, nev);
   for i := 1 to n do
       for j := 1 to n do
          if (i <> j) then veze[i, j] := 10000;
   read(br_cr); for i := 1 to br_cr do read(crkve[i]);
   read(br_kaf); for i := 1 to br_kaf do read(kafici[i]);
   read(m); while (not(eof(input))) do begin
       readln(j, k); veze[j, k] := 1; veze[k, j] := 1;
   end;

   for i := 1 to br_cr do dijkstra(crkve[i]);

   for i := 1 to br_kaf do
      for j := i+1 to br_kaf do begin
          tre := 0;
          for k := 1 to br_cr do if (min(veze[kafici[i], crkve[k]], veze[kafici[j], crkve[k]])-veze[nev, crkve[k]] > tre) then
                              tre := min(veze[kafici[i], crkve[k]], veze[kafici[j], crkve[k]])-veze[nev, crkve[k]];
          if (tre <= best) then begin
             best := tre; b1 := kafici[i]; b2 := kafici[j];
          end;
      end;

   writeln(b1, ' ', b2);

end.
