-- Lab 5 recap --

/*5a) S? se afi?eze informa?ii despre angaja?ii al c?ror salariu dep??e?te valoarea medie a
salariilor colegilor s?i de departament.
b) Analog cu cererea precedent?, afi?ându-se ?i numele departamentului ?i media salariilor
acestuia ?i num?rul de angaja?i (2 solutii: subcerere necorelat? în clauza FROM, subcerere
corelat? în clauza SELECT).*/
SELECT *
FROM employees e1
WHERE salary > (SELECT AVG(salary)
FROM employees e2
WHERE e1.employee_id <> e2.employee_id and e1.department_id = e2.department_id);

--b
SELECT department_name, e.*, (SELECT ROUND(AVG(salary),2) FROM employees WHERE d.department_id = department_id) "Medie"
FROM departments d
JOIN employees e ON(e.department_id = d.department_id)
WHERE salary > (SELECT AVG(salary)
FROM employees e2
WHERE e.employee_id <> e2.employee_id and e.department_id = e2.department_id);

--b
SELECT department_name, e.*, med
FROM employees e
JOIN departments d ON(e.department_id = d.department_id)
JOIN (SELECT ROUND(AVG(salary),2) med, department_id FROM employees GROUP BY department_id) aux ON (aux.department_id = d.department_id) 
WHERE salary > (SELECT AVG(salary)
FROM employees e2
WHERE e.employee_id <> e2.employee_id and e.department_id = e2.department_id);


/*S? se afi?eze numele ?i salariul angaja?ilor al c?ror salariu este mai mare decât salariile medii
din toate departamentele. Se cer 2 variante de rezolvare: cu operatorul ALL sau cu func?ia MAX.*/
SELECT last_name, salary
FROM employees
WHERE salary > (SELECT MAX(AVG(salary)) 
                FROM employees
                GROUP BY department_id);

SELECT last_name, salary
FROM employees
WHERE salary > ALL(SELECT AVG(salary)
                FROM employees
                GROUP BY department_id);
                
/*Sa se afiseze numele si salariul celor mai prost platiti angajati din fiecare departament (se cer 3
solutii: subcerere sincronizata, subcerere nesincronizata si subcerere în clauza FROM).*/
SELECT last_name, salary
FROM employees e1
WHERE salary = (SELECT MIN(salary)
                FROM employees
                WHERE department_id = e1.department_id);
                
SELECT last_name, salary
FROM employees e1
JOIN (SELECT MIN(salary) salariu, department_id FROM employees GROUP BY department_id) aux ON(e1.department_id = aux.department_id)
WHERE e1.salary = aux.salariu;

SELECT last_name, salary
FROM employees
WHERE (salary, department_id) IN (SELECT MIN(salary), department_id FROM employees GROUP BY department_id);


/*8. Pentru fiecare departament, s? se obtina numele salariatului avand cea mai mare vechime din
departament. S? se ordoneze rezultatul dup? numele departamentului.*/
SELECT last_name, hire_date, department_id
FROM employees
WHERE (hire_date, department_id) IN (SELECT MIN(hire_date), department_id FROM employees GROUP BY department_id)
ORDER BY 3;

--var 2 subcerere sincronizata
SELECT last_name, hire_date, department_id
FROM employees e
WHERE hire_date = (SELECT MIN(hire_date) FROM employees WHERE e.department_id = department_id);

-- var 3 subcerere in from
SELECT last_name, data_min, e.department_id
FROM employees e
JOIN (SELECT MIN(hire_date) data_min, department_id FROM employees GROUP BY department_id) aux ON (aux.department_id = e.department_id)
WHERE e.hire_date = data_min;

/*9. Sa se obtina numele salariatilor care lucreaza intr-un departament in care exista cel putin un
angajat cu salariul egal cu salariul maxim din departamentul 30 (operatorul exists).*/
SELECT last_name, department_id
FROM employees e
WHERE EXISTS (SELECT 1 FROM employees
            WHERE salary = (SELECT MAX(salary)
                            FROM employees
                            WHERE department_id = 30) AND department_id = e.department_id);
                            
                            
/*Sa se obtina numele primilor 3 angajati avand salariul maxim. Rezultatul se va afi?a în ordine
cresc?toare a salariilor.*/
SELECT *
FROM (SELECT last_name, salary
      FROM employees
      ORDER BY 2 DESC)
