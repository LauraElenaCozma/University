-- Tema Laborator 7 --

-- Exercitiul 16 --
/* Scrieti o cerere ierarhica pentru a afisa codul salariatului, codul managerului si numele salariatului,
pentru angajatii care sunt cu 2 niveluri sub De Haan.
Afisati, de asemenea, nivelul angajatului în ierarhie.*/

SELECT LEVEL , employee_id , manager_id , last_name
FROM employees
WHERE LEVEL = (SELECT LEVEL
FROM employees
WHERE UPPER(last_name) LIKE 'DE HAAN'
START WITH  employee_id = (SELECT employee_id
                          FROM employees
                          WHERE manager_id IS NULL) 
CONNECT BY PRIOR employee_id = manager_id
) + 2
START WITH employee_id = (SELECT employee_id
                          FROM employees
                          WHERE manager_id IS NULL)
CONNECT BY PRIOR employee_id = manager_id;

-- Exercitiul 17 --
/*Pentru fiecare linie din tabelul EMPLOYEES, se va afisa o structura arborescenta in care va ap?rea
angajatul, managerul s?u, managerul managerului etc. Coloanele afi?ate vor fi: codul angajatului,
codul managerului, nivelul în ierarhie (LEVEL) si numele angajatului. */
SELECT employee_id , manager_id , LEVEL , LPAD (last_name , LEVEL - 1 + LENGTH(last_name)) as "Nume"
FROM employees
CONNECT BY PRIOR manager_id = employee_id;

-- Exercitiul 18 --
/* S? se afi?eze ierarhia de sub angajatul având salariul maxim, re?inând numai angaja?ii al c?ror
salariu este mai mare de 5000. Se vor afi?a codul, numele, salariul, nivelul din ierarhie ?i codul
managerului.*/
SELECT employee_id , LPAD (last_name , LEVEL - 1 + LENGTH(last_name)) as "Nume" , salary , LEVEL , manager_id
FROM employees
WHERE salary > 5000 AND LEVEL <> 1                            -- level <> 1 pentru nu a afisa si angajatul cu salariul maxim
START WITH salary IN (SELECT MAX(salary) FROM employees)
CONNECT BY PRIOR employee_id = manager_id
ORDER BY LEVEL;

-- Exercitiul 12 cu join --
/* 12. S? se determine loca?iile în care se afl? cel pu?in un departament.*/
SELECT DISTINCT city
FROM locations
JOIN departments USING(location_id);

-- Exercitiul 13 cu join --
/*S? se determine departamentele în care nu exist? nici un angajat (operatorul exists; cererea a
mai fost rezolvata si printr-o cerere necorelata). */
SELECT department_id
FROM departments
LEFT JOIN employees USING(department_id)
MINUS 
SELECT department_id 
FROM departments
JOIN employees USING(department_id);

-- Exercitiul 15 afisare arborescenta --
/*15. S? se ob?in? ierarhia ?ef-subaltern, considerând ca r?d?cin? angajatul având codul 114.*/
SELECT LEVEL , employee_id , LPAD (last_name , LEVEL - 1 + LENGTH(last_name)) , hire_date , salary , manager_id  --level - 1 pentru a nu avea spatiu si inaintea numelui de pe primul nivel 
FROM employees
START WITH employee_id = 114
CONNECT BY PRIOR employee_id = manager_id  --sa afisam ierarhia 
ORDER BY LEVEL;
