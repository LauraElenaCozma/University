-- lab 2 refacere pentru antrenament --
--1
SELECT first_name || ' ' || last_name || ' castiga ' || salary || ' lunar dar doreste ' || salary * 3 "Salariu ideal"
from employees;

SELECT concat(first_name,concat(' ', concat(last_name, concat(' castiga ', concat( salary, concat(' dar doreste ' , salary * 3))))) ) "Salariu ideal"
from employees;

--2
SELECT INITCAP(first_name) "Prenume", last_name "Nume", LENGTH(last_name) "Lungime"
from  employees
WHERE UPPER(last_name) LIKE 'J%' OR UPPER(last_name) LIKE 'M%' OR UPPER(last_name) LIKE '__A%'
ORDER BY 3;
-- v2

SELECT INITCAP(first_name) "Prenume", last_name "Nume", LENGTH(last_name) "Lungime"
from  employees
WHERE UPPER(SUBSTR(last_name,1,1)) = 'J'
    OR UPPER(SUBSTR(last_name,1,1)) = 'M'
    OR  UPPER(SUBSTR(last_name,3,1)) = 'A'
ORDER BY 3;

-- 3
SELECT employee_id, last_name
from employees
WHERE upper(TRIM(BOTH FROM first_name)) = 'STEVEN';

--4
SELECT employee_id, last_name, INSTR(LOWER(last_name), 'a')
FROM employees
where UPPER(last_name) LIKE '%E';

--5
SELECT *
FROM employees
WHERE MOD(ROUND(sysdate - hire_date),7) = 0;
--6
SELECT employee_id, last_name, salary, ROUND(salary * 1.15,2), ROUND(salary * 0.0115,2)
FROM employees
WHERE mod(SALARY,1000) <> 0;

--7
SELECT last_name, RPAD(hire_date,LENGTH(hire_date)+5)
FROM employees
WHERE commission_pct IS NOT NULL;

--8
SELECT TO_CHAR(sysdate + 30, 'MONTH-DD-YYYY hh:mm:ss') 
FROM dual;

--9
SELECT last_day(sysdate) - sysdate
FROM dual;

--10
SELECT TO_CHAR(sysdate + 1/2 , 'DD/MM/YYYY')
FROM dual;

--b de peste 5 min
SELECT TO_CHAR(sysdate + INTERVAL '5' MINUTE , 'HH:MI')
FROM dual;

--11
select last_name, NEXT_DAY(ADD_MONTHS(hire_date, 6), 'Monday')
FROM employees;

--12
SELECT employee_id, ROUND(months_between(sysdate, hire_datE))
from employees
order by 2;

--13
select last_name, to_char(hire_date, 'day')
from employees;

--14
SELECT last_name, DECODE(commission_pct, NULL, 'Fara comision', commission_pct) "Comision"
FROM employees;
SELECT last_name, NVL(TO_CHAR(commission_pct), 'Fara comision') "Comision"
FROM employees;

--16
SELECT last_name, job_id, salary,DECODE(upper(job_id), 'IT_PROG', salary * 1.2,  'SA_REP', salary * 1.25, 'SA_MAN' , salary * 1.35, salary) "SALARIU RENEGOCIAT"
FROM employees;

--17
SELECT last_name, department_id, department_name
FROM employees
JOIN departments USING(department_id);

--18
SELECT DISTINCT job_title
FROM jobs
JOIN employees USING(job_id)
WHERE department_id = 30;

--19
SELECT last_name, department_name, city
FROM employees
JOIN departments USING(department_id)
JOIN locations USING(location_id)
WHERE commission_pct IS NOT NULL;

--20
SELECT last_name, department_name
FROM employees
JOIN departments USING(department_id)
WHERE lower(last_name) LIKE '%a%';

--21
SELECT last_name, job_id, department_id, department_name
FROM employees
JOIN departments USING(department_id)
JOIN locations USING(location_id)
WHERE initcap(city) = 'Oxford';

--22
SELECT e1.employee_id "Ang#", e1.last_name "Angajat", e2.employee_id "Mgr#", e2.last_name "Manager"
FROM employees e1
JOIN employees e2 ON(e1.employee_id = e2.manager_id);

--23
SELECT e1.employee_id "Ang#", e1.last_name "Angajat", e2.employee_id "Mgr#", e2.last_name "Manager"
FROM employees e1
LEFT JOIN employees e2 ON(e1.employee_id = e2.manager_id);

--24
SELECT e1.employee_id, e1.department_id, e2.employee_id
FROM employees e1
JOIN employees e2 ON(e1.department_id = e2.department_id AND e1.employee_id <> e2.employee_id)
ORDER BY 1;

--26
SELECT last_name, hire_date
FROM employees
WHERE hire_date > (SELECT hire_date
                    FROM employees
                    WHERE UPPER(last_name) = 'GATES');
                    
SELECT e.last_name, e.hire_date, g.last_name, g.hire_date
FROM employees e
JOIN employees g ON(e.hire_date > g.hire_date AND INITCAP(g.last_name) LIKE '%Gates%');

--27
SELECT e1.employee_id "Ang#", e1.last_name "Angajat" ,e1.hire_date, e2.employee_id "Mgr#", e2.last_name "Manager", e2.hire_date
FROM employees e1
JOIN employees e2 ON(e1.employee_id = e2.manager_id AND e1.hire_date < e2.hire_date);
