--L4 lucru examen--

--2
SELECT MAX(salary), MIN(salary), SUM(salary), AVG(salary)
FROM employees;

--3
SELECT MAX(salary), MIN(salary), SUM(salary), AVG(salary)
FROM employees
GROUP BY job_id;

--4
SELECT count(employee_id)
FROM employees
GROUP BY job_id;

--5
SELECT count(DISTINCT manager_id)
fROM employees
WHERE manager_id IS NOT NULL;

select * from employees;

-- 6
SELECT MAX(salary) - MIN(salary)
FROM employees;

--7
SELECT department_name, location_id, COUNT(employee_id), AVG(salary)
FROM employees
JOIN departments USING(department_id)
GROUP BY department_name, location_id;

--8
SELECT employee_id, last_name
FROM employees
WHERE salary > (SELECT AVG(salary) from employees)
ORDER  BY salary DESC;

--9
SELECT manager_id, MIN(salary)
FROM employees
WHERE manager_id IS NOT NULL
GROUP BY manager_id
HAVING MIN(salary) >= 1000
ORDER BY 2 DESC;

--10
SELECT department_id, department_name, MAX(salary)
FROM employees
JOIN departments USING(department_id)
GROUP BY department_id, department_name
HAVING MAX(salary) > 3000;

-- 11
SELECT MIN(AVG(salary))
from employees
GROUP BY job_id;

--12
SELECT department_id, department_name, SUM(salary)
FROM employees
JOIN departments USING(department_id)
GROUP BY department_id, department_name;

--13
SELECT MAX(AVG(salary))
from employees
GROUP BY department_id;

--14
SELECT job_id, job_title, AVG(salary)
FROM employees
JOIN jobs USING(job_id)
GROUP BY job_id, job_title
HAVING AVG(salary) = (SELECT MIN(AVG(salary))
FROM employees
group by job_id);

--15
SELECT AVG(salary)
FROM employees
HAVING AVG(salary) > 2500;

--16
SELECT SUM(salary), department_id, job_id
FROM employees
GROUP BY department_id, job_id
order by 2,3;

--17
SELECT department_name, MIN(salary)
FROM employees
JOIN departments USING(department_id)
GROUP BY department_name
HAVING AVG(salary) = (SELECT MAX(AVG(salary)) from employees group by department_id);


SELECT d.department_name , MIN(e.salary)
FROM employees e
JOIN departments d ON(e.department_id = d.department_id)
JOIN (SELECT department_id , AVG(salary) AS medie
    FROM employees
    GROUP BY department_id) aux ON(aux.department_id = e.department_id)
WHERE medie = (SELECT MAX(AVG(salary))
FROM employees
GROUP BY department_id)
GROUP BY department_name;

--L4

/*18.Sa se afiseze codul, numele departamentului si numarul de angajati care lucreaza
in acel departament pentru:
a) departamentele in care lucreaza mai putin de 4 angajati;
b) departamentul care are numarul maxim de angajati.*/
SELECT d.department_id, department_name, COUNT(employee_id)
FROM employees e
JOIN departments d ON(d.department_id = e.department_id)
GROUP BY d.department_id, department_name
HAVING COUNT(employee_id) > 4;

SELECT d.department_id, department_name, COUNT(employee_id)
FROM employees e
JOIN departments d ON(d.department_id = e.department_id)
GROUP BY d.department_id, department_name
HAVING COUNT(employee_id) = (SELECT MAX(COUNT(employee_id))
                            FROM employees
                            GROUP BY department_id);
                            
/*19. Sa se afiseze salariatii care au fost angajati în aceeasi zi a lunii în care cei mai multi
dintre salariati au fost angajati.*/
SELECT employee_id, last_name, hire_date
FROM employees
WHERE EXTRACT (DAY FROM hire_date) = (SELECT EXTRACT(DAY FROM hire_date)
                                    FROM employees
                                    GROUP BY EXTRACT(DAY FROM hire_date)
                                    HAVING COUNT(employee_id) = (SELECT MAX(COUNT(employee_id))
                                                                FROM employees
                                                                GROUP BY EXTRACT(DAY FROM hire_date)));
                                                                
                                                                
