

----------------- PACHETE --------------
CREATE OR REPLACE PACKAGE pachet1
IS
    
/*CURSOR c_emp(cod_job VARCHAR2)
    RETURN emp_lco%ROWTYPE;*/

/*CURSOR c_job
    RETURN jobs_lco%ROWTYPE;*/
    
FUNCTION get_salary(cod_dep employees.department_id%TYPE,
                    cod_job employees.job_id%TYPE)
        RETURN NUMBER;
        
FUNCTION get_manager(nume employees.last_name%TYPE,
                    prenume employees.first_name%TYPE)
        RETURN NUMBER;
        
FUNCTION get_dept(nume_dept departments.department_name%TYPE)
        RETURN NUMBER;
        
FUNCTION get_job(nume_job jobs.job_title%TYPE)
        RETURN VARCHAR2;
PROCEDURE add_emp(
    nume VARCHAR2,
    prenume VARCHAR2,
    telefon VARCHAR2,
    email VARCHAR2,
    nume_job VARCHAR2,
    nume_dep VARCHAR2,
    nume_manager VARCHAR2,
    prenume_manager VARCHAR2);

END pachet1;
/


CREATE OR REPLACE PACKAGE BODY pachet1
IS
FUNCTION get_salary(cod_dep employees.department_id%TYPE,
                    cod_job employees.job_id%TYPE)
        RETURN NUMBER
        IS
        v_sal employees.salary%TYPE;
        v_cod_dep NUMBER;
        v_cod_job NUMBER;
        BEGIN
        SELECT COUNT(department_id) INTO v_cod_dep
        FROM employees
        WHERE department_id = cod_dep;
        
        SELECT COUNT(job_id) INTO v_cod_job
        FROM employees
        WHERE job_id = cod_job;
        
        IF v_cod_dep = 0 OR v_cod_job = 0 THEN
            RAISE_APPLICATION_ERROR(-20001, 'Date incorecte');
        ELSE
        SELECT MIN(salary)
        INTO v_sal
        FROM employees
        WHERE department_id = cod_dep AND job_id = cod_job;
        END IF;
        RETURN v_sal;
        END;
FUNCTION get_manager(nume employees.last_name%TYPE,
                    prenume employees.first_name%TYPE)
        RETURN NUMBER
        IS
        v_manager_id NUMBER;
        BEGIN
        SELECT manager_id INTO v_manager_id
        FROM employees
        WHERE UPPER(last_name) = UPPER(nume) AND UPPER(first_name) = UPPER(prenume);
        
        RETURN v_manager_id;
        END;

FUNCTION get_dept(nume_dept departments.department_name%TYPE)
        RETURN NUMBER
        IS
        v_dept_id NUMBER;
        BEGIN
        SELECT department_id INTO v_dept_id
        FROM departments
        WHERE UPPER(department_name) = UPPER(nume_dept);
        RETURN v_dept_id;
        END;

FUNCTION get_job(nume_job jobs.job_title%TYPE)
        RETURN VARCHAR2
        IS
        v_job_id employees.job_id%TYPE;
        BEGIN
        SELECT job_id INTO v_job_id
        FROM jobs
        WHERE job_title = nume_job;
        RETURN v_job_id;
        END;

PROCEDURE add_emp(
    nume VARCHAR2,
    prenume VARCHAR2,
    telefon VARCHAR2,
    email VARCHAR2,
    nume_job VARCHAR2,
    nume_dep VARCHAR2,
    nume_manager VARCHAR2,
    prenume_manager VARCHAR2)
    IS
    v_cod_dep NUMBER;
    v_cod_job employees.job_id%TYPE;
    BEGIN
    v_cod_dep := get_dept(nume_dep);
    v_cod_job := get_job(nume_job);
    INSERT INTO emp_lco
    VALUES(SEQ.NEXTVAL, prenume, nume, email, telefon, SYSDATE,v_cod_job, 
        get_salary(v_cod_dep, v_cod_job), NULL, get_manager(prenume_manager, nume_manager), v_cod_dep, 100);
    END;
END pachet1;
/
CREATE SEQUENCE seq INCREMENT BY 1
                    START WITH 1
                    MAXVALUE 999;
                    
                    
SELECT pachet1.get_salary(90, 'AD_PRES') FROM dual;

SELECT pachet1.get_manager('KING','STEVEN') FROM dual;

SELECT pachet1.get_dept('Sales') FROM dual;

SELECT pachet1.get_job('Programmer') FROM dual;

EXECUTE pachet1.add_emp('nume', 'prenume', '1',  '2', 'Programmer', 'Finance', 'Steven', 'King');
SELECT * FROM departments;
SELECT * FROM emp_lco;

DROP TRIGGER trig4;