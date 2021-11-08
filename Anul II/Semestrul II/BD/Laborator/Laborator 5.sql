--- Laborator 5 ---

-- Exercitiul 1 --
SELECT department_name , job_title, ROUND(AVG(salary) , 2)
FROM departments
JOIN employees USING(department_id)
JOIN jobs USING(job_id)
GROUP BY ROLLUP(department_name , job_title);

--0 daca a participat la calculul lui avg
--b
SELECT department_name , GROUPING(department_name) , 
job_title, GROUPING(job_title) , 
ROUND(AVG(salary) , 2)
FROM departments
JOIN employees USING(department_id)
JOIN jobs USING(job_id)
GROUP BY ROLLUP(department_name , job_title);

--Exercitiul 2--
SELECT department_name , GROUPING(department_name) , 
job_title, GROUPING(job_title) , 
ROUND(AVG(salary) , 2)
FROM departments
JOIN employees USING(department_id)
JOIN jobs USING(job_id)
GROUP BY CUBE(department_name , job_title);
--nu exista joburi pe care sa nu lucreze angajati
--se face avg tinand cont de o coloana sau de alta sau de amandoua

-- b
SELECT department_name , job_title , 
ROUND(AVG(salary) , 2) ,      --ambele 0 => au participat amandoua --
DECODE(GROUPING(department_name) , 0 , DECODE(GROUPING(job_title) , 0 , 'Dept si job' , 1 , 'Dept') , 1 , DECODE(GROUPING(job_title) , 0 , 'Jobs' , '-')) "Participare la avg"
FROM departments
JOIN employees USING(department_id)
JOIN jobs USING(job_id)
GROUP BY CUBE(department_name , job_title);

-- Exercitiul 3 --
-- department name sau id, job si manager id
SELECT department_name , job_title , employees.manager_id , MAX(salary) , SUM(salary)
FROM departments
JOIN employees USING(department_id)
JOIN jobs USING(job_id)
GROUP BY GROUPING SETS((department_name , job_title) , (job_title , employees.manager_id) , ()); --si intreg tabelul

-- Exercitiul 4--
SELECT MAX(salary)
FROM employees
HAVING MAX(salary) > 15000;

-- Exercitiul 5 --
SELECT last_name , employee_id , salary
FROM employees e
WHERE salary > (SELECT AVG(salary)
                FROM employees
                WHERE e.employee_id <> employee_id AND department_id = e.department_id);
            
-- b --
SELECT employee_id , last_name , salary , department_name , 
(SELECT AVG(salary) FROM employees WHERE department_id = e.department_id) "Medie"
FROM employees e
JOIN departments d ON(d.department_id = e.department_id)
WHERE salary > (SELECT AVG(salary)
                FROM employees
                WHERE e.employee_id <> employee_id AND department_id = e.department_id);


--subcerere la from --
SELECT employee_id , last_name , salary , department_name , medie 
FROM employees e
JOIN (SELECT AVG(salary) medie , department_id FROM employees GROUP BY department_id) aux ON(aux.department_id = e.department_id)
JOIN departments d ON(d.department_id = e.department_id)
WHERE salary > medie;

-- Exercitiul 6 --
SELECT last_name , salary
FROM employees
WHERE salary > (SELECT AVG(salary) FROM employees GROUP BY department_id);
-- nu merge deoarece select intoarce mai multe randuri

--FOLOSIM ALL. ADICA SA FIE MAI MARE DECAT TOATE
SELECT last_name , salary
FROM employees
WHERE salary > ALL(SELECT AVG(salary) FROM employees GROUP BY department_id);

--varianta 2 folosind max--
SELECT last_name , salary
FROM employees
WHERE salary > (SELECT MAX(AVG(salary)) FROM employees GROUP BY department_id);

/*Exercitiul 7
Sa se afiseze numele si salariul celor mai prost platiti angajati din fiecare departament (se cer 3
solutii: subcerere sincronizata, subcerere nesincronizata si subcerere în clauza FROM).*/
-- v1 sincronizata - la where --
SELECT last_name , salary
FROM employees e
WHERE salary = (SELECT MIN(salary)
                FROM employees
                WHERE department_id = e.department_id); 
