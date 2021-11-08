--- Tema laborator 9 ---

-- Exercitiul 1 --
/*S? se listeze informatii despre angajatii care au lucrat în toate proiectele demarate în primele 6 luni
ale anului 2006. Implementa?i toate variantele.*/

-- varianta 3 cu minus --
SELECT employee_id     --din toti angajatii care lucreaza la cel putin un proiect ii scadem pe cei care
FROM works_on
MINUS
SELECT employee_id
FROM (SELECT employee_id, project_id                
      FROM (SELECT employee_id FROM works_on) emp1,             
           (SELECT project_id FROM projects WHERE EXTRACT(month FROM start_date) BETWEEN 1 AND 6) proj1
      MINUS           --din toate combinatiile de angajati care lucreaza la cel putin un proiect si proiectele care indeplinesc conditia
      SELECT employee_id, project_id  --se scad 
      FROM works_on);
      
-- varianta 4 A include B --
SELECT DISTINCT a.employee_id, e.first_name, e.last_name, e.hire_date
FROM works_on a
JOIN employees e ON(e.employee_id = a.employee_id)
WHERE NOT EXISTS ((SELECT project_id
                FROM projects
                WHERE EXTRACT(month FROM start_date) BETWEEN 1 AND 6)
                MINUS
                (SELECT p.project_id
                FROM projects p, works_on w
                WHERE p.project_id = w.project_id AND a.employee_id = w.employee_id));

-- Exercitiul 2 --
/*S? se listeze informa?ii despre proiectele la care au participat to?i angaja?ii care au de?inut alte 2
posturi în firm?.*/
-- varianta 2 cu count --
SELECT w.project_id, p.project_name, p.budget, p.start_date, p.deadline, p.delivery_date, p.project_manager
FROM works_on w
JOIN projects p ON (p.project_id = w.project_id)
WHERE w.employee_id IN (SELECT employee_id
FROM job_history jh
GROUP BY employee_id
HAVING COUNT(*) >= 2)
GROUP BY w.project_id, p.project_name, p.budget, p.start_date, p.deadline, p.delivery_date, p.project_manager
HAVING COUNT(w.employee_id) = (SELECT COUNT(COUNT(*)) --numaram cati angajati au detinut alte 2 posturi in firma
FROM job_history jh2
GROUP BY employee_id
HAVING COUNT(job_id) >= 2);

-- varianta 3 cu minus --
SELECT project_id, project_name
FROM projects
MINUS
SELECT project_id, project_name
FROM (SELECT project_id, project_name, employee_id FROM
                                                (SELECT project_id, project_name FROM projects),
                                                (SELECT employee_id
                                                FROM job_history jh
                                                GROUP BY employee_id
                                                HAVING COUNT(*) >= 2) 
MINUS 
SELECT w.project_id, p.project_name, w.employee_id
FROM works_on w
JOIN projects p ON(w.project_id = p.project_id));

-- varianta 4 --
SELECT DISTINCT p.*                          --nu exista angajat care sa nu fi lucrat la proiect si sa indeplineasca conditiile
FROM works_on t1                             --la proiect nu a lucrat niciun angajat care sa nu indeplineasca conditiile
JOIN projects p ON(p.project_id = t1.project_id)
WHERE NOT EXISTS (SELECT employee_id         --selectam toti angajatii care au avut 2 joburi minim
                  FROM job_history t2
                  GROUP BY employee_id
                  HAVING COUNT(*) >= 2
                  MINUS                      --selectam toti angajatii care au lucrat la un proiect
                  SELECT employee_id
                  FROM works_on t3
                  WHERE t1.project_id = t3.project_id);
                  
                  
-- Exercitiul 12 --
/*a) S? se ob?in? numele angaja?ilor care au lucrat cel pu?in pe acelea?i proiecte ca ?i angajatul
având codul 200.*/
SELECT DISTINCT e.first_name, e.last_name, e.employee_id
FROM works_on w
JOIN employees e ON(e.employee_id = w.employee_id)
WHERE NOT EXISTS (SELECT project_id          --toate proiectele la care lucreaza angajatul 200 -
                  FROM works_on
                  WHERE employee_id = 200
                  MINUS
                  SELECT project_id          --toate proiectele la care lucreaza angajatul nostru
                  FROM works_on
                  WHERE employee_id = e.employee_id)
AND e.employee_id <> 200;
                  
/*b) S? se ob?in? numele angaja?ilor care au lucrat cel mult pe acelea?i proiecte ca ?i angajatul având
codul 200.*/
select * from works_on order by 2;
SELECT DISTINCT e.first_name, e.last_name, e.employee_id
FROM works_on w
JOIN employees e ON(e.employee_id = w.employee_id)
WHERE NOT EXISTS (SELECT project_id          --toate proiectele la care lucreaza angajatul nostru
                  FROM works_on
                  WHERE employee_id = e.employee_id
                  MINUS
                  SELECT project_id          --toate proiectele la care lucreaza angajatul 200 -
                  FROM works_on
                  WHERE employee_id = 200)
AND e.employee_id <> 200;
-- Exercitiul 13 --
/*S? se ob?in? angaja?ii care au lucrat pe acelea?i proiecte ca ?i angajatul având codul 200.
*/
SELECT DISTINCT e.first_name, e.last_name, e.employee_id
FROM works_on w
JOIN employees e ON(e.employee_id = w.employee_id)
WHERE NOT EXISTS (SELECT project_id          --toate proiectele la care lucreaza angajatul nostru
                  FROM works_on
                  WHERE employee_id = e.employee_id
                  MINUS
                  SELECT project_id          --toate proiectele la care lucreaza angajatul 200 -
                  FROM works_on
                  WHERE employee_id = 200)
AND NOT EXISTS (SELECT project_id          --toate proiectele la care lucreaza angajatul 200 -
                  FROM works_on
                  WHERE employee_id = 200
                  MINUS
                  SELECT project_id          --toate proiectele la care lucreaza angajatul nostru
                  FROM works_on
                  WHERE employee_id = e.employee_id)
AND e.employee_id <> 200;

-- Exercitiul 14 --
/*Modelul HR con?ine un tabel numit JOB_GRADES, care con?ine grilele de salarizare ale companiei.
a) Afi?a?i structura ?i con?inutul acestui tabel.*/
SELECT * FROM job_grades;
DESC job_grades;
/*b) Pentru fiecare angajat, afi?a?i numele, prenumele, salariul ?i grila de salarizare corespunz?toare.
Ce opera?ie are loc între tabelele din interogare?*/
SELECT last_name, first_name, salary, grade_level
FROM employees, job_grades
WHERE salary > lowest_sal AND salary < highest_sal;
-- am facut produsul cartezian intre cele 2 tabele
