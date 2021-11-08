/*Laborator 2, Exercitiul 27 --- tema --- 
S? se afi?eze numele salariatului ?i data angaj?rii împreun? cu numele ?i data angaj?rii
?efului direct pentru salaria?ii care au fost angaja?i înaintea ?efilor lor. Se vor eticheta
coloanele Angajat, Data_ang, Manager si Data_mgr.*/

SELECT e1.first_name AS "Angajat",e1.hire_date AS "Data_ang" ,e2.first_name AS "Manager", e2.hire_date AS "Data_mgr"
FROM employees e1
JOIN employees e2 ON(e1.manager_id = e2.employee_id AND e1.hire_date<e2.hire_date);


/*Laborator 2, Exercitiul 25 --- tema ---
S? se listeze structura tabelului JOBS. Crea?i o cerere prin care s? se afi?eze numele,
codul job-ului, titlul job-ului, numele departamentului ?i salariul angaja?ilor.
*/
DESC jobs;
SELECT e.last_name , j.job_id , j.job_title , d.department_name , e.salary
FROM jobs j
JOIN employees e ON(j.job_id = e.job_id)
JOIN departments d ON(e.department_id = d.department_id);
