--- TEMA LABORATOR 8 ---

-- Exercitiul 23 cu decode --
/*S? se afi?eze informa?ii despre departamente, în formatul urm?tor:*/
SELECT 'Departamentul ' || department_name || ' este condus de ' || NVL(TO_CHAR(manager_id),'nimeni') || ' ?i ' ||
       DECODE(numar , NULL , 'nu are salariati' , 'are num?rul de salaria?i ' || numar) AS "Informatii"
FROM departments
LEFT JOIN (SELECT department_id,COUNT(*) numar
            FROM employees
            GROUP BY department_id) USING(department_id);

-- Exercitiul 25 cu case --
/*S? se afi?eze numele, data angaj?rii, salariul ?i o coloan? reprezentând salariul dup? ce se
aplic? o m?rire, astfel: pentru salaria?ii angaja?i în 1989 cre?terea este de 20%, pentru cei angaja?i
în 1990 cre?terea este de 15%, iar salariul celor angaja?i în anul 1991 cre?te cu 10%.
Pentru salaria?ii angaja?i în al?i ani valoarea nu se modific?.*/

SELECT last_name, hire_date, salary, 
    CASE 
       WHEN TO_CHAR(hire_date , 'YYYY') LIKE '1989' THEN salary * 1.2
       WHEN TO_CHAR(hire_date , 'YYYY') LIKE '1990' THEN salary * 1.15
       WHEN TO_CHAR(hire_date , 'YYYY') LIKE '1991' THEN salary * 1.1
       ELSE salary
    END AS "Marire"
FROM employees;

-- Exercitiul 26 cu decode --
/*S? se afi?eze:
- suma salariilor, pentru job-urile care incep cu litera S;
- media generala a salariilor, pentru job-ul avand salariul maxim;
- salariul minim, pentru fiecare din celelalte job-uri.*/
SELECT job_id, DECODE(UPPER(job_id), 
                        'S%',SUM(salary),
                        (SELECT UPPER(job_id) FROM employees
                            WHERE salary = (SELECT MAX(salary) 
                                                FROM employees)),AVG(salary),
                        MIN(salary)) AS "Informatii"
FROM employees
GROUP BY job_id;

