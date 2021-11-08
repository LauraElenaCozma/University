
CREATE TABLE LOCATIONS_LCO
    (location_id NUMBER(4) PRIMARY KEY,
     location_name VARCHAR2(30) NOT NULL,
     city VARCHAR2(20) NOT NULL,
     country VARCHAR2(20) NOT NULL);
     
INSERT INTO LOCATIONS_LCO (location_id, location_name, city, country)
VALUES (1, 'Sala Polivalenta', 'Bucuresti', 'Romania');
INSERT INTO LOCATIONS_LCO (location_id, location_name, city, country)
VALUES (2, 'Arenele Romane', 'Bucuresti', 'Romania');
INSERT INTO LOCATIONS_LCO (location_id, location_name, city, country)
VALUES (3, 'Control Club', 'Bucuresti', 'Romania');
INSERT INTO LOCATIONS_LCO (location_id, location_name, city, country)
VALUES (4, 'Form Space', 'Cluj-Napoca', 'Romania');
INSERT INTO LOCATIONS_LCO (location_id, location_name, city, country)
VALUES (5, 'Casa de cultura', 'Roman', 'Romania');

SELECT * FROM locations_lco;



CREATE TABLE CLIENTS_LCO
    (cnp VARCHAR2(13) PRIMARY KEY,
     last_name VARCHAR2(20) NOT NULL,
     first_name VARCHAR2(25) NOT NULL,
     email VARCHAR2(20) UNIQUE,
     phone_number VARCHAR2(10) UNIQUE);  
    
SELECT * FROM clients_lco;
INSERT INTO CLIENTS_LCO(cnp, last_name, first_name, email, phone_number)
VALUES ('2992107340823', 'Mihalache', 'Miruna', 'miruna21@gmail.com', '0723342718');
INSERT INTO CLIENTS_LCO(cnp, last_name, first_name, email, phone_number)
VALUES ('2962001243401', 'Viorel', 'Eduard', 'ediviorel@gmail.com', '0723123712');
INSERT INTO CLIENTS_LCO(cnp, last_name, first_name, email, phone_number)
VALUES ('2728391992032', 'Anton', 'Lena', 'lenanton@yahoo.com', '0721120023');
INSERT INTO CLIENTS_LCO(cnp, last_name, first_name, email, phone_number)
VALUES ('1827392001923', 'Acsinte', 'Codrin', 'cody29@gmail.com', '0724120292');
INSERT INTO CLIENTS_LCO(cnp, last_name, first_name, email, phone_number)
VALUES ('1232127340422', 'Nechita', 'Sebastian', 'sebinechita@yahoo.ro', '0723342232');
INSERT INTO CLIENTS_LCO(cnp, last_name, first_name, email, phone_number)
VALUES ('2219227300022', 'Suhan', 'Magda', 'magdasuhan@yahoo.com', '0743342232');

CREATE TABLE BANDS_LCO
    (band_id NUMBER(4) PRIMARY KEY,
     band_name VARCHAR2(40) NOT NULL,
     musical_style VARCHAR2(20));
          
INSERT INTO BANDS_LCO 
VALUES (1, 'Hooverphonic','indie pop');
INSERT INTO BANDS_LCO 
VALUES (2, 'Florence and the Machine','indie pop');
INSERT INTO BANDS_LCO 
VALUES (3, 'byron','alternative rock');
INSERT INTO BANDS_LCO 
VALUES (4, 'The Mono Jacks','alternative rock');

SELECT * FROM bands_lco;


CREATE TABLE MUSICIANS_LCO
    (musician_id NUMBER(4) PRIMARY KEY,
     last_name VARCHAR2(20) NOT NULL,
     first_name VARCHAR2(20) NOT NULL,
     instrument VARCHAR2(15) NOT NULL,
     band_id NUMBER(4) REFERENCES BANDS_LCO(band_id) ON DELETE CASCADE,
     leader NUMBER(4) REFERENCES MUSICIANS_LCO(musician_id));
