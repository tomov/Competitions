
{
HIO 2004
Zadatak ROBOT
}

{
   Ovaj zadatak rjesavamo DFS-om. DFS je nacin prolaska kroz
   graf u dubinu. To znaci da ako ima netko s kime smo spojeni
   tad cemo ici na njega, a tek poslije na druge. To se
   implementira rekurzivno i slozenost mu je O(N).
   Imamo polje[2000, 2000] koje nam govori da li smo na nekom
   polju vec bili. Dakle mi sami pamtimo na kojem smo sad.
   Iz trenutnog polja se DFS-om sirimo na susjedna polja ako
   tamo jos nismo bili i povecamo rjesenje za jedan.
}

Uses robotlib;

var polje: array[1..2000, 1..2000] of boolean;
    r, s: integer;
    dr, ds, obrnuto: array[0..4] of integer;

function dfs( s1: integer ): longint;
var rjes: integer;
begin
    rjes := 0;
    if ( polje[ r+dr[s1], s+ds[s1] ] = false ) then begin
       polje[ r+dr[s1], s+dr[s1] ] := true;

       if ((s1 = 0) or ( Hodaj(s1) )) then begin

          r := r + dr[s1]; s := s + ds[s1];
          rjes := 1 + dfs(1) + dfs(2) + dfs(3) + dfs(4);
          r := r - dr[s1]; s := s - ds[s1];

          if (s1 > 0) then Hodaj( obrnuto[s1] );

       end;

    end;
    dfs := rjes;
end;

begin
  dr[0] := 0; dr[1] := -1; dr[2] := 0; dr[3] := 1; dr[4] := 0;
  ds[0] := 0; ds[1] := 0; ds[2] := 1; ds[3] := 0; ds[4] := -1;
  obrnuto[0] := 0; obrnuto[0] := 3; obrnuto[0] := 4; obrnuto[0] := 1; obrnuto[0] := 2;
  Init();
  Rjesenje( dfs( 0 ) );
end.
