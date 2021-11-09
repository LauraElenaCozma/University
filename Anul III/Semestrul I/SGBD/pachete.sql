----- PACHETE ------

/*1. Defini?i un pachet care permite prin intermediul a dou? func?ii calculul num?rului de angaja?i ?i
suma ce trebuie alocat? pentru plata salariilor ?i a comisioanelor pentru un departament al c?rui
cod este dat ca parametru.*/

CREATE OR REPLACE PACKAGE pachet_1
AS
FUNCTION f_numar(v_dept dept_lco.department_id%TYPE)
    RETURN number;
FUNCTION f_suma(v_dept dept_lco.department_id%TYPE)
    RETURN number;
END pachet_1;
/

CREATE OR REPLACE PACKAGE BODY pachet_1
AS
FUNCTION f_numar(v_dept dept_lco.department_id%TYPE)
RETURN NUMBER IS numar NUMBER;
BEGIN
SELECT COUNT(*) INTO numar
FROM emp_lco
WHERE department_id = v_dept;
RETURN numar;
END;

FUNCTION f_suma(v_dept dept_lco.department_id%TYPE)
RETURN NUMBER IS suma NUMBER;
BEGIN
SELECT SUM(salary + salary * NVL(commission_pct, 0)) INTO suma
FROM emp_lco
WHERE department_id = v_dept;
RETURN suma;
END;
END;
/

---- APEL
SELECT pachet_1.f_suma(100), pachet_1.f_numar(100)
FROM dual;

/*2. Crea?i un pachet ce include ac?iuni pentru ad?ugarea unui nou departament în tabelul dept_*** ?i
a unui nou angajat (ce va lucra în acest departament) în tabelul emp_***. Procedurile pachetului
vor fi apelate din SQL, respectiv din PL/SQL. Se va verifica dac? managerul departamentului
exist? înregistrat ca salariat. De asemenea, se va verifica dac? loca?ia departamentului exist?.
Pentru inserarea codului salariatului se va utiliza o secven??.*/
CREATE OR REPLACE PACKAGE pachet_2
AS 
PROCEDURE add_employee(v_first_name emp_lco.first_name%TYPE,
                        v_last_name emp_lco.last_name%TYPE,
                        v_email emp_lco.email%TYPE,
                        v_phone_number emp_lco.phone_number%TYPE:=NULL,
                        v_hire_date emp_lco.hire_date%TYPE :=SYSDATE,
                        v_job_id emp_lco.job_id%TYPE,
                        v_salary emp_lco.salary%TYPE :=0,
                        v_commission_pct emp_lco.commission_pct%TYPE:=0,
                        v_manager_id emp_lco.manager_id%TYPE,
                        v_department_id emp_lco.department_id%TYPE);

FUNCTION is_valid (v_manager dept_lco.manager_id%TYPE,
                    v_loc dept_lco.location_id%TYPE)
RETURN number;
END;
/

CREATE OR REPLACE PACKAGE BODY pachet_2
AS 
PROCEDURE add_employee(v_first_name emp_lco.first_name%TYPE,
                        v_last_name emp_lco.last_name%TYPE,
                        v_email emp_lco.email%TYPE,
                        v_phone_number emp_lco.phone_number%TYPE:=NULL,
                        v_hire_date emp_lco.hire_date%TYPE :=SYSDATE,
                        v_job_id emp_lco.job_id%TYPE,
                        v_salary emp_lco.salary%TYPE :=0,
                        v_commission_pct emp_lco.commission_pct%TYPE:=0,
                        v_manager_id emp_lco.manager_id%TYPE,
                        v_department_id emp_lco.department_id%TYPE)
AS
BEGIN
INSERT INTO emp_lco
VALUES(emp_lco_seq.NEXTVAL,v_first_name, v_last_name, v_email, v_phone_number,
v_hire_date, v_job_id, v_salary, v_commission_pct, v_manager_id, v_department_id);
END;
FUNCTION is_valid (v_manager dept_lco.manager_id%TYPE,
                    v_loc dept_lco.location_id%TYPE)
    RETURN number
IS
rez_loc NUMBER;
rez_manag NUMBER;
rezultat NUMBER := 1;
BEGIN
    SELECT COUNT(*) INTO rez_loc
    FROM locations
    WHERE location_id = v_loc;
    
    SELECT COUNT(*) INTO rez_manag
    FROM emp_lco
    WHERE employee_id = v_manager;
    IF rez_loc = 0 OR rez_manag = 0 THEN
        rezultat := 0;
    END IF;
    RETURN rezultat;
END;
PROCEDURE add_department(v_cod dept_lco.department_id%TYPE,
                        v_nume dept_lco.department_name%TYPE,
                        v_manager dept_lco.manager_id%TYPE,
                        v_loc dept_lco.location_id%TYPE)
IS
BEGIN
IF is_valid(v_manager, v_loc) = 1 THEN
    INSERT INTO dept_lco (department_id, department_name, manager_id, location_id)
    VALUES (v_cod, v_nume, v_manager, v_loc);
