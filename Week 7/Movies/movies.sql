-- 1
SELECT title
FROM movies
WHERE year = 2008;

-- 2
SELECT birth
FROM people
WHERE name = 'Emma Stone';

-- 3
SELECT title
FROM movies
WHERE year >= 2018
GROUP BY title;

-- 4
SELECT COUNT(rating)
FROM ratings
WHERE rating = 10.0;

-- 5
SELECT title, year
FROM movies
WHERE title LIKE 'Harry Potter%'
ORDER BY year ASC;

-- 6
SELECT AVG(rating)
FROM ratings
JOIN movies ON ratings.movie_id = movies.id
WHERE movies.year = 2012;

-- 7
SELECT movies.title, ratings.rating
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE movies.year = 2010
ORDER BY ratings.rating DESC, movies.title;

-- 8
SELECT name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.title = 'Toy Story';

-- 9
SELECT DISTINCT name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.year = 2004
ORDER BY people.birth;

-- 10
SELECT DISTINCT name
FROM people
JOIN directors ON people.id = directors.person_id
JOIN movies ON directors.movie_id = movies.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.rating >= 9.0;

-- 11
SELECT title
FROM movies
JOIN stars on movies.id = stars.movie_id
JOIN people on stars.person_id = people.id
JOIN ratings on movies.id = ratings.movie_id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;

-- 12
SELECT m.title
FROM movies m
JOIN stars s1 ON m.id = s1.movie_id
JOIN people p1 ON s1.person_id = p1.id AND p1.name = 'Bradley Cooper'
JOIN stars s2 ON m.id = s2.movie_id
JOIN people p2 ON s2.person_id = p2.id AND p2.name = 'Jennifer Lawrence';

-- 13
SELECT DISTINCT p1.name
FROM people p1
JOIN stars s1 ON p1.id = s1.person_id AND p1.name != 'Kevin Bacon'
JOIN movies m1 ON s1.movie_id = m1.id
JOIN stars s2 ON m1.id = s2.movie_id
JOIN people p2 ON s2.person_id = p2.id AND p2.name = 'Kevin Bacon';


