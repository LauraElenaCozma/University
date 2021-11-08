--- Exercitiul 1 ---
/*S? se listeze informa?ii despre angaja?ii care au lucrat în toate proiectele demarate în primele 6 luni
ale anului 2006.*/
----!!! combinatie cu de 2 ori minus??       TEMA CELELALTE 2 VARIANTE

SELECT *
FROM works_on;

SELECT *
FROM projects;
-- varianta 1 --
SELECT employee_id, last_name, hire_date, salary
FROM employees e
WHERE NOT EXISTS  (SELECT 1                 --intoarce true sau false
                   FROM projects p
                   WHERE EXTRACT(year FROM start_date)= 2006 AND 
                   EXTRACT(month FROM start_date)   BETWEEN 1 AND 6
                   AND NOT EXISTS (SELECT 'q' 
                                   FROM works_on w
                                   WHERE w.project_id = p.project_id
                                   AND w.employee_id = e.employee_id));  
                                   
-- varianta 2 --
SELECT employee_id, last_name, salary
FROM employees JOIN works_on USING (employee_id)
WHERE project_id IN (SELECT project_id      --proiectele care lucreaza sa fie in multimea asta
                     FROM projects
                     WHERE EXTRACT(year FROM start_date)= 2006 AND 
                     EXTRACT(month FROM start_date)   BETWEEN 1 AND 6)
GROUP BY employee_id, last_name, salary
HAVING COUNT(project_id) = (SELECT COUNT(project_id)
                            FROM projects
                            WHERE EXTRACT(year FROM start_date)= 2006 AND 
                            EXTRACT(month FROM start_date)   BETWEEN 1 AND 6);
                            

-- Exercitiul 2 --
SELECT *
FROM projects p -- sa nu uitam de sincronizare!!!
WHERE NOT EXISTS (  SELECT 2
                    FROM job_history jh
                    WHERE NOT EXISTS (SELECT 'd'
                                FROM works_on w
                                WHERE w.employee_id = jh.employee_id
                                AND w.project_id = p.project_id)
                    GROUP BY employee_id
                    HAVING COUNT(job_id) = 2);
                    
                    
SELECT * from job_history order by 1;

-- Exercitiul 3 --
/*S? se ob?in? num?rul de angaja?i care au avut cel pu?in trei job-uri, luându-se în considerare ?i job-ul
curent.*/
SELECT COUNT(COUNT(employee_id))     --cati sunt care respecta conditia; fara al doilea count numara cate joburi are fiecare angajat
FROM job_history
GROUP BY employee_id
HAVING COUNT(job_id) >= 2;  --2 + jobul prezent = 3


-- Exercitiul 4 --
/*Pentru fiecare tar?, s? se afi?eze num?rul de angajati din cadrul acesteia.*/
SELECT country_name, COUNT(*)  --count(employee_id)
FROM employees 
JOIN departments USING(department_id)
JOIN locations USING(location_id)
JOIN countries USING(country_id)
GROUP BY country_name; --pentru fiecare tara

-- Exercitiul 5 --
/*S? se listeze angaja?ii (codul ?i numele acestora) care au lucrat pe cel pu?in dou? proiecte nelivrate
la termen.*/
--deadline ul a fost depasit
--delivery date > deadline
SELECT employee_id, last_name
FROM employees e
WHERE (SELECT COUNT(COUNT(w.project_id))
FROM works_on w
JOIN projects p ON (w.project_id = p.project_id)
WHERE w.employee_id = e.employee_id AND delivery_date > deadline
GROUP BY w.project_id) >= 2;  --grupam dupa proiecte, le numaram, verificam daca nr depaseste 2

--Exercitiul 6 --
/*S? se listeze codurile angaja?ilor ?i codurile proiectelor pe care au lucrat. Listarea va cuprinde ?i
angaja?ii care nu au lucrat pe nici un proiect.*/

SELECT last_name, w.employee_id, w.project_id, p.project_name
FROM employees e
LEFT JOIN works_on w ON (e.employee_id = w.employee_id)
LEFT JOIN projects p ON (p.project_id = w.project_id);

