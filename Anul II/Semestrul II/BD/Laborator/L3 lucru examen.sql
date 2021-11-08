/*1.Scrieti o cerere pentru a se afisa numele, luna (în litere) ?i anul angaj?rii pentru toti
salariatii din acelasi departament cu Gates, al c?ror nume con?ine litera “a”. Se va
exclude Gates. Se vor da 2 solu?ii pentru determinarea apari?iei literei “A” în nume. De
asemenea, pentru una din metode se va da ?i varianta join-ului conform standardului
SQL99.*/
SELECT e1.last_name, TO_CHAR(e1.hire_date, 'MONTH YYYY')
FROM employees e1
JOIN employees e2 ON (e1.department_id = e2.department_id AND lower(e2.last_name) LIKE 'gates' AND e1.employee_id <> e2.employee_id)
WHERE LOWER(e1.last_name) LIKE '%a%';


/*2.Sa se afiseze codul ?i numele angaja?ilor care lucreaz? în acelasi departament cu
cel pu?in un angajat al c?rui nume con?ine litera “t”. Se vor afi?a, de asemenea, codul ?i
numele departamentului respectiv. Rezultatul va fi ordonat alfabetic dup? nume. Salva?i
cererea într-un fi?ier p2l3.sql.*/
SELECT employee_id, last_name, d.department_id, department_name
FROM employees e
JOIN departments d ON (d.department_id = e.department_id)
WHERE EXISTS(SELECT 1
FROM employees
WHERE department_id = e.department_id
AND employee_id <> e.employee_id
AND lower(last_name) LIKE '%t%')
ORDER BY 2;


SELECT DISTINCT e1.employee_id , e1.last_name , d.department_id , d.department_name
FROM employees e1
JOIN departments d ON (e1.department_id = d.department_id)
JOIN employees e2 ON(e2.department_id = d.department_id AND UPPER(e2.last_name) LIKE '%T%' AND e1.employee_id <> e2.employee_id)
ORDER BY 2;

/*3.Sa se afiseze numele, salariul, titlul job-ului, ora?ul ?i ?ara în care lucreaz? angajatii
condusi direct de King.*/
SELECT last_name, salary, job_title, city, country_name
FROM employees emp
JOIN departments USING(department_id)
JOIN jobs USING(job_id)
JOIN locations USING(location_id)
JOIN countries USING(country_id)
WHERE emp.manager_id IN (SELECT employee_id FROM employees WHERE lower(last_name) = 'king');

SELECT emp.last_name, emp.salary, job_title, city, country_name
FROM employees emp
JOIN departments USING(department_id)
JOIN jobs USING(job_id)
JOIN locations USING(location_id)
JOIN countries USING(country_id)
JOIN employees emp2 ON(emp.manager_id = emp2.employee_id AND lower(emp2.last_name) = 'king');

/*5.Sa se afiseze codul departamentului, numele departamentului, numele si job-ul
tuturor angajatilor din departamentele al c?ror nume con?ine ?irul ‘ti’. De asemenea, se
va lista salariul angaja?ilor, în formatul “$99,999.00”. Rezultatul se va ordona alfabetic
dup? numele departamentului, ?i în cadrul acestuia, dup? numele angaja?ilor.*/
SELECT e.department_id, department_name, last_name, job_id, CONCAT('$', ROUND(salary, 2))
FROM employees e
JOIN departments d ON(d.department_id = e.department_id)
WHERE LOWER(department_name) like '%ti%' 
ORDER BY department_name, last_name;

/*6.Sa se afiseze numele angajatilor, numarul departamentului, numele departamentului,
ora?ul si job-ul tuturor salariatilor al caror departament este localizat in Oxford.*/
SELECT last_name, d.department_id, department_name, city, job_id
FROM employees e
JOIN departments d ON(d.department_id = e.department_id)
JOIN locations loc ON(loc.location_id = d.location_id)
WHERE INITCAP(city) LIKE 'Oxford';

