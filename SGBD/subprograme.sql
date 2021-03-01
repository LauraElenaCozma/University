---Defini?i un subprogram prin care s? ob?ine?i salariul unui angajat al c?rui nume este specificat.
--Trata?i toate excep?iile ce pot fi generate.
--Apela?i subprogramul pentru urm?torii angaja?i: Bell, King, Kimball.
--Rezolva?i problema folosind o func?ie local?.
SET SERVEROUTPUT ON
DECLARE
nume_citit employees.last_name%TYPE := '&p_nume';
salariu    employees.salary%TYPE;
PROCEDURE sal_ang (nume IN employees.last_name%TYPE, sal OUT employees.salary%TYPE)
IS
    BEGIN
    SELECT salary INTO sal
    FROM employees
    WHERE UPPER(last_name) = UPPER(nume);
    EXCEPTION 
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('Nu exista angajati cu numele dat');
        WHEN TOO_MANY_ROWS THEN
            DBMS_OUTPUT.PUT_LINE('Exista mai multi angajati cu numele dat');    
        WHEN OTHERS THEN
            DBMS_OUTPUT.PUT_LINE('Alta eroare'); 
    END sal_ang;
BEGIN
    sal_ang(nume_citit,salariu);
    DBMS_OUTPUT.PUT_LINE('Salariul este: ' || salariu);
END;
/

--ATENTIE: Cum putem sa tratam eroarea si in blocul principal?

--cu function
DECLARE
FUNCTION sal_emp_funct 
    RETURN employees.salary%TYPE
    IS
    v_name employees.last_name%TYPE := '&v_nume';
    sal employees.salary%TYPE;
    BEGIN
        SELECT salary INTO sal
        FROM employees
        WHERE UPPER(last_name) = UPPER(v_name);
        RETURN sal;
        EXCEPTION 
            WHEN NO_DATA_FOUND THEN
                DBMS_OUTPUT.PUT_LINE('Nu exista angajati cu numele dat');
                RETURN sal;    
            WHEN TOO_MANY_ROWS THEN
                DBMS_OUTPUT.PUT_LINE('Exista mai multi angajati cu numele dat');    
                RETURN sal;    
            WHEN OTHERS THEN
                DBMS_OUTPUT.PUT_LINE('Alta eroare'); 
                RETURN sal;
    END sal_emp_funct;
BEGIN
    DBMS_OUTPUT.PUT_LINE('Salariul este: ' || sal_emp_funct);
END;
/
--ATENTIE: Cum facem ca in caz de exceptie sa returneze altceva


--folosind functie stocata
CREATE OR REPLACE
FUNCTION sal_emp_funct_stoc 
    RETURN employees.salary%TYPE
    IS
    v_name employees.last_name%TYPE := '&v_nume';
    sal employees.salary%TYPE;
    BEGIN
        SELECT salary INTO sal
        FROM employees
        WHERE UPPER(last_name) = UPPER(v_name);
        RETURN sal;
        EXCEPTION 
            WHEN NO_DATA_FOUND THEN
                DBMS_OUTPUT.PUT_LINE('Nu exista angajati cu numele dat');
                RETURN sal;    
            WHEN TOO_MANY_ROWS THEN
                DBMS_OUTPUT.PUT_LINE('Exista mai multi angajati cu numele dat');    
                RETURN sal;    
            WHEN OTHERS THEN
                DBMS_OUTPUT.PUT_LINE('Alta eroare'); 
                RETURN sal;
    END sal_emp_funct_stoc;
/

CREATE OR REPLACE FUNCTION sal_emp_f_param (nume employees.last_name%TYPE)
RETURN employees.salary%TYPE
IS
sal employees.salary%TYPE;
BEGIN
    SELECT salary INTO sal
    FROM employees
    WHERE last_name = nume;
    RETURN sal;
    EXCEPTION 
            WHEN NO_DATA_FOUND THEN
                DBMS_OUTPUT.PUT_LINE('Nu exista angajati cu numele dat');
                RETURN sal;    
            WHEN TOO_MANY_ROWS THEN
                DBMS_OUTPUT.PUT_LINE('Exista mai multi angajati cu numele dat');    
                RETURN sal;    
            WHEN OTHERS THEN
                DBMS_OUTPUT.PUT_LINE('Alta eroare'); 
                RETURN sal;
END sal_emp_f_param;
/
DECLARE
nume employees.last_name%TYPE := '&p_nume';
BEGIN
    DBMS_OUTPUT.PUT_LINE(sal_emp_f_param(nume));
    DBMS_OUTPUT.PUT_LINE(sal_emp_funct_stoc);
END;
/
DROP FUNCTION sal_emp_funct_stoc;
DROP FUNCTION f3_lco;
DROP FUNCTION suma;


--Procedura stocata
CREATE OR REPLACE PROCEDURE salary_proc (nume IN employees.last_name%TYPE)
IS
salariu employees.salary%TYPE;
BEGIN
SELECT salary INTO salariu
FROM employees
WHERE UPPER(last_name) = UPPER(nume);
DBMS_OUTPUT.PUT_LINE('Salariul e ' || salariu);
EXCEPTION 
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Nu exista angajati cu numele dat');
    WHEN TOO_MANY_ROWS THEN
        DBMS_OUTPUT.PUT_LINE('Exista mai multi angajati cu numele dat');    
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('Alta eroare'); 
END salary_proc;
/


