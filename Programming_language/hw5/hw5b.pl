n_queen(N, Positions):-
    write("B911139"), nl,
    range(1, N, Range),
    permutation(Range, Positions),
    safe_queens(Positions).

range(Min, Min, [Min]).

range(Min, Max, [Min | Rest]):-
    Min < Max,
    Next is Min + 1,
    range(Next, Max, Rest).

permutation([], []).

permutation(List, [Element | Rest]):-
    select(Element, List, Remaining),
    permutation(Remaining, Rest).

safe_queens([]).

safe_queens([Q | Qs]):-
    safe_queens(Qs, Q, 1),
    safe_queens(Qs).

safe_queens([], _, _).

safe_queens([Q | Qs], Q0, D0):-
    Q0 =\= Q,
    abs(Q0 - Q) =\= D0,
    D1 is D0 + 1,
    safe_queens(Qs, Q0, D1).
