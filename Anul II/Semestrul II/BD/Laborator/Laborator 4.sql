/*
S? se afi?eze minimul, maximul, suma ?i media salariilor pentru fiecare job.*/
SELECT MAX(salary) "Maxim" , MIN(salary) "Minim" , SUM(salary) "Suma" , Round(AVG(salary) , 2) "Media"
FROM employees;
-- daca nu puneam round afisa multe zecimale--

--daca vrem sa afisam mai multe rezultate(dupa departament etc) facem cu group by
SELECT MAX(salary) "Maxim" , MIN(salary) "Minim" , SUM(salary) "Suma" , ROUND(AVG(salary) , 2) "Media"
FROM employees 
GROUP BY job_id;

--S? se afi?eze num?rul de angaja?i pentru fiecare job.
SELECT COUNT(employee_id) , job_id "Job"
FROM employees
GROUP BY job_id;

--S? se determine num?rul de angaja?i care sunt ?efi. Etichetati coloana “Nr. manageri”.
SELECT COUNT(manager_id)
FROM employees
WHERE manager_id IS NOT NULL
GROUP BY manager_id; --numara de cate ori un angajat e sef peste altii

SELECT SUM(COUNT(DISTINCT manager_id))
FROM employees
WHERE manager_id IS NOT NULL
GROUP BY manager_id; --numara de cate ori un angajat e sef peste altii

SELECT COUNT(DISTINCT manager_id) "Nr manageri"
FROM employees
WHERE manager_id IS NOT NULL;

--S? se afi?eze diferen?a dintre cel mai mare si cel mai mic salariu. Etichetati coloana.
SELECT MAX(salary) - MIN(salary) "Diferenta"
FROM employees;

/*Scrie?i o cerere pentru a se afi?a numele departamentului, loca?ia, num?rul de
angaja?i ?i salariul mediu pentru angaja?ii din acel departament. Coloanele vor fi
etichetate corespunz?tor.*/
SELECT department_name , city , COUNT(employee_id) , AVG(salary)
FROM employees
JOIN departments d USING(department_id)
JOIN locations USING(location_id)
GROUP BY department_name , city; --trebuie sa apara daca nu e argument al unei functii de grup

/*S? se afi?eze codul ?i numele angaja?ilor care câstiga mai mult decât salariul mediu
din firm?. Se va sorta rezultatul în ordine descresc?toare a salariilor.*/

SELECT employee_id , last_name 
FROM employees
WHERE salary > (SELECT AVG(salary)
                FROM employees)
ORDER BY salary DESC;

/*9. Pentru fiecare ?ef, s? se afi?eze codul s?u ?i salariul celui mai prost platit
subordonat. Se vor exclude cei pentru care codul managerului nu este cunoscut. De
asemenea, se vor exclude grupurile în care salariul minim este mai mic de 1000$.
Sorta?i rezultatul în ordine descresc?toare a salariilor.*/
SELECT manager_id , MIN(salary)
FROM employees
WHERE manager_id IS NOT NULL 
GROUP BY manager_id
HAVING MIN(salary) > 3000;

--daca vrem sa afisam si employee_id
SELECT manager_id , MIN(salary) , employee_id --employee id are valori unice
--grupurile de linie contin doar cate o linie
FROM employees
WHERE manager_id IS NOT NULL 
GROUP BY manager_id , employee_id
HAVING MIN(salary) > 3000;

--daca vrem sa vedem si alte detalii ca sa nu fie la having
--facem o subcerere
SELECT ang.employee_id, ang.last_name, ang2.manager_id, minim
FROM (
	SELECT manager_id, MIN(salary) AS minim
	FROM employees
	WHERE manager_id IS NOT NULL
	GROUP BY manager_id
	HAVING MIN(salary) >= 3000
) ang2
JOIN employees ang ON ang.manager_id = ang2.manager_id
WHERE ang.salary = minim;

--in ang 2 afisez date despre o persoana care este sef
--in join ul exterior nu stie cine e manager id

/*
Pentru departamentele in care salariul maxim dep??e?te 3000$, s? se ob?in? codul,
numele acestor departamente ?i salariul maxim pe departament.*/
SELECT department_id , MAX(salary)
FROM employees
JOIN departments USING(department_id)
GROUP BY department_id 
HAVING MAX(salary) >= 3000;