BEGIN
    salary_proc('&p_nume');
END;
/
DROP PROCEDURE salary_proc;
--Crea?i o procedur? stocat? care prime?te printr-un parametru codul unui angajat ?i returneaz?
--prin intermediul aceluia?i parametru codul managerului corespunz?tor acelui angajat
--(parametru de tip IN OUT).

--procedura stocata
CREATE OR REPLACE PROCEDURE cod_mgr (cod IN OUT employees.employee_id%TYPE) 
IS
BEGIN
SELECT manager_id INTO cod
FROM employees
WHERE employee_id = cod;
END cod_mgr;
/

DECLARE
cod employees.employee_id%TYPE := &p_cod;
BEGIN
cod_mgr(cod);
DBMS_OUTPUT.PUT_LINE('Codul managerului e ' || cod);
END;
/

--6. Declara?i o procedur? local? care are parametrii:
--- rezultat (parametru de tip OUT) de tip last_name din employees;
--- comision (parametru de tip IN) de tip commission_pct din employees, ini?ializat cu NULL;
--- cod (parametru de tip IN) de tip employee_id din employees, ini?ializat cu NULL.
--Dac? comisionul nu este NULL atunci în rezultat se va memora numele salariatului care are
--comisionul respectiv. În caz contrar, în rezultat se va memora numele salariatului al c?rui cod are
--valoarea dat? în apelarea procedurii.

DECLARE
cod employees.employee_id%TYPE := &p_cod;
comision employees.commission_pct%TYPE := &p_comision;
rezultat employees.last_name%TYPE;

PROCEDURE f_comision(rezultat OUT employees.last_name%TYPE, comision IN employees.commission_pct%TYPE DEFAULT NULL, cod IN employees.employee_id%TYPE)
IS
BEGIN
    IF comision IS NOT NULL
        THEN SELECT last_name INTO rezultat
            FROM employees
            WHERE commission_pct = comision;
    ELSE SELECT last_name INTO rezultat
        FROM employees
        WHERE employee_id = cod;
    END IF;
    EXCEPTION 
        WHEN NO_DATA_FOUND THEN DBMS_OUTPUT.PUT_LINE('Nu sunt ang cu acel comision');
        WHEN TOO_MANY_ROWS THEN DBMS_OUTPUT.PUT_LINE('Sunt prea multi ang cu acel comision');
        WHEN OTHERS THEN DBMS_OUTPUT.PUT_LINE('Alta eroare');
END f_comision;

BEGIN
    f_comision(rezultat,cod=>cod);
    DBMS_OUTPUT.PUT_LINE(rezultat);
    f_comision(rezultat,comision=>comision,cod=>cod);
    DBMS_OUTPUT.PUT_LINE(rezultat);
END;
/

SELECT * FROM employees;

--7. Defini?i dou? func?ii locale cu acela?i nume (overload) care s? calculeze media salariilor astfel:
--- prima func?ie va avea ca argument codul departamentului, adic? func?ia calculeaz? media
--salariilor din departamentul specificat;
--- a doua func?ie va avea dou? argumente, unul reprezentând codul departamentului, iar cel?lalt
--reprezentând job-ul, adic? func?ia va calcula media salariilor dintr-un anumit departament ?i
--care apar?in unui job specificat.

DECLARE
FUNCTION med_sal (cod_dep IN employees.department_id%TYPE) 
RETURN NUMBER
    IS
    med NUMBER(10) := 0;
    BEGIN
    SELECT AVG(salary) INTO med
    FROM employees
    WHERE department_id = cod_dep;
    RETURN NVL(med,0);
    END med_sal;
    
FUNCTION med_sal (cod_dep IN employees.department_id%TYPE, cod_job IN employees.job_id%TYPE)
RETURN NUMBER
    IS 
    med NUMBER(10) := 0;
    BEGIN
    SELECT AVG(salary) INTO med
    FROM employees
    WHERE department_id = cod_dep AND UPPER(job_id) = UPPER(cod_job);
    RETURN NVL(med,0);
    END med_sal;
BEGIN
    DBMS_OUTPUT.PUT_LINE('Fct 1: ' || med_sal(100));
    DBMS_OUTPUT.PUT_LINE('Fct 2: ' || med_sal(100,'IT_PROG'));
END;
/

SELECT * FROM employees WHERE department_id = 100;

--Calculeaza factorialul unui numar recuriv
CREATE OR REPLACE FUNCTION factorial (n NUMBER) RETURN NUMBER
IS 
BEGIN
    IF n = 0 THEN RETURN 1;
    ELSE 
        RETURN n * factorial(n - 1);
    END IF;
END;
/

BEGIN
DBMS_OUTPUT.PUT_LINE(factorial(4));
END;
/
--Afi?a?i numele ?i salariul angaja?ilor al c?ror salariu este mai mare decât media tuturor
--salariilor. Media salariilor va fi ob?inut? prin apelarea unei func?ii stocate.

CREATE OR REPLACE FUNCTION med_sal RETURN NUMBER
IS
med NUMBER(10,2);
BEGIN
SELECT AVG(salary) INTO med
FROM employees;
RETURN med;
END;
/

SELECT last_name, salary FROM employees
WHERE salary > med_sal;

