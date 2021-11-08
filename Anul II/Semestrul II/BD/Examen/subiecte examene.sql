/*Pentru fiecare job s? se afi?eze câ?i candida?i au punctajul peste medie, egal cu media ?i sub medie.*/
SELECT job_id, (SELECT COUNT(cod_candidat)
FROM aplica a
WHERE punctaj_cv >  (SELECT AVG(punctaj_cv) FROM aplica WHERE a.cod_job = cod_job)
AND cod_job = j.job_id) "Peste",
(SELECT COUNT(cod_candidat)
FROM aplica a
WHERE punctaj_cv = (SELECT AVG(punctaj_cv) FROM aplica WHERE a.cod_job = cod_job)
AND cod_job = j.job_id) "Egal",
(SELECT COUNT(cod_candidat)
FROM aplica a
WHERE punctaj_cv <  (SELECT AVG(punctaj_cv) FROM aplica WHERE a.cod_job = cod_job)
AND cod_job = j.job_id) "Sub"
FROM job j;
 
 
/*S? se ob?in? lista joburilor (data_aplicare si data interviu in formatul zi/luna/an) la care a aplicat cel mai tân?r candidat.*/
SELECT * FROM aplica;
SELECT * FROM candidat;
SELECT cod_job, TO_CHAR(data_aplicare, 'DD/MM/YYYY') data_aplicare, TO_CHAR(data_interviu, 'DD/MM/YYYY') data_interviu
FROM interviu
JOIN aplica USING(cod_job, cod_candidat)
WHERE cod_candidat = (SELECT id_candidat
FROM candidat
WHERE data_nastere = (SELECT MAX(data_nastere) FROM candidat));
 
/*S? se adauge în tabelul job coloana numar_candidati . Sa se actualizeze datele memorate in numar_candidati astfel incat sa indice numarul de candidati care au aplicat la un anumit job.*/
ALTER TABLE angajati_eco
ADD nr_ang number(4);
SELECT COUNT(cod_candidat)
FROM aplica
GROUP BY cod_job;
SELECT cod_job, AVG(punctaj_cv) FROM aplica group by cod_job;

/*S? se afiseze denumirile joburilor, numele candida?ilor programa?i la interviu ?i data la care au fost programa?i. Se vor afi?a ?i joburile pentru care nu s -a programat niciun interviu*/
SELECT denumire, nume, data_interviu
FROM interviu i
LEFT JOIN candidat c ON (i.cod_candidat = c.id_candidat)
RIGHT JOIN job j ON (i.cod_job = j.job_id);

SELECT * FROM aplica;

/*S? se afi?eze denumirile joburilor la care au aplicat cel pu?in 3 candida?i. Pentru aceste joburi se va afi?a num?rul de candida?i care au punctaj mai mare de 70.*/

SELECT job_id, denumire, nr_candidati
FROM job j
JOIN (SELECT cod_job
      FROM aplica
      GROUP BY cod_job
      HAVING COUNT(cod_candidat) >= 3) aux1 ON(j.job_id = aux1.cod_job)
JOIN (SELECT COUNT(cod_candidat) nr_candidati, cod_job 
      FROM aplica 
      WHERE punctaj_cv > 70 
      GROUP BY cod_job)aux2 ON(j.job_id = aux2.cod_job);


/*numele candidatilor care au aplicat la anunturi publicate in mai*/
SELECT DISTINCT id_candidat, nume
FROM candidat c
JOIN aplica a ON (a.cod_candidat = c.id_candidat)
WHERE EXTRACT(month FROM data_aplicare) = 5
ORDER BY 1;

SELECT * FROM candidat;

SELECT cod_candidat, nume, prenume
FROM candidat c
JOIN aplica a ON (a.cod_candidat = c.id_candidat)
WHERE NOT EXISTS (SELECT 1 
FROM aplica a1
WHERE a1.cod_candidat = a.cod_candidat
AND NOT EXISTS (SELECT 1
FROM aplica a3 
JOIN candidat c3 ON (a3.cod_candidat = c3.id_candidat)
WHERE a1.cod_job = a3.cod_job and UPPER(nume) = 'ALEXANDRU' AND UPPER(prenume) = 'ANCA'));

SELECT cod_candidat, MAX(punctaj_cv), COUNT(cod_job)
FROM aplica
GROUP BY cod_candidat
HAVING COUNT(cod_job) > 2;

DELETE FROM aplica
WHERE punctaj_cv = (SELECT MIN(punctaj_cv) FROM aplica);