INSERT INTO MUSICIANS_LCO (musician_id, last_name, first_name, instrument, band_id)
VALUES (1, 'Byron', 'Dan', 'vocal', 3);
INSERT INTO MUSICIANS_LCO
VALUES (2, 'Mitrofan', 'Sergiu', 'clape', 3, 1);
INSERT INTO MUSICIANS_LCO
VALUES (3, 'Georgescu', 'Dan', 'chitara', 3, 1);
INSERT INTO MUSICIANS_LCO
VALUES (4, 'Summers', 'Isabella', 'vocal', 2, 5);
INSERT INTO MUSICIANS_LCO (musician_id, last_name, first_name, instrument, band_id)
VALUES (5, 'Welch', 'Florence', 'vocal', 2);
INSERT INTO MUSICIANS_LCO (musician_id, last_name, first_name, instrument, band_id)
VALUES (6, 'Cruysberghs', 'Luka', 'vocal', 1);
INSERT INTO MUSICIANS_LCO 
VALUES (8, 'Schimbo', 'Sulym', 'clape', 1, 6);
INSERT INTO MUSICIANS_LCO (musician_id, last_name, first_name, instrument, band_id)
VALUES (7, 'Trascau', 'Doru', 'chitara', 4);
INSERT INTO MUSICIANS_LCO
VALUES(9, 'Mirror', 'Stephen','harpa', 2, 5);

SELECT * FROM MUSICIANS_LCO;


CREATE TABLE CONCERTS_LCO
    (concert_id NUMBER(4) PRIMARY KEY,
     band_id NUMBER(4) REFERENCES BANDS_LCO(band_id) ON DELETE CASCADE,
     location_id NUMBER(4) REFERENCES LOCATIONS_LCO(location_id) ON DELETE CASCADE,
     concert_date DATE NOT NULL,
     concert_hour VARCHAR2(5) NOT NULL,
     price NUMBER(4) DEFAULT 0);
     
SELECT * FROM CONCERTS_LCO;

INSERT INTO concerts_lco
VALUES (1, 1, 2, TO_DATE('02/02/2021','DD/MM/YYYY'), '20:00', 60);
INSERT INTO concerts_lco
VALUES (2, 3, 1, TO_DATE('13/05/2021','DD/MM/YYYY'), '19:00', 90);
INSERT INTO concerts_lco
VALUES (3, 4, 3, TO_DATE('10/12/2021','DD/MM/YYYY'), '19:30', 40);
INSERT INTO concerts_lco
VALUES (4, 3, 2, TO_DATE('20/01/2021','DD/MM/YYYY'), '19:30', 25);
INSERT INTO concerts_lco
VALUES (5, 1, 4, TO_DATE('19/02/2021','DD/MM/YYYY'), '20:30', 50);
INSERT INTO concerts_lco
VALUES (6, 2, 3, TO_DATE('10/10/2020','DD/MM/YYYY'), '18:30', 55);
INSERT INTO concerts_lco
VALUES (7, 1, 1, TO_DATE('19/12/2020','DD/MM/YYYY'), '20:00', 100);
INSERT INTO concerts_lco
VALUES (8, 4, NULL, TO_DATE('19/02/2022','DD/MM/YYYY'), '20:00', 200);
INSERT INTO concerts_lco
VALUES (9, 1, NULL, TO_DATE('03/03/2021','DD/MM/YYYY'), '19:00', 15);
INSERT INTO concerts_lco
VALUES (10, 2, NULL, TO_DATE('30/11/2020','DD/MM/YYYY'), '19:30', 150);

CREATE TABLE BUY_LCO
    (ticket_id NUMBER(4) PRIMARY KEY,
     cnp VARCHAR2(20) REFERENCES CLIENTS_LCO(cnp) ON DELETE CASCADE,
     concert_id NUMBER(4) REFERENCES CONCERTS_LCO(concert_id) ON DELETE CASCADE,
     ticket_type VARCHAR(10)); --student, pensioner, child or nothing


INSERT INTO buy_lco
VALUES (1, '2962001243401', 2, 'student');
INSERT INTO buy_lco
VALUES (2, '2962001243401', 2, 'student');
INSERT INTO buy_lco (ticket_id, cnp, concert_id)
VALUES (3, '2962001243401', 2);
INSERT INTO buy_lco (ticket_id, cnp, concert_id)
VALUES (4, '1827392001923', 1);
INSERT INTO buy_lco (ticket_id, cnp, concert_id, ticket_type)
VALUES (5, '2219227300022', 6, 'pensionar');
INSERT INTO buy_lco(ticket_id, cnp, concert_id)
VALUES (6,'1232127340422', 7);
INSERT INTO buy_lco
VALUES (7,'1232127340422', 5, 'copil');
INSERT INTO buy_lco
VALUES (8, '1827392001923', 5, 'copil');
INSERT INTO buy_lco
VALUES (9, '2992107340823', 6, NULL);
INSERT INTO buy_lco
VALUES (10, '2992107340823', 7, NULL);
INSERT INTO buy_lco
VALUES(11,NULL, 4, NULL);
INSERT INTO buy_lco
VALUES(12,NULL, 5, NULL);
INSERT INTO buy_lco
VALUES(13,NULL, 6, NULL);