WHERE ROWNUM <=3;

/*11.S? se afi?eze codul, numele ?i prenumele angaja?ilor care au cel pu?in doi subalterni.*/
SELECT employee_id, first_name, last_name
FROM employees e
WHERE (SELECT COUNT(manager_id)
FROM employees
WHERE manager_id = e.employee_id) >= 2;

/*12. S? se determine loca?iile în care se afl? cel pu?in un departament.*/
SELECT city
FROM locations loc
WHERE EXISTS (SELECT 1
            FROM departments
            WHERE location_id = loc.location_id);

SELECT city 
FROM locations
WHERE location_id IN (SELECT location_id FROM departments);

/*13.S? se determine departamentele în care nu exist? nici un angajat (operatorul exists; cererea a
mai fost rezolvata si printr-o cerere necorelata).*/
SELECT department_id, department_name
FROM departments d
WHERE NOT EXISTS (SELECT 1 FROM employees WHERE d.department_id = department_id);

/*19. Utilizând clauza WITH, s? se scrie o cerere care afi?eaz? numele departamentelor ?i valoarea
total? a salariilor din cadrul acestora. Se vor considera departamentele a c?ror valoare total? a
salariilor este mai mare decât media valorilor totale ale salariilor tuturor angajatilor.*/
WITH salariu AS (SELECT SUM(salary) AS sum_salariu, department_id FROM employees GROUP BY department_id)
SELECT department_name, sum_salariu
FROM salariu s
JOIN departments d ON(s.department_id = d.department_id)
WHERE sum_salariu > (SELECT AVG(sum_salariu) FROM salariu);

/*20. S? se afi?eze ierarhic codul, prenumele ?i numele (pe aceea?i coloan?), codul job-ului ?i data
angaj?rii, pornind de la subordona?ii direc?i ai lui Steven King care au cea mai mare vechime.
Rezultatul nu va con?ine angaja?ii în anul 1970.*/
SELECT * FROM EMPLOYEES;
WITH king AS (SELECT employee_id cod
FROM employees
WHERE INITCAP(last_name) = 'King' AND INITCAP(first_name) = 'Steven')
SELECT employees.employee_id, first_name, last_name, job_id, hire_date, manager_id
FROM employees CROSS JOIN king 
WHERE level = 2 AND TO_CHAR(hire_date, 'YYYY') <> '1970'
START WITH employees.employee_id = cod
CONNECT BY PRIOR  employees.employee_id = manager_id;


/*21. 21. S? se detemine primii 10 cei mai bine pl?ti?i angaja?i.*/
SELECT * FROM (
SELECT last_name, first_name, salary
FROM employees
ORDER BY 3 DESC)
WHERE ROWNUM  <= 10;
/*22. S? se determine cele mai prost pl?tite 3 job-uri, din punct de vedere al mediei salariilor.*/
SELECT * FROM 
(SELECT job_id, AVG(salary)
FROM employees
GROUP BY job_id
ORDER BY 2)
WHERE ROWNUM <=3;


--Laborator 6
--ex 1
/*S? se listeze informa?ii despre angaja?ii care au lucrat în toate proiectele demarate în primele 6 luni
ale anului 2006. Implementa?i toate variantele.*/

-- varianta 1: nu exista proiect la care sa nu fi lucrat acel angajat
SELECT e.employee_id, last_name, first_name, salary
FROM employees e
WHERE NOT EXISTS (SELECT 1
FROM projects p
WHERE EXTRACT(MONTH FROM p.start_date) BETWEEN 1 AND 6 AND TO_CHAR(p.start_date, 'YYYY') = '2006'
AND NOT EXISTS(SELECT 1
FROM works_on
WHERE e.employee_id = employee_id
AND p.project_id = project_id));

-- varianta 2: cu count si group by
SELECT w.employee_id, last_name, first_name, salary
FROM works_on w
JOIN employees e ON(e.employee_id = w.employee_id)
WHERE project_id IN(SELECT project_id
FROM projects
WHERE EXTRACT(MONTH FROM start_date) BETWEEN 1 AND 6 AND EXTRACT(YEAR FROM start_date) = 2006)
GROUP BY w.employee_id, last_name, first_name, salary
HAVING COUNT(project_id) = (SELECT COUNT(project_id)
FROM projects
WHERE EXTRACT(MONTH FROM start_date) BETWEEN 1 AND 6 AND EXTRACT(YEAR FROM start_date) = 2006);

