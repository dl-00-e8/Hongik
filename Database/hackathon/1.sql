-- (1) 인기도
SELECT a.name, COUNT(car.artist_name) as popularity
FROM Artists a, customer_artist_ref car
WHERE a.name = car.artist_name
GROUP By a.name
ORDER BY popularity desc;