SELECT e.last_name , e.department_id , d.department_name , loc.city , j.job_title
FROM jobs j
JOIN employees e ON(e.job_id = j.job_id)
JOIN departments d ON(e.department_id = d.department_id)
JOIN locations loc ON(d.location_id = loc.location_id AND INITCAP(loc.city) LIKE 'Oxford');

/*7.Sa se modifice fisierul p2l3.sql pentru a afisa codul, numele si salariul tuturor
angajatilor care castiga mai mult decat salariul mediu pentru job-ul corespunz?tor si
lucreaza intr-un departament cu cel putin unul din angajatii al caror nume contine litera
“t”. Salvati ca p7l3.sql. Executati cererea.*/
-- prima varianta elimina persoanele care au in nume litera t si verifica daca mai exista inca unul cu litera t
SELECT DISTINCT e1.employee_id , e1.last_name , d.department_id , d.department_name
FROM employees e1
JOIN departments d ON (e1.department_id = d.department_id)
JOIN employees e2 ON(e2.department_id = d.department_id AND UPPER(e2.last_name) LIKE '%T%' AND e1.employee_id <> e2.employee_id)
WHERE e1.salary > (SELECT AVG(salary) FROM employees WHERE e1.job_id = job_id)
ORDER BY 2;

SELECT DISTINCT e1.employee_id , e1.last_name , e1.salary
FROM jobs j
JOIN employees e1 ON (j.job_id = e1.job_id AND e1.salary > (SELECT AVG(e2.salary) FROM employees e2 WHERE e2.job_id = j.job_id))
JOIN departments d ON (e1.department_id = d.department_id)
JOIN employees e3 ON(e3.department_id = d.department_id AND UPPER(e3.last_name) LIKE '%T%')
ORDER BY 2;


/*8.S? se afi?eze numele salaria?ilor ?i numele departamentelor în care lucreaz?. Se vor
afi?a ?i salaria?ii care nu au asociat un departament. (right outer join, 2 variante).*/
SELECT last_name, department_name
FROM employees 
LEFT JOIN departments USING(department_id);

/*11.Se cer codurile departamentelor al c?ror nume con?ine ?irul “re” sau în care
lucreaz? angaja?i având codul job-ului “SA_REP”.*/
SELECT DISTINCT department_id, department_name          --!!!! ATENTIE, NU E CORECT. POATE SUNT DEP IN CARE NU LUCREAZA ANGAJATI DELOC
FROM departments
JOIN employees USING(department_id)
WHERE lower(department_name) LIKE '%re%' OR lower(job_id) LIKE 'sa_rep';


SELECT department_id, department_name         
FROM departments
JOIN employees USING(department_id)
WHERE lower(job_id) LIKE 'sa_rep'
UNION
SELECT DISTINCT department_id, department_name 
FROM departments
WHERE lower(department_name) LIKE '%re%';

/*13.Sa se obtina codurile departamentelor in care nu lucreaza nimeni (nu este introdus
nici un salariat in tabelul employees). Se cer dou? solu?ii.*/
SELECT department_id
FROM departments
MINUS
SELECT department_id
FROM employees;

SELECT department_id
FROM departments
WHERE department_id NOT IN (SELECT NVL(department_id, 0) FROM employees);

/*14.Se cer codurile departamentelor al c?ror nume con?ine ?irul “re” ?i în care lucreaz?
angaja?i având codul job-ului “HR_REP”.*/
SELECT department_id, department_name
FROM departments
JOIN employees USING(department_id)
WHERE lower(department_name) like '%re%'  and lower(job_id) LIKE 'hr_rep';
-- sau cu intersect

/*15. S? se determine codul angaja?ilor, codul job-urilor ?i numele celor al c?ror salariu
este mai mare decât 3000 sau este egal cu media dintre salariul minim ?i cel maxim
pentru job-ul respectiv.*/
SELECT employee_id, e.job_id, last_name, salary, min_salary, max_salary
FROM employees e
JOIN jobs j ON(e.job_id = j.job_id)
WHERE salary > 3000 OR salary = (j.min_salary + j.max_salary)/2;


SELECT employee_id, job_id, last_name
FROM employees
WHERE (job_id, salary)
IN (SELECT job_id, salary
FROM employees
WHERE salary > 3000
UNION
SELECT job_id, (min_salary+max_salary)/2
FROM jobs);

