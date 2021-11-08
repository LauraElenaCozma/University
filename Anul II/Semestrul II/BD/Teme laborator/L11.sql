-- Tema laborator 11 din laboratorul 7--

-- Exercitiul 13 --
/*S? se creeze tabelul EMP0_PNU cu aceea?i structur? ca tabelul EMPLOYEES (f?r? constrângeri),
dar f?r? nici o înregistrare. Copia?i din tabelul EMPLOYEES:
- în tabelul EMP0_PNU salaria?ii care lucreaz? în departamentul 80;
- în tabelul EMP1_PNU salaria?ii care au salariul mai mic decât 5000;
- în tabelul EMP2_PNU salaria?ii care au salariul cuprins între 5000 ?i 10000;
- în tabelul EMP3_PNU salaria?ii care au salariul mai mare decât 10000.
Dac? un salariat se încadreaz? în tabelul emp0_pnu atunci acesta nu va mai fi inserat ?i în alt tabel
(tabelul corespunz?tor salariului s?u).*/

CREATE TABLE emp0_lco as SELECT * FROM employees WHERE 1 = -1;

select * from emp3_lco;

INSERT ALL          -- cu insert all ni s-a adaugat acelasi angajat si in emp0 si in emp2(ex) daca respectau ambele conditii
WHEN department_id = 80 THEN INTO emp0_lco
WHEN salary < 5000 THEN INTO emp1_lco
WHEN salary between 5000 AND 10000 THEN INTO emp2_lco
WHEN salary > 10000 THEN INTO emp3_lco
SELECT *
FROM employees;

-- Exercitiul 18 --
/*S? se modifice adresa de e-mail pentru angaja?ii care câ?tig? cel mai mult în departamentul în
care lucreaz? astfel încât acesta s? devin? ini?iala numelui concatenat? cu prenumele. Dac? nu
are prenume atunci în loc de acesta apare caracterul ‘.’. Anula?i modific?rile.*/
SELECT * from emp_lco;
UPDATE emp_lco e1
SET email = CONCAT(substr(last_name, 1, 1), NVL(first_name, ','))
WHERE salary = (SELECT MAX(salary)
                FROM emp_lco
                WHERE department_id = e1.department_id);
            
ROLLBACK;
-- Exercitiul 19 --
/*Pentru fiecare departament s? se m?reasc? salariul celor care au fost angaja?i primii astfel
încât s? devin? media salariilor din companie. ?ine?i cont de liniile introduse anterior.*/
UPDATE emp_lco
SET salary = (SELECT AVG(salary) FROM emp_lco)
WHERE (hire_date, department_id) IN (SELECT DISTINCT MIN(hire_date), department_id
                                    FROM emp_lco
                                    GROUP BY department_id);
                                    
SELECT * FROM emp_lco;
ROLLBACK;
-- Exercitiul 20 --
/*S? se modifice jobul ?i departamentul angajatului având codul 114, astfel încât s? fie la fel cu
cele ale angajatului având codul 205.*/
UPDATE emp_lco
SET (job_id, department_id) =  (SELECT job_id, department_id
                                FROM emp_lco
                                WHERE employee_id = 205)
WHERE employee_id = 114;
-- Exercitiul 21 --
/*Crea?i un script prin intermediul caruia sa fie posibil? actualizarea în mod interactiv de înregistr?ri
ale tabelului dept_pnu. Se va cere codul departamentului care urmeaz? a fi actualizat, se va afi?a
linia respectiv?, iar apoi se vor cere valori pentru celelalte câmpuri.*/
ACCEPT p_department_id PROMPT "department_id ="
SELECT * FROM dept_lco
WHERE department_id = '&&p_department_id';
ACCEPT p_department_name
ACCEPT p_manager_id
ACCEPT p_location_id
UPDATE dept_lco
SET department_name = '&&p_department_name', manager_id = '&&p_manager_id', location_id = '&&p_location_id'
WHERE department_id = &&p_department_id;
ROLLBACK;