SELECT * FROM buy_lco;

SELECT * FROM buy_lco;
/*2.	S? se afi?eze numele clien?ilor, adresa de email, num?rul de telefon, id-ul concertului, data, tipul biletului ?i noul pre?ul dup? ce s-a aplicat un discount asupra pre?ului astfel:
- discount de 40% pentru studen?ii al caror num?r de telefon este în re?eaua Vodafone
- discount de 30% pentru studen?ii care au adres? de gmail
- discount de 25% pentru pensionarii care au achizi?ionat bilete din luna mai din orice an
- pre?ul este 0 pentru copiii înso?iti de cel pu?in un adult, student sau pensionar
- discount de 20% pentru cei care sunt pensionari, studen?i sau copii ?i nu se încadreaz? în categoriile de mai sus
- restul persoanelor nu vor primi discount*/
SELECT * FROM buy_lco;
SELECT DISTINCT last_name, first_name, email, phone_number, b.concert_id, ticket_type,
CASE 
WHEN (UPPER(ticket_type) = 'STUDENT' AND INSTR(phone_number,'072') = 1) THEN price * 0.6 
WHEN (UPPER(ticket_type) = 'STUDENT' AND LOWER(email) LIKE '%gmail%') THEN price * 0.7 
WHEN (UPPER(ticket_type) = 'PENSIONAR' AND TO_CHAR(concert_date,'MM') = '05') THEN price * 0.75
WHEN (UPPER(ticket_type) = 'COPIL' AND EXISTS (SELECT 1 FROM buy_lco WHERE b.cnp = cnp AND (ticket_type is NULL OR UPPER(ticket_type) <> 'COPIL'))) THEN 0
WHEN (UPPER(ticket_type) = 'STUDENT' OR UPPER(ticket_type) = 'PENSIONAR' OR UPPER(ticket_type) = 'COPIL') THEN price * 0.8
ELSE price
END "Pret dupa discount"
FROM clients_lco c
JOIN buy_lco b ON(c.cnp = b.cnp)
JOIN concerts_lco concert ON(concert.concert_id = b.concert_id)
ORDER BY 1;
/*1. S? se afi?eze concertele care au drept loca?ie pe cea unde au loc cele mai multe evenimente ?i trupa care particip? la concert are minim doi membri.*/
SELECT * 
FROM concerts_lco
WHERE location_id IN (SELECT location_id
                      FROM concerts_lco
                      WHERE location_id IS NOT NULL
                      GROUP BY location_id
                      HAVING COUNT(concert_id) = (SELECT MAX(COUNT(concert_id))
                                                  FROM concerts_lco
                                                  WHERE location_id IS NOT NULL
                                                  GROUP BY location_id))
AND band_id IN (SELECT band_id
                FROM bands_lco
                JOIN musicians_lco USING(band_id)
                GROUP BY band_id
                HAVING COUNT(musician_id) >= 2);
SELECT * FROM concerts_lco;

/*12.	S? se afi?eze clien?ii ale c?ror bilete la concerte au loc în mai pu?in de 6 luni fa?? de data curent?, al?turi de num?rul acestora pentru fiecare client. Se vor afi?a ?i biletele ce nu con?in cnp.*/
SELECT 'Clientul cu id-ul ' || cnp || ' cu numele ' || last_name || ' ' || first_name || ' are '|| nr_bilete || ' bilete in mai putin de 6 luni' "Detalii clienti"
FROM clients_lco
JOIN buy_lco USING(cnp)
RIGHT JOIN (SELECT COUNT(concert_id) nr_bilete, cnp 
      FROM buy_lco  
      JOIN concerts_lco USING(concert_id)
      WHERE MONTHS_BETWEEN(concert_date, sysdate) <= 6
      GROUP BY cnp) buy_aux USING (cnp)
WHERE nr_bilete > 0; 


/*9. S? se afi?eze cânt?re?ii care au primele dou? litere ale numelui de familie la fel ca primele dou? litere ale numelui de familie ale unei persoane care ?i-a cump?rat bilet la concertul acesteia.*/
SELECT musician_id, first_name, last_name
FROM musicians_lco m
WHERE LOWER(SUBSTR(m.last_name, 1, 2)) IN (SELECT LOWER(SUBSTR(last_name, 1, 2)) 
                                           FROM clients_lco
                                           JOIN buy_lco USING(cnp)
                                           JOIN concerts_lco USING(concert_id)
                                           JOIN bands_lco USING(band_id)
                                           WHERE m.band_id = band_id);
                                           