---- EXERCITII ------
--1. Crea?i tabelul info_*** cu urm?toarele coloane:
--- utilizator (numele utilizatorului care a ini?iat o comand?)
--- data (data ?i timpul la care utilizatorul a ini?iat comanda)
--- comanda (comanda care a fost ini?iat? de utilizatorul respectiv)
--- nr_linii (num?rul de linii selectate/modificate de comand?)
--- eroare (un mesaj pentru excep?ii).

--3. Defini?i o func?ie stocat? care determin? num?rul de angaja?i care au avut cel pu?in 2 joburi
--diferite ?i care în prezent lucreaz? într-un ora? dat ca parametru. Trata?i cazul în care ora?ul dat
--ca parametru nu exist?, respectiv cazul în care în ora?ul dat nu lucreaz? niciun angajat. Insera?i
--în tabelul info_*** informa?iile corespunz?toare fiec?rui caz determinat de valoarea dat? pentru
--parametru.

CREATE OR REPLACE FUNCTION nr_ang (oras locations.city%TYPE)
RETURN NUMBER
IS
nr NUMBER(3);
BEGIN
    SELECT COUNT(COUNT(employee_id)) INTO nr
    FROM job_history
    JOIN departments USING (department_id)
    JOIN locations USING (location_id)
    WHERE UPPER(city) = UPPER(oras) 
    GROUP BY employee_id
    HAVING COUNT(job_id) >= 2;
    RETURN nr;
END nr_ang;
/
    
SET SERVEROUTPUT ON;
BEGIN
    DBMS_OUTPUT.PUT_LINE(nr_ang('Roman'));
END;
/
SELECT * FROM job_history
order by 1;


SELECT city FROM locations JOIN departments USING(location_id) WHERE department_id IN (110, 80, 90);

--4. Defini?i o procedur? stocat? care m?re?te cu 10% salariile tuturor angaja?ilor condu?i direct sau
--indirect de c?tre un manager al c?rui cod este dat ca parametru. Trata?i cazul în care nu exist?
--niciun manager cu codul dat. Insera?i în tabelul info_*** informa?iile corespunz?toare fiec?rui
--caz determinat de valoarea dat? pentru parametru.

SELECT * FROM employees;

CREATE OR REPLACE PROCEDURE mareste_sal (cod IN emp_lco.employee_id%TYPE)
IS
BEGIN
UPDATE emp_lco
SET salary = salary * 1.1;
END;
/

--Sa se scrie o procedura care sa intoarca angajatii(cod, nume, job_id) care au avut cele mai multe job-uri

DECLARE
TYPE rec_ang IS RECORD
    (cod employees.employee_id%TYPE,
    nume employees.last_name%TYPE,
    id_job employees.job_id%TYPE);
TYPE tab_index IS TABLE OF rec_ang INDEX BY PLS_INTEGER;
t tab_index;
PROCEDURE nr_joburi (t OUT tab_index)
IS
nr_max_joburi NUMBER;
BEGIN
    SELECT MAX(COUNT(*)) INTO nr_max_joburi
    FROM job_history
    GROUP BY employee_id;
    
    SELECT e.employee_id, last_name, e.job_id BULK COLLECT INTO t
    FROM job_history j
    JOIN employees e ON(e.employee_id = j.employee_id)
    GROUP BY e.employee_id, last_name, e.job_id
    HAVING COUNT(j.job_id) = nr_max_joburi;
END nr_joburi;
BEGIN
    nr_joburi(t);
    FOR i IN t.first..t.last LOOP
        IF t.exists(i) THEN
            DBMS_OUTPUT.PUT_LINE(t(i).cod || ' ' || t(i).nume || ' ' || t(i).id_job);
        END IF;
    END LOOP;
END;
/

SET SERVEROUTPUT ON;


--Sa se scrie o functie care primeste un cod de manager si intoarce numarul subalternilor acestuia.
DECLARE
FUNCTION subalterni (cod employees.employee_id%TYPE) RETURN NUMBER
IS
nr NUMBER;
BEGIN
    SELECT COUNT(*) INTO nr
    FROM employees
    WHERE manager_id = cod;
    RETURN nr;
END subalterni;
BEGIN
    DBMS_OUTPUT.PUT_LINE(subalterni(103));
END;
/
--ATENTIE: subalterni directi sau orice subalterni?
--ATENTIE: alta metoda de apelare?

--Sa se scrie o procedura care primeste ca argument un cod de angajat si intoarce, folosind
--acelasi parametru, codul angajatului care a fost angajat dupa acesta. Tratati erorile!

DECLARE
cod employees.employee_id%TYPE := &p_cod;
PROCEDURE urm_angajat (cod IN OUT employees.employee_id%TYPE)
IS
data_ang DATE;
BEGIN
SELECT hire_date INTO data_ang
FROM employees
WHERE employee_id = cod;

SELECT employee_id INTO cod
FROM employees
WHERE hire_date = (SELECT MIN(hire_date)
                    FROM employees
                    WHERE hire_date > data_ang);
EXCEPTION
    WHEN NO_DATA_FOUND THEN DBMS_OUTPUT.PUT_LINE('Nu exista angajati');
    WHEN TOO_MANY_ROWS THEN DBMS_OUTPUT.PUT_LINE('Prea multi angajati');
    WHEN OTHERS THEN DBMS_OUTPUT.PUT_LINE('Alta eroare');
