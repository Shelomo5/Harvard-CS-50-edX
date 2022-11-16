-- In 11.sql, write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Chadwick Boseman.


SELECT title FROM movies
JOIN stars on stars.movie_id = movies.id
JOIN people on people.id = stars.person_id
JOIN ratings on movies.id = ratings.movie_id
WHERE people.name = "Chadwick Boseman"
ORDER by rating DESC LIMIT 5;