--am sincronizat cu exteriorul


-- v1 nesincronizata. tot la where
SELECT last_name , salary
FROM employees
WHERE (salary , department_id) IN (SELECT MIN(salary) , department_id
                FROM employees
                GROUP BY department_id); 
                
-- v3 subcerere la from
SELECT last_name , salary
FROM employees e
JOIN (SELECT MIN(salary) minim , department_id
                FROM employees
                GROUP BY department_id) aux ON(aux.department_id = e.department_id)
WHERE salary = minim;

-- Exercitiul 8 --
-- angajatii cei mai batrani din companie din fiecare departament
SELECT last_name
FROM employees e
WHERE hire_date = (SELECT MIN(hire_date) 
                    FROM employees
                    WHERE e.department_id = department_id);

-- Exercitiul 9 --
SELECT last_name
FROM employees e
WHERE EXISTS (SELECT 1 from employees  -- 1 adica e true. macar o linie
                WHERE department_id = e.department_id --colegi
                AND salary = (SELECT MAX(salary)      --pentru care salariul este egal cu maximul din op 30
                                FROM employees 
                                WHERE department_id = 30));
-- Exercitiul 10 --
--teste
SELECT last_name , salary
FROM employees
ORDER BY salary DESC;

--nu merge --
SELECT last_name , salary
FROM employees
WHERE ROWNUM <= 5 --nu ii afiseaza pe primii cei mai mici cu salariul 
ORDER BY salary DESC;
--vrem mai intai sa ordoneze si dupa sa taie primele 5

--TOP N CEI MAI BINE PLATITI ANGAJATI. 2 SUBCERERI
SELECT *
FROM (SELECT last_name , salary
FROM employees
ORDER BY salary DESC)
WHERE ROWNUM <= 3
ORDER BY salary;

-- Exercitiul 11 --
SELECT employee_id , last_name , first_name
FROM employees e
WHERE (SELECT COUNT(manager_id)
FROM employees
WHERE manager_id = e.employee_id
GROUP BY manager_id) >= 2;

-- Exercitiul 12 --
--daca exista macar un departament cu locatia respectiva
SELECT city
FROM locations l
WHERE EXISTS (SELECT 'C' FROM departments WHERE l.location_id = location_id);

--cu operatorul in--
--tema:cum s ar face folosind jjoin uri sau minus
--trb sa eliminam fin full join ceva
SELECT city
FROM locations
WHERE location_id IN (SELECT location_id FROM departments);


-- Exercitiul 13 --
--departamente in care nu am angajati
--tema cu join uri
SELECT department_id , department_name
FROM departments d
WHERE NOT EXISTS(SELECT -1 
FROM employees
WHERE d.department_id = department_id);

-- Exercitiul 14 --
SELECT employee_id , last_name , hire_date , salary , manager_id
FROM employees
WHERE LEVEL = 2 --adica nodurile copii
START WITH employee_id = (SELECT employee_id
                            FROM employees
                            WHERE UPPER(last_name) LIKE 'DE HAAN')
CONNECT BY PRIOR employee_id = manager_id;  --sa afisam ierarhia 

--ierarhia
SELECT LEVEL , employee_id , last_name , hire_date , salary , manager_id
FROM employees
START WITH employee_id = (SELECT employee_id
                            FROM employees
                            WHERE UPPER(last_name) LIKE 'DE HAAN')
CONNECT BY PRIOR employee_id = manager_id;  --sa afisam ierarhia 

-- Exercitiul 15 --
SELECT LEVEL , employee_id , last_name , hire_date , salary , manager_id
FROM employees
START WITH employee_id = 114
CONNECT BY PRIOR employee_id = manager_id;  --sa afisam ierarhia 


--test
SELECT LEVEL , employee_id , last_name , hire_date , salary , manager_id
FROM employees
--nu va considera nicio radacina
--le va lua pe toate la rand
CONNECT BY PRIOR employee_id = manager_id;  --sa afisam ierarhia 