END;
BEGIN
urm_angajat(cod);
DBMS_OUTPUT.PUT_LINE(cod);
END;
/
--ATENTIE: cum facem ca la eroare sa nu se mai afiseze si codul?
SELECT * FROM employees order by 6;

--Se cere un subprogram care primeste ca argument 2 date si intoarce numarul de angajati care
--care au lucrat la un proiect in aceasta perioada
DECLARE
    nr_ang NUMBER;
    PROCEDURE proiecte (start_d IN works_on.start_date%TYPE, end_d IN works_on.end_date%TYPE, nr_ang OUT NUMBER)
    IS
    BEGIN
    SELECT COUNT(DISTINCT employee_id) INTO nr_ang
    FROM works_on
    WHERE start_date >= start_d AND end_date <= end_d;
    END proiecte;
BEGIN
    proiecte(TO_DATE('01-MAY-06','DD-MON-YY'),TO_DATE('1-JAN-07','DD-MON-YY'),nr_ang);
    DBMS_OUTPUT.PUT_LINE(nr_ang);
END;
/
--La fel pentru lista angajatilor
DECLARE
TYPE ang IS RECORD 
(cod employees.employee_id%TYPE,
nume employees.last_name%TYPE);
TYPE t_index IS TABLE OF ang INDEX BY PLS_INTEGER;
t t_index;
FUNCTION proiecte (st_d works_on.start_date%TYPE, end_d works_on.end_date%TYPE) RETURN t_index
    IS
        t t_index;
    BEGIN
        SELECT DISTINCT employee_id, last_name BULK COLLECT INTO t
        FROM employees
        JOIN works_on USING(employee_id)
        WHERE start_date >= st_d AND end_date <= end_d;
        RETURN t;
    END;
BEGIN
    t := proiecte(TO_DATE('01-MAY-06','DD-MON-YY'),TO_DATE('17-JAN-07','DD-MON-YY'));
    FOR i IN t.FIRST..t.LAST LOOP
        IF t.EXISTS(i) THEN
            DBMS_OUTPUT.PUT_LINE(t(i).cod || ' ' || t(i).nume);
        END IF;
    END LOOP;
END;
/
SELECT * FROM projects;
SELECT * FROM works_on ORDER BY 3;

SET SERVEROUTPUT ON;

--Sa se adauge o coloana next_sef tabelului emp. Sa se scrie o functie care actualizeaza aceasta coloana.
--viitorul sef va fi ales dintre subalternii (directi) sefului curent (angajatul care are vechimea cea mai mare
--dintre acestia).
ALTER TABLE emp_lco
ADD next_sef NUMBER(4);


CREATE OR REPLACE PROCEDURE viitor_sef (ang_curent IN employees.employee_id%TYPE)
IS
sef employees.employee_id%TYPE;
v_sef employees.employee_id%TYPE;
BEGIN
    SELECT manager_id INTO sef
    FROM employees
    WHERE employee_id = ang_curent;
    
    IF sef IS NULL 
        THEN v_sef := NULL;
    ELSE
        SELECT employee_id INTO v_sef
        FROM employees
        WHERE manager_id = sef 
        AND hire_date = (SELECT MIN(hire_date)
                        FROM employees
                        WHERE manager_id = sef);
    END IF;
    
    UPDATE emp_lco
    SET next_sef = v_sef
    WHERE employee_id = ang_curent;
END;
/

DECLARE
TYPE t_index IS TABLE OF employees.employee_id%TYPE INDEX BY PLS_INTEGER;
t t_index;
BEGIN
SELECT employee_id BULK COLLECT INTO t
FROM employees;

FOR i IN t.FIRST..t.LAST LOOP
viitor_sef(t(i));
END LOOP;
END;
/

----CU CURSOARE
CREATE OR REPLACE PROCEDURE viitor_sef_2 
IS
v_manager employees.manager_id%TYPE;
v_next_m  employees.manager_id%TYPE;
BEGIN
    FOR c IN (SELECT employee_id, manager_id 
              FROM employees) LOOP
        IF c.manager_id IS NULL 
                THEN v_manager := c.employee_id;
        ELSE v_manager := c.manager_id;
        END IF;
        
        SELECT employee_id INTO v_next_m
        FROM employees
        WHERE manager_id = v_manager
        AND hire_date = (SELECT MIN(hire_date) FROM employees WHERE manager_id = v_manager);
        
        UPDATE emp_lco
        SET next_sef = v_next_m
        WHERE employee_id = c.employee_id;
    END LOOP;
END;
/
--ATENTIE: alta varianta de implementare care sa faca simultan update
SELECT * FROM emp_lco ORDER BY manager_id, hire_date;

BEGIN
viitor_sef_2;
END;
/

--O procedura care mareste cu p% salariul angajatilor care lucreaza in departamente
--care au minim 5 angajati si micsoreaza cu acelasi procent la ceilalti angajati
--Sa se intoarca folosind 2 parametrii numarul angajatilor care au obtinut marire
--de salariu si nr de ang carora li s-a micsorat salariul

