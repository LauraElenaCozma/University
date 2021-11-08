-- Laborator 10 --

--Exercitiul 1 --
/*S? se creeze tabelele EMP_pnu, DEPT_pnu*/
CREATE TABLE emp_lco AS SELECT * FROM employees;
CREATE TABLE dept_lco AS SELECT * FROM departments;

-- Exercitiul 2 --
/*Lista?i structura tabelelor surs? ?i a celor create anterior.*/
desc emp_lco
desc employees
desc dept_lco
desc departments
-- ca sa vedem ce coloane sunt not null
SELECT * 
FROM user_constraints
WHERE UPPER(table_name) LIKE ('EMP_%')
ORDER BY table_name;

-- Exercitiul 3
/*Lista?i con?inutul tabelelor create anterior*/
SELECT *
FROM emp_lco;

--ex 4
/*Pentru introducerea constrângerilor de integritate, executa?i instruc?iunile LDD indicate în
continuare. Prezentarea detaliat? a LDD se va face în cadrul laboratorului 4.*/
ALTER TABLE emp_lco
ADD CONSTRAINT pk_emp_lco PRIMARY KEY(employee_id);

ALTER TABLE dept_lco
ADD CONSTRAINT pk_dept_lco PRIMARY KEY(department_id);

ALTER TABLE emp_lco
ADD CONSTRAINT fk_emp_lco FOREIGN KEY(department_id) REFERENCES dept_lco(department_id);
--nu avem in emp_lco cheie straina pe manager id etc

-- Exercitiul 5
INSERT INTO DEPT_lco
VALUES (300, 'Programare'); --nu merge deoarece mai avem si cod locatie si cod sef

INSERT INTO DEPT_lco (department_id, department_name)
VALUES (300, 'Programare'); --daca aveam pe location id constrangere not null nu ar mai merge

INSERT INTO DEPT_lco (department_name, department_id)
VALUES (300, 'Programare'); -- eroare inversate sus

INSERT INTO DEPT_lco (department_id, department_name, location_id)
VALUES (300, 'Programare', null);  --constrangere de unicitate la depatment id

INSERT INTO DEPT_lco (department_name, location_id)
VALUES ('Programare', null);  --eroare not null avem constrangere de cheie primara
-- nu merge sa inseram de 2 ori

-- Exercitiul 6 --
/*S? se insereze un angajat corespunz?tor departamentului introdus anterior în tabelul EMP_pnu,
precizând valoarea NULL pentru coloanele a c?ror valoare nu este cunoscut? la inserare
(metoda implicit? de inserare). Efectele instruc?iunii s? devin? permanente.*/
SELECT * FROM dept_ama; --nu se vede programare 300 pt ca nu a dat commit
SELECT * FROM dept_lco;

INSERT INTO emp_lco(employee_id, last_name, department_id, job_id, hire_date, email)
VALUES (employees_seq.nextVal, 'Cozma', 300, 'IT_PROG', sysdate, 'laura@gmail.com');
-- ROLLBACK; sterge toate inregistrarile facute
SELECT * FROM emp_lco;
COMMIT;

--tema pana la 10 inclusiv



-- Exercitiul 6 --
/*S? se insereze un angajat corespunz?tor departamentului introdus anterior în tabelul EMP_pnu,
precizând valoarea NULL pentru coloanele a c?ror valoare nu este cunoscut? la inserare
(metoda implicit? de inserare). Efectele instruc?iunii s? devin? permanente.*/
SELECT * FROM emp_lco;
INSERT INTO emp_lco VALUES(employees_seq.nextVal, NULL, 'ceva', 'VNAME', NULL, sysdate, 'IT_PROG', NULL, NULL, NULL, NULL);
COMMIT;

-- Exercitiul 7 --
/*S? se mai introduc? un angajat corespunz?tor departamentului 300, precizând dup? numele
tabelului lista coloanelor în care se introduc valori (metoda explicita de inserare). Se presupune c?
data angaj?rii acestuia este cea curent? (SYSDATE). Salva?i înregistrarea.*/
SELECT * FROM dept_lco;
INSERT INTO emp_lco (employee_id, last_name, hire_date, job_id, email, department_id)
        VALUES(employees_seq.nextVal, 'Rose', sysdate, 'IT_PROG', 'ROSEGMAIL', 300);
