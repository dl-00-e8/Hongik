sorting(List, X):-
    write("B911139"), nl, write("X = "), write(List), nl,
    sorting(List, [], X).

sorting([], Sorted, Sorted).

sorting([A|B], SortedTail, X):-
    write("X = "), write(SortedTail), write(A), write(B), nl,
    insert(A, SortedTail, NewSortedTail),
    sorting(B, NewSortedTail, X).

insert(A, [B|C], [B|D]):-
    A @> B,
    !,
    insert(A, C, D).

insert(A, C, [A|C]).
