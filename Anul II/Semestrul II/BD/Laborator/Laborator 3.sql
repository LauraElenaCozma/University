
----- LABORATOR 3 ------

/*Exercitiul 1
1. Scrieti o cerere pentru a se afisa numele, luna (în litere) ?i anul angaj?rii pentru toti
salariatii din acelasi departament cu Gates, al c?ror nume con?ine litera “a”. Se va
exclude Gates. Se vor da 2 solu?ii pentru determinarea apari?iei literei “A” în nume. De
asemenea, pentru una din metode se va da ?i varianta join-ului conform standardului
SQL99.*/

SELECT e1.last_name , TO_CHAR(e1.hire_date , 'month - yyyy') 
FROM employees e1
JOIN employees e2 ON(e1.department_id = e2.department_id AND UPPER(e2.last_name) LIKE 'GATES' AND LOWER(e1.last_name) LIKE '%a%' AND UPPER(e1.last_name) NOT LIKE 'GATES');

/*Exercitiul 2
Sa se afiseze codul ?i numele angaja?ilor care lucreaz? în acelasi departament cu
cel pu?in un angajat al c?rui nume con?ine litera “t”. Se vor afi?a, de asemenea, codul ?i
numele departamentului respectiv. Rezultatul va fi ordonat alfabetic dup? nume. Salva?i
cererea într-un fi?ier p2l3.sql.
*/
SELECT DISTINCT e1.employee_id , e1.last_name , d.department_id , d.department_name
FROM employees e1
JOIN departments d ON (e1.department_id = d.department_id)
JOIN employees e2 ON(e2.department_id = d.department_id AND UPPER(e2.last_name) LIKE '%T%')
ORDER BY 2;

/*Exercitiul 3
Sa se afiseze numele, salariul, titlul job-ului, ora?ul ?i ?ara în care lucreaz? angajatii
condusi direct de King.*/
SELECT e.last_name , e.salary , j.job_title , loc.city , c.country_name
FROM jobs j
JOIN employees e ON (e.job_id = j.job_id)
JOIN departments d ON (d.department_id = e.department_id)
JOIN locations loc ON (loc.location_id = d.location_id)
JOIN countries c ON (c.country_id = loc.country_id)
JOIN employees e2 ON(e.manager_id = e2.employee_id AND upper(e2.last_name) LIKE 'KING');

/*Exercitiul 4
Executa?i comenzile SQL*Plus urm?toare:
SET LINESIZE 120
SET PAGESIZE 20

dup? care rula?i comanda de la exerci?iul precedent (e suficient “/” pentru rularea buffer-
ului). Ce observa?i? Ce efect au comenzile SET LINESIZE n, SET PAGESIZE n?*/
SET LINESIZE 120
SET PAGESIZE 20

/*Exercitiul 5
Sa se afiseze codul departamentului, numele departamentului, numele si job-ul
tuturor angajatilor din departamentele al c?ror nume con?ine ?irul ‘ti’. De asemenea, se
va lista salariul angaja?ilor, în formatul “$99,999.00”. Rezultatul se va ordona alfabetic
dup? numele departamentului, ?i în cadrul acestuia, dup? numele angaja?ilor.*/
SELECT d.department_id , d.department_name , e.last_name , j.job_title , CONCAT('$' , e.salary)
FROM jobs j
JOIN employees e ON (j.job_id = e.job_id)
JOIN departments d ON (e.department_id = d.department_id AND UPPER(d.department_name) LIKE '%TI%')
ORDER BY d.department_name ASC , e.last_name ASC;

/*Exercitiul 6
Sa se afiseze numele angajatilor, numarul departamentului, numele departamentului,
ora?ul si job-ul tuturor salariatilor al caror departament este localizat in Oxford.*/

SELECT e.last_name , e.department_id , d.department_name , loc.city , j.job_title
FROM jobs j
JOIN employees e ON(e.job_id = j.job_id)
JOIN departments d ON(e.department_id = d.department_id)
JOIN locations loc ON(d.location_id = loc.location_id AND INITCAP(loc.city) LIKE 'Oxford');

/*Exercitiul 7
Sa se modifice fisierul p2l3.sql pentru a afisa codul, numele si salariul tuturor
angajatilor care castiga mai mult decat salariul mediu pentru job-ul corespunz?tor si
lucreaza intr-un departament cu cel putin unul din angajatii al caror nume contine litera
“t”. Salvati ca p7l3.sql. Executati cererea.*/
SELECT DISTINCT e1.employee_id , e1.last_name , e1.salary
FROM jobs j
JOIN employees e1 ON (j.job_id = e1.job_id AND e1.salary > (SELECT AVG(e2.salary) FROM employees e2 WHERE e2.job_id = j.job_id))
JOIN departments d ON (e1.department_id = d.department_id)
JOIN employees e3 ON(e3.department_id = d.department_id AND UPPER(e3.last_name) LIKE '%T%');