/*20.Sa se obtina numarul departamentelor care au cel putin 15 angajati.*/
SELECT COUNT(department_id)
FROM departments
WHERE department_id IN (SELECT department_id
                        FROM employees
                        GROUP BY department_id
                        HAVING COUNT(employee_id) >= 15);
                        
/*21. Sa se obtina codul departamentelor si suma salariilor angajatilor care lucreaza în
acestea, în ordine crescatoare. Se considera departamentele care au mai mult de 10
angajati si al caror cod este diferit de 30.*/
SELECT department_id, SUM(salary)
FROM employees
WHERE department_id <> 30
GROUP BY department_id
HAVING COUNT(employee_id) > 10;

/*22. Sa se afiseze codul, numele departamentului, numarul de angajati si salariul mediu
din departamentul respectiv, impreuna cu numele, salariul si jobul angajatilor din acel
departament. Se vor afisa si departamentele fara angajati (outer join).*/

SELECT d.department_id, department_name, nr_ang, med_sal, last_name, salary, job_id
FROM departments d
JOIN employees e ON(e.department_id = d.department_id)
JOIN (SELECT COUNT(employee_id) nr_ang, ROUND(AVG(salary),2) med_sal, department_id
FROM employees
GROUP BY department_id) aux ON(e.department_id = aux.department_id);

/*23 Scrieti o cerere pentru a afisa, pentru departamentele avand codul > 80, salariul total
pentru fiecare job din cadrul departamentului. Se vor afisa orasul, numele
departamentului, jobul si suma salariilor. Se vor eticheta coloanele corespunzator.*/
SELECT DISTINCT loc.city, d.department_name, e.job_id, sum_sal
FROM employees e
JOIN departments d ON(e.department_id = d.department_id)
JOIN locations loc ON(loc.location_id = d.location_id)
JOIN (SELECT department_id, job_id, SUM(salary) sum_sal
FROM employees
GROUP BY department_id, job_id) aux ON (aux.department_id = d.department_id AND aux.job_id = e.job_id)
WHERE department_id > 80;

/*24. Care sunt angajatii care au mai avut cel putin doua joburi?*/
SELECT employee_id
FROM job_history
GROUP BY employee_id
HAVING COUNT(start_date) >= 2;

/*30.Sa se afiseze codul, numele departamentului si suma salariilor pe departamente.*/
SELECT d.department_id, department_name, SUM(salary)
FROM employees e
JOIN departments d  ON(e.department_id = d.department_id)
GROUP BY d.department_id, department_name;

/*31. Sa se afiseze numele, salariul, codul departamentului si salariul mediu din departamentul
respectiv.*/
SELECT last_name, salary, e.department_id, sal_med
FROM employees e
JOIN (SELECT AVG(salary) sal_med, department_id FROM employees GROUP BY department_id) aux ON(aux.department_id = e.department_id);

/*32. Modificati cererea anterioara, pentru a determina si listarea numarului de angajati din
departamente.*/
SELECT last_name, salary, e.department_id, sal_med, nr_ang
FROM employees e
JOIN (SELECT AVG(salary) sal_med, COUNT(employee_id) nr_ang, department_id FROM employees GROUP BY department_id) aux ON(aux.department_id = e.department_id);

/*33.Pentru fiecare departament, sa se afiseze numele acestuia, numele si salariul celor mai
prost platiti angajati din cadrul sau.*/
SELECT e.department_id, last_name, salary
FROM employees e
JOIN (SELECT MIN(salary) sal_min,department_id FROM employees GROUP BY department_id) aux ON (e.department_id = aux.department_id AND e.salary = aux.sal_min);



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




