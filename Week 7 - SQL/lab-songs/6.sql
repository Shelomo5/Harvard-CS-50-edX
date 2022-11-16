-- In 6.sql, write a SQL query that lists the names of songs that are by Post Malone.
-- Your query should output a table with a single column for the name of each song.
-- You should not make any assumptions about what Post Malone’s artist_id is.
--There is no artist column in songs table but there artist id in songs table which corresponds to some id in artists table
--In parentheses is what you call a nested query where we select the id from artists table for post malone then match then
-- set it equal to the names from songs which have corresponding id


SELECT name FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = "Post Malone");