-- varianta 3 cu minus
SELECT w.employee_id, last_name, first_name, salary
FROM works_on w
JOIN employees e ON(e.employee_id = w.employee_id)
MINUS
SELECT e1.employee_id, last_name, first_name, salary FROM
(SELECT employee_id, project_id 
FROM (SELECT employee_id FROM works_on),
(SELECT project_id FROM projects WHERE EXTRACT(MONTH FROM start_date) BETWEEN 1 AND 6 AND EXTRACT(YEAR FROM start_date) = 2006)
MINUS
SELECT employee_id, project_id
FROM works_on) aux
JOIN employees e1 ON(e1.employee_id = aux.employee_id);

-- Varianta 4
SELECT DISTINCT w.employee_id, last_name, first_name, salary
FROM works_on w
JOIN employees e ON(e.employee_id = w.employee_id)
WHERE NOT EXISTS (SELECT project_id
FROM projects WHERE EXTRACT(MONTH FROM start_date) BETWEEN 1 AND 6 AND EXTRACT(YEAR FROM start_date) = 2006
MINUS
SELECT project_id
FROM works_on w1
WHERE w.employee_id = w1.employee_id);

/*S? se ob?in? codurile salaria?ilor ata?a?i tuturor proiectelor pentru care s-a alocat un buget
egal cu 10000.*/
-- varianta 1
SELECT DISTINCT employee_id
FROM works_on w
WHERE NOT EXISTS (SELECT 1 FROM projects p 
WHERE budget = 10000 
AND NOT EXISTS (SELECT 1 FROM works_on 
WHERE w.employee_id = employee_id AND p.project_id  = project_id));

-- varianta 2
SELECT employee_id
FROM works_on
WHERE project_id IN (SELECT project_id FROM projects WHERE budget = 10000)
GROUP BY employee_id
HAVING COUNT(project_id) = (SELECT COUNT(project_id) FROM projects WHERE budget = 10000);


--varianta 3 cu minus
SELECT employee_id
FROM works_on
MINUS
SELECT employee_id FROM
(SELECT employee_id, project_id
FROM (SELECT employee_id FROM works_on),
(SELECT  project_id FROM projects WHERE budget = 10000)
MINUS
SELECT employee_id, project_id
FROM works_on);

--b\a = muultimea vida; nu exista proiect
SELECT DISTINCT employee_id
FROM works_on w
WHERE NOT EXISTS (SELECT project_id 
FROM projects
WHERE budget = 10000
MINUS
SELECT project_id
FROM works_on
WHERE w.employee_id = employee_id);

/*2.S? se listeze informa?ii despre proiectele la care au participat to?i angaja?ii care au de?inut alte 2
posturi în firm?.*/
SELECT p.*
FROM projects p
WHERE NOT EXISTS (SELECT 1
FROM job_history jh
WHERE NOT EXISTS (SELECT 1
FROM works_on
WHERE jh.employee_id = employee_id AND p.project_id = project_id)
GROUP BY employee_id
HAVING COUNT(start_date) = 2);

/*3.S? se ob?in? num?rul de angaja?i care au avut cel pu?in trei job-uri, luându-se în considerare ?i job-ul
curent.*/
SELECT COUNT(COUNT(employee_id))
FROM job_history
GROUP BY employee_id
HAVING COUNT(employee_id) >=2;
SELECT * FROM job_history
order by 1;
/*4. Pentru fiecare ?ar?, s? se afi?eze num?rul de angaja?i din cadrul acesteia.*/
SELECT country_name, COUNT(employee_id)
FROM countries c
JOIN locations loc ON(c.country_id = loc.country_id)
JOIN departments d ON(d.location_id = loc.location_id)
JOIN employees e ON(e.department_id = d.department_id)
GROUP BY country_name;