DECLARE
p NUMBER := 3;
nr_marire NUMBER;
nr_mics NUMBER;
PROCEDURE modifica_salariu (p NUMBER, nr_ang_marire OUT NUMBER, nr_ang_mics OUT NUMBER)
IS
TYPE tab_index IS TABLE OF emp_lco.department_id%TYPE INDEX BY PLS_INTEGER;
TYPE tab_index_emp IS TABLE OF emp_lco.employee_id%TYPE INDEX BY PLS_INTEGER;
dep_marire tab_index;
ang tab_index_emp;
BEGIN
    
    UPDATE emp_lco
    SET salary = salary * (1 + p/100)
    WHERE department_id IN (SELECT department_id 
                            FROM employees
                            GROUP BY department_id
                            HAVING COUNT(employee_id) >= 5)
    RETURNING employee_id BULK COLLECT INTO ang;
    
    nr_ang_marire := ang.COUNT;

    ang.DELETE;
    
    UPDATE emp_lco
    SET salary = salary * (1 - p/100)
    WHERE department_id IN (SELECT department_id 
                            FROM employees
                            GROUP BY department_id
                            HAVING COUNT(employee_id) < 5)
    RETURNING employee_id BULK COLLECT INTO ang;
    nr_ang_mics := ang.COUNT;
    
END modifica_salariu;

BEGIN
    modifica_salariu(p,nr_marire,nr_mics);
    DBMS_OUTPUT.PUT_LINE('Nr ang cu salariul marit: ' || nr_marire || ' nr ang cu salariul micsorat: ' || nr_mics);
END;
/


SELECT * FROM emp_lco;
ROLLBACK;


----SELECTEAZA numele proiectelor care au avut loc intr-un an dat ca parametru dupa care pentru fiecare proiect 
--lista cu numele angajatilor care au lucrat pe proiectul respectiv
DECLARE
PROCEDURE proiecte (an VARCHAR2)
IS
BEGIN
    FOR cur_p IN (SELECT project_name, project_id
                  FROM projects
                  WHERE TO_CHAR(START_DATE, 'YYYY') = an) LOOP
        DBMS_OUTPUT.PUT_LINE(cur_p.project_name || ' cu angajatii:');
        FOR cur_emp IN (SELECT last_name
                        FROM employees
                        JOIN works_on USING(employee_id)
                        WHERE project_id = cur_p.project_id) LOOP
           DBMS_OUTPUT.PUT(cur_emp.last_name || ' ');
        END LOOP;
        DBMS_OUTPUT.NEW_LINE;
    END LOOP;
END;
BEGIN
    proiecte(&v_an);
END;
/

SET SERVEROUTPUT ON;


SELECT sysdate - TO_DATE('15-DEC-06', 'DD-MON-YY')
FROM dual;

---Model statie achizitie problema 1 pe employees
--Sa se selecteze angajatii dintr-un departament dat ca parametru care nu au mai lucrat pe un proiect in ultimele 5090 de zile

DROP TYPE tab_imbri;
/

DECLARE
TYPE tab_imbri IS TABLE OF employees.last_name%TYPE;
t tab_imbri;
c departments.department_id%TYPE := 50;
PROCEDURE f_statie (cod IN departments.department_id%TYPE)
IS
t tab_imbri;
BEGIN
SELECT DISTINCT last_name BULK COLLECT INTO t
FROM employees
JOIN works_on USING (employee_id)
WHERE department_id = cod
AND (sysdate - start_date) > 5090;
FOR i IN t.FIRST..t.LAST LOOP
    DBMS_OUTPUT.PUT_LINE(t(i) || ' ');
END LOOP;
END;
BEGIN
f_statie(c);

END;
/

DROP PROCEDURE f_statie;
SELECT * FROM employees ORDER BY 2;

SELECT * FROM works_on ORDER BY 2;

---Model pacienti adaptat la employees ex 1
--Returnati numele proiectului impreuna cu durata de zile in care a lucrat la el pentru un anumit angajat
DECLARE
TYPE rec IS RECORD 
(p_name projects.project_name%TYPE);--,
--durata NUMBER(6,3));
TYPE tab_imbri IS TABLE OF rec;
t tab_imbri;
PROCEDURE f_proj (cod IN employees.employee_id%TYPE, t OUT tab_imbri)
IS
BEGIN
SELECT project_name BULK COLLECT INTO t
FROM projects
JOIN works_on USING (project_id)
WHERE employee_id = cod;
END;
BEGIN
f_proj(125,t);
END;
/

--Pentru fiecare departament afiseaza numele si lista angajatilor care au salariu mai mare decat media salariilor colegilor
--si care au lucrat pe cel putin 2 proiecte
DECLARE
PROCEDURE func 
IS
cnt NUMBER := 0;
TYPE rec IS RECORD  
    (last_name employees.last_name%TYPE,
     salary employees.salary%TYPE);
TYPE tab_imbri IS TABLE OF rec;
t tab_imbri;
CURSOR c_dep IS (SELECT department_id, department_name FROM departments);
CURSOR c_emp(p departments.department_id%TYPE) IS
    (SELECT e.last_name, e.salary
    FROM employees e
    WHERE e.department_id = p AND e.salary > (SELECT AVG(salary) FROM employees WHERE department_id = p AND employee_id != e.employee_id)
    AND e.employee_id IN (SELECT employee_id FROM works_on GROUP BY employee_id HAVING COUNT(project_id) >= 2));
