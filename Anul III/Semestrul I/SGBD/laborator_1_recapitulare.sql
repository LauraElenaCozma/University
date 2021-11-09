/*S? se afi?eze numele ?i data angaj?rii pentru fiecare salariat care a fost angajat în
1987. Se cer 2 solu?ii: una în care se lucreaz? cu formatul implicit al datei ?i alta prin
care se formateaz? data.*/
SELECT last_name, hire_date
FROM employees
WHERE TO_CHAR(hire_date, 'YYYY') = 1987;

SELECT last_name, hire_date
FROM employees
WHERE EXTRACT(year FROM hire_date) = 1987;

SELECT last_name, hire_date
FROM employees
WHERE hire_date LIKE '%87%';

/*7.S? se afi?eze numele, salariul ?i comisionul pentru toti salaria?ii care câ?tig? comision.
S? se sorteze datele în ordine descresc?toare a salariilor ?i comisioanelor.*/
SELECT last_name, salary, commission_pct
FROM employees
WHERE commission_pct IS NOT NULL
ORDER BY salary DESC, commission_pct DESC;

/*9. S? se listeze numele tuturor angajatilor care au a treia liter? din nume ‘A’.*/
SELECT last_name
FROM employees
WHERE UPPER(last_name) LIKE '__A%';

/*10. S? se listeze numele tuturor angajatilor care au 2 litere ‘L’ in nume ?i lucreaz? în
departamentul 30 sau managerul lor este 102.*/
SELECT last_name, department_id, manager_id
FROM employees
WHERE UPPER(last_name) LIKE '%L%L%' AND department_id = 30 OR manager_id = 102;

/*11. S? se afiseze numele, job-ul si salariul pentru toti salariatii al caror job con?ine ?irul
“CLERK” sau “REP” ?i salariul nu este egal cu 1000, 2000 sau 3000. (operatorul NOT
IN)*/
SELECT last_name, job_id, SALARY
FROM employees
WHERE salary NOT IN (1000, 2000, 3000) AND (UPPER(job_id) LIKE '%CLERK%' OR UPPER(job_id) LIKE '%REP%');

/*12.S? se afi?eze numele salaria?ilor ?i numele departamentelor în care lucreaz?. Se vor
afi?a ?i salaria?ii care nu au asociat un departament.*/
SELECT last_name, department_name
FROM employees
LEFT JOIN departments USING(department_id);

/*13.S? se afi?eze numele departamentelor ?i numele salaria?ilor care lucreaz? în ele. Se
vor afi?a ?i departamentele care nu au salaria?i.*/
SELECT department_name, last_name
FROM employees
RIGHT JOIN departments USING (department_id);

/*14. S? se afi?eze codul angajatului ?i numele acestuia, împreun? cu numele ?i codul
?efului s?u direct.*/
SELECT e1.employee_id "Cod angajat", e1.last_name "Nume angajat", e2.employee_id "Cod sef", e2.first_name "Nume sef"
FROM employees e1
INNER JOIN employees e2 ON (e1.manager_id = e2.employee_id);

/*15. S? se modifice cererea anterioar? pentru a afi?a to?i salaria?ii, inclusiv cei care nu au
?ef.*/
SELECT e1.employee_id "Cod angajat", e1.last_name "Nume angajat", e2.employee_id "Cod sef", e2.first_name "Nume sef"
FROM employees e1
LEFT JOIN employees e2 ON (e1.manager_id = e2.employee_id);

/*16. S? se ob?in? codurile departamentelor în care nu lucreaza nimeni (nu este introdus
nici un salariat în tabelul employees).*/
SELECT department_id
FROM departments
WHERE department_id NOT IN (SELECT NVL(department_id, 0)
                                    FROM employees);
                                
SELECT department_id
FROM departments
MINUS
SELECT department_id
FROM employees;

/*17. S? se afi?eze cel mai mare salariu, cel mai mic salariu, suma ?i media salariilor
tuturor angaja?ilor. Eticheta?i coloanele Maxim, Minim, Suma, respectiv Media. Sa se
rotunjeasca rezultatele.*/
SELECT MAX(salary) "Maxim", MIN(salary) "Minim", ROUND(AVG(salary)) "Media", SUM(Salary) "Suma"
FROM employees;


/*18. S? se afi?eze minimul, maximul, suma ?i media salariilor pentru fiecare job.*/
SELECT MAX(salary) "Maxim", MIN(salary) "Minim", ROUND(AVG(salary)) "Media", SUM(Salary) "Suma", job_id
FROM employees
GROUP BY job_id
ORDER BY 2 DESC;

/*19. S? se afi?eze num?rul de angaja?i pentru fiecare job.*/
SELECT COUNT(employee_id), job_id
FROM employees
GROUP BY job_id;
/*20. Scrie?i o cerere pentru a se afi?a numele departamentului, loca?ia, num?rul de
angaja?i ?i salariul mediu pentru angaja?ii din acel departament. Coloanele vor fi
etichetate corespunz?tor.*/
SELECT department_name, city, COUNT(employee_id), ROUND(AVG(salary))
FROM employees
JOIN departments USING(department_id)
JOIN locations USING(location_id)
GROUP BY department_name, city;

/*21. S? se afi?eze codul ?i numele angaja?ilor care câstiga mai mult decât salariul mediu
din firm?. Se va sorta rezultatul în ordine descresc?toare a salariilor.*/
SELECT employee_id, last_name, salary
FROM employees
WHERE salary > (SELECT AVG(salary) FROM employees)
ORDER BY salary DESC;