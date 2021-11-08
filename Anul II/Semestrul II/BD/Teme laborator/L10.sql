-- Tema laborator 10--

--- Exercitiul 20 ---
/*Sa se realizeze un script pentru a afisa numele angajatului, codul job-ului, salariul si numele
departamentului pentru salariatii care lucreaza intr-o locatie data de utilizator. Va fi permisa cautarea
case-insensitive.*/

ACCEPT p_city PROMPT "city =" 
SELECT last_name, first_name,job_id, salary, department_name
FROM employees
JOIN departments USING(department_id)
JOIN locations USING(location_id)
WHERE LOWER(city) = LOWER('&&p_city');
UNDEFINE p_city

--- Exercitiul 21 ---
/*b)Modificati cererea anterioar? astfel încât s? afiseze doar zilele lucr?toare dintre cele dou? date
calendaristice introduse.
ACCEPT p_data1 PROMPT "data1 = "
ACCEPT p_data2 PROMPT "data2 = "
SELECT TO_DATE('&p_data1','MM/DD/YYYY') + ROWNUM - 1
FROM dual
CONNECT BY ROWNUM < TO_DATE('&p_data2','MM/DD/YYYY') - TO_DATE('&p_data1','MM/DD/YYYY') + 1;*/

ACCEPT p_data1 PROMPT "data1 = "
ACCEPT p_data2 PROMPT "data2 = "
SELECT * 
FROM (SELECT TO_DATE('&&p_data1','MM/DD/YYYY') + ROWNUM - 1 data_zi
      FROM dual
      CONNECT BY ROWNUM < TO_DATE('&&p_data2','MM/DD/YYYY') - TO_DATE('&&p_data1','MM/DD/YYYY') + 1)
WHERE TO_CHAR(data_zi, 'D') BETWEEN 2 AND 6;

--- Exercitiul 7 ---
/*S? se mai introduc? un angajat corespunz?tor departamentului 300, precizând dup? numele
tabelului lista coloanelor în care se introduc valori (metoda explicita de inserare). Se presupune c?
data angaj?rii acestuia este cea curent? (SYSDATE). Salva?i înregistrarea.*/
select * from emp_lco;
INSERT INTO emp_lco(employee_id, first_name, last_name, department_id, job_id, hire_date, email)
VALUES (employees_seq.nextVal, 'Emily','Smith', 300, 'IT_PROG', sysdate, 'EMILYS');
COMMIT;

--- Exercitiul 8 ---
/*Este posibil? introducerea de înregistr?ri prin intermediul subcererilor (specificate în locul tabelului).
Ce reprezint?, de fapt, aceste subcereri? (view) Încerca?i dac? este posibil? introducerea unui
angajat, precizând pentru valoarea employee_id o subcerere care returneaz? (codul maxim +1).*/
select * from emp_lco;
INSERT INTO emp_lco(employee_id, first_name, last_name, department_id, job_id, hire_date, email)
VALUES ((SELECT MAX(employee_id) + 1 FROM employees), 'Jean','Moliere', 300, 'IT_PROG', sysdate, 'MOLJEAN');
COMMIT;

--- Exercitiul 9 ---
/*Crea?i un nou tabel, numit EMP1_PNU, care va avea aceea?i structur? ca ?i EMPLOYEES, dar
nici o înregistrare. Copia?i în tabelul EMP1_PNU salaria?ii (din tabelul EMPLOYEES) al c?ror
comision dep??e?te 25% din salariu.*/
CREATE TABLE emp1_lco AS SELECT * FROM employees WHERE commission_pct > 0.25;
ALTER TABLE emp1_lco
ADD CONSTRAINT pk_emp1_lco PRIMARY KEY(employee_id);
ALTER TABLE emp1_lco
ADD CONSTRAINT fk_emp1_lco FOREIGN KEY(department_id) REFERENCES dept_lco(department_id);
SELECT * FROM emp1_lco;

--- Exercitiul 10 ---
/*Insera?i o nou? înregistrare în tabelul EMP_PNU care s? totalizeze salariile, s? fac? media
comisioanelor, iar câmpurile de tip dat? s? con?in? data curent? ?i câmpurile de tip caracter s?
con?in? textul 'TOTAL'. Numele ?i prenumele angajatului s? corespund? utilizatorului curent
(USER). Pentru câmpul employee_id se va introduce valoarea 0, iar pentru manager_id ?i
department_id se va da valoarea null.*/

desc emp_lco
INSERT INTO emp_lco(employee_id, first_name, last_name, EMAIL, PHONE_NUMBER, hire_date, job_id, salary, commission_pct, department_id, manager_id)
VALUES (0, (SELECT user FROM dual), (SELECT user FROM dual), 'TOTAL', 'TOTAL', sysdate, 'TOTAL', (SELECT SUM(salary) FROM employees), (SELECT AVG(DECODE(commission_pct , NULL , 0 , commission_pct))FROM employees), NULL, NULL);
COMMIT;