/*16. Folosind subcereri, s? se afi?eze numele ?i data angaj?rii pentru salaria?ii care au
fost angaja?i dup? Gates.*/
SELECT last_name, hire_date
FROM employees
WHERE hire_date > (SELECT hire_date
FROM employees
WHERE lower(last_name) LIKE 'gates');

/*17. Folosind subcereri, scrie?i o cerere pentru a afi?a numele ?i salariul pentru to?i
colegii (din acela?i departament) lui Gates. Se va exclude Gates.*/
SELECT last_name, salary
FROM employees
WHERE lower(last_name) <> 'gates'
AND department_id = (SELECT department_id FROM employees
WHERE lower(last_name) LIKE 'gates');

WITH gates AS (SELECT department_id dep, employee_id cod FROM employees
WHERE lower(last_name) LIKE 'gates')
SELECT last_name, salary
FROM employees e CROSS JOIN gates
WHERE e.employee_id <> cod
AND e.department_id = dep;

/*18. Folosind subcereri, s? se afi?eze numele ?i salariul angaja?ilor condu?i direct de
pre?edintele companiei (acesta este considerat angajatul care nu are manager).*/
SELECT last_name, salary
FROM employees
WHERE manager_id = (SELECT employee_id FROM employees WHERE manager_id IS NULL);

/*19. Scrieti o cerere pentru a afi?a numele, codul departamentului si salariul angajatilor
al caror num?r de departament si salariu coincid cu numarul departamentului si salariul
unui angajat care castiga comision.*/
SELECT last_name, department_id, salary
FROM employees
WHERE (department_id, salary) IN (SELECT department_id, salary FROM employees WHERE commission_pct IS NOT NULL);

SELECT e.last_name , e.department_id , e.salary
FROM employees e
WHERE e.department_id in (SELECT department_id
                        FROM employees
                        WHERE commission_pct IS NOT NULL)
AND salary in (SELECT salary 
              FROM employees
              WHERE department_id = e.department_id AND commission_pct IS NOT NULL);
              
/* 21. Scrieti o cerere pentru a afisa angajatii care castiga mai mult decat oricare
functionar (job-ul con?ine ?irul “CLERK”). Sortati rezultatele dupa salariu, in ordine
descrescatoare. (ALL)*/
SELECT last_name, salary
FROM employees
WHERE salary > ALL (SELECT salary FROM employees WHERE lower(job_id) LIKE '%clerk%')
ORDER BY 2 DESC;


/*22. Scrie?i o cerere pentru a afi?a numele, numele departamentului ?i salariul angaja?ilor
care nu câ?tig? comision, dar al c?ror ?ef direct coincide cu ?eful unui angajat care
câ?tig? comision.*/
SELECT last_name, department_ID, salary
FROM employees
WHERE commission_pct IS NULL
AND manager_id IN (SELECT manager_id FROM employees WHERE commission_pct IS NOT NULL);

/*23. Sa se afiseze numele, departamentul, salariul ?i job-ul tuturor angajatilor al caror
salariu si comision coincid cu salariul si comisionul unui angajat din Oxford.*/
SELECT last_name, department_ID, salary, job_id
FROM employees
WHERE (salary, commission_pct) IN (SELECT salary, commission_pct FROM employees
                                    JOIN departments USING(department_id)
                                    JOIN locations USING(location_id)
                                    WHERE lower(city) LIKE 'oxford');
                                    
/*24. S? se afi?eze numele angaja?ilor, codul departamentului ?i codul job-ului salaria?ilor
al c?ror departament se afl? în Toronto.*/
SELECT last_name, department_ID, salary, job_id
FROM employees
JOIN departments USING(department_id)
JOIN locations USING(location_id)
WHERE lower(city) LIKE 'toronto';

SELECT last_name , department_id , job_id
FROM employees
WHERE department_id = (SELECT d.department_id 
                        FROM departments d
                        JOIN locations loc ON(d.location_id = loc.location_id AND INITCAP(loc.city) LIKE 'Toronto'));