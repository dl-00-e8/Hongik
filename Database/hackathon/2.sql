-- (2)
SELECT a.name, AVG(w.price) AS average_price
FROM Artists a, Works w
WHERE a.name = w.artist_name
GROUP BY a.name
ORDER BY average_price ASC;

--> Nested Query
SELECT a.name
FROM Artists a, Works w
WHERE a.name = w.artist_name
GROUP BY a.name
HAVING AVG(w.price) = (
	SELECT MIN(avg_price)
	FROM (
		SELECT AVG(price) as avg_price
		FROM Works
		GROUP BY artist_name
	) 
)