BEGIN
    FOR c IN c_dep LOOP
        OPEN c_emp(c.department_id);
        FETCH c_emp BULK COLLECT INTO t;
        IF t.COUNT <> 0 THEN 
        DBMS_OUTPUT.PUT_LINE('In dep: ' || c.department_name || ' lucreaza: ');
        FOR i IN t.FIRST..t.LAST LOOP
            DBMS_OUTPUT.PUT_LINE(t(i).last_name || ' cu salariul ' || t(i).salary); 
        END LOOP;
        END IF;
        CLOSE c_emp;
        /*FOR c_e IN c_emp(c.department_id) LOOP
            cnt := cnt + 1;
           DBMS_OUTPUT.PUT_LINE(c_e.last_name || ' cu salariul ' || c_e.salary); 
        END LOOP;
        IF cnt = 0 THEN DBMS_OUTPUT.PUT_LINE('Nu exista angajati care sa respecte conditiile');
        END IF;*/
    END LOOP;
END;
BEGIN
    func;
END;
/

--Laborator 4

/*Defini?i o procedur? stocat? care m?re?te cu 10% salariile tuturor angaja?ilor condu?i direct sau
indirect de c?tre un manager al c?rui cod este dat ca parametru. Trata?i cazul în care nu exist?
niciun manager cu codul dat. Insera?i în tabelul info_*** informa?iile corespunz?toare fiec?rui
caz determinat de valoarea dat? pentru parametru.*/

CREATE OR REPLACE PROCEDURE p4 (cod employees.employee_id %TYPE := 100)
IS
    v_nr NUMBER;
    CURSOR c_subordonati IS (SELECT employee_id
                            FROM emp_lco
                            WHERE level > 1
                            START WITH employee_id = cod
                            CONNECT BY manager_id = PRIOR employee_id);
    v_cod_ang employees.employee_id%TYPE;
    v_nr_linii NUMBER := 0;
BEGIN
    SELECT COUNT(*) INTO v_nr
    FROM emp_lco
    WHERE manager_id = cod;
    

    IF v_nr = 0 THEN
        INSERT INTO info_lco
        VALUES (user, SYSDATE, 'SELECT', v_nr, 'Nu ex ang cu cod');
        RETURN;
    END IF;
    
    OPEN c_subordonati;
    
    LOOP
    FETCH c_subordonati INTO v_cod_ang;
    EXIT WHEN c_subordonati%NOTFOUND;
    UPDATE emp_lco
    SET salary = salary * 1.1
    WHERE employee_id = v_cod_ang;
    
    END LOOP;
    v_nr_linii := c_subordonati%ROWCOUNT;
    
    CLOSE c_subordonati;
    
    INSERT INTO info_lco
    VALUES(user,sysdate,'UPDATE',v_nr_linii,'Act. subord: ' || cod);
    
END;
/

BEGIN
    p4(100);
END;
/
SELECT * FROM info_lco;
SELECT * FROM emp_lco;


CREATE OR REPLACE PROCEDURE p5 IS
CURSOR c_dept IS
(SELECT department_name, zi, nr_ang
FROM departments 
LEFT JOIN (SELECT department_id,TO_CHAR(hire_date,'D') zi, COUNT(*) nr_ang
     FROM employees e
     GROUP BY department_id, TO_CHAR(hire_date,'D')
     HAVING COUNT(*) = (
                        SELECT MAX(COUNT(*))
                        FROM employees
                        GROUP BY employees.department_id, TO_CHAR(hire_date,'D')
                        HAVING department_id = e.department_id)
     ) USING (department_id));

BEGIN
    FOR linie IN c_dept LOOP
        IF linie.zi IS NULL THEN 
            DBMS_OUTPUT.PUT_LINE('In dep: ' || linie.department_name || ' nu exista angajati');
        ELSE 
            DBMS_OUTPUT.PUT_LINE(linie.department_name || ' cu ziua cu ang maxime: ' 
                                || linie.zi || ' cu nr ang: ' || linie.nr_ang);
    
            FOR ang IN (SELECT first_name, ROUND(SYSDATE-hire_date) vechime, salary * (1 + NVL(commission_pct,0)) sal
                        FROM employees
                        JOIN departments USING (department_id)
                        WHERE department_name = linie.department_name AND TO_CHAR(hire_date,'D') = linie.zi)
            LOOP
                DBMS_OUTPUT.PUT_LINE('Nume: ' || ang.first_name || 
                                    ' vechime: ' || ang.vechime || 
                                    ' venit: ' || ang.sal);
            END LOOP;
        END IF;
    DBMS_OUTPUT.PUT_LINE('--------------------------------');
    END LOOP;
END;
/

BEGIN
p5;
END;
/
                

--a) Creati o functie numita VALID_DEPTID_pnu pentru validarea unui cod de departament specificat ca parametru. 
---------Functia va întoarce o valoare booleana (TRUE daca departamentul exista).

CREATE OR REPLACE FUNCTION valid_deptid_lco (cod_dep departments.department_id%TYPE) RETURN BOOLEAN
IS
BEGIN
    FOR c IN (SELECT department_id FROM departments) LOOP
        IF c.department_id = cod_dep 
                THEN RETURN TRUE;
        END IF;
    END LOOP;
    RETURN FALSE;
END;
/

SET SERVEROUTPUT ON;


--b) Creati o procedura numit ADD_EMP_pnu care adauga un angajat în tabelul EMP_pnu. 
-------- Linia respectiva va fi adugata în tabel doar daca departamentul specificat este valid, altfel utilizatorul va primi un mesaj adecvat.
-------- Procedura va avea urmatorii parametrii, cu valorile DEFAULT specificate între paranteze: 
-------- first_name, last_name, email, job_id (SA_REP), manager_id (145), salary (1000), commission_pct (0), department_id (30).
-------- Pentru codul angajatului se va utiliza o secventa EMP_SEQ_pnu, iar data angajrii se considera a fi TRUNC(SYSDATE).