/*Care este salariul mediu minim al job-urilor existente? Salariul mediu al unui job va fi
considerat drept media arirmetic? a salariilor celor care îl practic?.*/
SELECT MIN(AVG(salary))
FROM employees
GROUP BY job_id;
--calculeaza avg pentru fiecare job id si ia minimum dintre ele

/*S? se afi?eze codul, numele departamentului ?i suma salariilor pe departamente.*/
SELECT department_id , department_name , SUM(salary)
FROM employees
JOIN departments USING(department_id)
GROUP BY department_id , department_name;

/*S? se afi?eze maximul salariilor medii pe departamente.*/
SELECT ROUND(MAX(AVG(salary)) , 2)
FROM employees
GROUP BY department_id; --merge si cu max round

/*14. S? se obtina codul, titlul ?i salariul mediu al job-ului pentru care salariul mediu este
minim.*/
SELECT job_id , job_title , ROUND(AVG(salary) , 2)
FROM employees
JOIN jobs USING(job_id)
GROUP BY job_id , job_title
HAVING ROUND(AVG(salary) , 2) = (
                                SELECT ROUND(MIN(AVG(salary)) , 2)
                                FROM employees
                                GROUP BY job_id);

--15.S? se afi?eze salariul mediu din firm? doar dac? acesta este mai mare decât 2500.
--(clauza HAVING f?r? GROUP BY)

SELECT ROUND(AVG(salary) , 2)
FROM employees
HAVING AVG(salary) > 2500;

/*S? se afi?eze suma salariilor pe departamente ?i, în cadrul acestora, pe job-uri.*/
SELECT SUM(salary)
FROM employees
GROUP BY department_id , job_id;

SELECT SUM(salary)
FROM employees
GROUP BY job_id , department_id;

/*S? se afi?eze numele departamentului si cel mai mic salariu din departamentul
avand cel mai mare salariu mediu.*/
--nu e corect
SELECT department_name , MIN(salary)
FROM employees
JOIN departments USING(department_id)
GROUP BY department_name, salary
HAVING salary = (SELECT MAX(AVG(salary))
                    FROM employees
                    GROUP BY department_id);  
                    
SELECT MIN(salary)
FROM employees
GROUP BY department_id;

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

/*18.Sa se afiseze codul, numele departamentului si numarul de angajati care lucreaza
in acel departament pentru:
a) departamentele in care lucreaza mai putin de 4 angajati;
b) departamentul care are numarul maxim de angajati.*/
--a
SELECT d.department_id , department_name , COUNT(e.employee_id)
FROM employees e
JOIN departments d ON(e.department_id = d.department_id)
GROUP BY d.department_id , department_name
HAVING COUNT(*) < 4;

--b
SELECT d.department_id , department_name , COUNT(e.employee_id)
FROM employees e
JOIN departments d ON(e.department_id = d.department_id)
GROUP BY d.department_id , department_name
HAVING COUNT(*) = (SELECT MAX(COUNT(employee_id))
                    FROM employees
                    GROUP BY department_id);

/*19.Sa se afiseze salariatii care au fost angajati în aceea?i zi a lunii în care cei mai multi
dintre salariati au fost angajati.*/
SELECT last_name 
FROM employees
WHERE TO_CHAR(hire_date , 'DD') = (
SELECT TO_CHAR(hire_date , 'DD')
FROM employees
GROUP BY TO_CHAR(hire_date , 'DD')
HAVING COUNT(*) = (SELECT MAX(COUNT(*))
                    FROM employees
                    GROUP BY TO_CHAR(hire_date , 'DD')));
               


---- Laborator 4 -----
-- 20 --
SELECT COUNT(COUNT(department_id)) "Numar departamente"
FROM employees
GROUP BY department_id
HAVING COUNT(employee_id) > 15;

-- 21 --
SELECT department_id , SUM(salary)
FROM employees
GROUP BY department_id
HAVING COUNT(employee_id) > 10 AND department_id <> 30;

-- 22 --
SELECT e.department_id , department_name , nr , medie , last_name , salary
FROM employees e
RIGHT JOIN departments d ON (e.department_id = d.department_id)
LEFT JOIN (SELECT department_id , COUNT(employee_id) nr , ROUND(AVG(salary) , 2) medie
     FROM employees ---un tabel cu 3 coloane
     GROUP BY department_id) aux ON(d.department_id = aux.department_id);

