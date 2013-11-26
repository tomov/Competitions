
{
HIO 2004
Zadatak MRAVI
}

{
   Ovo je jedan zadatak koji se bazira na slijedecoj
   cinjenici:
      Ako se susretnu mravi m1 i m2, i recimo da m1
      putuje na desno, a mrav m2 na lijevo tada nakon
      odbijanja, smjer mrava m2 mozemo smatrati novim
      smjerom mrava m1 i obratno. To se moze lagano
      dokazati. I sad mozemo za svakog mrava smatrati
      da ce se on samo odbijati od ruba, a ne od drugih
      mrava. Dakle za svakog mrava prema tome trazimo
      gdje ce zavrsiti, te zavrsne pozicije sortiramo
      i ispisemo.
   Slozenost ovog algoritma je O(N log(N)), pri cemu
   je N broj mrava.
}

var heap: array[1..150000] of longint;
    i, n, k, m, d, s: longint;
    c: char;

procedure heap_push(k: longint);
var j, m1: longint;
begin
    m := m + 1;
    heap[m] := k; m1 := m;
    while ((m1 > 1) and (heap[m1 div 2] > heap[m1])) do begin
        j := heap[m1 div 2]; heap[m1 div 2] := heap[m1]; heap[m1] := j;
        m1 := m1 div 2;
    end;
end;

function heap_top : longint;
begin
    heap_top := heap[1];
end;

procedure heap_pop;
var j, k: longint;
begin
    heap[1] := heap[m];
    m := m - 1; j := 1;
    while (((heap[j] > heap[j*2]) or (heap[j] > heap[j*2+1])) and (j <= m div 2)) do begin
        if (heap[j*2] < heap[j*2+1]) then begin
           k := heap[j]; heap[j] := heap[j*2]; heap[j*2] := k;
           j := j*2;
        end else begin
           k := heap[j]; heap[j] := heap[j*2+1]; heap[j*2+1] := k;
           j := j*2+1;
        end;
        if (j*2 > m) then break;
    end;
end;

function racunaj(poz: longint; kamo: char): longint;
var s1: longint;
begin
    if (kamo = 'D') then begin
       s1 := s + poz;
       s1 := s1 mod (2*d-2);
       if (s1 < d) then racunaj := s1 else racunaj := d - s1 + d - 2;
    end else racunaj := d-racunaj(d-poz-1, 'D')-1;
end;

begin
    read(d, s); d := d + 1;
    read(n); m := 0;
    for i := 1 to n do begin
        readln(k, c, c);
        k := racunaj(k, c);
        heap_push(k);
    end;

    for i := 1 to n do begin
        write(heap_top()); if (i < n) then write(' ');
        heap_pop();
    end; writeln;

end.