/*5.S? se listeze angaja?ii (codul ?i numele acestora) care au lucrat pe cel pu?in dou? proiecte nelivrate
la termen.*/
SELECT DISTINCT e.employee_id, last_name
FROM employees e
WHERE (SELECT COUNT(COUNT(w.project_id))
FROM projects pr
JOIN works_on w ON(pr.project_id = w.project_id)
WHERE deadline < delivery_date AND e.employee_id = w.employee_id
GROUP BY w.project_id) >= 2;

/*6.S? se listeze codurile angaja?ilor ?i codurile proiectelor pe care au lucrat. Listarea va cuprinde ?i
angaja?ii care nu au lucrat pe nici un proiect.*/
SELECT w.employee_id, w.project_id
FROM employees e
LEFT JOIN works_on w ON(e.employee_id = w.employee_id)
LEFT JOIN projects p ON(p.project_id = w.project_id);

/*S? se afi?eze angaja?ii care lucreaz? în acela?i departament cu cel pu?in un manager de proiect.*/
SELECT employee_id
FROM employees e
WHERE department_id IN (SELECT department_id
                        FROM employees
                        WHERE employee_id IN (SELECT project_manager FROM projects)
                        AND e.employee_id <> employee_id);
    

/*8.S? se afi?eze angaja?ii care nu lucreaz? în acela?i departament cu nici un manager de proiect.*/
SELECT employee_id, last_name
FROM employees e
WHERE NOT EXISTS (SELECT 1
FROM employees
WHERE e.department_id = department_id
AND employee_id IN (SELECT project_manager FROM projects));

/*9.S? se determine departamentele având media salariilor mai mare decît un num?r dat.*/

SELECT department_id, AVG(salary)
FROM employees
GROUP BY department_id
HAVING AVG(salary) > &med;


/*10.Se cer informa?ii (nume, prenume, salariu, num?r proiecte) despre managerii de proiect care au
condus 2 proiecte.*/
SELECT * from works_on order by 2;
SELECT e.employee_id, last_name, first_name, salary, COUNT(project_id)
FROM employees e
JOIN projects p ON (p.project_manager = e.employee_id)
GROUP BY e.employee_id, last_name, first_name, salary
HAVING COUNT(project_id) = 2;

/*11.S? se afi?eze lista angaja?ilor care au lucrat numai pe proiecte conduse de managerul de proiect
având codul 102.*/
SELECT DISTINCT e.employee_id, last_name
FROM works_on w
JOIN employees e ON(e.employee_id = w.employee_id)
WHERE NOT EXISTS   (SELECT project_id
                    FROM projects 
                    WHERE project_manager = 102
                    MINUS
                    SELECT project_id
                    FROM works_on
                    WHERE e.employee_id = employee_id)
AND NOT EXISTS     (SELECT project_id
                    FROM works_on
                    WHERE e.employee_id = employee_id
                    MINUS
                    SELECT project_id
                    FROM projects 
                    WHERE project_manager = 102);


SELECT DISTINCT e.employee_id, last_name
FROM works_on w
JOIN employees e ON(e.employee_id = w.employee_id)
WHERE NOT EXISTS   (SELECT project_id
                    FROM projects p
                    WHERE project_manager = 102
                    AND NOT EXISTS 
                    (SELECT project_id
                    FROM works_on
                    WHERE e.employee_id = employee_id AND p.project_id = project_id));      --- solutia nu da incluziune? sa fi lucrat pe cel putin aceleasi proiecte ca 102
                    

/*12. a) S? se ob?in? numele angaja?ilor care au lucrat cel pu?in pe acelea?i proiecte ca ?i angajatul
având codul 200.
b) S? se ob?in? numele angaja?ilor care au lucrat cel mult pe acelea?i proiecte ca ?i angajatul având
codul 200.*/
--a
SELECT DISTINCT e.employee_id, last_name
FROM employees e
JOIN works_on w ON(e.employee_id = w.employee_id)
WHERE NOT EXISTS (SELECT project_id 
FROM works_on 
WHERE employee_id = 200
MINUS
SELECT project_id
FROM works_on
WHERE employee_id = w.employee_id)
AND e.employee_id <> 200;


--b
SELECT DISTINCT e.employee_id, last_name
FROM employees e
JOIN works_on w ON(e.employee_id = w.employee_id)
WHERE NOT EXISTS (SELECT project_id
FROM works_on
WHERE employee_id = w.employee_id
MINUS
SELECT project_id 
FROM works_on 
WHERE employee_id = 200)
AND e.employee_id <> 200;