--test
--tema: cum sa afisam numele cu padding ca sa arate arborescent
SELECT LEVEL , employee_id , last_name , hire_date , salary , manager_id
FROM employees
START WITH employee_id = 100
CONNECT BY PRIOR employee_id = manager_id;  --sa afisam ierarhia 

--tema urmatoarele pana la clauza with

-- Exercitiul 16 --
/* Scrieti o cerere ierarhica pentru a afisa codul salariatului, codul managerului si numele salariatului,
pentru angajatii care sunt cu 2 niveluri sub De Haan.
Afisati, de asemenea, nivelul angajatului în ierarhie. */

SELECT LEVEL, employee_id, manager_id, last_name
FROM employees
WHERE LEVEL = 3
START WITH employee_id = (SELECT employee_id 
                          FROM employees 
                          WHERE UPPER(last_name) LIKE 'DE HAAN')
CONNECT BY PRIOR  employee_id = manager_id;

--test
--sunt 2 king. vrem sa aratam ca ii ia pe amandoi ca radacina
SELECT LEVEL, employee_id, manager_id, last_name
FROM employees
START WITH UPPER(last_name) LIKE 'KING'
CONNECT BY PRIOR  employee_id = manager_id;


-- Exercitiul 17 --
/* Pentru fiecare linie din tabelul EMPLOYEES, se va afisa o structura arborescenta in care va ap?rea
angajatul, managerul s?u, managerul managerului etc. Coloanele afi?ate vor fi: codul angajatului,
codul managerului, nivelul în ierarhie (LEVEL) si numele angajatului.*/

SELECT LEVEL, employee_id, manager_id, LPAD(last_name , 3 * LEVEL)
FROM employees
CONNECT BY PRIOR  employee_id = manager_id;

-- Exercitiul 18 --
/* S? se afi?eze ierarhia de sub angajatul având salariul maxim, re?inând numai angaja?ii al c?ror
salariu este mai mare de 5000. Se vor afi?a codul, numele, salariul, nivelul din ierarhie ?i codul
managerului.*/
--aici subalternii pot avea si sub 15000
SELECT LEVEL, employee_id, last_name, salary, manager_id
FROM employees
START WITH employee_id = (SELECT employee_id 
                            FROM employees
                            WHERE salary = (SELECT MAX(salary) 
                                            FROM employees))
CONNECT BY PRIOR salary > 15000 AND PRIOR employee_id = manager_id;

--test
SELECT employee_id, last_name, salary, manager_id
FROM employees
WHERE salary > 15000 
START WITH employee_id = (SELECT employee_id 
                            FROM employees
                            WHERE salary = (SELECT MAX(salary) 
                                            FROM employees))
CONNECT BY PRIOR employee_id = manager_id;


-- Exercitiul 19--
/*
WITH
aux AS (SELECT...)
aux2 AS (SELECT...)
...
auxn AS (SELECT...)
SELECT ...
FROM aux CROSS JOIN aux2 CROSS JOIN auxn
WHERE ...
...
*/

/*Utilizând clauza WITH, s? se scrie o cerere care afi?eaz? numele departamentelor ?i valoarea
total? a salariilor din cadrul acestora. Se vor considera departamentele a c?ror valoare total? a
salariilor este mai mare decât media valorilor totale ale salariilor tuturor angajatilor.*/
WITH
total AS (SELECT department_id , SUM(salary) as sum
          FROM employees
          GROUP BY department_id)
SELECT department_name, sum
FROM departments
JOIN total USING(department_id)
WHERE sum > (SELECT AVG(sum)
             FROM total);

--Exercitiul 20--
/*S? se afi?eze ierarhic codul, prenumele ?i numele (pe aceea?i coloan?), codul job-ului ?i data
angaj?rii, pornind de la subordona?ii direc?i ai lui Steven King care au cea mai mare vechime.
Rezultatul nu va con?ine angaja?ii în anul 1970.*/