COMMIT;
-- Exercitiul 8 --
/*S? se mai introduc? un angajat corespunz?tor departamentului 300, precizând dup? numele
tabelului lista coloanelor în care se introduc valori (metoda explicita de inserare). Se presupune c?
data angaj?rii acestuia este cea curent? (SYSDATE). Salva?i înregistrarea.*/
-- varianta 1 --
INSERT INTO emp_lco(employee_id, last_name, hire_date, job_id, email, department_id) 
        VALUES((SELECT MAX(employee_id) FROM emp_lco) + 1, 'Rose', sysdate, 'IT_PROG', 'ROSEGMAIL', 300);
COMMIT;

-- varianta 2 --
INSERT INTO emp_lco(employee_id, last_name, hire_date, job_id, email, department_id) 
SELECT(SELECT MAX(employee_id) FROM emp_lco) + 1, 'Tessa', sysdate, 'IT_PROG', 'ROSEGMAIL', 300
FROM DUAL;
COMMIT;
-- Exercitiul 9 --
/*Crea?i un nou tabel, numit EMP1_PNU, care va avea aceea?i structur? ca ?i EMPLOYEES, dar
nici o înregistrare. Copia?i în tabelul EMP1_PNU salaria?ii (din tabelul EMPLOYEES) al c?ror
comision dep??e?te 25% din salariu.*/
CREATE TABLE emp2_lco as SELECT * FROM employees WHERE 1 = -1; --copiaza tabelul fara date in el
INSERT INTO emp2_lco
SELECT * FROM employees WHERE commission_pct > 0.25;

-- Exercitiul 10 --
/*10. Insera?i o nou? înregistrare în tabelul EMP_PNU care s? totalizeze salariile, s? fac? media
comisioanelor, iar câmpurile de tip dat? s? con?in? data curent? ?i câmpurile de tip caracter s?
con?in? textul 'TOTAL'. Numele ?i prenumele angajatului s? corespund? utilizatorului curent
(USER). Pentru câmpul employee_id se va introduce valoarea 0, iar pentru manager_id ?i
department_id se va da valoarea null.*/
INSERT INTO emp_lco (employee_id, last_name, first_name, hire_date, job_id, email, salary, commission_pct)
VALUES (0, USER, USER, sysdate, 'TOTAL', 'TOTAL', (SELECT SUM(salary) FROM emp_lco), (SELECT SUM(commission_pct)/COUNT(*) FROM emp_lco));

-- Exercitiul 11 --
/*S? se creeze un fi?ier (script file) care s? permit? introducerea de înregistr?ri în tabelul EMP_PNU
în mod interactiv. Se vor cere utilizatorului: codul, numele, prenumele si salariul angajatului.
Câmpul email se va completa automat prin concatenarea primei litere din prenume ?i a primelor 7
litere din nume. Executati script-ul pentru a introduce 2 inregistrari in tabel.*/
INSERT INTO emp_lco (employee_id, last_name, first_name, hire_date, job_id, email, salary)
VALUES(&&p_cod, '&&p_nume', '&&p_prenume', sysdate, 'TOTAL', substr('&p_prenume', 1, 1) || substr('&p_nume', 1, 7), &p_salary);
select * from emp_lco;
COMMIT;

-- Exercitiul 12 --
/*Crea?i 2 tabele emp2_pnu ?i emp3_pnu cu aceea?i structur? ca tabelul EMPLOYEES, dar f?r?
înregistr?ri (accept?m omiterea constrângerilor de integritate). Prin intermediul unei singure comenzi,
copia?i din tabelul EMPLOYEES:
- în tabelul EMP1_PNU salaria?ii care au salariul mai mic decât 5000;
- în tabelul EMP2_PNU salaria?ii care au salariul cuprins între 5000 ?i 10000;
- în tabelul EMP3_PNU salaria?ii care au salariul mai mare decât 10000.
Verifica?i rezultatele, apoi ?terge?i toate înregistr?rile din aceste tabele.*/
select * from emp1_lco;
CREATE TABLE emp2_lco as SELECT * FROM employees WHERE 1 = -1;
CREATE TABLE emp3_lco as SELECT * FROM employees WHERE 1 = -1;

INSERT ALL
WHEN salary < 5000 THEN INTO emp1_lco
WHEN salary BETWEEN 5000 AND 10000 THEN INTO emp2_lco
ELSE INTO emp3_lco
SELECT * FROM employees;

-- TEMA EX 13


