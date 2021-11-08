-- laborator 7 recapitulare
SELECT * FROM user_constraints
WHERE table_name LIKE '%EMP_ECO';

/*1. S? se creeze tabelele EMP_pnu, DEPT_pnu (în ?irul de caractere “pnu”, p reprezint? prima
liter? a prenumelui, iar nu reprezint? primele dou? litere ale numelui dumneavoastr?), prin
copierea structurii ?i con?inutului tabelelor EMPLOYEES, respectiv DEPARTMENTS.*/
CREATE TABLE emp_eco AS SELECT * FROM employees;
CREATE TABLE dept_eco AS SELECT * FROM departments;
SELECT * FROM emp_eco;
SELECT * FROM dept_eco;
DESC emp_eco        
-- nu s a copiat constrangerea de not null de pe primary key; nu se pastreaza cheia primara
DESC employees

/*4. Pentru introducerea constrângerilor de integritate, executa?i instruc?iunile LDD indicate în
continuare.*/

ALTER TABLE emp_eco
ADD CONSTRAINT pk_emp_eco PRIMARY KEY(employee_id);
ALTER TABLE dept_eco
ADD CONSTRAINT pk_dept_eco PRIMARY KEY(department_id);
ALTER TABLE emp_lco
ADD CONSTRAINT fk_emp_dept_eco
FOREIGN KEY(department_id) REFERENCES dept_eco(department_id);

/*5. S? se insereze departamentul 300, cu numele Programare în DEPT_pnu.*/
INSERT INTO dept_eco (department_id, department_name)
VALUES (300, 'Programare');

SELECT * FROM dept_eco;

INSERT INTO DEPT_eco            --daca dam mai putine trebuie sa specificam sus cui dam valori
VALUES (300, 'Programare');


/*6. S? se insereze un angajat corespunz?tor departamentului introdus anterior în tabelul EMP_pnu,
precizând valoarea NULL pentru coloanele a c?ror valoare nu este cunoscut? la inserare
(metoda implicit? de inserare). Efectele instruc?iunii s? devin? permanente.*/
INSERT INTO emp_eco (employee_id, last_name, email, hire_date, job_id)
VALUES (EMPLOYEES_SEQ.nextval, 'Steven', 'STK', sysdate, 'IT_PROG');
SELECT * FROM emp_eco;
COMMIT;

/*7. S? se mai introduc? un angajat corespunz?tor departamentului 300, precizând dup? numele
tabelului lista coloanelor în care se introduc valori (metoda explicita de inserare). Se presupune c?
data angaj?rii acestuia este cea curent? (SYSDATE). Salva?i înregistrarea.*/
INSERT INTO emp_eco (employee_id, last_name, email, hire_date, job_id, department_id)
VALUES (EMPLOYEES_SEQ.nextval, 'Brett', 'BRT', sysdate, 'IT_PROG', 300);
COMMIT;

/*8. Este posibil? introducerea de înregistr?ri prin intermediul subcererilor (specificate în locul tabelului).
Ce reprezint?, de fapt, aceste subcereri? (view) Încerca?i dac? este posibil? introducerea unui
angajat, precizând pentru valoarea employee_id o subcerere care returneaz? (codul maxim +1).*/
INSERT INTO emp_eco (employee_id, last_name, email, hire_date, job_id, department_id)
VALUES ((SELECT MAX(employee_id) FROM emp_eco) + 1, 'Styles', 'Styles', sysdate, 'IT_PROG', 300);

/* 9. Crea?i un nou tabel, numit EMP1_PNU, care va avea aceea?i structur? ca ?i EMPLOYEES, dar
nici o înregistrare. Copia?i în tabelul EMP1_PNU salaria?ii (din tabelul EMPLOYEES) al c?ror
comision dep??e?te 25% din salariu.*/
CREATE TABLE emp1_eco AS SELECT * FROM employees WHERE 1 = -1;
SELECT * FROM emp1_eco;
INSERT INTO emp1_eco
SELECT * FROM employees WHERE commission_pct > 0.25;
SELECT * FROM emp_eco;
/*10. Insera?i o nou? înregistrare în tabelul EMP_PNU care s? totalizeze salariile, s? fac? media
comisioanelor, iar câmpurile de tip dat? s? con?in? data curent? ?i câmpurile de tip caracter s?
con?in? textul 'TOTAL'. Numele ?i prenumele angajatului s? corespund? utilizatorului curent
(USER). Pentru câmpul employee_id se va introduce valoarea 0, iar pentru manager_id ?i
department_id se va da valoarea null.*/
INSERT INTO emp_eco (employee_id, first_name, last_name, email, phone_number, hire_date, job_id, salary, commission_pct, manager_id, department_id)
VALUES (0, USER, USER, 'TOTAL', 'TOTAL', sysdate, 'TOTAL', (SELECT SUM(salary) FROM emp_eco), (SELECT SUM(commission_pct)/COUNT(*) FROM emp_eco), null, null);

/*11. S? se creeze un fi?ier (script file) care s? permit? introducerea de înregistr?ri în tabelul EMP_PNU
în mod interactiv. Se vor cere utilizatorului: codul, numele, prenumele si salariul angajatului.
Câmpul email se va completa automat prin concatenarea primei litere din prenume ?i a primelor 7
litere din nume. Executati script-ul pentru a introduce 2 inregistrari in tabel.*/
INSERT INTO emp_eco (employee_id, last_name, first_name, salary, email, hire_date, job_id)
VALUES(&p_cod, '&&p_nume', '&&p_prenume', &salary, CONCAT(SUBSTR('&&p_prenume', 1, 1), SUBSTR('&&p_nume',1, 7)), sysdate, 'TOTAL');