WITH
king as (SELECT employee_id kod
         FROM employees
         WHERE UPPER(last_name) LIKE 'KING' AND UPPER(first_name) LIKE 'STEVEN')
SELECT employees.employee_id, first_name || ' ' || last_name, job_id, hire_date
FROM employees CROSS JOIN king
WHERE LEVEL = 2/* AND hire_date = (SELECT min(hire_date) from employees)*/
AND EXTRACT(year FROM hire_date) <> 1970
START WITH employees.employee_id = kod
CONNECT BY PRIOR employees.employee_id = manager_id;

--Exercitiul 21--
/*S? se detemine primii 10 cei mai bine pl?ti?i angaja?i.*/
--acum e order by si dupa where
SELECT *
FROM (SELECT last_name, salary
      FROM employees
      ORDER BY salary DESC)
WHERE ROWNUM <= 10;

--Exercitiul 22--
/*S? se determine cele mai prost pl?tite 3 job-uri, din punct de vedere al mediei salariilor.*/
SELECT *
FROM (SELECT job_title
FROM jobs
ORDER BY (min_salary + max_salary)/2)
WHERE ROWNUM <=3;

--Exercitiul 23--
/*S? se afi?eze informa?ii despre departamente, în formatul urm?tor: „Departamentul
<department_name> este condus de {<manager_id> | nimeni} ?i {are num?rul de salaria?i
<n> | nu are salariati}“.*/
--tema verificare daca merge cu decode
SELECT 'Departamentul ' || department_name || ' este condus de ' || NVL(TO_CHAR(manager_id) , 'nimeni') || ' si ' || CASE
    WHEN nr > 0 THEN 'are numarul de salariati  ' || nr
    ELSE 'nu are salariati' END as "Informatii"
FROM departments d LEFT JOIN(SELECT department_id, COUNT(employee_id) nr
FROM employees
GROUP BY department_id) aux 
ON(d.department_id = aux.department_id);

--Exercitiul 24--
/*S? se afi?eze numele, prenumele angaja?ilor ?i lungimea numelui pentru înregistr?rile în care
aceasta este diferit? de lungimea prenumelui. (nullif)*/
SELECT last_name , first_name , length(last_name)
FROM employees
WHERE NULLIF(length(last_name) , length(first_name)) IS NOT NULL;--pentru ca vrem sa fie diferite

--Exercitiul 25--
/*S? se afi?eze numele, data angaj?rii, salariul ?i o coloan? reprezentând salariul dup? ce se
aplic? o m?rire, astfel: pentru salaria?ii angaja?i în 1989 cre?terea este de 20%, pentru cei angaja?i
în 1990 cre?terea este de 15%, iar salariul celor angaja?i în anul 1991 cre?te cu 10%.
Pentru salaria?ii angaja?i în al?i ani valoarea nu se modific?.*/
SELECT last_name , hire_date , salary , DECODE(TO_CHAR(hire_date , 'YYYY') , 1989 , salary * 1.2 , 1990 , salary * 1.15 , 1991 , salary * 1.1 , salary) as "Marire"
FROM employees;
--tema cu case--

--Exercitiul 26--
/*S? se afi?eze:
- suma salariilor, pentru job-urile care incep cu litera S;
- media generala a salariilor, pentru job-ul avand salariul maxim;
- salariul minim, pentru fiecare din celelalte job-uri.*/
SELECT (SELECT SUM(salary)
        FROM employees
        WHERE lower(job_id) LIKE 's%') "Suma", 
       (SELECT AVG(salary) 
        FROM employees
        WHERE (job_id , salary) IN (SELECT job_id , MAX(salary)
                        FROM employees
                        GROUP BY job_id)) "Medie"
--  , SELECT MIN(salary) FROM employees WHERE lower(job_id) NOT LIKE 's%' AND (job_id , salary) <> (SELECT...) as "Minim"
FROM dual;
-- cum se face cu case
/*
select case
when job_id like s then sum salary
when job id...(sincronizat) then avg salary
*/
        