-- 23 --
SELECT city , department_name , job_id , SUM(salary)
FROM departments
JOIN locations USING(location_id)
JOIN employees USING(department_id)
GROUP BY city , department_name , job_id , department_id
HAVING department_id > 80;


-- var 2 --
SELECT city , department_name , job_id , SUM(salary)
FROM departments
JOIN locations USING(location_id)
JOIN employees USING(department_id)
WHERE department_id > 80
GROUP BY city , department_name , job_id;

-- 24 --
SELECT last_name 
FROM employees
WHERE employee_id in
(SELECT employee_id
FROM job_history
GROUP BY employee_id
HAVING COUNT(job_id) >=2);
     
     
-- var 2 --
SELECT last_name
FROM employees e
JOIN (select employee_id , count(job_id) nr
    from job_history
    group by employee_id) aux
ON (e.employee_id = aux.employee_id)
where nr >= 2;

 -- 25 --
 SELECT SUM(commission_pct) / COUNT(*)
 FROM employees;
 
SELECT AVG(NVL(commission_pct , 0))
from employees;

SELECT AVG(DECODE(commission_pct , NULL , 0 , commission_pct))
FROM employees;

-- 27 --
SELECT job_id as "Job" , SUM(salary) as "Total" , 
(SELECT SUM(salary) FROM employees WHERE department_id = 30) AS "Dep30" , 
(SELECT SUM(salary) FROM employees WHERE department_id = 50) AS "Dep50" ,
(SELECT SUM(salary) FROM employees WHERE department_id = 80) AS "Dep80"
FROM employees
GROUP BY job_id;

-- var 2 mai corect --
-- cu decode --
SELECT job_id as "Job" , SUM(salary) as "Total" , 
SUM(DECODE(department_id , 30 , salary , 0)) AS "Dep30" , --daca nu e dep 30 sa nu adauge la suma nimic de asta e 0
SUM(DECODE(department_id , 50 , salary , 0)) AS "Dep50" ,
SUM(DECODE(department_id , 80 , salary , 0)) AS "Dep80"
FROM employees
GROUP BY job_id;

-- 28 --
SELECT COUNT(employee_id) , 
SUM(DECODE(TO_CHAR(hire_date , 'YYYY') , 1997 , 1 , 0)) as "1997" ,
SUM(DECODE(TO_CHAR(hire_date , 'YYYY') , 1998 , 1 , 0)) as "1998" ,
SUM(DECODE(TO_CHAR(hire_date , 'YYYY') , 1999 , 1 , 0)) as "1999" ,
SUM(DECODE(TO_CHAR(hire_date , 'YYYY') , 2000 , 1 , 0)) as "2000"
FROM employees;

-- 29 --
SELECT e.department_id , department_name , 
(SELECT COUNT(employee_id) FROM employees
WHERE department_id = e.department_id) as nr ,  -- trebuie sa ne asiguram ca retuneaza o singura iesire
(SELECT ROUND(AVG(salary) , 2) FROM employees
WHERE department_id = e.department_id) as medie , last_name , salary
FROM employees e
RIGHT JOIN departments d ON (e.department_id = d.department_id);

-- 30 --
SELECT department_id , department_name , suma
FROM (select SUM(salary) suma , department_id
    FROM employees
    GROUP BY department_id)
JOIN departments USING(department_id);

-- 31 ---
SELECT last_name , salary , e.department_id , salariu_mediu
FROM employees e
JOIN (SELECT AVG(salary) salariu_mediu , department_id
FROM employees
GROUP BY department_id) aux
ON (e.department_id = aux.department_id);

-- 32 --
SELECT last_name , salary , e.department_id , salariu_mediu , nr_angajati
FROM employees e
JOIN (SELECT AVG(salary) salariu_mediu , department_id , COUNT(employee_id) nr_angajati
FROM employees
GROUP BY department_id) aux
ON (e.department_id = aux.department_id);


-- 33 --
SELECT department_name , last_name , salary
FROM employees e
JOIN departments d
ON (d.department_id = e.department_id)
JOIN (SELECT department_id , MIN(salary) minim
    FROM employees 
    GROUP BY department_id) aux
ON(d.department_id = aux.department_id AND salary = minim);
-- putem pune si la where salary = minim --

