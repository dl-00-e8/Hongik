SELECT a.title, a.price
FROM Artwork a
WHERE a.price = (SELECT MAX(price)
								FROM Artwork
								WHERE title IN (SELECT ag.title
								FROM Belong ag
								GROUP BY ag.title
								HAVING COUNT(ag.gname) > 1))
	AND a.title IN (SELECT ag.title
								FROM Belong ag
								GROUP BY ag.title
								HAVING COUNT(ag.gname) > 1)