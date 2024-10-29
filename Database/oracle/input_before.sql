SELECT B.name, COUNT(*)
FROM Boats B, Reserve R
WHERE B.bid = R.bid AND B.color = 'red'
GROUP BY B.name