-- v2 --
-- subcerere in where
SELECT department_name , last_name , salary
FROM employees e
JOIN departments d
ON (d.department_id = e.department_id)
WHERE (e.department_id , salary) IN
    (SELECT department_id , MIN(salary) minim
    FROM employees 
    GROUP BY department_id);


-- 34 --
SELECT e.department_id , department_name , nr , medie , last_name , salary , job_id
FROM employees e , departments d ,
(SELECT department_id , COUNT(employee_id) nr , ROUND(AVG(salary) , 2) medie
FROM employees ---un tabel cu 3 coloane
    GROUP BY department_id) aux 
WHERE e.department_id(+) = d.department_id AND d.department_id = aux.department_id(+);
-- nu merge daca sunt puse in cadrul aceleiasi egalitati
-- punem + in dreptul tabelei in care vrem valorile null

--        ROLLUP
/*
as fi scris 3 instructiuni select si faceam reuniunea lor
nu e eficient dpdv al performantei
tabelele vor fi accesate de 3 ori
rollup:
daca am n coloane in lista de argumente calculeaza niste totaluri ca si cum am fi scris la group by
apoi face alte totaluri tinand cont de n - 1
n + 1 rez = + 1 rezultatul in care nu mai tine cont de niciun criteriu
-celula goala inseamna ca nu se tine cont de anul angajarii si se face suma totala pe departament
-ultimul rand:nu a mai tinut cont de niciun criteriu, a adunat salariilor tuturor angajatilor
*/

SELECT department_id , TO_CHAR(hire_date , 'YYYY') , SUM(salary)
FROM employees
WHERE department_id < 50
GROUP BY ROLLUP(department_id , TO_CHAR(hire_date , 'YYYY'));

-- var 2--
SELECT department_id , TO_CHAR(hire_date , 'YYYY') , SUM(salary)
FROM employees
WHERE department_id < 50
GROUP BY department_id , TO_CHAR(hire_date , 'YYYY')

UNION

SELECT department_id , null , SUM(salary) -- ca sa avem neapart 3 coloane si sa nu ne ceara la group by
FROM employees
WHERE department_id < 50
GROUP BY department_id

UNION 

SELECT null , null , SUM(salary)
FROM employees
WHERE department_id < 50;

--performanta e imbunatatita folosind rollup

--- EXEMPLU CUBE ----
SELECT department_id , TO_CHAR(hire_date , 'YYYY') , SUM(salary)
FROM employees
WHERE department_id < 50
GROUP BY CUBE(department_id , TO_CHAR(hire_date , 'YYYY'));

-- v2 --
SELECT department_id , TO_CHAR(hire_date , 'YYYY') , SUM(salary)
FROM employees
WHERE department_id < 50
GROUP BY department_id , TO_CHAR(hire_date , 'YYYY')

UNION

SELECT department_id , null , SUM(salary) -- ca sa avem neapart 3 coloane si sa nu ne ceara la group by
FROM employees
WHERE department_id < 50
GROUP BY department_id

UNION

SELECT null , TO_CHAR(hire_date , 'YYYY') , SUM(salary)
FROM employees
WHERE department_id < 50
GROUP BY TO_CHAR(hire_date , 'YYYY')

UNION 

SELECT null , null , SUM(salary)
FROM employees
WHERE department_id < 50;


-- ex 3
--nu vrem sa afisam totalurile pe itnreaga companie
SELECT department_id , TO_CHAR(hire_date , 'YYYY') , SUM(salary)
FROM employees
WHERE department_id < 50
GROUP BY GROUPING SETS((department_id , TO_CHAR(hire_date , 'YYYY')) , (department_id));
--perechea () e aceeasi cu a lui rollup
SELECT department_id , TO_CHAR(hire_date , 'YYYY') , SUM(salary)
FROM employees
WHERE department_id < 50
GROUP BY GROUPING SETS((department_id , TO_CHAR(hire_date , 'YYYY')) , (department_id) , ());

--- simulam cube
SELECT department_id , TO_CHAR(hire_date , 'YYYY') , SUM(salary)
FROM employees
WHERE department_id < 50
GROUP BY GROUPING SETS((department_id , TO_CHAR(hire_date , 'YYYY')) , (department_id) , (TO_CHAR(hire_date , 'YYYY')) , ());