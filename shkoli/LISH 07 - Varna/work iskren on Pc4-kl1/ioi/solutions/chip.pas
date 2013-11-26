
{
HIO 2004
Zadatak CHIP
}

{
  Sortirajmo tocke po x koordinati slijeva na desno.
  Pretpostavimo da smo spojili SVE tocke lijevo tocki I.

  1.) Ako zelimo tocku I spojiti s desnom stranom kvadrata ne smeta nam niti
  jedna tocka buduci da su sve dosad spojene tocke njoj lijevo.

  2.) Ako zelimo tocku I spojiti s lijevom stranom kvadrata, mogu nam smetati
  linije koje su nastale spajanjem neke tocke s gornjom stranom kvadrata
  ( u primjeru su to tocke A i D ), ili spajanjem neke tocke s donjom
  stranom kvadrata ( u primjeru je to tocka C ).
  Od svih takvih duzina spojenih s gornjom ili donjom stanicom zanimaju nas
  samo dvije najduze ( u primjeru su to tocke C i D ).

  3.) Ako zelimo tocku I spojiti s gornjom ili donjom stranicom kvadrata, mogu
  nam smetati linije koje su nastale spajanjem neke tocke s desnom stranicom
  kvadrata ( u primjeru su to tocke E, G i H ). Od svih tocaka koje smo spojili
  desno zanimaju nas samo najvisa i najniza ( tocke H i G ).

  +-------------------------+
  |  |   |                  |
  |  A   |        H---------|
  |      |                  |
  |      |E-----------------|
  |---B  |                  |
  |      D                  |
  |                         |
  |                         |
  |                   I     |
  |                         |
  |                         |
  |----------F           J  |
  |    C                    |
  |    |        G-----------|
  |    |                    |
  +-------------------------+
                      ^
                      |

  Tih pet podatka ( tocka koju promatramo, duljina najduljih linija spojenih
  prema gore i dolje, te visine najvise i najnize linije spojene prem desno )
  definiraju sva moguca stanja koja mogu nastati kad spajamo tocke redom slijeva
  na desno.
  Buduci da veze izmedju tih stanja tvore usmjereni aciklicki graf, optimalno
  spajanje mozemo racunati metodom dinamickog programiranja ili tehnikom
  memoizacije rekurzije ( ovdje implementirano ).
}

Var
  Cnt : longint;
  Hsh : Array[1..32,1..32] of longint;
  Memo : Array[0..32*32 div 2 * 32*32 div 2 * 100] of integer;
  MinX, MaxX, MinY, MaxY : Array[0..32] of integer;
  X, Y, Sorted : Array[1..100] of integer;
  A, N : integer;
  Rjesenje : Array[1..100] of string;

Procedure Init;
Var
  i, j : integer;
Begin
  Cnt := 0;
  For i := 1 to 32 do
    For j := i to 32 do
    Begin
      Hsh[i][j] := Cnt;
      Hsh[j][i] := Cnt;
      Inc( Cnt );
    End;
  For i := 1 to 32 do
  Begin
    MinX[i] := 32; MaxX[i] := 0;
    MinY[i] := 32; MaxY[i] := 0;
  End;
End;

Procedure GetData;
Var
  i, j, t : integer;
Begin
  Readln( A );
  Readln( N );
  For i := 1 to N do
  Begin
    Readln( X[i], Y[i] );
    Sorted[i] := i;
    If X[i] < MinX[Y[i]] Then MinX[Y[i]] := X[i];
    If X[i] > MaxX[Y[i]] Then MaxX[Y[i]] := X[i];
    If Y[i] < MinY[X[i]] Then MinY[X[i]] := Y[i];
    If Y[i] > MaxY[X[i]] Then MaxY[X[i]] := Y[i];
  End;
  For i := 1 to N do
    For j := i+1 to N do
      If X[Sorted[i]] > X[Sorted[j]] Then
        Begin t := Sorted[i]; Sorted[i] := Sorted[j]; Sorted[j] := t; End;
End;

Function Hash( i, g, d, y1, y2 : longint ) : longint;
Begin Hash := (i-1)*Cnt*Cnt + Hsh[g][d]*Cnt + Hsh[y1][y2]; End;

Function Min2( a, b : integer ) : integer;
Begin If a < b Then Min2 := a else Min2 := b; End;

Function Max2( a, b : integer ) : integer;
Begin If a > b Then Max2 := a else Max2 := b; End;

Function Rec( i, g, d, y1, y2, reconstruct : integer ) : integer;
Var
  H : longint;
  xx, yy, t, How : integer;
Begin
  If i > N Then Begin Rec := 0; Exit; End;
  If g < d Then g := d;

  H := Hash( i, g, d, y1, y2 );

  If (Reconstruct = 0) and (Memo[H] > 0) Then Begin Rec := Memo[H]; Exit; End;

  Memo[H] := 10000;

  xx := X[Sorted[i]]; yy := Y[Sorted[i]];

  If (MinX[yy] = xx) and (yy > d) and (yy < g) Then
  Begin
    t := Rec( i+1, g, d, y1, y2, 0 ) + xx;
    If t < Memo[H] Then How := 1;
    If t < Memo[H] Then Memo[H] := t;
  End;
  If (MinY[xx] = yy) and (yy < y1) Then
  Begin
    t := Rec( i+1, g, Max2( d, yy ), y1, y2, 0 ) + yy;
    If t < Memo[H] Then How := 2;
    If t < Memo[H] Then Memo[H] := t;
  End;
  If (MaxY[xx] = yy) and (yy > y2) Then
  Begin
    t := Rec( i+1, Min2( g, yy ), d, y1, y2, 0 ) + A-yy;
    If t < Memo[H] Then How := 3;
    If t < Memo[H] Then Memo[H] := t;
  End;
  If (MaxX[yy] = xx) Then
  Begin
    t := Rec( i+1, g, d, Min2( y1, yy ), Max2( y2, yy ), 0 ) + A-xx;
    If t < Memo[H] Then How := 4;
    If t < Memo[H] Then Memo[H] := t;
  End;

  If Reconstruct = 1 Then
  Begin
    If How = 1 Then Rjesenje[Sorted[i]] := 'LIJEVO';
    If How = 2 Then Rjesenje[Sorted[i]] := 'DOLJE';
    If How = 3 Then Rjesenje[Sorted[i]] := 'GORE';
    If How = 4 Then Rjesenje[Sorted[i]] := 'DESNO';

    If How = 1 Then Rec( i+1, g, d, y1, y2, 1 );
    If How = 2 Then Rec( i+1, g, Max2( d, yy ), y1, y2, 1 );
    If How = 3 Then Rec( i+1, Min2( g, yy ), d, y1, y2, 1 );
    If How = 4 Then Rec( i+1, g, d, Min2( y1, yy ), Max2( y2, yy ), 1 );
  End;

  Rec := Memo[H];
End;

Var i : integer;
Begin
  Init;
  GetData;
  Writeln( Rec( 1, A, 0, A, 0, 1 ) );
  Rec( 1, A, 0, A, 0, 1 );
  For i := 1 to N do Writeln( Rjesenje[i] );
End.