/*7.	S? se afi?eze cnp-ul clien?ilor care ?i-au luat bilete la concerte care au loc în minim dou? ora?e diferite sau la cel pu?in un concert care are mai mult de dou? persoane în trup?.*/
SELECT DISTINCT cnp
FROM buy_lco
JOIN concerts_lco USING (concert_id)
JOIN locations_lco USING (location_id)
WHERE cnp IS NOT NULL
GROUP BY cnp
HAVING COUNT(DISTINCT city) >= 2
UNION
SELECT DISTINCT cnp
FROM buy_lco b
JOIN concerts_lco c ON (c.concert_id = b.concert_id)
JOIN (SELECT band_id
      FROM bands_lco
      JOIN musicians_lco USING (band_id)
      GROUP BY band_id
      HAVING COUNT(musician_id) >= 2) aux ON (aux.band_id = c.band_id)
WHERE cnp IS NOT NULL;
                
                                
     
/*14.	S? se determine arti?tii(în ordine alfabetic?) trupelor care are drept gen muzical "indie pop" în ordine descresc?toare a câ?tigurilor din concertele din Bucure?ti, împreun? cu valoarea câ?tigului.*/
SELECT last_name, first_name, suma
FROM (SELECT band_id
      FROM bands_lco
      WHERE UPPER(musical_style) = 'INDIE POP') muz1
JOIN (SELECT band_id, SUM(price) suma
      FROM bands_lco
      JOIN concerts_lco USING (band_id)
      JOIN buy_lco USING (concert_id)
      JOIN locations_lco USING (location_id)
      WHERE UPPER(city) = 'BUCURESTI'
      GROUP BY band_id) muz2 ON (muz1.band_id = muz2.band_id)
JOIN musicians_lco m ON (m.band_id = muz2.band_id)
ORDER BY suma DESC, last_name;

/*8.	S? se afi?eze data ini?ial? ?i data actualizat? a concertelor peste dou? luni dac? îndeplinesc urm?toarele condi?ii:
-	au mai mult de 2 spectatori la concert
-	sunt din anul 2020*/
SELECT concert_id, band_name, concert_date, ADD_MONTHS(concert_date, 2)
FROM concerts_lco
JOIN bands_lco USING (band_id)
WHERE EXTRACT(YEAR FROM concert_date) = 2020 
AND  concert_id IN (SELECT concert_id
                    FROM concerts_lco
                    JOIN buy_lco USING (concert_id)
                    GROUP BY concert_id
                    HAVING COUNT(cnp) >= 2);

/*4.	S? se afi?eze toate datele calendaristice dintre cele mai îndep?rtate concerte.*/
SELECT TO_DATE(data_min, 'DD/MM/YYYY') + ROWNUM -1
FROM (SELECT MIN(concert_date) data_min 
      FROM concerts_lco)
CROSS JOIN (SELECT MAX(concert_date) data_max 
            FROM concerts_lco) aux
CONNECT BY ROWNUM < TO_DATE(data_max, 'DD/MM/YYYY') - TO_DATE(data_min, 'DD/MM/YYYY') + 1;





/*3. Sa se afiseze subalternii liderului trupei care are pretul cel mai mare la un concert*/
SELECT  LPAD (last_name || ' ' || first_name , LEVEL - 1 + LENGTH(last_name || ' ' || first_name)) as "Nume", instrument
FROM musicians_lco m
START WITH musician_id = (SELECT musician_id
                          FROM musicians_lco
                          WHERE band_id IN (SELECT band_id
                                            FROM bands_lco
                                            JOIN concerts_lco USING (band_id)
                                            WHERE price = (SELECT MAX(price)
                                                           FROM concerts_lco))
                         AND leader is NULL) 
CONNECT BY PRIOR musician_id = leader;



/*15.	S? se afi?eze informa?ii despre to?i clien?ii care au cump?rat bilete la toate concertele lunii februarie 2021.*/

SELECT DISTINCT c.*
FROM buy_lco b
JOIN clients_lco c ON (b.cnp = c.cnp)
WHERE NOT EXISTS (SELECT 1
                  FROM concerts_lco c1
                  WHERE TO_CHAR(concert_date, 'MM/YYYY') = '02/2021'
                  AND NOT EXISTS (SELECT 1
                                  FROM buy_lco
                                  WHERE c1.concert_id = concert_id AND c.cnp = cnp));