/*Exercitiul 8
S? se afi?eze numele salaria?ilor ?i numele departamentelor în care lucreaz?. Se vor
afi?a ?i salaria?ii care nu au asociat un departament. (right outer join, 2 variante).*/
--- varianta 1 ---
SELECT e.last_name , d.department_name 
FROM departments d
RIGHT OUTER JOIN employees e ON(e.department_id = d.department_id);
--- varianta 2 ---
SELECT e.last_name , d.department_name 
FROM employees e
LEFT OUTER JOIN departments d ON(e.department_id = d.department_id);

/*Exercitiul 9
S? se afi?eze numele departamentelor ?i numele salaria?ilor care lucreaz? în ele. Se
vor afi?a ?i departamentele care nu au salaria?i.*/
--- varianta 1 ---
SELECT d.department_name , e.last_name
FROM departments d
LEFT OUTER JOIN employees e ON(e.department_id = d.department_id);

--- varianta 2 ---
SELECT d.department_name , e.last_name
FROM employees e
RIGHT OUTER JOIN departments d ON(e.department_id = d.department_id);

/*Exercitiul 10
Cum se poate implementa full outer join?*/
--- varianta 1 ---
SELECT d.department_name , e.last_name
FROM departments d
LEFT OUTER JOIN employees e ON(e.department_id = d.department_id)
UNION
SELECT  d.department_name , e.last_name 
FROM departments d
RIGHT OUTER JOIN employees e ON(e.department_id = d.department_id);

--- varianta 2 --- 
SELECT DISTINCT d.department_name , e.last_name
FROM employees e
FULL OUTER JOIN departments d ON(e.department_id = d.department_id);


/*Exercitiul 11
Se cer codurile departamentelor al c?ror nume con?ine ?irul “re” sau în care
lucreaz? angaja?i având codul job-ului “SA_REP”.
Cum este ordonat rezultatul?
R: Crescator dupa codul departamentului*/
SELECT department_id , department_name
FROM departments
WHERE UPPER(department_name) LIKE '%RE%'
UNION
SELECT d.department_id , d.department_name
FROM departments d
JOIN employees e ON(d.department_id = e.department_id AND UPPER(e.job_id) = 'SA_REP');


/*Exercitiul 12
Ce se întâmpl? dac? înlocuim UNION cu UNION ALL în comanda precedent??*/

--- R: Apar duplicate si se pierde ordonarea
SELECT department_id , department_name
FROM departments
WHERE UPPER(department_name) LIKE '%RE%'
UNION ALL
SELECT d.department_id , d.department_name
FROM departments d
JOIN employees e ON(d.department_id = e.department_id AND UPPER(e.job_id) = 'SA_REP');

/*Exercitiul 13
Sa se obtina codurile departamentelor in care nu lucreaza nimeni (nu este introdus
nici un salariat in tabelul employees). Se cer dou? solu?ii.*/

---- varianta 1 Fara NVL----
SELECT department_id “Cod departament”
FROM departments
MINUS
SELECT department_id
FROM employees;

---- varianta 2 Cu NVL ----
-- Se foloseste NVL pentru ca department_id poate fi null ---
SELECT department_id
FROM departments
WHERE department_id NOT IN (SELECT DISTINCT NVL(department_id,0)
FROM employees);

/*Exercitiul 14 
Se cer codurile departamentelor al c?ror nume con?ine ?irul “re” ?i în care lucreaz?
angaja?i având codul job-ului “HR_REP”.*/
SELECT department_id
FROM departments
WHERE UPPER(department_name) LIKE '%RE%'
INTERSECT
SELECT d.department_id
FROM departments d
JOIN employees e ON(d.department_id = e.department_id AND UPPER(e.job_id) LIKE 'HR_REP'); 

/*Exercitiul 15
S? se determine codul angaja?ilor, codul job-urilor ?i numele celor al c?ror salariu
este mai mare decât 3000 sau este egal cu media dintre salariul minim ?i cel maxim
pentru job-ul respectiv.*/
SELECT employee_id, job_id, last_name
FROM employees
WHERE (job_id, salary)
IN (SELECT job_id, salary
FROM employees
WHERE salary > 3000
UNION
SELECT job_id, (min_salary+max_salary)/2
FROM jobs);