CREATE OR REPLACE PROCEDURE add_emp_lco (first_name employees.first_name%TYPE,
                                        last_name employees.last_name%TYPE,
                                        email employees.email%TYPE,
                                        job_id employees.job_id%TYPE DEFAULT 'SA_REP',
                                        manager_id employees.manager_id%TYPE DEFAULT 145,
                                        salary employees.salary%TYPE DEFAULT 1000,
                                        commission_pct employees.commission_pct%TYPE DEFAULT 0,
                                        department_id employees.department_id%TYPE DEFAULT 30)
IS
val BOOLEAN;
BEGIN
    val := valid_deptid_lco(department_id);
    IF val = TRUE 
        THEN 
            INSERT INTO emp_lco (employee_id, first_name, last_name, email, hire_date, job_id, salary, commission_pct, manager_id, department_id) 
            VALUES (EMP_LCO_seq.nextval,first_name, last_name, email, TRUNC(sysdate), job_id, salary, commission_pct, manager_id, department_id);
    ELSE    DBMS_OUTPUT.PUT_LINE('Codul departamentului nu e valid');
    END IF;
END;
/

CREATE SEQUENCE emp_lco_seq
 START WITH     207
 INCREMENT BY   1
 NOCACHE
 NOCYCLE;

SELECT all_sequences FROM DUAL;


/*c) Testati procedura, adugând un angajat pentru care se specifica numele, prenumele, codul departamentului = 15 (?),
iar restul parametrilor se lasa DEFAULT.
Adugati un angajat pentru care se specifica numele, prenumele, codul departamentului =80, iar restul parametrilor ramân la valorile DEFAULT.
Adaugati un angajat precizând valori pentru toti parametrii procedurii.*/

BEGIN
    add_emp_lco('Richard', 'Castle', 'RICHARDCASTLE', department_id =>20);
END;
/
SELECT * FROM emp_lco ORDER BY 1;

select * FROM job_history;

--angajatii care au avut cele mai multe job-uri cod nume si job_id
DECLARE
PROCEDURE joburi_max 
IS
BEGIN
    FOR c IN (SELECT e.employee_id, e.last_name, e.job_id 
             FROM employees e
             JOIN job_history j ON (e.employee_id = j.employee_id)
             GROUP BY e.employee_id, e.last_name, e.job_id 
             HAVING COUNT(j.job_id) = ( SELECT MAX(COUNT(job_id))
                                             FROM job_history
                                             GROUP BY employee_id))
    LOOP
        DBMS_OUTPUT.PUT_LINE('Cod ang: ' || c.employee_id || 
                            ' nume: ' || c.last_name || 
                            ' job_id: ' || c.job_id);
    END LOOP;
END;
BEGIN
    joburi_max;
END;


/*1. Subprogram care populeaz? tabelul info cu informa?ii (pentru fiecare cod de angajat se re?in codurile utilajelor 
pe care le-a folosit ?i num?rul total de ore de munc? pe aceste utilaje).*/
CREATE OR REPLACE PROCEDURE pop_info
IS
t utilaje := utilaje();
BEGIN
    FOR i IN (SELECT cod_ang FROM angajat) LOOP
        DBMS_OUTPUT.PUT_LINE(i.cod_ang);
        SELECT pereche2(id_utilaj, SUM(nr_ore)) BULK COLLECT INTO t
        FROM lucreaza
        WHERE cod_angajat = i.cod_ang
        GROUP BY id_utilaj;
        --INSERT INTO info VALUES (i.cod_ang, t);
    END LOOP;
    
    FOR i IN (SELECT * FROM info) LOOP
        DBMS_OUTPUT.PUT_LINE('Angajatul ' || i.cod);
        IF i.fisa.COUNT != 0 THEN
        FOR j IN i.fisa.FIRST..i.fisa.LAST LOOP
            DBMS_OUTPUT.PUT_LINE(i.fisa(j).id_u || ' ' || i.fisa(j).ore);    
        END LOOP;
        DBMS_OUTPUT.NEW_LINE;
        END IF;
    END LOOP;
END;
/

SELECT * FROM INFO;
SET SERVEROUTPUT ON

BEGIN
pop_info;
END;
/


SELECT * FROM note;
SELECT * FROM curs;
SELECT * FROM student;
SELECT * FROM profesor;

/*2. Crea?i un subprogram care prime?te ca parametru un num?r natural n. 
Pentru studen?ii care au acumulat mai mult de n credite se vor returna num?rul matricol, 
CNP-ul ?i cel mai mare num?r de credite pe care l-au acumulat la un singur examen.*/
CREATE OR REPLACE TYPE obj_stud IS OBJECT
    (nr_mat NUMBER(20),
    cnp VARCHAR2(20),
    max_credite NUMBER(20));
/
CREATE OR REPLACE TYPE tab_stud IS TABLE OF obj_stud;
/
CREATE OR REPLACE PROCEDURE credite_studenti(n IN NUMBER, 
                            t OUT tab_stud)