/*12. Crea?i 2 tabele emp2_pnu ?i emp3_pnu cu aceea?i structur? ca tabelul EMPLOYEES, dar f?r?
înregistr?ri (accept?m omiterea constrângerilor de integritate). Prin intermediul unei singure comenzi,
copia?i din tabelul EMPLOYEES:
- în tabelul EMP1_PNU salaria?ii care au salariul mai mic decât 5000;
- în tabelul EMP2_PNU salaria?ii care au salariul cuprins între 5000 ?i 10000;
- în tabelul EMP3_PNU salaria?ii care au salariul mai mare decât 10000.
Verifica?i rezultatele, apoi ?terge?i toate înregistr?rile din aceste tabele.*/
CREATE TABLE emp3_eco AS SELECT * FROM employees WHERE 1 = -1;
SELECT * FROM emp1_eco;



/*14. 14. M?ri?i salariul tuturor angaja?ilor din tabelul EMP_PNU cu 5%. Vizualizati, iar apoi anula?i
modific?rile.*/
SELECT * FROM emp_eco order by 11;
UPDATE emp_eco
SET salary = salary * 1.05;
ROLLBACK;

/*15. 15. Schimba?i jobul tuturor salaria?ilor din departamentul 80 care au comision în 'SA_REP'. Anula?i
modific?rile.*/
UPDATE emp_eco
SET job_id = 'SA_REP'
WHERE department_id = 80 AND commission_pct IS NOT NULL;
ROLLBACK;

/*16. S? se promoveze Douglas Grant la manager în departamentul 20, având o cre?tere de salariu
cu 1000$. Se poate realiza modificarea prin intermediul unei singure comenzi?*/
SELECT * FROM emp_eco WHERE first_name = 'Douglas';
SELECT * FROM dept_eco;
UPDATE dept_eco
SET manager_id = (SELECT employee_id FROM emp_eco WHERE INITCAP(first_name) = 'Douglas')
WHERE department_id = 20;

UPDATE emp_eco
SET salary = salary + 1000
WHERE INITCAP(first_name) = 'Douglas';
ROLLBACK;

/*17. Schimba?i salariul ?i comisionul celui mai prost pl?tit salariat din firm?, astfel încât s? fie egale
cu salariul si comisionul ?efului s?u.*/
UPDATE emp_eco e1
SET salary = (SELECT salary FROM emp_eco WHERE employee_id = e1.manager_id), commission_pct = (SELECT commission_pct FROM emp_eco WHERE employee_id = e1.manager_id)
WHERE salary = (SELECT MIN(salary) FROM emp_eco);

/*18. S? se modifice adresa de e-mail pentru angaja?ii care câ?tig? cel mai mult în departamentul în
care lucreaz? astfel încât acesta s? devin? ini?iala numelui concatenat? cu prenumele. Dac? nu
are prenume atunci în loc de acesta apare caracterul ‘.’. Anula?i modific?rile.*/
UPDATE emp_eco e1
SET email = CONCAT(SUBSTR(last_name, 1, 1), NVL(first_name,'.'))
WHERE salary = (SELECT MAX(salary) FROM emp_eco WHERE department_id = e1.department_id);

/*19. Pentru fiecare departament s? se m?reasc? salariul celor care au fost angaja?i primii astfel
încât s? devin? media salariilor din companie. ?ine?i cont de liniile introduse anterior.*/
UPDATE emp_eco e1
SET salary = (SELECT SUM(salary)/COUNT(*) FROM emp_eco)
WHERE (hire_date, department_id) IN (SELECT MIN(hire_date), department_id FROM emp_eco GROUP BY department_id);

SELECT * FROM emp_eco order by 1;

/*20. S? se modifice jobul ?i departamentul angajatului având codul 114, astfel încât s? fie la fel cu
cele ale angajatului având codul 205.*/
UPDATE emp_eco
SET (job_id, department_id) = (SELECT job_id, department_id FROM emp_eco WHERE employee_id = 205)
WHERE employee_id = 114;


/*23. ?terge?i angaja?ii care nu au comision. Anula?i modific?rile.*/
DELETE FROM emp_eco
WHERE commission_pct is NULL;
ROLLBACK;

/*24. Suprima?i departamentele care un au nici un angajat. Anula?i modific?rile.*/
DELETE FROM dept_eco
WHERE department_id IN (SELECT department_id FROM dept_eco LEFT JOIN employees USING(department_id) GROUP BY department_id HAVING COUNT(employee_id) = 0);
ROLLBACK;           --nu mergeee

DELETE FROM dept_eco d
WHERE NOT EXISTS (SELECT 1 FROM emp_eco
                  	WHERE d.department_id = department_id);
ROLLBACK;


/*25.S? se creeze un fi?ier script prin care se cere utilizatorului un cod de angajat din tabelul EMP_PNU.
Se va lista inregistrarea corespunzatoare acestuia, iar apoi linia va fi suprimat? din tabel.*/
DELETE FROM emp_eco
WHERE employee_id = &p_cod;
ROLLBACK;

SAVEPOINT A;
DELETE FROM emp_eco;
ROLLBACK TO A;
SELECT * FROM emp_eco;