/*S? se ob?in? angaja?ii care au lucrat pe acelea?i proiecte ca ?i angajatul având codul 200.*/
SELECT DISTINCT e.employee_id, last_name
FROM employees e
JOIN works_on w ON(e.employee_id = w.employee_id)
WHERE NOT EXISTS (SELECT project_id
                FROM works_on
                WHERE employee_id = w.employee_id
                MINUS
                SELECT project_id 
                FROM works_on 
                WHERE employee_id = 200)
AND NOT EXISTS (SELECT project_id 
                FROM works_on 
                WHERE employee_id = 200
                MINUS
                SELECT project_id
                FROM works_on
                WHERE employee_id = w.employee_id)
AND e.employee_id <> 200;


/*15. Sa se afiseze codul, numele, salariul si codul departamentului din care face parte pentru un angajat
al carui cod este introdus de utilizator de la tastatura. Analizati diferentele dintre cele 4 posibilitati:*/
---v 4
ACCEPT p_cod PROMPT "Codul angajatului:"
SELECT employee_id, last_name, salary, department_id
FROM employees
WHERE employee_id = &p_cod;

--- v 1
SELECT employee_id, last_name, salary, department_id
FROM employees WHERE employee_id = &p_cod;

-- v2
DEFINE p_cod; -- Ce efect are?
SELECT employee_id, last_name, salary, department_id
FROM employees WHERE employee_id = &p_cod;
UNDEFINE p_cod;

--v3
DEFINE p_cod=100;
SELECT employee_id, last_name, salary, department_id
FROM employees WHERE employee_id = &&p_cod;
UNDEFINE p_cod;

/*16.Sa se afiseze numele, codul departamentului si salariul anual pentru toti angajatii care au un anumit
job.*/
SELECT * FROM employees order by hire_date;
SELECT last_name, department_id, salary * 12
FROM employees
WHERE LOWER(job_id) = LOWER('&p_job');

/*17.Sa se afiseze numele, codul departamentului si salariul anual pentru toti angajatii care au fost
angajati dupa o anumita data calendaristica.*/
SELECT last_name, department_id, salary * 12, hire_date
FROM employees
WHERE hire_date >= TO_DATE('&p_data','DD/MM/YYYY');

/*18. Sa se afiseze o coloana aleasa de utilizator, dintr-un tabel ales de utilizator, ordonand dupa aceeasi
coloana care se afiseaza. De asemenea, este obligatorie precizarea unei conditii WHERE.*/
SELECT &&p_coloana                          ---!!!!!!!!!!atentie sa nu punem intre ' ' numele tabellului
FROM &p_tabel
WHERE &&p_coloana LIKE &p_valoare
ORDER BY &&p_coloana;

/*19. S? se realizeze un script prin care s? se afi?eze numele, job-ul ?i data angaj?rii salariatilor care
au început lucrul între 2 date calendaristice introduse de utilizator. S? se concateneze numele
si job-ul, separate prin spatiu si virgul?, si s? se eticheteze coloana "Angajati".
Se vor folosi comanda ACCEPT si formatul pentru data calendaristica MM/DD/YY.*/
ACCEPT p_data1 PROMPT "data1:"
ACCEPT p_data2 PROMPT "data2:"
SELECT last_name || ' ' || job_id "Angajati", hire_date
FROM employees
WHERE hire_date BETWEEN TO_DATE('&p_data1', 'MM/DD/YY')  AND TO_DATE('&p_data2', 'MM/DD/YY');
UNDEFINE &p_data1



/*20. Sa se realizeze un script pentru a afisa numele angajatului, codul job-ului, salariul si numele
departamentului pentru salariatii care lucreaza intr-o locatie data de utilizator. Va fi permisa cautarea
case-insensitive.*/
SELECT last_name, job_id, salary, department_name,city
FROM employees
JOIN departments USING (department_id)
JOIN locations USING(location_id)
WHERE LOWER(city) LIKE LOWER('&p_city');


-Laborator 6
--ex 1
/*S? se listeze informa?ii despre angaja?ii care au lucrat în toate proiectele demarate în primele 6 luni
ale anului 2006. Implementa?i toate variantele.*/