IS
nr_credite NUMBER := 0;
max_nr NUMBER := 0;
BEGIN
    t := tab_stud();
    FOR i IN (SELECT * FROM student) LOOP
        SELECT SUM(nr_credite * DECODE(nota, 4, 0, nota)) INTO nr_credite
        FROM note 
        JOIN curs USING(cod_curs)
        WHERE cod_student = i.cod_student;
        
        --DBMS_OUTPUT.PUT_LINE(i.nr_matricol || ' nr credite ' || nr_credite);
        
        IF nr_credite IS NOT NULL AND nr_credite > n THEN
        --DBMS_OUTPUT.PUT_LINE(nr_credite);
            SELECT MAX(nr_credite * DECODE(nota, 4, 0, nota)) INTO max_nr
            FROM note 
            JOIN curs USING(cod_curs)
            WHERE cod_student = i.cod_student;
            
            t.extend;
            t(t.last) := obj_stud(i.nr_matricol, i.cnp, max_nr);
        END IF;
    END LOOP;
END;
/

DECLARE
t tab_stud;
BEGIN
    credite_studenti(69, t);
    FOR i IN t.FIRST..t.LAST LOOP
    DBMS_OUTPUT.PUT_LINE(t(i).nr_mat || ' ' || t(i).cnp || ' ' || t(i).max_credite);
    END LOOP;
END;
/


/*3. Subprogram care prime?te ca parametru un cod de angajat ?i 
returneaz? lista pacien?ilor de  care  acesta  a  avut grij?,  
împreun?  cu  num?rul  de  zile  de  internare  pentru  fiecare pacient (indiferent de angajat).*/

SELECT * FROM trateaza order by 1, 2;
SELECT * FROM pacienti;
SELECT * FROM personal;
SELECT * FROM specializare;
SELECT * FROM functii;

CREATE OR REPLACE TYPE date_pacient IS OBJECT
    (pacient NUMBER,
    nr_zile NUMBER);
/
CREATE OR REPLACE TYPE tab_pacient IS TABLE OF date_pacient;
/
CREATE OR REPLACE PROCEDURE medici(cod_ang IN NUMBER, t OUT tab_pacient)
IS
BEGIN
    t := tab_pacient();
    SELECT date_pacient(id_pacient, SUM(data_externare-data_internare)) BULK COLLECT INTO t
    FROM trateaza
    WHERE id_salariat = cod_ang
    GROUP BY id_pacient;
END;
/

DECLARE
t tab_pacient;
BEGIN
    medici(22, t);
    IF t.COUNT != 0 THEN
        FOR i IN t.FIRST..t.LAST LOOP
            DBMS_OUTPUT.PUT_LINE(t(i).pacient || ' ' || t(i).nr_zile);
        END LOOP;
    END IF;
END;
/

/*Adauga o coloana in tabelul turist care sa contina pt fiecare turist nr de zile pentru fiecare excursie achizitionata.*/
CREATE OR REPLACE TYPE date_excur IS OBJECT
    (cod_ex NUMBER,
    nr_zile NUMBER);
    /
    
CREATE OR REPLACE TYPE tab_excur IS TABLE OF date_excur;
/

ALTER TABLE turist
ADD (date_ex tab_excur)
NESTED TABLE date_ex STORE AS turist_excursii;

DECLARE
t tab_excur;
BEGIN
    FOR i IN (SELECT * FROM turist) LOOP
    SELECT date_excur(ac.cod_excursie, SUM(durata)) BULK COLLECT INTO t
    FROM achizitioneaza ac
    JOIN excursie ex ON(ex.id_excursie = ac.cod_excursie)
    WHERE cod_turist = i.id_turist
    GROUP BY ac.cod_excursie;
    UPDATE turist
    SET date_ex = t
    WHERE id_turist = i.id_turist;
    END LOOP;
    
END;
/


SELECT * FROM cazare;
SELECT * FROM rezervare;
SELECT * FROM camera;
SELECT * FROM hotel;


/*. Functie care primeste drept parametri un id de camera, o data de sosire, respectiv o data de plecare si 
returneaza daca se poate efectua sau nu o cazare cu datele transmise 
(pentru înregistr?rile în care data_plecare este null, considera?i ocupat? camera doar în ziua sosirii). 
Se poate folosi aceasta functie in cadrul unui trigger care sa valideze operatiile pe tabelul cazare?*/

CREATE OR REPLACE FUNCTION valid_camera(camera NUMBER,
                                        sosire DATE,
                                        plecare DATE)
RETURN NUMBER
IS

BEGIN
    FOR i IN (SELECT data_sosire sos, data_plecare plec, id_camera
            FROM cazare
            WHERE id_camera = camera) LOOP

        IF plecare IS NOT NULL THEN
            IF i.plec IS NOT NULL AND sosire <= i.plec AND plecare >= i.sos 
                THEN return 0;
            ELSIF i.plec IS NULL AND sosire <= i.sos AND plecare >= i.sos 
                THEN return 0;
            END IF;
        ELSE
            IF i.plec IS NOT NULL AND sosire >= i.sos AND sosire <= i.plec THEN return 0;
            ELSIF i.plec IS NULL AND sosire = i.sos  
                THEN return 0;
            END IF;
        END IF;
        
    END LOOP;
    return 1;
END;
/

BEGIN
DBMS_OUTPUT.PUT_LINE(valid_camera(2,TO_DATE('20-JAN-12','DD-MON-YY'),null));
END;
/