ELSE 
    RAISE_APPLICATION_ERROR(-20001, 'Valorile introduse pentru dep sunt incorecte');
END IF;
END;
END;
/

EXECUTE pachet_2.add_department(201,'Economic',200, 2000);

EXECUTE pachet_2.add_department(202,'Economic',200,3);

SELECT * FROM locations order by 1;
ROLLBACK;


/*3. Defini?i un pachet cu ajutorul c?ruia s? se ob?in? salariul maxim înregistrat pentru salaria?ii care
lucreaz? într-un anumit ora? ?i lista salaria?ilor care au salariul mai mare sau egal decât acel
maxim. Pachetul va con?ine un cursor ?i un subprogram func?ie.*/

CREATE OR REPLACE PACKAGE pachet_3
AS
FUNCTION sal_max(v_oras locations.city%TYPE) RETURN NUMBER;
CURSOR c(max_sall NUMBER) 
    RETURN employees%ROWTYPE;
END;
/

CREATE OR REPLACE PACKAGE BODY pachet_3
AS
CURSOR c(max_sall NUMBER) RETURN employees%ROWTYPE
IS 
    SELECT * FROM employees
    WHERE salary >= max_sall;

FUNCTION sal_max(v_oras locations.city%TYPE) RETURN NUMBER
IS
    max_sal NUMBER;
BEGIN
    SELECT MAX(salary) INTO max_sal
    FROM employees
    JOIN departments USING(department_id)
    JOIN locations USING (location_id)
    WHERE UPPER(city) = UPPER(v_oras);
    RETURN max_sal;
END;
END;
/

DECLARE
sal employees.salary%TYPE;
BEGIN
    sal := pachet_3.sal_max('Oxford');
    DBMS_OUTPUT.PUT_LINE(sal);
    FOR i IN pachet_3.c(sal) LOOP
        DBMS_OUTPUT.PUT_LINE(i.last_name || ' ');
    END LOOP;
END;
/
SET SERVEROUTPUT ON;
SELECT * FROM employees 
JOIN departments USING(department_id)
JOIN locations USING (location_id)
ORDER BY city;

/*4. Defini?i un pachet care s? con?in? o procedur? prin care se verific? dac? o combina?ie specificat?
dintre câmpurile employee_id ?i job_id este o combina?ie care exist? în tabelul employees.*/
-- ATENTIE: Abordare diferita, cu cursor

CREATE OR REPLACE PACKAGE pachet_4
IS
PROCEDURE exista_comb(cod_ang employees.employee_id%TYPE,
                      cod_job employees.job_id%TYPE);
CURSOR c RETURN employees%ROWTYPE;
END;
/

CREATE OR REPLACE PACKAGE BODY pachet_4
IS
CURSOR c RETURN employees%ROWTYPE
IS
    SELECT * 
    FROM employees;
    
PROCEDURE exista_comb(cod_ang employees.employee_id%TYPE,
                      cod_job employees.job_id%TYPE)
IS
gasit NUMBER := 0;
ang employees%ROWTYPE;
BEGIN
    OPEN c;
    LOOP
        FETCH c INTO ang;
        EXIT WHEN c%NOTFOUND;
        IF ang.employee_id = cod_ang AND UPPER(ang.job_id) = UPPER(cod_job)
            THEN
                gasit := 1;
                EXIT;
        ELSIF ang.employee_id = cod_ang
           THEN EXIT;
        END IF;
    END LOOP;
    IF gasit > 0 THEN 
        DBMS_OUTPUT.PUT_LINE('Exista ');
    ELSE 
        DBMS_OUTPUT.PUT_LINE('Nu exista');
    END IF;
    CLOSE c;
END;
END;
/
EXECUTE pachet_4.exista_comb(100, 'IT_PROG');

SELECT * FROM employees;


--Exercitii propuse
/*1. Defini?i un pachet care s? permit? gestiunea angaja?ilor companiei. Pachetul va con?ine:*/
/*a. o procedur? care determin? ad?ugarea unui angajat, dându-se informa?ii complete despre
acesta:
- codul angajatului va fi generat automat utilizându-se o secven??;
- informa?iile personale vor fi date ca parametrii (nume, prenume, telefon, email);
- data angaj?rii va fi data curent?;
- salariul va fi cel mai mic salariu din departamentul respectiv, pentru jobul respectiv (se
vor ob?ine cu ajutorul unei func?ii stocate în pachet);
- nu va avea comision;
- codul managerului se va ob?ine cu ajutorul unei func?ii stocate în pachet care va avea ca
parametrii numele ?i prenumele managerului);
- codul departamentului va fi ob?inut cu ajutorul unei func?ii stocate în pachet, dându-se
ca parametru numele acestuia;
- codul jobului va fi ob?inut cu ajutorul unei func?ii stocate în pachet, dându-se ca
parametru numele acesteia.
Observa?ie: Trata?i toate excep?iile.*/