-- varianta 1: nu exista proiect la care sa nu fi lucrat acel angajat
SELECT e.employee_id, last_name, first_name, salary
FROM employees e
WHERE NOT EXISTS (SELECT 1
FROM projects p
WHERE EXTRACT(MONTH FROM p.start_date) BETWEEN 1 AND 6 AND TO_CHAR(p.start_date, 'YYYY') = '2006'
AND NOT EXISTS(SELECT 1
FROM works_on
WHERE e.employee_id = employee_id
AND p.project_id = project_id));

-- varianta 2: cu count si group by
SELECT w.employee_id, last_name, first_name, salary
FROM works_on w
JOIN employees e ON(e.employee_id = w.employee_id)
WHERE project_id IN(SELECT project_id
FROM projects
WHERE EXTRACT(MONTH FROM start_date) BETWEEN 1 AND 6 AND EXTRACT(YEAR FROM start_date) = 2006)
GROUP BY w.employee_id, last_name, first_name, salary
HAVING COUNT(project_id) = (SELECT COUNT(project_id)
FROM projects
WHERE EXTRACT(MONTH FROM start_date) BETWEEN 1 AND 6 AND EXTRACT(YEAR FROM start_date) = 2006);

-- varianta 3 cu minus
SELECT w.employee_id, last_name, first_name, salary
FROM works_on w
JOIN employees e ON(e.employee_id = w.employee_id)
MINUS
SELECT e1.employee_id, last_name, first_name, salary FROM
(SELECT employee_id, project_id 
FROM (SELECT employee_id FROM works_on),
(SELECT project_id FROM projects WHERE EXTRACT(MONTH FROM start_date) BETWEEN 1 AND 6 AND EXTRACT(YEAR FROM start_date) = 2006)
MINUS
SELECT employee_id, project_id
FROM works_on) aux
JOIN employees e1 ON(e1.employee_id = aux.employee_id);

-- Varianta 4
SELECT DISTINCT w.employee_id, last_name, first_name, salary
FROM works_on w
JOIN employees e ON(e.employee_id = w.employee_id)
WHERE NOT EXISTS (SELECT project_id
FROM projects WHERE EXTRACT(MONTH FROM start_date) BETWEEN 1 AND 6 AND EXTRACT(YEAR FROM start_date) = 2006
MINUS
SELECT project_id
FROM works_on w1
WHERE w.employee_id = w1.employee_id);

/*S? se ob?in? codurile salaria?ilor ata?a?i tuturor proiectelor pentru care s-a alocat un buget
egal cu 10000.*/
-- varianta 1
SELECT DISTINCT employee_id
FROM works_on w
WHERE NOT EXISTS (SELECT 1 FROM projects p 
WHERE budget = 10000 
AND NOT EXISTS (SELECT 1 FROM works_on 
WHERE w.employee_id = employee_id AND p.project_id  = project_id));

-- varianta 2
SELECT employee_id
FROM works_on
WHERE project_id IN (SELECT project_id FROM projects WHERE budget = 10000)
GROUP BY employee_id
HAVING COUNT(project_id) = (SELECT COUNT(project_id) FROM projects WHERE budget = 10000);


--varianta 3 cu minus
SELECT employee_id
FROM works_on
MINUS
SELECT employee_id FROM
(SELECT employee_id, project_id
FROM (SELECT employee_id FROM works_on),
(SELECT  project_id FROM projects WHERE budget = 10000)
MINUS
SELECT employee_id, project_id
FROM works_on);

--b\a = muultimea vida; nu exista proiect
SELECT DISTINCT employee_id
FROM works_on w
WHERE NOT EXISTS (SELECT project_id 
FROM projects
WHERE budget = 10000
MINUS
SELECT project_id
FROM works_on
WHERE w.employee_id = employee_id);

/*2.S? se listeze informa?ii despre proiectele la care au participat to?i angaja?ii care au de?inut alte 2
posturi în firm?.*/
SELECT p.*
FROM projects p
WHERE NOT EXISTS (SELECT 1
FROM job_history jh
WHERE NOT EXISTS (SELECT 1
FROM works_on
WHERE jh.employee_id = employee_id AND p.project_id = project_id)
GROUP BY employee_id
HAVING COUNT(start_date) = 2);