-- Exercitiul 7 --
SELECT employee_id, last_name, salary
FROM employees
WHERE department_id IN (SELECT department_id
                        FROM employees
                        WHERE employee_id IN (SELECT project_manager FROM projects));
                        
-- Exercitiul 8 --
SELECT employee_id, last_name, salary
FROM employees
MINUS
SELECT employee_id, last_name, salary
FROM employees
WHERE department_id IN (SELECT department_id
                        FROM employees
                        WHERE employee_id IN (SELECT project_manager FROM projects));

-- Exercitiul 9 --            
/*S? se determine departamentele având media salariilor mai mare decît un num?r dat.*/
SELECT department_id
FROM employees
GROUP BY department_id
HAVING AVG(salary) > &&p; --&& salveaza in buffer

SELECT employee_id
FROM employees
WHERE salary = &w; -- a folosit valoarea din buffer

UNDEFINE p

ACCEPT w PROMPT 'w='

-- Exercitiul 10 --
/*10. Se cer informa?ii (nume, prenume, salariu, num?r proiecte) despre managerii de proiect care au
condus 2 proiecte.*/
SELECT last_name, first_name, salary, nr_proiecte
FROM employees e
JOIN (  SELECT project_manager, COUNT(project_id) nr_proiecte
        FROM projects
        GROUP BY project_manager) t
ON (e.employee_id = t.project_manager)
WHERE nr_proiecte = 2;

-- Exercitiul 11 --
/*11. S? se afi?eze lista angaja?ilor care au lucrat numai pe proiecte conduse de managerul de proiect
având codul 102.*/
-- da-ne angajatii pentru care nu exista sa lucreze la proiecte la care lucreaza 102 ...???
SELECT *
FROM employees e
WHERE NOT EXISTS (SELECT 'unu' 
                  FROM projects p
                  WHERE project_manager = 102 AND NOT EXISTS (SELECT 'altul' 
                                                            FROM works_on w
                                                            WHERE w.employee_id = e.employee_id /*am facut sincronizarea*/ 
                                                            AND w.project_id = p.project_id));
                                                            
-- TEMA: 12, 13, 14, ex 1 cele 2 variante

-- Exercitiul 11 --
/*S? se afi?eze lista angaja?ilor care au lucrat numai pe proiecte conduse de managerul de proiect
având codul 102.*/
SELECT last_name, employee_id
FROM employees e   --nu exista proiect la care sa nu lucreze acest angajat
WHERE NOT EXISTS   (SELECT '1' 
                    FROM projects p
                    WHERE project_manager = 102 AND
                    NOT EXISTS (SELECT 1
                                FROM works_on
                                WHERE employee_id = e.employee_id
                                AND project_id = p.project_id));
                                
-- Exercitiul 12 --
/*a) S? se ob?in? numele angaja?ilor care au lucrat cel pu?in pe acelea?i proiecte ca ?i angajatul
având codul 200.
b) S? se ob?in? numele angaja?ilor care au lucrat cel mult pe acelea?i proiecte ca ?i angajatul având
codul 200.*/
--a) aceleasi eventual si altele
SELECT last_name, employee_id
FROM employees e
WHERE NOT EXISTS   (SELECT '1'
                    FROM works_on w
                    WHERE employee_id = 200
                    AND NOT EXISTS (SELECT 1 
                                    FROM works_on
                                    WHERE w.project_id = project_id
                                    AND employee_id = e.employee_id))
AND e.employee_id <> 200;


--b)
SELECT DISTINCT e.last_name, e.employee_id
FROM employees e
JOIN works_on w2 ON (e.employee_id = w2.employee_id)
WHERE NOT EXISTS   (SELECT project_id
                    FROM works_on w
                    WHERE w.employee_id = e.employee_id
                    MINUS
                    SELECT project_id
                    FROM works_on
                    WHERE employee_id = 200)
AND e.employee_id <> 200;