CREATE OR REPLACE PACKAGE pachet_5
IS
PROCEDURE add_employee (v_first_name emp_lco.first_name%TYPE,
                        v_last_name emp_lco.last_name%TYPE,
                        v_email emp_lco.email%TYPE,
                        v_phone_number emp_lco.phone_number%TYPE,
                        v_nume_job jobs.job_title%TYPE,
                        v_manager_prenume emp_lco.first_name%TYPE,
                        v_manager_nume emp_lco.last_name%TYPE, 
                       v_department_name dept_lco.department_name%TYPE);
FUNCTION get_salary(v_cod_dep employees.department_id%TYPE,
                    v_job_id employees.job_id%TYPE)
RETURN NUMBER;
FUNCTION get_manager(v_manager_nume emp_lco.last_name%TYPE,
                    v_manager_prenume emp_lco.first_name%TYPE)
    RETURN emp_lco.employee_id%TYPE;
FUNCTION get_department(v_nume_dep dept_lco.department_name%TYPE)
    RETURN emp_lco.department_id%TYPE;
FUNCTION get_job(v_nume_job jobs.job_title%TYPE)
    RETURN emp_lco.job_id%TYPE;
END;
/

CREATE OR REPLACE PACKAGE BODY pachet_5
IS
PROCEDURE add_employee (v_first_name emp_lco.first_name%TYPE,
                        v_last_name emp_lco.last_name%TYPE,
                        v_email emp_lco.email%TYPE,
                        v_phone_number emp_lco.phone_number%TYPE,
                        v_nume_job jobs.job_title%TYPE,
                        v_manager_prenume emp_lco.first_name%TYPE,
                        v_manager_nume emp_lco.last_name%TYPE, 
                       v_department_name dept_lco.department_name%TYPE)
    IS
        cod_dep departments.department_id%TYPE;
        cod_job jobs.job_id%TYPE;
        sal emp_lco.salary%TYPE;
        cod_manager emp_lco.manager_id%TYPE;
    BEGIN
        cod_dep := get_department(v_department_name);
        cod_job := get_job(v_nume_job);
        sal := get_salary(cod_dep, cod_job);
        cod_manager := get_manager(v_manager_nume, v_manager_prenume);
        INSERT INTO emp_lco
        VALUES (emp_lco_seq.NEXTVAL, v_first_name, v_last_name, v_email, v_phone_number,
                sysdate, cod_job, sal, NULL, cod_manager, cod_dep);
    END;

FUNCTION get_salary(v_cod_dep employees.department_id%TYPE,
                    v_job_id employees.job_id%TYPE)
    RETURN NUMBER
    AS
        min_sal employees.salary%TYPE;
    BEGIN
        SELECT MIN(salary) INTO min_sal
        FROM employees
        WHERE department_id = v_cod_dep AND UPPER(job_id) = UPPER(v_job_id);
        IF min_sal = NULL           --nu mai exista o astfel de combinatie
            THEN min_sal := 1000;
        END IF;
        RETURN min_sal;
    END;


FUNCTION get_manager(v_manager_nume emp_lco.last_name%TYPE,
                    v_manager_prenume emp_lco.first_name%TYPE)
    RETURN emp_lco.employee_id%TYPE
    IS
        cod emp_lco.employee_id%TYPE := 0;
    BEGIN
        SELECT employee_id INTO cod
        FROM emp_lco
        WHERE UPPER(v_manager_nume) = UPPER(last_name)
        AND UPPER(v_manager_prenume) = UPPER(first_name);
        EXCEPTION
        WHEN NO_DATA_FOUND
            THEN RAISE_APPLICATION_ERROR(-20001, 'Date incorecte');
        RETURN cod;
    END;


FUNCTION get_department(v_nume_dep dept_lco.department_name%TYPE)
    RETURN emp_lco.department_id%TYPE
    IS
        dep_id emp_lco.department_id%TYPE := 0;
    BEGIN
        SELECT department_id INTO dep_id
        FROM departments
        WHERE UPPER(department_name) = UPPER(v_nume_dep);
        EXCEPTION
        WHEN NO_DATA_FOUND
            THEN RAISE_APPLICATION_ERROR(-20001, 'Date incorecte');
        RETURN dep_id;
    END;

FUNCTION get_job(v_nume_job jobs.job_title%TYPE)
    RETURN emp_lco.job_id%TYPE
    IS
        j_id emp_lco.job_id%TYPE;
    BEGIN
        SELECT job_id INTO j_id
        FROM jobs
        WHERE UPPER(job_title) = UPPER(v_nume_job);
        EXCEPTION
        WHEN NO_DATA_FOUND
            THEN RAISE_APPLICATION_ERROR(-20001, 'Date incorecte');
        RETURN j_id;
    END;
END;
/
SELECT * FROM jobs;

EXECUTE pachet_5.add_employee('Emilia', 'Clarke', 'ECLARKE', '0739111920', 'Accountant', 'Steven', 'King', 'IT');

SELECT * FROM emp_lco ORDER BY 1;


