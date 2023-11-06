select distinct name from people as p join stars as s join movies as m where p.id = s.person_id and s.movie_id = m.id and m.year = 2004 order by birth;