-- Exercitiul 13 --
/*S? se ob?in? angaja?ii care au lucrat pe acelea?i proiecte ca ?i angajatul având codul 200.*/
SELECT last_name, employee_id
FROM employees e   --nu exista proiect la care sa nu lucreze acest angajat
WHERE e.employee_id <> 200 AND NOT EXISTS(SELECT '1'
                    FROM works_on w
                    WHERE employee_id = 200
                    AND NOT EXISTS (SELECT 1 
                                    FROM works_on
                                    WHERE w.project_id = project_id
                                    AND employee_id = e.employee_id))
AND NOT EXISTS (SELECT project_id
                    FROM works_on w
                    WHERE w.employee_id = e.employee_id
                    MINUS
                    SELECT project_id
                    FROM works_on
                    WHERE employee_id = 200);

-- Exercitiul 14
desc job_grades

SELECT * 
FROM job_grades;

SELECT last_name, employee_id, salary, grade_level
FROM employees
CROSS JOIN job_grades
WHERE salary BETWEEN lowest_sal AND highest_sal;

-- Exercitiul 15 --
SELECT employee_id, last_name, salary, department_id
FROM employees WHERE employee_id = &p_cod;
DEFINE p_cod -- Ce efect are? apare mesajul de eroare undefined
SELECT employee_id, last_name, salary, department_id
FROM employees WHERE employee_id = &p_cod;
UNDEFINE p_cod

DEFINE p_cod=100

SELECT employee_id, last_name, salary, department_id
FROM employees WHERE employee_id = &&p_cod; --apare pt codul 100 definit de noi mai devreme
UNDEFINE p_cod -- un & sau 2 tot se salveaza in buffer

ACCEPT p_cod PROMPT "cod= ";
SELECT employee_id, last_name, salary, department_id
FROM employees WHERE employee_id = &p_cod;


-- Exercitiul 16 --
/*Sa se afiseze numele, codul departamentului si salariul anual pentru toti angajatii care au un anumit
job.*/
ACCEPT p_jobId PROMPT "job id = " 
SELECT employee_id, last_name, department_id, salary * 12, job_id --salariu anual
FROM employees
WHERE lower(job_id) = lower('&p_jobId');

-- Exercitiul 17 --
/*Sa se afiseze numele, codul departamentului si salariul anual pentru toti angajatii care au fost
angajati dupa o anumita data calendaristica.*/
ACCEPT p_date PROMPT "date = " --ce facem daca nu stim formatul? folosim to date
SELECT last_name, department_id, salary * 12, hire_date
FROM employees
WHERE hire_date >= TO_DATE('&p_date','DD-MM-YYYY');

-- Exercitiul 18 --
/*Sa se afiseze o coloana aleasa de utilizator, dintr-un tabel ales de utilizator, ordonand dupa aceeasi
coloana care se afiseaza. De asemenea, este obligatorie precizarea unei conditii WHERE.*/
-- sa facem un top 5
--folosim pt coloana de 2 ori & pt ca ne trebuie de 2 ori
SELECT *
FROM (SELECT &&p_coloana
FROM &p_tabel
ORDER BY &p_coloana)
WHERE ROWNUM <= 5;


-- Exercitiul 19 --
ACCEPT p_data1 PROMPT "data1 = "
ACCEPT p_data2 PROMPT "data2 = "
SELECT last_name || ' , ' || job_id "Angajati" , hire_date
FROM employees
WHERE hire_date BETWEEN TO_DATE('&p_data1','MM/DD/YYYY') AND  TO_DATE('&p_data2','MM/DD/YYYY');

-- ex 20 tema folosim city
--ex 21 a ca tema

-- Exercitiul 21 --
/*21. a)S? se citeasc? dou? date calendaristice de la tastatur? si s? se afiseze zilele dintre aceste dou? date.*/
ACCEPT p_data1 PROMPT "data1 = "
ACCEPT p_data2 PROMPT "data2 = "
SELECT TO_DATE('&p_data1','MM/DD/YYYY') + ROWNUM - 1
FROM dual
CONNECT BY ROWNUM < TO_DATE('&p_data2','MM/DD/YYYY') - TO_DATE('&p_data1','MM/DD/YYYY') + 1;
