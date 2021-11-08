
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