/*Exercitiul 16
Folosind subcereri, s? se afi?eze numele ?i data angaj?rii pentru salaria?ii care au
fost angaja?i dup? Gates.*/
SELECT last_name, hire_date
FROM employees
WHERE hire_date > (SELECT hire_date
                    FROM employees
                    WHERE INITCAP(last_name)=’Gates’);

/*Exercitiul 17
Folosind subcereri, scrie?i o cerere pentru a afi?a numele ?i salariul pentru to?i
colegii (din acela?i departament) lui Gates. Se va exclude Gates.*/
SELECT last_name, salary
FROM employees
WHERE department_id IN (SELECT department_id
                        FROM employees
                        WHERE LOWER(last_name)=’gates’)
AND LOWER(last_name) <> ’gates’;

/*Exercitiul 18
Folosind subcereri, s? se afi?eze numele ?i salariul angaja?ilor condu?i direct de
pre?edintele companiei (acesta este considerat angajatul care nu are manager).*/
SELECT last_name , salary
FROM employees
WHERE manager_id = (SELECT employee_id
                    FROM employees
                    WHERE manager_id IS NULL);
                    
/*Exercitiul 19
Scrieti o cerere pentru a afi?a numele, codul departamentului si salariul angajatilor
al caror num?r de departament si salariu coincid cu numarul departamentului si salariul
unui angajat care castiga comision.*/
select * from employees;
SELECT e.last_name , e.department_id , e.salary
FROM employees e
WHERE e.department_id in (SELECT department_id
                        FROM employees
                        WHERE commission_pct IS NOT NULL)
AND salary in (SELECT salary 
              FROM employees
              WHERE department_id = e.department_id AND commission_pct IS NOT NULL);

/*Exercitiul 20
Rezolva?i problema 7 utilizând subcereri.*/
SELECT DISTINCT e1.employee_id , e1.last_name , e1.salary
FROM employees e1
WHERE e1.salary > (SELECT AVG(salary) 
                    FROM employees
                    WHERE e1.job_id = job_id)
AND department_id IN (SELECT d.department_id
                      FROM departments d
                      JOIN employees e ON (d.department_id = e.department_id AND UPPER(e.last_name) LIKE '%T%'));

/*Exercitiul 21
Scrieti o cerere pentru a afisa angajatii care castiga mai mult decat oricare
functionar (job-ul con?ine ?irul “CLERK”). Sortati rezultatele dupa salariu, in ordine
descrescatoare. (ALL)*/
SELECT last_name 
FROM employees
WHERE salary > ALL(SELECT salary
                FROM employees
                WHERE UPPER(job_id) LIKE '%CLERK%')
ORDER BY salary DESC;
-- cu any
SELECT last_name 
FROM employees
WHERE salary > ANY(SELECT salary
                FROM employees
                WHERE UPPER(job_id) LIKE '%CLERK%')
ORDER BY salary DESC;
 --- R: exista o valoare care sa satisfaca conditia, nu toate ---
 
/*Exercitiul 22
Scrie?i o cerere pentru a afi?a numele, numele departamentului ?i salariul angaja?ilor
care nu câ?tig? comision, dar al c?ror ?ef direct coincide cu ?eful unui angajat care
câ?tig? comision.*/
SELECT e.last_name , d.department_name, e.salary
FROM employees e
JOIN departments d ON(d.department_id = e.department_id)
WHERE e.commission_pct IS NULL AND e.manager_id IN (SELECT manager_id 
                                               FROM employees
                                                WHERE commission_pct IS NOT NULL);
                                                
/*Exercitiul 23
Sa se afiseze numele, departamentul, salariul ?i job-ul tuturor angajatilor al caror
salariu si comision coincid cu salariul si comisionul unui angajat din Oxford.*/
SELECT last_name , department_id , salary , job_id , commission_pct
FROM employees 
WHERE salary IN (SELECT e.salary
                FROM employees e
                JOIN departments d ON(e.department_id = d.department_id)
                JOIN locations loc ON(loc.location_id = d.location_id AND UPPER(loc.city) LIKE 'OXFORD'))
AND commission_pct IN (SELECT e.commission_pct
                FROM employees e
                JOIN departments d ON(e.department_id = d.department_id)
                JOIN locations loc ON(loc.location_id = d.location_id AND UPPER(loc.city) LIKE 'OXFORD')
                WHERE e.salary = salary);
            
/*Exercitiul 24
S? se afi?eze numele angaja?ilor, codul departamentului ?i codul job-ului salaria?ilor
al c?ror departament se afl? în Toronto.*/
SELECT last_name , department_id , job_id
FROM employees
WHERE department_id = (SELECT d.department_id 
                        FROM departments d
                        JOIN locations loc ON(d.location_id = loc.location_id AND INITCAP(loc.city) LIKE 'Toronto'));