-- Exercitiul 14 --
/*14. M?ri?i salariul tuturor angaja?ilor din tabelul EMP_PNU cu 5%. Vizualizati, iar apoi anula?i
modific?rile.*/
UPDATE emp_lco
SET salary = salary * 1.05;
ROLLBACK;

-- Exercitiul 15 --
/*Schimba?i jobul tuturor salaria?ilor din departamentul 80 care au comision în 'SA_REP'. Anula?i
modific?rile.*/
UPDATE emp_lco
SET job_id = 'SA_REP'
WHERE department_id = 80;
ROLLBACK;

-- Exercitiul 16 --
/*S? se promoveze Douglas Grant la manager în departamentul 20, având o cre?tere de salariu
cu 1000$. Se poate realiza modificarea prin intermediul unei singure comenzi?*/
-- nu, trebuie sa facem 2 actualizari in departments pt manager id si dupa in employees
UPDATE dept_lco
SET manager_id = (SELECT employee_id FROM emp_lco WHERE LOWER(first_name) || ' ' || LOWER(last_name) = 'douglas grant')
WHERE department_id = 20;
COMMIT;
update emp_lco
SET salary = salary * 1000
WHERE employee_id = (SELECT employee_id FROM emp_lco WHERE LOWER(first_name) || ' ' || LOWER(last_name) = 'douglas grant');

-- Exercitiul 17 --
UPDATE emp_lco sub
SET (salary, commission_pct) = (SELECT salary, commission_pct FROM employees WHERE sub.manager_id = employee_id)
WHERE salary = (SELECT MIN(salary) FROM emp_lco);

-- ex 13 + 18 -> 21
-- Laborator 7 --
-- Exercitiul 18 --
UPDATE emp_lco
SET email = INITCAP(SUBSTR(last_name, 1, 1)) || NVL(first_name, '.')
WHERE (department_id, salary) IN (SELECT department_id, MAX(salary)
                                 FROM employees
                                 GROUP BY department_id);
                                 
ROLLBACK;


-- Exercitiul 22 --
SELECT * from dept_lco;
DELETE from dept_lco;

-- Exercitiul 23 --
/*?terge?i angaja?ii care nu au comision. Anula?i modific?rile.*/
DELETE from emp_lco
WHERE commission_pct is NULL;
ROLLBACK;

-- Exercitiul 24 --
/*Suprima?i departamentele care un au nici un angajat. Anula?i modific?rile.*/
DELETE FROM dept_lco
WHERE department_id NOT IN (SELECT DISTINCT NVL(department_id, 0)
                            FROM employees);

DELETE FROM dept_lco d
WHERE NOT EXISTS (SELECT 1
                  FROM employees
                  WHERE department_id = d.department_id);     
--nu merge; trebuie analizate constrangerile de cheie straina                  
select * from dept_lco;

-- Exercitiul 25 --
/*S? se creeze un fi?ier script prin care se cere utilizatorului un cod de angajat din tabelul EMP_PNU.
Se va lista inregistrarea corespunzatoare acestuia, iar apoi linia va fi suprimat? din tabel.*/
ACCEPT p_cod PROMPT "Dati un cod de angajat: "
SELECT * FROM emp_lco
WHERE employee_id = &&p_cod;
DELETE FROM emp_lco
WHERE employee_id = &&p_cod;
undefine p_cod
ROLLBACK;
-- Exercitiul 27 --
SAVEPOINT A;
-- Exercitiul 28 --
DELETE FROM emp_lco;
SELECT * FROM emp_lco;
ROLLBACK TO A;

-- Exercitiul 31 --
MERGE INTO emp_lco x
USING employees e
ON ( x.employee_id = e.employee_id)
WHEN MATCHED THEN
    UPDATE SET
        x.first_name = e.first_name,
        x.last_name = e.last_name,
        x.email = e.email,
        x.phone_number = e.phone_number,
        x.hire_date = e.hire_date,
        x.job_id = e.job_id,
        x.salary = e.salary,
        x.commission_pct = e.commission_pct,
        x.manager_id = e.manager_id,
        x.department_id = e.department_id
WHEN NOT MATCHED THEN
INSERT VALUES (e.employee_id, e.first_name,e.last_name,e.email,e.phone_number,
e.hire_date,e.job_id,e.salary,e.commission_pct,e.manager_id,e.department_id);
select * from emp_lco;