/*5.	S? se afi?eze numele ?i prenumele tuturor persoanelor care au cel pu?in acelea?i bilete ca Suhan Magda.*/
SELECT last_name, first_name
FROM clients_lco c
WHERE NOT EXISTS (SELECT concert_id
                  FROM buy_lco
                  JOIN clients_lco USING(cnp)
                  WHERE INITCAP(last_name) = 'Suhan' AND INITCAP(first_name) = 'Magda'
                  MINUS
                  SELECT concert_id
                  FROM buy_lco
                  WHERE c.cnp = cnp)
AND INITCAP(last_name) <> 'Suhan' AND INITCAP(first_name) <> 'Magda';



/*6.	S? se afi?eze detalii despre arti?tii care au concerte în 2020 ?i care mai au cel pu?in un coleg în trup?.*/
SELECT m.* 
FROM musicians_lco m
JOIN bands_lco b ON (b.band_id = m.band_id)
JOIN concerts_lco c ON (c.band_id = b.band_id)
WHERE EXTRACT(YEAR FROM concert_date) = '2020'
INTERSECT
SELECT *
FROM musicians_lco m
WHERE EXISTS (SELECT 1 
              FROM musicians_lco
              WHERE m.band_id = band_id
              AND m.musician_id <> musician_id);
              
              
/*11. S? se afi?eze concertele care au loc între data curent? si 01/01/2023, împreuna cu loca?ia lor ?i numele trupei. Se vor afi?a atât concertele f?r? loca?ie, cât ?i loca?iile f?r? concerte.*/
SELECT 'Concertul cu id-ul ' ||  DECODE(concert_id, NULL, 'fara id', concert_id)
       || DECODE(TO_CHAR(concert_date, 'DD/MM/YYYY'), NULL, ' fara data', ' de pe ' || TO_CHAR(concert_date, 'DD/MM/YYYY')) || 
       DECODE(band_id, NULL, ' fara trupa ', CONCAT(' cu trupa ', band_id))|| 
       DECODE(location_id, NULL, ' nu are stabilita locatia', ' are loc in ' || location_name)
FROM concerts_lco
FULL JOIN locations_lco USING (location_id)
WHERE TO_DATE(concert_date, 'DD/MM/YYYY') BETWEEN TO_DATE(sysdate, 'DD/MM/YYYY') AND TO_DATE('01/01/2023', 'DD/MM/YYYY') 
      OR concert_date IS NULL;




/*13.	S? se afi?eze numele locatiei, numele trupei, numele clien?ilor concertului, num?rul clien?ilor in formatul "Nume P", al?turi de tipul cânt?re?ilor forma?iei(instrument, vocal etc.). 
Se vor afi?a ?i concertele care nu au clien?i ?i biletele care nu au trecut cnp-ul clientului.*/

SELECT location_name, band_name, c.last_name || ' ' || SUBSTR(c.first_name, 1, 1), numar_bilete, instrument
FROM concerts_lco co
LEFT JOIN buy_lco b ON(b.concert_id = co.concert_id)
LEFT JOIN clients_lco c ON(b.cnp = c.cnp)
JOIN locations_lco loc ON(loc.location_id = co.location_id)
JOIN bands_lco ba ON(ba.band_id = co.band_id)
JOIN musicians_lco m ON(m.band_id = ba.band_id)
JOIN (SELECT concert_id, COUNT(ticket_id) numar_bilete
FROM concerts_lco
LEFT JOIN buy_lco USING(concert_id)
GROUP BY concert_id) aux ON (co.concert_id = aux.concert_id);


/*10.	S? se afi?eze, pentru arti?tii care au lungimea prenumelui egal? cu lungimea numelui - 2, pre?ul mediu al biletelor cump?rate la concertele lor ?i num?rul loca?iilor concertelor.*/
SELECT last_name, first_name, 
NVL(TO_CHAR(leader), CONCAT(SUBSTR(last_name,1,1), CONCAT(SUBSTR(first_name,1,1),'. lider'))) lider,
(SELECT ROUND(AVG(price),2)
FROM concerts_lco 
JOIN buy_lco USING(concert_id)
JOIN bands_lco USING(band_id)
JOIN musicians_lco USING(band_id)
WHERE musician_id = m.musician_id
GROUP BY band_id) pret_mediu,

(SELECT COUNT(NVL(location_id,0))
FROM concerts_lco 
JOIN buy_lco USING(concert_id)
JOIN bands_lco USING(band_id)
JOIN musicians_lco USING(band_id)
JOIN locations_lco USING(location_id)
WHERE musician_id = m.musician_id
GROUP BY band_id) numar_locatii
FROM musicians_lco m
WHERE NULLIF(LENGTH(last_name) - 2, LENGTH(first_name)) IS NULL; 
