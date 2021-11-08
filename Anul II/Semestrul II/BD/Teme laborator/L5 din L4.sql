--- Tema laborator 5---
--20. S? se ob?in? num?rul departamentelor care au cel pu?in 15 angaja?i.
SELECT COUNT(DISTINCT department_id) "Numar departamente"
FROM employees
WHERE department_id IN(
                        SELECT department_id
                        FROM employees
                        GROUP BY department_id
                        HAVING COUNT(employee_id) >= 15);
                        
/*21. S? se ob?in? codul departamentelor ?i suma salariilor angaja?ilor care lucreaz? în
acestea, în ordine cresc?toare. Se consider? departamentele care au mai mult de 10
angaja?i ?i al c?ror cod este diferit de 30.*/

SELECT department_id , SUM(salary) "Suma salariilor"
FROM employees
WHERE department_id <> 30
GROUP BY department_id
HAVING COUNT(employee_id) > 10
ORDER BY 2;

/*22. Sa se afiseze codul, numele departamentului, numarul de angajati si salariul mediu
din departamentul respectiv, impreuna cu numele, salariul si jobul angajatilor din acel
departament. Se vor afi?a ?i departamentele f?r? angaja?i (outer join).*/
SELECT d.department_id , d.department_name , nr_angajati , medie_salariu , e.last_name , e.salary , e.job_id
FROM (SELECT department_id , last_name , salary , job_id
      FROM employees) e
FULL OUTER JOIN (SELECT department_id , department_name , COUNT(employee_id) as nr_angajati , AVG(salary) as medie_salariu
      FROM departments
      FULL OUTER JOIN employees USING(department_id) -- de ce nu afiseaza numele lui grant
      GROUP BY department_id , department_name) d
ON(e.department_id = d.department_id);

/*23. Scrieti o cerere pentru a afisa, pentru departamentele avand codul > 80, salariul total
pentru fiecare job din cadrul departamentului. Se vor afisa orasul, numele
departamentului, jobul si suma salariilor. Se vor eticheta coloanele corespunzator.*/
SELECT DISTINCT city , department_name , job_title , salariu_total as "TOTAL_SALARY"
FROM (SELECT department_name ,department_id, city , job_id
      FROM employees
      JOIN departments USING(department_id)
      JOIN locations USING(location_id)) d
JOIN (SELECT job_id , department_id, SUM(salary) as salariu_total
     FROM employees
     GROUP BY  department_id , job_id
     HAVING department_id > 80) j
ON(j.job_id = d.job_id AND j.department_id = d.department_id)
JOIN jobs jb ON(j.job_id = jb.job_id);
--In cazul in care punem department_id > 80 in WHERE, rezultatele sunt grupate dupa department_name

/*24. Care sunt angajatii care au mai avut cel putin doua joburi?*/
SELECT last_name , COUNT(employee_id) "Numar joburi"
FROM employees
JOIN job_history USING(employee_id)
GROUP BY last_name 
HAVING COUNT(employee_id) >=2;

/*25. S? se calculeze comisionul mediu din firm?, luând în considerare toate liniile din
tabel.*/
SELECT AVG(DECODE(commission_pct , NULL , 0 , commission_pct))
FROM employees;